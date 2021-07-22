/*
 * m1750-coff-load
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute, 
 * and license this software and its documentation for any purpose, 
 * provided that existing copyright notices are retained in all copies 
 * and that this notice is included verbatim in any distributions. No 
 * written agreement, license, or royalty fee is required for any of the 
 * authorized uses. Modifications to this software may be copyrighted by 
 * their authors and need not follow the licensing terms described here, 
 * provided that the new terms are clearly indicated on the first page 
 * of each file where they apply. 
 *
 * $Log: $
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "bfd.h"


/*
 * Output Format:
 * The output format is Intel Hex with word addresses.
 * 
 * This is what Intel Hex files look like:
 * 
 * 1. INTEL FORMATS
 * 
 * A. Intel 1
 * 
 *    16-bit address-field format, for files 64k bytes in length or less.
 * 
 *    DATA RECORD
 *    Byte 1       Header = colon(:)
 *    2..3         The number of data bytes in hex notation
 *    4..5         High byte of the record load address
 *    6..7         Low byte of the record load address
 *    8..9         Record type, must be "00"
 *    10..x        Data bytes in hex notation:
 *         x = (number of bytes - 1) * 2 + 11
 *    x+1..x+2     Checksum in hex notation
 *    x+3..x+4     Carriage return, line feed
 * 
 *    END RECORD
 *    Byte 1       Header = colon (:)
 *    2..3         The byte count, must be "00"
 *    4..7         Transfer-address (usually "0000")
 *                 the jump-to address, execution start address
 *    8..9         Record type, must be "01"
 *    10..11       Checksum, in hex notation
 *    12..13       Carriage return, line feed
 * 
 * B. INTEL 2
 * 
 *    MCS-86 format, using a 20-bit address for files larger than 64K bytes.
 * 
 *    DATA RECORD
 *    Byte 1       Header = colon (:)
 *    2..3         The byte count of this record, hex notation
 *    4..5         High byte of the record load address
 *    6..7         Low byte of the record load address
 *    8..9         Record type, must be "00"
 *    10..x        The data bytes in hex notation:
 *         x = (number of data bytes - 1) * 2 + 11
 *    x+1..x+2     Checksum in hex notation
 *    x+3..x+4     Carriage return, line feed
 * 
 *    EXTENDED ADDRESS RECORD
 *    Byte 1       Header = colon(:)
 *    2..3         The byte count, must be "02"
 *    4..7         Load address, must be "0000"
 *    8..9         Record type, must be "02"
 *    10..11       High byte of the offset address
 *    12..13       Low byte of the offset address
 *    14..15       Checksum in hex notation
 *    16..17       Carriage return, line feed
 * 
 *    The checksums are the two's complement of the 8-bit sum
 *    without carry of the byte count, offset address, and the
 *    record type.
 * 
 *    START ADDRESS RECORD
 *    Byte 1       Header = colon (:)
 *    2..3         The byte count, must be "04"
 *    4..7         Load address, must be "0000"
 *    8..9         Record type, must be "03"
 *    10..13       8086 CS value
 *    14..17       8086 IP value
 *    18..19       Checksum in hex notation
 *    20..21       Carriage return, line feed
 */

/* 
 * The number of bytes we put on one line during output.
 */
#define CHUNK (32)

/*
 * Input/Output stuff
 */
FILE *outfile;

/*
 * Record types
 */
#define data_record (0)
#define end_record (1)
#define extended_address_record (2)
#define start_address_record (3)
#define eof_record (-1)


static int
write_record (int count, unsigned long addr, unsigned int type, unsigned char *data)
{
  static const char digs[] = "0123456789ABCDEF";
  char buf[9 + CHUNK * 2 + 4 + 1];
  char *p;
  unsigned int chksum;
  unsigned int i;

#define TOHEX(buf, v) \
  ((buf)[0] = digs[((v) >> 4) & 0xf], (buf)[1] = digs[(v) & 0xf])

  buf[0] = ':';
  TOHEX (buf + 1, count);
  TOHEX (buf + 3, (addr >> 8) & 0xff);
  TOHEX (buf + 5, addr & 0xff);
  TOHEX (buf + 7, type);

  chksum = count + addr + (addr >> 8) + type;

  for (i = 0, p = buf + 9; i < count; i++, p += 2, data++)
    {
      TOHEX (p, *data);
      chksum += *data;
    }

  TOHEX (p, (-chksum) & 0xff);
  p[2] = '\r';
  p[3] = '\n';
  p[4] = '\0';

  fputs (buf, outfile);
}


void
write_block (int col, bfd_vma vma, unsigned char *buffer, size_t size)
{
  /*
   * Write out a contiguous block of data in as Intel hex records.
   * The first record is an extended adddress record, and the second
   * record contains the first byte of data, at the lowest address.
   * The remaining bytes of data follow, and the address increments
   * by one for each byte. Note bytes after the first will not be
   * at the address they were at in the source file.
   */
  const int width = 2;		/* width of word in columns */
  const int bits = 8;
  unsigned char addr[2];
  unsigned long segbase;
  int cnt;
  int in_offset = 0;
  int out_offset = 0;
  unsigned char obuf[32];

  /* Workaround for ERA Monitor bug.  */
  addr[0] = 0x00;
  addr[1] = 0x00;
  write_record (2, 0, extended_address_record, addr);

  /* Now write the offset/segment base record.  */
  segbase = vma & 0x01fe0000;

  addr[0] = (segbase >> 13) & 0xff;
  addr[1] = (segbase >> 5) & 0xff;
  write_record (2, 0, extended_address_record, addr);

  cnt = size;
  while (cnt > 0)
    {
      int i;
      int j = 0;
      int lcnt = (cnt > CHUNK * width ? CHUNK * width : cnt);
      int out_start = out_offset;

      for (i = 0; i < lcnt; i++)
	if ((i % width) == col)
	  {
	    obuf[j++] = buffer[in_offset + i];
	    out_offset++;
	  }

      write_record (j, ((vma - segbase) >> 1) + out_start, data_record, obuf);

      in_offset += lcnt;
      cnt -= lcnt;
    }
}


/* Version number of GDB, as a string.  */

extern char *version;

/* Canonical host name as a string. */

extern char *host_name;

/* Canonical target name as a string. */

extern char *target_name;


void
print_run_version (stream)
     FILE *stream;
{
  fprintf (stream, "%s-load\n", target_name);
  fprintf (stream, "\
GDB %s (%s", version, host_name);

  fprintf (stream, " --target %s", target_name);

  fprintf (stream, "),\n");
  fprintf (stream, "Copyright 1997 Chris Nettleton Software.\n");
}


void
usage ()
{
  fprintf (stderr, "usage: load [-v] program > /dev/ttyb\n");
  exit (1);
}


extern int optind;

int
main (int argc, char *argv[])
{
  bfd *abfd;
  int i;

  while ((i = getopt (argc, argv, "v")) != EOF)
    switch (i)
      {
      case 'v':
	print_run_version (stdout);
	break;
      default:
	usage ();
      }
  argc -= optind;
  argv += optind;

  outfile = stdout;

  while (argc--)
    {
      char *name = *argv++;

      abfd = bfd_openr (name, "coff-m1750");

      if (!abfd)
	{
	  perror (name);
	  exit (1);
	}
      else
	{
	  if (bfd_check_format (abfd, bfd_object))
	    {
	      char buf[2];
	      asection *s;
	      bfd_vma start_address = bfd_get_start_address (abfd); 

	      /* Load the low order bytes */
	      for (s = abfd->sections; s; s = s->next)
		{
		  if (strcmp (s->name, ".bss") != 0)
		    {
		      char *buffer = (char *) malloc (bfd_section_size (abfd, s));
		      bfd_get_section_contents (abfd, s, buffer, 0, bfd_section_size (abfd, s));
		      write_block (1, s->vma, buffer, bfd_section_size (abfd, s));
		    }
		}
	      write_record (0, start_address >> 1, end_record, NULL);

	      sleep (1);

	      /* Load the high order bytes */
	      for (s = abfd->sections; s; s = s->next)
		{
		  if (strcmp (s->name, ".bss") != 0)
		    {
		      char *buffer = (char *) malloc (bfd_section_size (abfd, s));
		      bfd_get_section_contents (abfd, s, buffer, 0, bfd_section_size (abfd, s));
		      write_block (0, s->vma, buffer, bfd_section_size (abfd, s));
		    }
		}
	      write_record (0, start_address >> 1, end_record, NULL);

	    }
	}
    }

  exit (0);
}
