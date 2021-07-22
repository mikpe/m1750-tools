/* ELF object file format
   Copyright (C) 1992, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2,
   or (at your option) any later version.

   GAS is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#define OBJ_HEADER "obj-elf.h"
#include "as.h"
#include "subsegs.h"
#include "obstack.h"

#ifndef ECOFF_DEBUGGING
#define ECOFF_DEBUGGING 0
#else
#define NEED_ECOFF_DEBUG
#endif

#ifdef NEED_ECOFF_DEBUG
#include "ecoff.h"
#endif

#ifdef TC_MIPS
#include "elf/mips.h"
#endif

#ifdef TC_PPC
#include "elf/ppc.h"
#endif

#ifdef NEED_ECOFF_DEBUG
static boolean elf_get_extr PARAMS ((asymbol *, EXTR *));
static void elf_set_index PARAMS ((asymbol *, bfd_size_type));
#endif

static void obj_elf_line PARAMS ((int));
void obj_elf_version PARAMS ((int));
static void obj_elf_size PARAMS ((int));
static void obj_elf_type PARAMS ((int));
static void obj_elf_ident PARAMS ((int));
static void obj_elf_weak PARAMS ((int));
static void obj_elf_local PARAMS ((int));
static void obj_elf_common PARAMS ((int));
static void obj_elf_data PARAMS ((int));
static void obj_elf_text PARAMS ((int));

static const pseudo_typeS elf_pseudo_table[] =
{
  {"comm", obj_elf_common, 0},
  {"ident", obj_elf_ident, 0},
  {"local", obj_elf_local, 0},
  {"previous", obj_elf_previous, 0},
  {"section", obj_elf_section, 0},
  {"section.s", obj_elf_section, 0},
  {"sect", obj_elf_section, 0},
  {"sect.s", obj_elf_section, 0},
  {"size", obj_elf_size, 0},
  {"type", obj_elf_type, 0},
  {"version", obj_elf_version, 0},
  {"weak", obj_elf_weak, 0},

/* These are used for stabs-in-elf configurations.  */
  {"line", obj_elf_line, 0},

  /* These are used for dwarf. */
  {"2byte", cons, 2},
  {"4byte", cons, 4},
  {"8byte", cons, 8},

  /* We need to trap the section changing calls to handle .previous.  */
  {"data", obj_elf_data, 0},
  {"text", obj_elf_text, 0},

  /* End sentinel.  */
  {NULL},
};

static const pseudo_typeS ecoff_debug_pseudo_table[] =
{
#ifdef NEED_ECOFF_DEBUG
  /* COFF style debugging information for ECOFF. .ln is not used; .loc
     is used instead.  */
  { "def",	ecoff_directive_def,	0 },
  { "dim",	ecoff_directive_dim,	0 },
  { "endef",	ecoff_directive_endef,	0 },
  { "file",	ecoff_directive_file,	0 },
  { "scl",	ecoff_directive_scl,	0 },
  { "tag",	ecoff_directive_tag,	0 },
  { "val",	ecoff_directive_val,	0 },

  /* COFF debugging requires pseudo-ops .size and .type, but ELF
     already has meanings for those.  We use .esize and .etype
     instead.  These are only generated by gcc anyhow.  */
  { "esize",	ecoff_directive_size,	0 },
  { "etype",	ecoff_directive_type,	0 },

  /* ECOFF specific debugging information.  */
  { "begin",	ecoff_directive_begin,	0 },
  { "bend",	ecoff_directive_bend,	0 },
  { "end",	ecoff_directive_end,	0 },
  { "ent",	ecoff_directive_ent,	0 },
  { "fmask",	ecoff_directive_fmask,	0 },
  { "frame",	ecoff_directive_frame,	0 },
  { "loc",	ecoff_directive_loc,	0 },
  { "mask",	ecoff_directive_mask,	0 },

  /* Other ECOFF directives.  */
  { "extern",	ecoff_directive_extern,	0 },

  /* These are used on Irix.  I don't know how to implement them.  */
  { "alias",	s_ignore,		0 },
  { "bgnb",	s_ignore,		0 },
  { "endb",	s_ignore,		0 },
  { "lab",	s_ignore,		0 },
  { "noalias",	s_ignore,		0 },
  { "verstamp",	s_ignore,		0 },
  { "vreg",	s_ignore,		0 },
#endif

  {NULL}			/* end sentinel */
};

#undef NO_RELOC
#include "aout/aout64.h"

void
elf_pop_insert ()
{
  pop_insert (elf_pseudo_table);
  if (ECOFF_DEBUGGING)
    pop_insert (ecoff_debug_pseudo_table);
}

static bfd_vma
elf_s_get_size (sym)
     symbolS *sym;
{
  return S_GET_SIZE (sym);
}

static void
elf_s_set_size (sym, sz)
     symbolS *sym;
     bfd_vma sz;
{
  S_SET_SIZE (sym, sz);
}

static bfd_vma
elf_s_get_align (sym)
     symbolS *sym;
{
  return S_GET_ALIGN (sym);
}

static void
elf_s_set_align (sym, align)
     symbolS *sym;
     bfd_vma align;
{
  S_SET_ALIGN (sym, align);
}

static void
elf_copy_symbol_attributes (dest, src)
     symbolS *dest, *src;
{
  OBJ_COPY_SYMBOL_ATTRIBUTES (dest, src);
}

static int
elf_sec_sym_ok_for_reloc (sec)
     asection *sec;
{
  return obj_sec_sym_ok_for_reloc (sec);
}

void
elf_file_symbol (s)
     char *s;
{
  symbolS *sym;

  sym = symbol_new (s, absolute_section, (valueT) 0, (struct frag *) 0);
  sym->sy_frag = &zero_address_frag;
  sym->bsym->flags |= BSF_FILE;

  if (symbol_rootP != sym)
    {
      symbol_remove (sym, &symbol_rootP, &symbol_lastP);
      symbol_insert (sym, symbol_rootP, &symbol_rootP, &symbol_lastP);
#ifdef DEBUG
      verify_symbol_chain (symbol_rootP, symbol_lastP);
#endif
    }
}

static void
obj_elf_common (ignore)
     int ignore;
{
  char *name;
  char c;
  char *p;
  int temp, size;
  symbolS *symbolP;
  int have_align;

  name = input_line_pointer;
  c = get_symbol_end ();
  /* just after name is now '\0' */
  p = input_line_pointer;
  *p = c;
  SKIP_WHITESPACE ();
  if (*input_line_pointer != ',')
    {
      as_bad ("Expected comma after symbol-name");
      ignore_rest_of_line ();
      return;
    }
  input_line_pointer++;		/* skip ',' */
  if ((temp = get_absolute_expression ()) < 0)
    {
      as_bad (".COMMon length (%d.) <0! Ignored.", temp);
      ignore_rest_of_line ();
      return;
    }
  size = temp;
  *p = 0;
  symbolP = symbol_find_or_make (name);
  *p = c;
  if (S_IS_DEFINED (symbolP))
    {
      as_bad ("Ignoring attempt to re-define symbol");
      ignore_rest_of_line ();
      return;
    }
  if (S_GET_VALUE (symbolP) != 0)
    {
      if (S_GET_VALUE (symbolP) != size)
	{
	  as_warn ("Length of .comm \"%s\" is already %ld. Not changed to %d.",
		   S_GET_NAME (symbolP), (long) S_GET_VALUE (symbolP), size);
	}
    }
  know (symbolP->sy_frag == &zero_address_frag);
  if (*input_line_pointer != ',')
    have_align = 0;
  else
    {
      have_align = 1;
      input_line_pointer++;
      SKIP_WHITESPACE ();
    }
  if (! have_align || *input_line_pointer != '"')
    {
      if (! have_align)
	temp = 0;
      else
	{
	  temp = get_absolute_expression ();
	  if (temp < 0)
	    {
	      temp = 0;
	      as_warn ("Common alignment negative; 0 assumed");
	    }
	}
      if (symbolP->local)
	{
	  segT old_sec;
	  int old_subsec;
	  char *pfrag;
	  int align;

	/* allocate_bss: */
	  old_sec = now_seg;
	  old_subsec = now_subseg;
	  if (temp)
	    {
	      /* convert to a power of 2 alignment */
	      for (align = 0; (temp & 1) == 0; temp >>= 1, ++align);
	      if (temp != 1)
		{
		  as_bad ("Common alignment not a power of 2");
		  ignore_rest_of_line ();
		  return;
		}
	    }
	  else
	    align = 0;
	  record_alignment (bss_section, align);
	  subseg_set (bss_section, 0);
	  if (align)
	    frag_align (align, 0);
	  if (S_GET_SEGMENT (symbolP) == bss_section)
	    symbolP->sy_frag->fr_symbol = 0;
	  symbolP->sy_frag = frag_now;
	  pfrag = frag_var (rs_org, 1, 1, (relax_substateT) 0, symbolP, size,
			    (char *) 0);
	  *pfrag = 0;
	  S_SET_SIZE (symbolP, size);
	  S_SET_SEGMENT (symbolP, bss_section);
	  S_CLEAR_EXTERNAL (symbolP);
	  subseg_set (old_sec, old_subsec);
	}
      else
	{
	allocate_common:
	  S_SET_VALUE (symbolP, (valueT) size);
	  S_SET_ALIGN (symbolP, temp);
	  S_SET_EXTERNAL (symbolP);
	  /* should be common, but this is how gas does it for now */
	  S_SET_SEGMENT (symbolP, bfd_und_section_ptr);
	}
    }
  else
    {
      input_line_pointer++;
      /* @@ Some use the dot, some don't.  Can we get some consistency??  */
      if (*input_line_pointer == '.')
	input_line_pointer++;
      /* @@ Some say data, some say bss.  */
      if (strncmp (input_line_pointer, "bss\"", 4)
	  && strncmp (input_line_pointer, "data\"", 5))
	{
	  while (*--input_line_pointer != '"')
	    ;
	  input_line_pointer--;
	  goto bad_common_segment;
	}
      while (*input_line_pointer++ != '"')
	;
      goto allocate_common;
    }
  demand_empty_rest_of_line ();
  return;

  {
  bad_common_segment:
    p = input_line_pointer;
    while (*p && *p != '\n')
      p++;
    c = *p;
    *p = '\0';
    as_bad ("bad .common segment %s", input_line_pointer + 1);
    *p = c;
    input_line_pointer = p;
    ignore_rest_of_line ();
    return;
  }
}

static void 
obj_elf_local (ignore)
     int ignore;
{
  char *name;
  int c;
  symbolS *symbolP;

  do
    {
      name = input_line_pointer;
      c = get_symbol_end ();
      symbolP = symbol_find_or_make (name);
      *input_line_pointer = c;
      SKIP_WHITESPACE ();
      S_CLEAR_EXTERNAL (symbolP);
      symbolP->local = 1;
      if (c == ',')
	{
	  input_line_pointer++;
	  SKIP_WHITESPACE ();
	  if (*input_line_pointer == '\n')
	    c = '\n';
	}
    }
  while (c == ',');
  demand_empty_rest_of_line ();
}

static void 
obj_elf_weak (ignore)
     int ignore;
{
  char *name;
  int c;
  symbolS *symbolP;

  do
    {
      name = input_line_pointer;
      c = get_symbol_end ();
      symbolP = symbol_find_or_make (name);
      *input_line_pointer = c;
      SKIP_WHITESPACE ();
      S_SET_WEAK (symbolP);
      symbolP->local = 1;
      if (c == ',')
	{
	  input_line_pointer++;
	  SKIP_WHITESPACE ();
	  if (*input_line_pointer == '\n')
	    c = '\n';
	}
    }
  while (c == ',');
  demand_empty_rest_of_line ();
}

static segT previous_section;
static int previous_subsection;

/* Handle the .section pseudo-op.  This code supports two different
   syntaxes.  

   The first is found on Solaris, and looks like
       .section ".sec1",#alloc,#execinstr,#write
   Here the names after '#' are the SHF_* flags to turn on for the
   section.  I'm not sure how it determines the SHT_* type (BFD
   doesn't really give us control over the type, anyhow).

   The second format is found on UnixWare, and probably most SVR4
   machines, and looks like
       .section .sec1,"a",@progbits
   The quoted string may contain any combination of a, w, x, and
   represents the SHF_* flags to turn on for the section.  The string
   beginning with '@' can be progbits or nobits.  There should be
   other possibilities, but I don't know what they are.  In any case,
   BFD doesn't really let us set the section type.  */

/* Certain named sections have particular defined types, listed on p.
   4-19 of the ABI.  */
struct special_section
{
  const char *name;
  int type;
  int attributes;
};

static struct special_section special_sections[] =
{
  { ".bss",	SHT_NOBITS,	SHF_ALLOC + SHF_WRITE		},
  { ".comment",	SHT_PROGBITS,	0				},
  { ".data",	SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE		},
  { ".data1",	SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE		},
  { ".debug",	SHT_PROGBITS,	0				},
  { ".fini",	SHT_PROGBITS,	SHF_ALLOC + SHF_EXECINSTR	},
  { ".init",	SHT_PROGBITS,	SHF_ALLOC + SHF_EXECINSTR	},
  { ".line",	SHT_PROGBITS,	0				},
  { ".note",	SHT_NOTE,	0				},
  { ".rodata",	SHT_PROGBITS,	SHF_ALLOC			},
  { ".rodata1",	SHT_PROGBITS,	SHF_ALLOC			},
  { ".text",	SHT_PROGBITS,	SHF_ALLOC + SHF_EXECINSTR	},

#ifdef ELF_TC_SPECIAL_SECTIONS
  ELF_TC_SPECIAL_SECTIONS
#endif

#if 0
  /* The following section names are special, but they can not
     reasonably appear in assembler code.  Some of the attributes are
     processor dependent.  */
  { ".dynamic",	SHT_DYNAMIC,	SHF_ALLOC /* + SHF_WRITE */ 	},
  { ".dynstr",	SHT_STRTAB,	SHF_ALLOC			},
  { ".dynsym",	SHT_DYNSYM,	SHF_ALLOC			},
  { ".got",	SHT_PROGBITS,	0				},
  { ".hash",	SHT_HASH,	SHF_ALLOC			},
  { ".interp",	SHT_PROGBITS,	/* SHF_ALLOC */			},
  { ".plt",	SHT_PROGBITS,	0				},
  { ".shstrtab",SHT_STRTAB,	0				},
  { ".strtab",	SHT_STRTAB,	/* SHF_ALLOC */			},
  { ".symtab",	SHT_SYMTAB,	/* SHF_ALLOC */			},
#endif

  { NULL,	0,		0				}
};

void
obj_elf_section (xxx)
     int xxx;
{
  char *string;
  int new_sec;
  segT sec;
  int type, attr;
  int i;
  flagword flags;

#ifdef md_flush_pending_output
  md_flush_pending_output ();
#endif

  if (flag_mri)
    {
      char mri_type;

      previous_section = now_seg;
      previous_subsection = now_subseg;

      s_mri_sect (&mri_type);

#ifdef md_elf_section_change_hook
      md_elf_section_change_hook ();
#endif

      return;
    }

  /* Get name of section.  */
  SKIP_WHITESPACE ();
  if (*input_line_pointer == '"')
    {
      string = demand_copy_C_string (&xxx);
      if (string == NULL)
	{
	  ignore_rest_of_line ();
	  return;
	}
    }
  else
    {
      char *p = input_line_pointer;
      char c;
      while (0 == strchr ("\n\t,; ", *p))
	p++;
      if (p == input_line_pointer)
	{
	  as_warn ("Missing section name");
	  ignore_rest_of_line ();
	  return;
	}
      c = *p;
      *p = 0;
      string = xmalloc ((unsigned long) (p - input_line_pointer + 1));
      strcpy (string, input_line_pointer);
      *p = c;
      input_line_pointer = p;
    }

  /* Switch to the section, creating it if necessary.  */
  previous_section = now_seg;
  previous_subsection = now_subseg;

  new_sec = bfd_get_section_by_name (stdoutput, string) == NULL;
  sec = subseg_new (string, 0);

  /* If this section already existed, we don't bother to change the
     flag values.  */
  if (! new_sec)
    {
      while (! is_end_of_line[(unsigned char) *input_line_pointer])
	++input_line_pointer;
      ++input_line_pointer;

#ifdef md_elf_section_change_hook
      md_elf_section_change_hook ();
#endif

      return;
    }

  SKIP_WHITESPACE ();

  type = SHT_NULL;
  attr = 0;

  if (*input_line_pointer == ',')
    {
      /* Skip the comma.  */
      ++input_line_pointer;

      SKIP_WHITESPACE ();
      if (*input_line_pointer == '"')
	{
	  /* Pick up a string with a combination of a, w, x.  */
	  ++input_line_pointer;
	  while (*input_line_pointer != '"')
	    {
	      switch (*input_line_pointer)
		{
		case 'a':
		  attr |= SHF_ALLOC;
		  break;
		case 'w':
		  attr |= SHF_WRITE;
		  break;
		case 'x':
		  attr |= SHF_EXECINSTR;
		  break;
		default:
		  {
		    char *bad_msg = "Bad .section directive: want a,w,x in string";
#ifdef md_elf_section_letter
		    int md_attr = md_elf_section_letter (*input_line_pointer, &bad_msg);
		    if (md_attr)
		      attr |= md_attr;
		    else
#endif
		      {
			as_warn (bad_msg);
			ignore_rest_of_line ();
			return;
		      }
		  }
		}
	      ++input_line_pointer;
	    }

	  /* Skip the closing quote.  */
	  ++input_line_pointer;

	  SKIP_WHITESPACE ();
	  if (*input_line_pointer == ',')
	    {
	      ++input_line_pointer;
	      SKIP_WHITESPACE ();
	      if (*input_line_pointer == '@')
		{
		  ++input_line_pointer;
		  if (strncmp (input_line_pointer, "progbits",
			       sizeof "progbits" - 1) == 0)
		    {
		      type = SHT_PROGBITS;
		      input_line_pointer += sizeof "progbits" - 1;
		    }
		  else if (strncmp (input_line_pointer, "nobits",
				    sizeof "nobits" - 1) == 0)
		    {
		      type = SHT_NOBITS;
		      input_line_pointer += sizeof "nobits" - 1;
		    }
		  else
		    {
#ifdef md_elf_section_type
		    int md_type = md_elf_section_type (&input_line_pointer);
		    if (md_type)
		      type = md_type;
		    else
#endif
		      {
			as_warn ("Unrecognized section type");
			ignore_rest_of_line ();
		      }
		    }
		}
	    }
	}
      else
	{
	  do
	    {
	      SKIP_WHITESPACE ();
	      if (*input_line_pointer != '#')
		{
		  as_warn ("Bad .section directive");
		  ignore_rest_of_line ();
		  return;
		}
	      ++input_line_pointer;
	      if (strncmp (input_line_pointer, "write",
			   sizeof "write" - 1) == 0)
		{
		  attr |= SHF_WRITE;
		  input_line_pointer += sizeof "write" - 1;
		}
	      else if (strncmp (input_line_pointer, "alloc",
				sizeof "alloc" - 1) == 0)
		{
		  attr |= SHF_ALLOC;
		  input_line_pointer += sizeof "alloc" - 1;
		}
	      else if (strncmp (input_line_pointer, "execinstr",
				sizeof "execinstr" - 1) == 0)
		{
		  attr |= SHF_EXECINSTR;
		  input_line_pointer += sizeof "execinstr" - 1;
		}
	      else
		{
#ifdef md_elf_section_word
		  int md_attr = md_elf_section_word (&input_line_pointer);
		  if (md_attr)
		    attr |= md_attr;
		  else
#endif
		    {
		      as_warn ("Unrecognized section attribute");
		      ignore_rest_of_line ();
		      return;
		    }
		}
	      SKIP_WHITESPACE ();
	    }
	  while (*input_line_pointer++ == ',');
	  --input_line_pointer;
	}
    }

  /* See if this is one of the special sections.  */
  for (i = 0; special_sections[i].name != NULL; i++)
    {
      if (string[1] == special_sections[i].name[1]
	  && strcmp (string, special_sections[i].name) == 0)
	{
	  if (type == SHT_NULL)
	    type = special_sections[i].type;
	  else if (type != special_sections[i].type)
	    as_warn ("Setting incorrect section type for %s", string);

	  if ((attr &~ special_sections[i].attributes) != 0)
	    as_warn ("Setting incorrect section attributes for %s", string);
	  attr |= special_sections[i].attributes;

	  break;
	}
    }

  flags = (SEC_RELOC
	   | ((attr & SHF_WRITE) ? 0 : SEC_READONLY)
	   | ((attr & SHF_ALLOC) ? SEC_ALLOC : 0)
	   | (((attr & SHF_ALLOC) && type != SHT_NOBITS) ? SEC_LOAD : 0)
	   | ((attr & SHF_EXECINSTR) ? SEC_CODE : 0));
  if (special_sections[i].name == NULL)
    {
      if (type == SHT_PROGBITS)
	flags |= SEC_ALLOC | SEC_LOAD;
      else if (type == SHT_NOBITS)
	{
	  flags |= SEC_ALLOC;
	  flags &=~ SEC_LOAD;
	}

#ifdef md_elf_section_flags
      flags = md_elf_section_flags (flags, attr, type);
#endif
    }

  bfd_set_section_flags (stdoutput, sec, flags);

#ifdef md_elf_section_change_hook
  md_elf_section_change_hook ();
#endif

  demand_empty_rest_of_line ();
}

/* Change to the .data section.  */

static void
obj_elf_data (i)
     int i;
{
  previous_section = now_seg;
  previous_subsection = now_subseg;
  s_data (i);
}

/* Change to the .text section.  */

static void
obj_elf_text (i)
     int i;
{
  previous_section = now_seg;
  previous_subsection = now_subseg;
  s_text (i);
}

void
obj_elf_previous (ignore)
     int ignore;
{
  if (previous_section == 0)
    {
      as_bad (".previous without corresponding .section; ignored");
      return;
    }
  subseg_set (previous_section, previous_subsection);
  previous_section = 0;
}

static void
obj_elf_line (ignore)
     int ignore;
{
  /* Assume delimiter is part of expression.  BSD4.2 as fails with
     delightful bug, so we are not being incompatible here. */
  new_logical_line ((char *) NULL, (int) (get_absolute_expression ()));
  demand_empty_rest_of_line ();
}

void 
obj_read_begin_hook ()
{
#ifdef NEED_ECOFF_DEBUG
  if (ECOFF_DEBUGGING)
    ecoff_read_begin_hook ();
#endif
}

void 
obj_symbol_new_hook (symbolP)
     symbolS *symbolP;
{
  symbolP->sy_obj = 0;

#ifdef NEED_ECOFF_DEBUG
  if (ECOFF_DEBUGGING)
    ecoff_symbol_new_hook (symbolP);
#endif
}

void 
obj_elf_version (ignore)
     int ignore;
{
  char *name;
  unsigned int c;
  char ch;
  char *p;
  asection *seg = now_seg;
  subsegT subseg = now_subseg;
  Elf_Internal_Note i_note;
  Elf_External_Note e_note;
  asection *note_secp = (asection *) NULL;
  int i, len;

  SKIP_WHITESPACE ();
  if (*input_line_pointer == '\"')
    {
      ++input_line_pointer;	/* -> 1st char of string. */
      name = input_line_pointer;

      while (is_a_char (c = next_char_of_string ()))
	;
      c = *input_line_pointer;
      *input_line_pointer = '\0';
      *(input_line_pointer - 1) = '\0';
      *input_line_pointer = c;

      /* create the .note section */

      note_secp = subseg_new (".note", 0);
      bfd_set_section_flags (stdoutput,
			     note_secp,
			     SEC_HAS_CONTENTS | SEC_READONLY);

      /* process the version string */

      len = strlen (name);

      i_note.namesz = ((len + 1) + 3) & ~3; /* round this to word boundary */
      i_note.descsz = 0;	/* no description */
      i_note.type = NT_VERSION;
      p = frag_more (sizeof (e_note.namesz));
      md_number_to_chars (p, (valueT) i_note.namesz, 4);
      p = frag_more (sizeof (e_note.descsz));
      md_number_to_chars (p, (valueT) i_note.descsz, 4);
      p = frag_more (sizeof (e_note.type));
      md_number_to_chars (p, (valueT) i_note.type, 4);

      for (i = 0; i < len; i++)
	{
	  ch = *(name + i);
	  {
	    FRAG_APPEND_1_CHAR (ch);
	  }
	}
      frag_align (2, 0);

      subseg_set (seg, subseg);
    }
  else
    {
      as_bad ("Expected quoted string");
    }
  demand_empty_rest_of_line ();
}

static void
obj_elf_size (ignore)
     int ignore;
{
  char *name = input_line_pointer;
  char c = get_symbol_end ();
  char *p;
  expressionS exp;
  symbolS *sym;

  p = input_line_pointer;
  *p = c;
  SKIP_WHITESPACE ();
  if (*input_line_pointer != ',')
    {
      *p = 0;
      as_bad ("expected comma after name `%s' in .size directive", name);
      *p = c;
      ignore_rest_of_line ();
      return;
    }
  input_line_pointer++;
  expression (&exp);
  if (exp.X_op == O_absent)
    {
      as_bad ("missing expression in .size directive");
      exp.X_op = O_constant;
      exp.X_add_number = 0;
    }
  *p = 0;
  sym = symbol_find_or_make (name);
  *p = c;
  if (exp.X_op == O_constant)
    S_SET_SIZE (sym, exp.X_add_number);
  else
    {
      sym->sy_obj = (expressionS *) xmalloc (sizeof (expressionS));
      *sym->sy_obj = exp;
    }
  demand_empty_rest_of_line ();
}

/* Handle the ELF .type pseudo-op.  This sets the type of a symbol.
   There are three syntaxes.  The first (used on Solaris) is
       .type SYM,#function
   The second (used on UnixWare) is
       .type SYM,@function
   The third (reportedly to be used on Irix 6.0) is
       .type SYM STT_FUNC
   */

static void
obj_elf_type (ignore)
     int ignore;
{
  char *name;
  char c;
  int type;
  const char *typename;
  symbolS *sym;

  name = input_line_pointer;
  c = get_symbol_end ();
  sym = symbol_find_or_make (name);
  *input_line_pointer = c;

  SKIP_WHITESPACE ();
  if (*input_line_pointer == ',')
    ++input_line_pointer;

  SKIP_WHITESPACE ();
  if (*input_line_pointer == '#' || *input_line_pointer == '@')
    ++input_line_pointer;

  typename = input_line_pointer;
  c = get_symbol_end ();

  type = 0;
  if (strcmp (typename, "function") == 0
      || strcmp (typename, "STT_FUNC") == 0)
    type = BSF_FUNCTION;
  else if (strcmp (typename, "object") == 0
	   || strcmp (typename, "STT_OBJECT") == 0)
    type = BSF_OBJECT;
  else
    as_bad ("ignoring unrecognized symbol type \"%s\"", typename);

  *input_line_pointer = c;

  sym->bsym->flags |= type;

  demand_empty_rest_of_line ();
}

static void
obj_elf_ident (ignore)
     int ignore;
{
  static segT comment_section;
  segT old_section = now_seg;
  int old_subsection = now_subseg;

  if (!comment_section)
    {
      char *p;
      comment_section = subseg_new (".comment", 0);
      bfd_set_section_flags (stdoutput, comment_section,
			     SEC_READONLY | SEC_HAS_CONTENTS);
      p = frag_more (1);
      *p = 0;
    }
  else
    subseg_set (comment_section, 0);
  stringer (1);
  subseg_set (old_section, old_subsection);
}

#ifdef INIT_STAB_SECTION

/* The first entry in a .stabs section is special.  */

void
obj_elf_init_stab_section (seg)
     segT seg;
{
  char *file;
  char *p;
  char *stabstr_name;
  unsigned int stroff;

  /* Force the section to align to a longword boundary.  Without this,
     UnixWare ar crashes.  */
  bfd_set_section_alignment (stdoutput, seg, 2);

  /* Make space for this first symbol. */
  p = frag_more (12);
  /* Zero it out. */
  memset (p, 0, 12);
  as_where (&file, (unsigned int *) NULL);
  stabstr_name = (char *) alloca (strlen (segment_name (seg)) + 4);
  strcpy (stabstr_name, segment_name (seg));
  strcat (stabstr_name, "str");
  stroff = get_stab_string_offset (file, stabstr_name);
  know (stroff == 1);
  md_number_to_chars (p, stroff, 4);
  seg_info (seg)->stabu.p = p;
}

#endif

/* Fill in the counts in the first entry in a .stabs section.  */

static void
adjust_stab_sections (abfd, sec, xxx)
     bfd *abfd;
     asection *sec;
     PTR xxx;
{
  char *name;
  asection *strsec;
  char *p;
  int strsz, nsyms;

  if (strncmp (".stab", sec->name, 5))
    return;
  if (!strcmp ("str", sec->name + strlen (sec->name) - 3))
    return;

  name = (char *) alloca (strlen (sec->name) + 4);
  strcpy (name, sec->name);
  strcat (name, "str");
  strsec = bfd_get_section_by_name (abfd, name);
  if (strsec)
    strsz = bfd_section_size (abfd, strsec);
  else
    strsz = 0;
  nsyms = bfd_section_size (abfd, sec) / 12 - 1;

  p = seg_info (sec)->stabu.p;
  assert (p != 0);

  bfd_h_put_16 (abfd, (bfd_vma) nsyms, (bfd_byte *) p + 6);
  bfd_h_put_32 (abfd, (bfd_vma) strsz, (bfd_byte *) p + 8);
}

#ifdef NEED_ECOFF_DEBUG

/* This function is called by the ECOFF code.  It is supposed to
   record the external symbol information so that the backend can
   write it out correctly.  The ELF backend doesn't actually handle
   this at the moment, so we do it ourselves.  We save the information
   in the symbol.  */

void
elf_ecoff_set_ext (sym, ext)
     symbolS *sym;
     struct ecoff_extr *ext;
{
  sym->bsym->udata.p = (PTR) ext;
}

/* This function is called by bfd_ecoff_debug_externals.  It is
   supposed to *EXT to the external symbol information, and return
   whether the symbol should be used at all.  */

static boolean
elf_get_extr (sym, ext)
     asymbol *sym;
     EXTR *ext;
{
  if (sym->udata.p == NULL)
    return false;
  *ext = *(EXTR *) sym->udata.p;
  return true;
}

/* This function is called by bfd_ecoff_debug_externals.  It has
   nothing to do for ELF.  */

/*ARGSUSED*/
static void
elf_set_index (sym, indx)
     asymbol *sym;
     bfd_size_type indx;
{
}

#endif /* NEED_ECOFF_DEBUG */

void
elf_frob_symbol (symp, puntp)
     symbolS *symp;
     int *puntp;
{
#ifdef NEED_ECOFF_DEBUG
  if (ECOFF_DEBUGGING)
    ecoff_frob_symbol (symp);
#endif

  if (symp->sy_obj)
    {
      switch (symp->sy_obj->X_op)
	{
	case O_subtract:
	  S_SET_SIZE (symp,
		      (S_GET_VALUE (symp->sy_obj->X_add_symbol)
		       + symp->sy_obj->X_add_number
		       - S_GET_VALUE (symp->sy_obj->X_op_symbol)));
	  break;
	case O_constant:
	  S_SET_SIZE (symp,
		      (S_GET_VALUE (symp->sy_obj->X_add_symbol)
		       + symp->sy_obj->X_add_number));
	  break;
	default:
	  as_bad (".size expression too complicated to fix up");
	  break;
	}
      free (symp->sy_obj);
      symp->sy_obj = 0;
    }

  /* Double check weak symbols.  */
  if (symp->bsym->flags & BSF_WEAK)
    {
      if (S_IS_COMMON (symp))
	as_bad ("Symbol `%s' can not be both weak and common",
		S_GET_NAME (symp));
    }

#ifdef TC_MIPS
  /* The Irix 5 assembler appears to set the type of any common symbol
     to STT_OBJECT.  We try to be compatible, since the Irix 5 linker
     apparently sometimes cares.  FIXME: What about Irix 6?  */
  if (S_IS_COMMON (symp))
    symp->bsym->flags |= BSF_OBJECT;
#endif

#ifdef TC_PPC
  /* Frob the PowerPC, so that the symbol always has object type
     if it is not some other type.  VxWorks needs this.  */
  if ((symp->bsym->flags & (BSF_FUNCTION | BSF_FILE | BSF_SECTION_SYM)) == 0
      && S_IS_DEFINED (symp))
    symp->bsym->flags |= BSF_OBJECT;
#endif
}

void 
elf_frob_file ()
{
  bfd_map_over_sections (stdoutput, adjust_stab_sections, (PTR) 0);

#ifdef elf_tc_final_processing
  elf_tc_final_processing ();
#endif

#ifdef NEED_ECOFF_DEBUG
  if (ECOFF_DEBUGGING)
    /* Generate the ECOFF debugging information.  */
    {
      const struct ecoff_debug_swap *debug_swap;
      struct ecoff_debug_info debug;
      char *buf;
      asection *sec;

      debug_swap
	= get_elf_backend_data (stdoutput)->elf_backend_ecoff_debug_swap;
      know (debug_swap != (const struct ecoff_debug_swap *) NULL);
      ecoff_build_debug (&debug.symbolic_header, &buf, debug_swap);

      /* Set up the pointers in debug.  */
#define SET(ptr, offset, type) \
    debug.ptr = (type) (buf + debug.symbolic_header.offset)

	SET (line, cbLineOffset, unsigned char *);
      SET (external_dnr, cbDnOffset, PTR);
      SET (external_pdr, cbPdOffset, PTR);
      SET (external_sym, cbSymOffset, PTR);
      SET (external_opt, cbOptOffset, PTR);
      SET (external_aux, cbAuxOffset, union aux_ext *);
      SET (ss, cbSsOffset, char *);
      SET (external_fdr, cbFdOffset, PTR);
      SET (external_rfd, cbRfdOffset, PTR);
      /* ssext and external_ext are set up just below.  */

#undef SET    

      /* Set up the external symbols.  */
      debug.ssext = debug.ssext_end = NULL;
      debug.external_ext = debug.external_ext_end = NULL;
      if (! bfd_ecoff_debug_externals (stdoutput, &debug, debug_swap, true,
				       elf_get_extr, elf_set_index))
	as_fatal ("Failed to set up debugging information: %s",
		  bfd_errmsg (bfd_get_error ()));

      sec = bfd_get_section_by_name (stdoutput, ".mdebug");
      assert (sec != NULL);

      know (stdoutput->output_has_begun == false);

      /* We set the size of the section, call bfd_set_section_contents
	 to force the ELF backend to allocate a file position, and then
	 write out the data.  FIXME: Is this really the best way to do
	 this?  */
      sec->_raw_size = bfd_ecoff_debug_size (stdoutput, &debug, debug_swap);

      if (! bfd_set_section_contents (stdoutput, sec, (PTR) NULL,
				      (file_ptr) 0, (bfd_size_type) 0))
	as_fatal ("Can't start writing .mdebug section: %s",
		  bfd_errmsg (bfd_get_error ()));

      know (stdoutput->output_has_begun == true);
      know (sec->filepos != 0);

      if (! bfd_ecoff_write_debug (stdoutput, &debug, debug_swap,
				   sec->filepos))
	as_fatal ("Could not write .mdebug section: %s",
		  bfd_errmsg (bfd_get_error ()));
    }
#endif /* NEED_ECOFF_DEBUG */
}

const struct format_ops elf_format_ops =
{
  bfd_target_elf_flavour,
  0,
  1,
  elf_frob_symbol,
  elf_frob_file,
  elf_s_get_size, elf_s_set_size,
  elf_s_get_align, elf_s_set_align,
  elf_copy_symbol_attributes,
#ifdef NEED_ECOFF_DEBUG
  ecoff_generate_asm_lineno,
  ecoff_stab,
#else
  0,
  0,				/* process_stab */
#endif
  elf_sec_sym_ok_for_reloc,
  elf_pop_insert,
#ifdef NEED_ECOFF_DEBUG
  elf_ecoff_set_ext,
#else
  0,
#endif
  obj_read_begin_hook,
  obj_symbol_new_hook,
};