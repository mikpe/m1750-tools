/*
 * GCC-1750 Run-Time System, 64K memory model only
 * 
 * #include <intrrpt.h>
 * extern struct {} ivt [];
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
 * $Log: ivt.c,v $
 * Revision 1.4  1997/08/08 09:00:32  nettleto
 * Added interrupt enable flag, for compatibility with
 * expanded memory (not used in 64K model)
 *
 * Revision 1.3  1997/07/27 14:50:49  nettleto
 * Added code to save and restore the base level interrupt mask.
 *
 * Revision 1.2  1997/07/20 15:47:25  nettleto
 * Removed _ERA_BOARD conditional code.
 *
 * Revision 1.1  1997/07/17 18:42:35  nettleto
 * Initial revision
 *
 */

#include <signal.h>
#include <intrrpt.h>

#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>

/*
 * The interrupt stack is used by asynchronous stack-switching interrupt 
 * handlers and anything that can interrupt such a handler. The minimum
 * size, assuming all 16 levels can interrupt, is 19 words per level
 * i.e. 19 * 15 = 285. The size is application dependent.
 */
static int istack [1000];

/*
 * This version keeps wall time in 'sys_times', which is accessible by the
 * library function _gettimeofday. This code may be replaced as necessary
 * to support some other source fo wall time. The time is updated 100 times
 * per second using timer A. (NOTE: Timer B is free for use by application
 * programs).
 */
struct timeval sys_time;


/*
 * The CPU times are recorded in sys_times. Only user time is measured.
 */
struct tms sys_times;


/*
 * These are the headers for the 31 handler functions. The function
 * bodies are introduced later, as small assembly language routines.
 */
static void power_down_handler () __attribute__ ((noreturn));
static void machine_error_handler () __attribute__ ((noreturn));
static void spare1_handler () __attribute__ ((noreturn));
static void floating_overflow_handler () __attribute__ ((noreturn));
static void fixed_overflow_handler () __attribute__ ((noreturn));
static void bex0_handler () __attribute__ ((noreturn));
static void bex1_handler () __attribute__ ((noreturn));
static void bex2_handler () __attribute__ ((noreturn));
static void bex3_handler () __attribute__ ((noreturn));
static void bex4_handler () __attribute__ ((noreturn));
static void bex5_handler () __attribute__ ((noreturn));
static void bex6_handler () __attribute__ ((noreturn));
static void bex7_handler () __attribute__ ((noreturn));
static void bex8_handler () __attribute__ ((noreturn));
static void bex9_handler () __attribute__ ((noreturn));
static void bex10_handler () __attribute__ ((noreturn));
static void bex11_handler () __attribute__ ((noreturn));
static void bex12_handler () __attribute__ ((noreturn));
static void bex13_handler () __attribute__ ((noreturn));
static void bex14_handler () __attribute__ ((noreturn));
static void bex15_handler () __attribute__ ((noreturn));
static void floating_underflow_handler () __attribute__ ((noreturn));
static void timer_a_handler () __attribute__ ((noreturn));
static void spare2_handler () __attribute__ ((noreturn));
static void timer_b_handler () __attribute__ ((noreturn));
static void spare3_handler () __attribute__ ((noreturn));
static void spare4_handler () __attribute__ ((noreturn));
static void level1_handler () __attribute__ ((noreturn));
static void spare5_handler () __attribute__ ((noreturn));
static void level2_handler () __attribute__ ((noreturn));
static void spare6_handler () __attribute__ ((noreturn));


/*
 * These are the 16 linkage areas where the old mask, old status and old
 * instruction counter are saved when the processor handles an interrupt.
 * Only number 5, the BEX instruction is re-entrant, in which case the
 * contents of the old area should be saved before any further BEX
 * instructions are executed.
 */
struct linkage_area
  {
    unsigned short mk;  /* Interrupt mask */
    unsigned short sw;  /* Status word */
    void *ic;           /* Instruction counter */
  };
static struct linkage_area power_down_old;           /*  0 */
static struct linkage_area machine_error_old;        /*  1 */
static struct linkage_area spare1_old;               /*  2 */
static struct linkage_area floating_overflow_old;    /*  3 */
static struct linkage_area fixed_overflow_old;       /*  4 */
static struct linkage_area bex_old;                  /*  5 */
static struct linkage_area floating_underflow_old;   /*  6 */
static struct linkage_area timer_a_old;              /*  7 */
static struct linkage_area spare2_old;               /*  8 */
static struct linkage_area timer_b_old;              /*  9 */
static struct linkage_area spare3_old;               /* 10 */
static struct linkage_area spare4_old;               /* 11 */
static struct linkage_area level1_old;               /* 12 */
static struct linkage_area spare5_old;               /* 13 */
static struct linkage_area level2_old;               /* 14 */
static struct linkage_area spare6_old;               /* 15 */


/*
 * These are the service areas where the new mask, new status and new
 * instruction counters for each of the 16 interrupt numbers. Note that
 * number 5, for the BEX instruction has an array of 16 instruction
 * counters
 */
struct service_area
  {
    unsigned short mk;        /* Interrupt mask */
    const unsigned short sw;  /* Status word */
    const void *ic;           /* Instruction counter */
  };
struct bex_service_area
  {
    unsigned short mk;        /* Interrupt mask */
    const unsigned short sw;  /* Status word */
    const void *ic [16];      /* entry to each of 16 bex handlers */
  };

#define default_mk 0x0000
#define default_sw 0x0000

static struct service_area power_down_new =         
  {default_mk, default_sw, &power_down_handler};
static struct service_area machine_error_new =      
  {default_mk, default_sw, &machine_error_handler};
static struct service_area spare1_new =             
  {default_mk, default_sw, &spare1_handler};
static struct service_area floating_overflow_new =  
  {default_mk, default_sw, &floating_overflow_handler};
static struct service_area fixed_overflow_new =     
  {default_mk, default_sw, &fixed_overflow_handler};
static struct bex_service_area bex_new =                
  {default_mk, default_sw, 
   {&bex0_handler, &bex1_handler, &bex2_handler, &bex3_handler,
    &bex4_handler, &bex5_handler, &bex6_handler, &bex7_handler,
    &bex8_handler, &bex9_handler, &bex10_handler, &bex11_handler,
    &bex12_handler, &bex13_handler, &bex14_handler, &bex15_handler}};
static struct service_area floating_underflow_new = 
  {default_mk, default_sw, &floating_underflow_handler};
static struct service_area timer_a_new =            
  {default_mk, default_sw, &timer_a_handler};
static struct service_area spare2_new =             
  {default_mk, default_sw, &spare2_handler};
static struct service_area timer_b_new =            
  {default_mk, default_sw, &timer_b_handler};
static struct service_area spare3_new =             
  {default_mk, default_sw, &spare3_handler};
static struct service_area spare4_new =             
  {default_mk, default_sw, &spare4_handler};
static struct service_area level1_new =             
  {default_mk, default_sw, &level1_handler};
static struct service_area spare5_new =             
  {default_mk, default_sw, &spare5_handler};
static struct service_area level2_new =             
  {default_mk, default_sw, &level2_handler};
static struct service_area spare6_new =             
  {default_mk, default_sw, &spare6_handler};


/*
 * This is the interrupt vector table. It gets copied from here
 * to its proper place when the program is started up, and before 
 * any interrupts are enabled.
 */
const struct
  {
    struct linkage_area *linkage_area_ptr;
    struct service_area *service_area_ptr;
  }
ivt [] =
{
  &power_down_old, &power_down_new,                 /* 0  */
  &machine_error_old, &machine_error_new,           /* 1  */
  &spare1_old, &spare1_new,                         /* 2  */
  &floating_overflow_old, &floating_overflow_new,   /* 3  */
  &fixed_overflow_old, &fixed_overflow_new,         /* 4  */
  &bex_old, (struct service_area *)&bex_new,        /* 5  */
  &floating_underflow_old, &floating_underflow_new, /* 6  */
  &timer_a_old, &timer_a_new,                       /* 7  */
  &spare2_old, &spare2_new,                         /* 8  */
  &timer_b_old, &timer_b_new,                       /* 9  */
  &spare3_old, &spare3_new,                         /* 10 */
  &spare4_old, &spare4_new,                         /* 11 */
  &level1_old, &level1_new,                         /* 12 */
  &spare5_old, &spare5_new,                         /* 13 */
  &level2_old, &level2_new,                         /* 14 */
  &spare6_old, &spare6_new                          /* 15 */
};


/*
 * This is the handler table. There is one entry for each of the 16 
 * interrupts, and the value of each entry is zero, meaning ignore the
 * interrupt, or some other value that is the address of the handler.
 * Note: _int_func[16] .. _int_func[31] are for BEX 0 to BEX 15.
 */
_handler_t _int_func [32];


/*
 * power_down_handler (asynchronous stack-switching interrupt)
 */
static void
power_down_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0 \n\t"
       "lim    r1,power_down_old" 
       :: "i" (INTPWRDWN));

  asm ("j      _icommon");
  l1: goto l1;
}


/*
 * machine_error_handler (synchronous exception)
 */
static void
machine_error_handler ()
{
  short ft;  /* Fault register */

  asm ("pshm   r0,r14");
  asm ("xio    %0,rcfr" : "=r" (ft));

  if (ft & 0xfb00)
    asm (
       "lim    r0,%0
        sjs    r15,raise" :: "i" (SIGBUS));
  else if (ft & 0x0090)
    asm (
       "lim    r0,%0
        sjs    r15,raise" :: "i" (SIGSEGV));
  else 
    asm (
       "lim    r0,%0
        sjs    r15,raise" :: "i" (SIGILL));

  asm ("popm   r0,r14
        xio    r0,enbl
        lst    machine_error_old");

  l1: goto l1;
}


/* 
 * spare1_handler (asynchronous stack-switching interrupt) 
 */
static void
spare1_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,spare1_old" :: "i" (INTSPARE1));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * floating_overflow_handler (synchronous exception) 
 */
static void
floating_overflow_handler ()
{
  asm (
       "pshm   R0,R14
        lim    r0,%0
        sjs    r15,raise
        popm   R0,R14
        xio    r0,enbl
        lst    floating_overflow_old" :: "i" (SIGFPE));

  l1: goto l1;
}


/* 
 * fixed_overflow_handler (synchronous exception) 
 */
static void
fixed_overflow_handler ()
{
  /* we ignore fixed point overflow */
  asm ("
        xio    r0,enbl
        lst    fixed_overflow_old");

  l1: goto l1;
}


/* 
 * bex0_handler (system call) 
 *
 */
static void
bex0_handler ()
{
  asm ("
        xio    r0,enbl
        lst    bex_old");

  l1: goto l1;
}


/* 
 * bex1_handler (system call) 
 *
 */
static void
bex1_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,bex_old" :: "i" (17));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * bex2_handler (system call) 
 *
 */
static void
bex2_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex3_handler (system call)
 *
 */
static void
bex3_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex4_handler (system call)
 */
static void
bex4_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex5_handler (system call)
 */
static void
bex5_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex6_handler (system call)
 */
static void
bex6_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex7_handler (system call)
 */
static void
bex7_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex8_handler (system call)
 */
static void
bex8_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex9_handler (system call)
 */
static void
bex9_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex10_handler (system call)
 */
static void
bex10_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex11_handler (system call)
 */
static void
bex11_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex12_handler (system call)
 */
static void
bex12_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex13_handler (system call)
 */
static void
bex13_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex14_handler (system call)
 */
static void
bex14_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * bex15_handler (system call)
 */
static void
bex15_handler ()
{
  asm ("xio    r0,enbl
        lst    bex_old");

  l1: goto l1; 
}


/* 
 * floating_underflow_handler (synchronous interrupt) 
 */
static void
floating_underflow_handler ()
{
  /* We ignore floating underflow.  */
  asm ("xio    r0,enbl
        lst    floating_underflow_old");

  l1: goto l1; 
}


/* 
 * timer_a_handler (asynchronous stack-switching interrupt)
 */
static void
timer_a_handler ()
{
  asm ("pshm   r0,r14");

  /* restart timer A to interrupt 10 mSec from now */
  asm ("xio    r0,ita
	aim    r0,%0
	xio    r0,ota" :: "i" (-1000));

  /* count the tick */
  sys_times.tms_utime++;

  /* increment system time by 10 mSec */
  sys_time.tv_usec += 10000;

  if (sys_time.tv_usec >= 1000000)
    {
      sys_time.tv_sec++;
      sys_time.tv_usec -= 1000000;
    }

  asm ("lim    r0,%0
	lim    r1,timer_a_old" :: "i" (INTTIMERA));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * spare2_handler (asynchronous stack-switching interrupt) 
 */
static void
spare2_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,spare2_old" :: "i" (INTSPARE2));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * timer_b_handler (asynchronous stack-switching interrupt)
 */
static void
timer_b_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,timer_b_old" :: "i" (INTTIMERB));

  asm ("j      _icommon");
  l1: goto l1;
}

/* 
 * spare3_handler (asynchronous stack-switching interrupt)
 */
static void
spare3_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,spare3_old" :: "i" (INTSPARE3));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * spare4_handler (asynchronous stack-switching interrupt)
 */ 
static void
spare4_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,spare4_old" :: "i" (INTSPARE4));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * level1_handler (asynchronous stack-switching interrupt) 
 */
static void
level1_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,level1_old" :: "i" (INTLEVEL1));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * spare5_handler (asynchronous stack-switching interrupt)
 */ 
static void
spare5_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,spare5_old" :: "i" (INTSPARE5));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * level2_handler (asynchronous stack-switching interrupt) 
 */
static void
level2_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
        lim    r1,level2_old" :: "i" (INTLEVEL2));

  asm ("j      _icommon");
  l1: goto l1;
}


/* 
 * spare6_handler (asynchronous stack-switching interrupt)
 */ 
static void
spare6_handler ()
{
  asm ("pshm   r0,r14");

  asm ("lim    r0,%0
	lim    r1,spare6_old" :: "i" (INTSPARE6));

  asm ("j      _icommon");
  l1: goto l1;
}


/*
 * Common interrupt handling code for aynchronous interrupts.
 * Here we check if the interrupt takes us from a thread into the
 * handler, and if so, the thread is partially saved. Then the
 * signal is passed to the handler (if any). On exit, if we are
 * returning to a thread (i.e. back to base level) then we 
 * restore the current thread. This may not be the same thread 
 * that was interrupted.
 */

/*
 * The variable 'level' is set to -1 while we are executing at base level
 * and is incremented each time we get an an interrupt. If the
 * value of level goes from -ve to +ve, then we have switched from base
 * level to interrupt level and before proceeding we switch to the
 * interrupt stack. Conversely at the end of an interrupt handler, we
 * decrement the level and if it goes from +ve to -ve then we switch back
 * to the base level stack.
 */
static int level; 

/*
 * The signal handler may switch threads at any point by saving
 * the variable crt_sp in the current thread, and setting
 * crt_sp to the stack pointer of some other thread. Of course
 * the complete context of a thread will include other variables
 * such as errno.
 */
static void *crt_sp;

static void *crt_sp_limit;
static unsigned crt_mk;

/* Flag for interrupt enable */
int _enbl;


void *
set_sp (void *sp)
{
  void *old_sp = crt_sp;
  
  crt_sp = sp;
  return old_sp;
}


static void
_icommon (int sig, void *old)
{
  int tmp;
  _handler_t h;

  /* save the three word context on the stack in correct order
     for an LST instruction */
  asm (
       "sisp   r15,3
        lm     2,0,%0
        stm    2,0,r15" :: "x" (old) : "r0", "r1", "r2");

  /* switch stacks when interrupting a thread */
  level++;
  if (level == 0)
    {
      /* Save base level interrupt mask.  */
      asm volatile ("l      %0,0,r15" : "=r" (crt_mk));

      /* Save stack limit and finish interrupted thread frame
         with a magic number.  */
      asm volatile ("pshm   %0,%0" :: "r" (crt_sp_limit));
      asm volatile ("pshm   %0,%0" :: "r" (IMAGIC));

      /* save stack ptr, and load new stack ptr */
      asm volatile (
       "st     r15,%0
        lim    r15,%1
        xorr   r14,r14" :: "m" (crt_sp), "i" (&istack [1000]));
      crt_sp_limit = (void *)&istack [0];
    }

  /* call the signal handler (if any) */
  h = _int_func [sig];
  if (h)
    asm volatile (
       "xio    r1,enbl
        lr     r0,%0
        sjs    r15,0,%1
        xio    r1,dsbl" :: "r" (sig), "x" (h));

  /* switch back to thread stack if we're returning to base level */
  level--;
  if (level < 0)
    {
      /* Get old stack pointer.  */
      asm volatile ("l      r15,%0" :: "m" (crt_sp));

      /* Read-clear magic number */
      asm volatile ("popm   %0,%0" : "=r" (tmp));
      asm volatile ("st     %0,-1,r15" :: "r" (0xdead));

      /* Stop if magic number check fails. Note the watchdog timer will
         eventually detect this, and raise an error condition.  */
      if (tmp != IMAGIC)
        while (1)
          ;

      /* And set stack limit for thread.  */
      asm volatile ("popm   %0,%0" : "=r" (crt_sp_limit));

      /* Restore base level interrupt mask.  */
      asm volatile ("st     %0,0,r15" :: "r" (crt_mk));
    }

  /* return to thread or interrupted handler via stack */
  asm (
       "aisp   r15,3
        popm   r0,r14
        xio    r0,enbl
        lst    -18,r15");
}


void intrrpt_init () __attribute__ ((constructor));

void
intrrpt_init ()
{
  void *ivt_20;
  int i;
  int reg, as;

  /* hide the constant 0x20 to avoid compiler problem */
  asm ("lim    %0,0x20" : "=r" (ivt_20));
  
  /* Copy the interrupt vector table into place at word 20 onward */
  memcpy (ivt_20, (void *)ivt, 32);

  /* clear cpu times */
  sys_times.tms_utime = 0;  /* user time */
  sys_times.tms_stime = 0;  /* system time */
  sys_times.tms_cutime = 0; /* user time of children */
  sys_times.tms_cstime = 0; /* system time of children */
 
  /* initialize the handler table */
  for (i = 0; i < 32; i++)
    _int_func [i] = INT_DFL;

  level = -1;

  /* Start timer A, and set to interrupt at 100Hz. */
  asm ("xio    %0,ota" :: "r" (-1000)); 

  /* and enable interrupts ... */
  asm ("xio    r0,enbl");

  /* Set interrupt masks. We enable power down, machine error and timer A only */
  set_mk (_intmask (INTPWRDWN) |
          _intmask (INTMACHERR) |
          _intmask (INTTIMERA));

}

