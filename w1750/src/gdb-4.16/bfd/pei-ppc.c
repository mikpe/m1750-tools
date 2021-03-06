/* BFD back-end for Intel 386 PE IMAGE COFF files.
   Copyright 1995 Free Software Foundation, Inc.

This file is part of BFD, the Binary File Descriptor library.

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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include "bfd.h"
#include "sysdep.h"

/* setting up for a PE environment stolen directly from the i386 structure */
#define E_FILNMLEN	18	/* # characters in a file name		*/

#define PPC

#define TARGET_LITTLE_SYM   bfd_powerpcle_pei_vec
#define TARGET_LITTLE_NAME "pei-powerpcle"

#define TARGET_BIG_SYM      bfd_powerpc_pei_vec
#define TARGET_BIG_NAME    "pei-powerpc"

#define IMAGE_BASE          NT_IMAGE_BASE

#define COFF_IMAGE_WITH_PE
#define COFF_WITH_PE

/* FIXME: Verify PCRELOFFSET is always false */

#include "coff-ppc.c"



