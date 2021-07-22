/* run front end support for SIM1750

   Copyright (C) 1987, 1992 Free Software Foundation, Inc.

   This file is part of SIM1750

   SIM1750 is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   SIM1750 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with SIM1750; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include <stdio.h>
#include "bfd.h"

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
  fprintf (stream, "\
GDB %s (%s", version, host_name);

  fprintf (stream, " --target %s", target_name);

  fprintf (stream, "),\n");
  fprintf (stream, "Copyright 1996 Free Software Foundation, Inc.\n");
}


void
usage ()
{
  fprintf (stderr, "usage: run [-v] program\n");
  exit (1);
}


extern int optind;

int
main (int argc, char *argv[])
{
  bfd *abfd;
  int i;
  int verbose = 0;

  while ((i = getopt (argc, argv, "v")) != EOF)
    switch (i)
      {
      case 'v':
	verbose = 1;
	break;
      default:
	usage ();
      }
  argc -= optind;
  argv += optind;

  if (verbose)
    print_run_version (stdout);

  while (argc--)
    {
      char *name = *argv++;

      sim_open ("");

      abfd = bfd_openr (name, "coff-m1750");

      if (!abfd)
	{
	  perror (name);
	  exit (1);
	}
      else
	{
	  if (verbose)
	    {
	      printf ("%s-run %s\n", target_name, name);
	    }

	  if (bfd_check_format (abfd, bfd_object))
	    {
	      char buf[2];
	      asection *s;
	      bfd_vma start_address;

	      /* Load the program */
	      for (s = abfd->sections; s; s = s->next)
		{
		  char *buffer = (char *) malloc (bfd_section_size (abfd, s));
		  bfd_get_section_contents (abfd, s, buffer, 0, bfd_section_size (abfd, s));
		  sim_write (s->vma, buffer, bfd_section_size (abfd, s));
		}

	      start_address = bfd_get_start_address (abfd);
	      sim_create_inferior (start_address, NULL, NULL);

	      /* single step the first instruction */
	      sim_resume (1, 0);

	      /* Overwrite the first instruction with a breakpoint, so
	         that if the program restarts the run command terminates. */
	      buf[0] = 0xff;
	      buf[1] = 0xff;

	      sim_write (start_address, buf, 2);

	      /* Now run the program until it restarts or gets an unhandled
	         exception. */
	      sim_resume (0, 0);

	      /* Report instruction counts etc. */
	      if (verbose)
		sim_info (0);
	    }
	}
    }

  exit (0);
}
