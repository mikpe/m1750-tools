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


/* LF: Line Numbered Output Stream */

typedef struct _lf lf;


#if !defined (__attribute__) && (!defined(__GNUC__) || __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7))
#define __attribute__(arg)
#endif

/* Open the file NAME for writing.  REAL_NAME is to be included in any
   line number outputs.  The output of line number information can be
   suppressed with LINE_NUMBERS */
extern lf *lf_open
(char *name,
 char *real_name,
 int number_lines);

extern void lf_close
(lf *file);


/* Suppress indentation for the next new line (current if not yet
   started) */
extern void lf_indent_suppress
(lf *file);

extern void lf_putchr
(lf *file,
 const char ch);

extern void lf_putstr
(lf *file,
 const char *string);

extern void lf_putint
(lf *file,
 int decimal);

extern void lf_printf
(lf *file,
 const char *fmt,
 ...) __attribute__((format(printf, 2, 3)));

extern void lf_print_lf_c_line_nr
(lf *file);

extern void lf_indent
(lf *file,
 int delta);

extern void lf_print_copyleft
(lf *file);

extern void lf_print_binary
(lf *file,
 int decimal,
 int width);

/* it is assumed that each line of code is prefixed by a tab character
   that should be suppressed */
extern void lf_print_c_code
(lf *file,
 char *code);


extern void lf_print_c_line_nr
(lf *file,
 int line_nr,
 char *file_name);


extern void lf_print_function_type
(lf *file,
 const char *type,
 const char *prefix,
 const char *trailing_space);
