/*  This file is part of the program psim.

    Copyright (C) 1994-1995, Andrew Cagney <cagney@highland.com.au>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
    */


#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "config.h"
#include "misc.h"
#include "lf.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

struct _lf {
  FILE *stream;
  int line_nr; /* nr complete lines written, curr line is line_nr+1 */
  int indent;
  int line_blank;
  char *file_name;
  int number_lines;
};


lf *
lf_open(char *name,
	char *real_name,
	int number_lines)
{
  /* create a file object */
  lf *new_lf = ZALLOC(lf);
  ASSERT(new_lf != NULL);
  new_lf->number_lines = number_lines;
  new_lf->file_name = (real_name == NULL
		       ? name
		       : real_name);

  /* attach to stdout if pipe */
  if (!strcmp(name, "-")) {
    new_lf->stream = stdout;
  }
  else {
    /* create a new file */
    new_lf->stream = fopen(name, "w");
    ASSERT(new_lf->stream != NULL);
  }
  return new_lf;
}


void
lf_close(lf *file)
{
  if (file->stream != stdout) {
    if (fclose(file->stream)) {
      perror("lf_close.fclose");
      exit(1);
    }
    free(file);
  }
}


void
lf_putchr(lf *file,
	  const char chr)
{
  if (chr == '\n') {
    file->line_nr += 1;
    file->line_blank = 1;
  }
  else if (file->line_blank) {
    int pad;
    for (pad = file->indent; pad > 0; pad--)
      putc(' ', file->stream);
    file->line_blank = 0;
  }
  putc(chr, file->stream);
}

void
lf_indent_suppress(lf *file)
{
  file->line_blank = 0;
}


void
lf_putstr(lf *file,
	  const char *string)
{
  const char *chp;
  if (string != NULL) {
    for (chp = string; *chp != '\0'; chp++) {
      lf_putchr(file, *chp);
    }
  }
}

static void
do_lf_putunsigned(lf *file,
	      unsigned u)
{
  if (u > 0) {
    do_lf_putunsigned(file, u / 10);
    lf_putchr(file, (u % 10) + '0');
  }
}


void
lf_putint(lf *file,
	  int decimal)
{
  if (decimal == 0)
    lf_putchr(file, '0');
  else if (decimal < 0) {
    lf_putchr(file, '-');
    do_lf_putunsigned(file, -decimal);
  }
  else if (decimal > 0) {
    do_lf_putunsigned(file, decimal);
  }
  else
    ASSERT(0);
}


void
lf_printf(lf *file,
	  const char *fmt,
	  ...)
{
  char buf[1024];
  va_list ap;

  va_start(ap, fmt);
  vsprintf(buf, fmt, ap);
  /* FIXME - this is really stuffed but so is vsprintf() on a sun! */
  ASSERT(strlen(buf) > 0 && strlen(buf) < sizeof(buf));
  lf_putstr(file, buf);
  va_end(ap);
}


void
lf_print_c_code(lf *file, char *code)
{
  char *chp = code;
  int in_bit_field = 0;
  while (*chp != '\0') {
    if (*chp == '\t')
      chp++;
    if (*chp == '#')
      lf_indent_suppress(file);
    while (*chp != '\0' && *chp != '\n') {
      if (chp[0] == '{' && !isspace(chp[1])) {
	in_bit_field = 1;
	lf_putchr(file, '_');
      }
      else if (in_bit_field && chp[0] == ':') {
	lf_putchr(file, '_');
      }
      else if (in_bit_field && *chp == '}') {
	lf_putchr(file, '_');
	in_bit_field = 0;
      }
      else {
	lf_putchr(file, *chp);
      }
      chp++;
    }
    if (in_bit_field)
      error("bit field paren miss match some where\n");
    if (*chp == '\n') {
      lf_putchr(file, '\n');
      chp++;
    }
  }
  lf_putchr(file, '\n');
}


void
lf_print_c_line_nr(lf *file,
		   int line_nr,
		   char *file_name)
{
  if (file->number_lines) {
    lf_indent_suppress(file);
    lf_putstr(file, "#line ");
    lf_putint(file, line_nr);
    lf_putstr(file, " \"");
    lf_putstr(file, file_name);
    lf_putstr(file, "\"\n");
  }
}

void
lf_print_lf_c_line_nr(lf *file)
{
  lf_print_c_line_nr(file, file->line_nr+2, file->file_name);
  /* line_nr == last_line, want to number from next */
}

void
lf_indent(lf *file, int delta)
{
  file->indent += delta;
}


void
lf_print_copyleft(lf *file)
{
  lf_putstr(file, "\
/*  This file is part of the program psim.

    Copyright (C) 1994-1995, Andrew Cagney <cagney@highland.com.au>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
    --

    This file was generated by the program gen */
");
}


void
lf_print_binary(lf *file, int decimal, int width)
{
  int bit;
  ASSERT(width > 0);

  for (bit = 1 << (width-1); bit != 0; bit >>= 1) {
    if (decimal & bit)
      lf_putchr(file, '1');
    else
      lf_putchr(file, '0');
  }

}

void
lf_print_function_type(lf *file,
		       const char *type,
		       const char *prefix,
		       const char *trailing_space)
{
  lf_printf(file, "%s\\\n(%s)", prefix, type);
  if (trailing_space != NULL)
    lf_printf(file, "%s", trailing_space);
#if 0
  const char *type_pointer = strrchr(type, '*');
  int type_pointer_offset = (type_pointer != NULL
			     ? type_pointer - type
			     : 0);
  if (type_pointer == NULL) {
    lf_printf(file, "%s %s", type, prefix);
  }
  else {
    char *munged_type = (char*)zalloc(strlen(type)
				      + strlen(prefix)
				      + strlen(" * ")
				      + 1);
    strcpy(munged_type, type);
    munged_type[type_pointer_offset] = '\0';
    if (type_pointer_offset > 0 && type[type_pointer_offset-1] != ' ')
      strcat(munged_type, " ");
    strcat(munged_type, prefix);
    strcat(munged_type, " ");
    strcat(munged_type, type + type_pointer_offset);
    lf_printf(file, "%s", munged_type);
    free(munged_type);
  }
  if (trailing_space != NULL && type_pointer_offset < strlen(type) - 1)
    lf_printf(file, trailing_space);
#endif
}
