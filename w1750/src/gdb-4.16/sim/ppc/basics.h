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


#ifndef _BASICS_H_
#define _BASICS_H_


/* from Michael Meissner, macro's to handle concating symbols better */

#ifdef __STDC__
#define CONCAT2(a,b)	 a##b
#define CONCAT3(a,b,c)	 a##b##c
#define CONCAT4(a,b,c,d) a##b##c##d
#else
#define CONCAT2(a,b)	 a/**/b
#define CONCAT3(a,b,c)	 a/**/b/**/c
#define CONCAT4(a,b,c,d) a/**/b/**/c/**/d
#endif

#define XCONCAT2(a,b)     CONCAT2(a,b)
#define XCONCAT3(a,b,c)   CONCAT3(a,b,c)
#define XCONCAT4(a,b,c,d) CONCAT4(a,b,c,d)


/* many things pass around the cpu and psim object with out knowing
   what it is */

typedef struct _cpu cpu;
typedef struct _psim psim;
typedef struct _device device;
typedef struct _device_instance device_instance;


/* many things are moving data between the host and target */

typedef enum {
  cooked_transfer,
  raw_transfer,
} transfer_mode;

/* possible exit statuses */

typedef enum {
  was_continuing, was_trap, was_exited, was_signalled
} stop_reason;


/* Basic configuration */

#include "config.h"
#include "ppc-config.h"
#include "inline.h"


/* Basic host dependant mess - hopefully <stdio.h> will bring
   potential conflicts out in the open */

#include <stdio.h>

#ifndef NORETURN
#define NORETURN
#endif

#ifndef NULL
#define NULL 0
#endif

#if !defined (__attribute__) && (!defined(__GNUC__) || __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7))
#define __attribute__(arg)
#endif

#if !defined (UNUSED)
#define UNUSED __attribute__((__unused__))
#endif


/* Basic definitions - ordered so that nothing calls what comes after
   it */

#include "sim_callbacks.h"

#include "debug.h"

#include "words.h"
#include "bits.h"
#include "sim-endian.h"

#endif /* _BASICS_H_ */
