/* Opcode table for MIL-STD-1750A and MIL-STD-1750B.
   Copyright 1989, 91, 92, 93, 94, 95, 1996 Free Software Foundation.

This file is part of GDB, GAS, and the GNU binutils.

GDB, GAS, and the GNU binutils are free software; you can redistribute
them and/or modify them under the terms of the GNU General Public
License as published by the Free Software Foundation; either version
1, or (at your option) any later version.

GDB, GAS, and the GNU binutils are distributed in the hope that they
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#include "ansidecl.h"
#include "opcode/m1750.h"

#define one(x) ((unsigned int) (x) << 16)
#define two(x, y) (((unsigned int) (x) << 16) + (y))

/* The assembler requires that all instances of the same mnemonic must
   be consecutive.  If they aren't, the assembler will bomb at
   runtime.  */

const struct m1750_opcode m1750_opcodes[] =
{
{"abcd",	one(0140400),	one(0170770), "DsDd", m1750a },

};

const int m1750_numopcodes = sizeof m1750_opcodes / sizeof m1750_opcodes[0];

/* These aliases used to be in the above table, each one duplicating
   all of the entries for its primary exactly.  This table was
   constructed by mechanical processing of the opcode table, with a
   small number of tweaks done by hand.  There are probably a lot more
   aliases above that could be moved down here, except for very minor
   differences.  */

const struct m1750_opcode_alias m1750_opcode_aliases[] =
{
  { "add",	"addw", },
};

const int m1750_numaliases =
  sizeof m1750_opcode_aliases / sizeof m1750_opcode_aliases[0];
