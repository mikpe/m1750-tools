/*
 * pthread_create - POSIX 16.2.2.
 *  
 * #include <pthread.h>
 * int pthread_create (
 *    pthread_t * thread,
 *    pthread_attr_t * attr,
 *    pthread_func_t func,
 *    any_t arg);
 *  
 * Copyright (C) 1992, 1993, 1994, 1995, 1996 the Florida State University
 * GCC-1750 changes Copyright (c) 1997, Chris Nettleton Software
 * 
 * This file is part of the GCC-1750 library. It is based on Pthreads
 * distributed by Florida State University and contains modifications for
 * GCC-1750 made under European Space Agency contract 11935/96/NL/JG.
 * 
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation (version 2).
 * 
 * This file is distributed "AS IS" in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with Pthreads; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * $Log: pthread_create.c,v $
 * Revision 1.3  1997/08/08 17:13:32  nettleto
 * pthread_body needs long call to thread body fo expanded
 * memory even though we only use a 16-bit address.
 *
 * Revision 1.2  1997/07/18 16:28:15  nettleto
 * thread id removed
 *
 * Revision 1.1  1997/07/17 14:12:32  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * pthread_terminate - internal.
 * terminate thread: call cleanup handlers and
 * destructor functions, allow no more signals, dequeue from ready,
 * and switch context
 */
void
pthread_terminate (
		    void)
{
  register pthread_t p, t = mac_pthread_self ();
  register pthread_key_t i;
  register cleanup_t new;

  /*
   * call cleanup handlers in LIFO
   */
  for (new = t->cleanup_top; new; new = new->next)
    (new->func) (new->arg);

  /*
   * call destructor functions for data keys (if both are defined)
   */
  for (i = 0; i < n_keys; i++)
    if (t->key[i] && key_destructor[i])
      (key_destructor[i]) (t->key[i]);

  /*
   * dequeue thread and schedule someone else
   */

  SET_KERNEL_FLAG;
  if (t->state & (T_SYNCTIMER | T_ASYNCTIMER))
    {
      pthread_cancel_timed_sigwait (t, FALSE, FALSE);
    }
  t->state &= ~T_RUNNING;
  t->state |= T_RETURNED;

  /*
   * Terminating thread has to be detached if anyone tries to join
   * but the memory is not freed until the dispatcher is called.
   * This is required by pthread_join().
   * The result is copied into the TCB of the joining threads to
   * allow the memory of the current thread to be reclaimed before
   * the joining thread accesses the result.
   */
  if (t->joinq.head)
    {
      t->state |= T_DETACHED;
      for (p = t->joinq.head; p; p = p->next_in_primary_q)
	p->result = t->result;
      pthread_q_wakeup_all (&t->joinq);
    }

  /*
   * The last threads switches off the light and calls UNIX exit
   */
  if (--n_pthreads)
    {
      pthread_q_deq (&ready, t);
      CLEAR_KERNEL_FLAG;
    }
  else
    {
      exit (EXIT_SUCCESS);
    }
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * pthread_body - internal.
 * base of the pthreads implementation.
 * Procedure invoked at the base of each pthread (as a wrapper).
 */
void
pthread_body (
	       void)
{
  pthread_t t = mac_pthread_self ();

  CLEAR_KERNEL_FLAG;

  /* long call needed because the body does a long return */
#ifdef MMU
  asm ("lr     r0,%0
        xorr   r11,r11
        lr     r12,%1
        bex    0"     :: "r" (t->arg), "r" (t->func)
                      : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
                        "r8", "r9", "r10", "r11", "r12", "r13");
  asm ("st     r0,%0" : "=m" (t->result));

#else
  t->result = (*(t->func)) (t->arg);
#endif

  pthread_terminate ();
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * Create a new thread of execution. the thread
 * structure and a queue and bind them together.
 * The completely created pthread is then put on the active list before
 * it is allowed to execute. Caution: The current implementation uses
 * pointers to the thread structure as thread ids. If a thread is not
 * valid it's pointer becomes a dangling reference but may still be
 * used for thread operations. It's up to the user to make sure he
 * never uses dangling thread ids. If, for example, the created thread
 * has a higher priority than the caller of pthread_create() and the
 * created thread does not block, the caller will suspend until the
 * child has terminated and receives a DANGLING REFERENCE as the
 * thread id in the return value of pthread_create()! This
 * implementation could be enhanced by modifying the type pthread_t of
 * a pointer to the thread control block and a serial number which had
 * to be compared with the serial number in the thread control block
 * for each thread operation. Also, threads had to be allocated from a
 * fixed-size thread control pool or the serial number would become a
 * "magic number".
 */
int
pthread_create (
		 pthread_t * thread,
		 pthread_attr_t * attr,
		 pthread_func_t func,
		 any_t arg)
{
  register pthread_t t;
  pthread_t parent_t = mac_pthread_self ();

  if (!attr)
    attr = &pthread_attr_default;

  if (!attr->flags || thread == NULL)
    {
      set_errno (EINVAL);
      return (-1);
    }

  t = (pthread_t) calloc (1, sizeof (struct pthread));
  if (t == NO_PTHREAD)
    {
      set_errno (EAGAIN);
      return (-1);
    }
  t->func = func;
  t->arg = arg;
  t->state = T_RUNNING | T_CONTROLLED;

  t->attr.stacksize = attr->stacksize;
  t->attr.flags = attr->flags;
  if (attr->inheritsched == PTHREAD_DEFAULT_SCHED)
    {
      t->attr.inheritsched = attr->inheritsched;
      t->attr.sched = attr->sched;
      t->attr.prio = attr->prio;
    }
  else
    {
      t->attr.inheritsched = parent_t->attr.inheritsched;
      t->attr.sched = parent_t->attr.sched;
      t->attr.prio = parent_t->attr.prio;
    }
  pthread_queue_init (&t->joinq);
  if (attr->detachstate)
    t->state |= T_DETACHED;
  SET_KERNEL_FLAG;
  ++n_pthreads;

  /*
   * Allocate stack space on heap for a thread
   * Stacks are deallocated when the thread has returned and is detached.
   */
  t->stack_base = (char *) malloc (t->attr.stacksize);
  if (t->stack_base == NULL)
    {
      CLEAR_KERNEL_FLAG;
      set_errno (ENOMEM);
      return (-1);
    }

  /*
   * Associate stack space with thread
   */
  /* 1750-specific code to initialize a thread's stack */
  {
    struct _iframe *fm = (struct _iframe *)
        (t->stack_base + t->attr.stacksize - sizeof (struct _iframe));
    unsigned mk;
    int i;

    /* get the current interrupt mask */
    asm ("xio    %0,rmk":"=r" (mk));

    fm->magic = IMAGIC;
    fm->sl = t->stack_base;
    fm->mk = mk;
    fm->sw = 0;			/* may need AS etc for EM */
    fm->ic = (short) pthread_body;

    for (i = 0; i <= 14; i++)
      fm->regs[i] = 0;

    t->sp = (void *) fm;
  }
  t->errno = errno;

  pthread_q_enq (&ready, t);
  CLEAR_KERNEL_FLAG;

  *thread = t;

  return (0);
}
