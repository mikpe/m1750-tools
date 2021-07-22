/*
 * m1750-coff/include/intrrpt.h
 *
 * GCC-1750 Extension: Interrupt handling
 *
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
 * European Space Agency contract 11935/96/NL/JG. Permission to use 
 * copy, modify, and distribute this software for any purpose without 
 * fee is hereby granted, provided that this entire notice is included 
 * in all copies of any software which is or includes a copy or 
 * modification of this software and in all copies of the supporting 
 * documentation for such software. This software is provided "as is", 
 * without any express or implied warranty. In particular, neither the 
 * author nor the European Space Agency makes any representation or 
 * warranty of any kind concerning the merchantability of this software 
 * or its fitness for any particular purpose. 
 *
 * $Log: intrrpt.h,v $
 * Revision 1.2  1997/07/27 15:03:40  nettleto
 * Added INT_ERR, INT_IGN.
 *
 * Revision 1.2  1997/07/27 07:57:09  nettleto
 * Added BEX and other macros.
 *
 * Revision 1.1  1997/07/17 19:00:52  nettleto
 * Initial revision
 *
 */

#ifndef _INTRRPT_H_
#define _INTRRPT_H_

#include <sys/cdefs.h>

#define NINT          32

#define INTPWRDWN     0
#define INTMACHERR    1
#define INTSPARE1     2
#define INTFLVFLOW    3
#define INTFXVFLOW    4
#define INTBEX        5
#define INTFLUFLOW    6
#define INTTIMERA     7
#define INTSPARE2     8
#define INTTIMERB     9
#define INTSPARE3    10
#define INTSPARE4    11
#define INTLEVEL1    12
#define INTSPARE5    13
#define INTLEVEL2    14
#define INTSPARE6    15

#define INTBEX0      16
#define INTBEX1      17
#define INTBEX2      18
#define INTBEX3      19
#define INTBEX4      20
#define INTBEX5      21
#define INTBEX6      22
#define INTBEX7      23
#define INTBEX8      24
#define INTBEX9      25
#define INTBEX10     26
#define INTBEX11     27
#define INTBEX12     28
#define INTBEX13     29
#define INTBEX14     30
#define INTBEX15     31

typedef void (*_handler_t)(int);

#define INT_DFL ((_handler_t)0)     /* default signal handling */
#define INT_ERR ((_handler_t)-1)    /* error return from signal */
#define INT_IGN ((_handler_t)1)     /* ignore signal */

/* Recognizable magic number */
#define IMAGIC 0xface

__BEGIN_DECLS

/* Interrupt frame */
struct _iframe
  {
    short magic;    /* valid frames have this set to IMAGIC */
    short sl;       /* stack limit register (not yet supported) */
    short mk;       /* register MK */
    short sw;       /* register SW */
    short ic;       /* register IC */
    short regs[15]; /* registers R0 to R14 */
  };

#define _intmask(int)  (1 << (15 - (int)))

_handler_t handler (int n, _handler_t func);

void *set_sp (void *sp);

__END_DECLS

#endif /* not _INTRRPT_H_ */

