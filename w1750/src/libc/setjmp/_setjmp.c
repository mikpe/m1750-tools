/*
 * _setjmp
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
 * $Log: _setjmp.c,v $
 * Revision 1.3  1997/08/06 16:47:18  nettleto
 * Updated for 2-word expanded memory links
 *
 * Revision 1.2  1997/07/17 18:59:57  nettleto
 * Added expanded memory support.
 *
 * Revision 1.1  1997/05/08 07:04:48  nettleto
 * Initial revision
 *
 */

#include <setjmp.h>

int
_setjmp (jmp_buf env);

#ifdef MMU
asm ("
	.globl _setjmp
_setjmp:
        lr     r5,r0           ! ptr to env
        xorr   r0,r0           ! return 0
        dl     r1,0,r15        ! 32-bit link
        lr     r3,r14          ! callers r14
        lim    r4,2,r15        ! callers r15
        stm    4,0,r5          ! save 5 words in env
        lurs   r15");


#else
asm ("
	.globl _setjmp
_setjmp:
        lr     r5,r0           ! ptr to env
        xorr   r0,r0 
        xio    r1,rsw          ! callers sw
        l      r2,0,r15        ! callers ic
        lr     r3,r14          ! callers r14
        lim    r4,1,r15        ! callers r15
        stm    4,0,r5
        xorr   r0,r0 
        urs    r15");
#endif

