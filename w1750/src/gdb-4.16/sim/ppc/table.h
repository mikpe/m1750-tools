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


/* load a table into memory */

typedef struct _table table;

typedef struct _table_model_entry table_model_entry;
struct _table_model_entry {
  table_model_entry *next;
  int line_nr;
  int nr_fields;
  char *fields[0];	/* User defined */
};

typedef struct _table_entry table_entry;
struct _table_entry {
  int line_nr;
  int nr_fields;
  char *file_name;
  table_model_entry *model_first;
  table_model_entry *model_last;
  char *annex;
  char *fields[0];	 /* User defined */
};


extern table *table_open
(char *file_name,
 int max_nr_fields,
 int max_nr_model_fields);

extern table_entry *table_entry_read
(table *file);

extern void dump_table_entry
(table_entry *entry,
 int indent);

extern void table_entry_lf_c_line_nr
(lf *file,
 table_entry *entry);
