/*
 * GCC-1750 Run-Time System
 * 
 * #include <intrrpt.h>
 * (*handler (int n, void (*func)(int))) (int);
 * 
 * Copyright (c) 1996, Chris Nettleton Software
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
 * $Log: handler.c,v $
 * Revision 1.3  1997/07/27 14:50:11  nettleto
 * Added code to set and remove mask bits.
 *
 * Revision 1.2  1997/07/18 13:01:02  nettleto
 * Changed error code to -1.
 *
 * Revision 1.1  1997/07/17 18:42:25  nettleto
 * Initial revision
 *
 */

#include <intrrpt.h>

#include <errno.h>

extern _handler_t _int_func [32];


/* Saves the LS 16 bits of the address of the given interrupt
   handler in the handler table, and returns the old value.
 */
_handler_t 
handler (int n, _handler_t func)
{
  _handler_t old_func;

  if (n >= 0 && n <= 32)
    {
      unsigned old_mk;

      asm volatile ("xio    r0,dsbl");
      asm volatile ("xio    %0,rmk": "=r" (old_mk));

      old_func = _int_func [n];
      _int_func [n] = func;

      if (n < 16)
        {
          if (func != INT_DFL)
            /* Insert bit in interrupt mask.  */
            set_mk (old_mk | _intmask (n));
          else
            /* Remove bit from interrupt mask.  */
            set_mk (old_mk & (~_intmask (n)));
        }
    }
  else
    {
      old_func = -1;
      errno = EINVAL;
    }

  return old_func;
}

