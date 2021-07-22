/*
 * crt0.c 
 *
 * GCC-1750 C/C++ Run-Time, 64K memory model, no interrupts
 *
 * Copyright (c) 1997 Chris Nettleton Software
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
 * $Log: crt0.c,v $
 * Revision 1.1  1997/07/17 18:44:42  nettleto
 * Initial revision
 *
 */


/*
 * Environment stuff. Environment variables, accessible via the library
 * function getenv, may be defined here. Each definition has the format
 * "name=value" (as a string literal). The list of definitions is 
 * terminated with a zero address. 
 */
const char *environ [] = 
  {
    "date=" __DATE__,
    "time=" __TIME__,
    "revision=$Revision: 1.1 $",
    0
  };

/*
 * Arguments. The arguments given in the following declaration are 
 * passed to the main program where they may be accessed via argc
 * and argv in the usual way. Example {"arg1", "arg2", 0}.
 */
static const char *argv [] = {0};


typedef void (*func_ptr) (void);
extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];

/*
 * start: Program entry point 
 */
void
start ()
{
  extern short *__bss_start;
  extern short *_end;
  short **p;
  unsigned cnt;

  /* create first stack frame (for the debugger) */
  asm volatile (
       "lim    r15,__stack
        xorr   r14,r14");

  /* Zero out the bss section */
  p = &__bss_start;
  cnt = &_end - &__bss_start;
  if (cnt != 0)
    {
      do 
        *p++ = 0;
      while (--cnt);
    }

  /* execute any global constructors */
  asm ("sjs    r15,_main");

  /* Call main (argc, argv) */
  asm ("lim    r0,%0
        lim    r1,%1
        sjs    r15,main" :: "i" (sizeof (argv) - 1), "i" (argv));

  /* execute any global destructors, and exit */
  asm ("xorr   r0,r0
        sjs    r15,_exit");
}


void
_main ()
{
  func_ptr *cp;

  for (cp = __CTOR_LIST__ + 3; *cp; cp += 2)
    (*cp) ();
}


void
_exit (int code)
{
  func_ptr *cp;

  /* execute any global destructors */
  for (cp = __DTOR_LIST__ + 3; *cp; cp += 2)
    (*cp) ();

  /* ... and restart the application program */
  asm ("bpt
        j      start");

}


