/*
 * ANSI Standard C: 7.6.1.2
 * 
 * #include <setjmp.h>
 * int longjmp (jmp_buf env, int val);
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
 * $Log: longjmp.c,v $
 * Revision 1.2  1997/07/17 18:58:30  nettleto
 * Updated for expanded memory.
 *
 * Revision 1.1  1997/05/08 07:05:40  nettleto
 * Initial revision
 *
 */

#include <setjmp.h>

void
longjmp (jmp_buf env, int val) 
{
  if (val == 0)
    val = 1;

  /* Get the mask, and ensure it gets set by the LST */
  asm volatile (
       "xio    r0,dsbl
        xio    r0,rmk
        st     r0,0,%0" :: "x" (env));

  /* Set the return value (as returned from setjmp), and reload
     registers r14, r15, sw and ic */
  asm volatile (
       "lr     r0,%1
        dl     r14,3,%0
        xio    r0,enbl
        lst    0,%0" :: "x" (env), "r" (val));
}

