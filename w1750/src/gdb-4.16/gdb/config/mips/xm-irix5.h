/* Definitions for irix5 hosting support.

Copyright (C) 1993 Free Software Foundation, Inc.

This file is part of GDB.

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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include "xm-sysv4.h"

#define CC_HAS_LONG_LONG 1
#define PRINTF_HAS_LONG_LONG 1
#define HOST_BYTE_ORDER BIG_ENDIAN

/* Override register locations in upage for SGI machines */
#undef REGISTER_U_ADDR
#define REGISTER_U_ADDR(addr, blockend, regno) 		\
  if (regno < PC_REGNUM)				\
      addr = regno;					\
  else							\
      addr = regno + NSIG_HNDLRS; /* Skip over signal handlers */

/* This enables reliable signals (and the associated setjmp/longjmp), and gives
   bsdish prototypes for getpgrp/setpgrg/setgroups and initgroups.  */
#define _BSD_COMPAT
