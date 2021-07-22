/*
 * pthread_internals.h
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
 * $Log: pthread_internals.h,v $
 * Revision 1.4  1997/08/11 08:22:34  nettleto
 * Added code set and clear _enbl. This allows the
 * code between SET_KERNEL_FLAG and CLEAR_KERNEL_FLAG to run
 * using the BEX based expanded memory machinsm.
 *
 * Revision 1.3  1997/07/18 16:33:05  nettleto
 * Added a queue for threads in intwait
 *
 * Revision 1.2  1997/07/17 18:24:16  nettleto
 * Increased default stack size to 102 words
 *
 * Revision 1.1  1997/07/17 09:43:17  nettleto
 * Initial revision
 *
 */

#ifndef _pthread_pthread_internals_h
#define _pthread_pthread_internals_h

/********************************/
/* Pthreads Interface Internals */
/********************************/

#include <pthread.h>
#include <intrrpt.h>

/* Program Specific Constants */
#define MAX_PRIORITY        100
#define MIN_PRIORITY        0
#define DEFAULT_PRIORITY    MIN_PRIORITY
#define DEFAULT_STACKSIZE   1024
#define MAX_STACKSIZE       32767
#define MAIN_STACKSIZE      2048


/****************************/
/*    Thread Status Bits    */
/****************************/

#define T_MAIN          0x1
#define T_RETURNED      0x2
#define T_DETACHED      0x4
#define T_RUNNING       0x8
#define T_BLOCKED       0x10
#define T_CONDTIMER     0x20
#define T_SIGWAIT       0x40
#define T_SYNCTIMER     0x80
#define T_SIGSUSPEND    0x100
#define T_CONTROLLED    0x200
#define T_INTR_POINT    0x400
#define T_ASYNCTIMER    0x800
#define T_LOCKED        0x1000
#define T_IO_OVER       0x2000


/*********************/
/*    Time Macros    */
/*********************/

#define ABS_TIME  0x01
#define REL_TIME  0x02

/* MINUS_NTIME only works if src1 > src2 */
#define MINUS_NTIME(dst, src1, src2) \
  { \
    if ((src2).tv_nsec > (src1).tv_nsec) { \
      (dst).tv_sec = (src1).tv_sec - (src2).tv_sec - 1L; \
      (dst).tv_nsec = ((src1).tv_nsec - (src2).tv_nsec) + 1000000000L; \
    } \
    else { \
      (dst).tv_sec = (src1).tv_sec - (src2).tv_sec; \
      (dst).tv_nsec = (src1).tv_nsec - (src2).tv_nsec; \
    } \
  }

#define PLUS_NTIME(dst, src1, src2) \
  { \
    if (1000000000L - (src2).tv_nsec <= (src1).tv_nsec) { \
      (dst).tv_sec = (src1).tv_sec + (src2).tv_sec + 1L; \
      (dst).tv_nsec = -1000000000L + (src1).tv_nsec + (src2).tv_nsec; \
    } \
    else { \
      (dst).tv_sec = (src1).tv_sec + (src2).tv_sec; \
      (dst).tv_nsec = (src1).tv_nsec + (src2).tv_nsec; \
    } \
  }

#define GT_NTIME(t1, t2) \
  (t1.tv_sec > t2.tv_sec || \
   (t1.tv_sec == t2.tv_sec && \
    t1.tv_nsec > t2.tv_nsec))

#define GTEQ_NTIME(t1, t2) \
  ((t1).tv_sec > (t2).tv_sec || \
   ((t1).tv_sec == (t2).tv_sec && \
    (t1).tv_nsec >= (t2).tv_nsec))

#define LE0_NTIME(t1) \
  ((t1).tv_sec < 0L || \
   ((t1).tv_sec == 0L && \
    (t1).tv_nsec <= 0L))


/*********************/
/*    Timer Queue    */
/*********************/

#define NO_TIMER_QUEUE ((pthread_t) NULL)

#define pthread_timer_queue_init \
  (pthread_timer = NO_TIMER_QUEUE)

extern int pthread_timed_sigwait         (pthread_t __p,
                                          struct timespec *__timeout,
                                          int __mode);
extern void pthread_cancel_timed_sigwait (pthread_t __first_p,
                                          int __signaled,
                                          int __activate);


/***********************/
/*    Primary Queue    */
/***********************/

#define NO_QUEUE      ((pthread_queue_t) NULL)
#define NO_QUEUE_ITEM ((struct pthread *) NULL)

#define pthread_queue_init(q) \
  ((q)->head = (q)->tail = NO_QUEUE_ITEM)

extern void pthread_q_enq           (pthread_queue_t __q,
                                     pthread_t __t);
extern void pthread_q_deq           (pthread_queue_t __q,
                                     pthread_t __t);
extern pthread_t pthread_q_deq_head (pthread_queue_t __q);
extern void pthread_q_sleep_thread  (pthread_queue_t __q,
                                     pthread_t __p);
extern void pthread_q_sleep         (pthread_queue_t __q);
extern void pthread_q_wakeup_thread (pthread_queue_t __q,
                                     pthread_t __p);
extern void pthread_q_wakeup_all    (pthread_queue_t __q);

#define NO_MUTEX     ((pthread_mutex_t *)0)
#define NO_COND      ((pthread_cond_t *)0)
#define NO_PTHREAD   ((pthread_t) 0)
#define NO_ATTRIBUTE ((pthread_attr_t *)0)


/*********************/
/*    Kernel Data    */
/*********************/

typedef struct kernel {
  pthread_t k_pthread_self;              /* thread that is currently running */
  volatile int k_state_change;           /* dispatcher state (run q/signals) */
  volatile struct pthread_queue k_ready; /* ready queue                      */
  volatile struct pthread_queue k_waitq; /* intwait queue                    */
  volatile struct timespec k_timeofday;  /* Time of Day                      */
  pthread_t k_pthread_timer;             /* timer queue                      */
  volatile int k_n_pthreads;
  volatile pthread_key_t k_n_keys;
  void (*k_key_destructor[_POSIX_DATAKEYS_MAX])();
  pthread_attr_t k_pthread_attr_default;
} kernel_t;

#ifdef PTHREAD_KERNEL
kernel_t pthread_kern;
#else
extern kernel_t pthread_kern;
#endif


/***********************/
/*    Kernel Macros    */
/***********************/

/*
 * changed for speed-up and interface purposes -
 * pthread_self() is now a function,
 * but mac_pthread_self() is used internally
 */
#define mac_pthread_self()   pthread_kern.k_pthread_self
#define state_change         pthread_kern.k_state_change
#define ready                pthread_kern.k_ready
#define waitq                pthread_kern.k_waitq
#define timeofday            pthread_kern.k_timeofday
#define pthread_timer        pthread_kern.k_pthread_timer
#define n_pthreads           pthread_kern.k_n_pthreads
#define n_keys               pthread_kern.k_n_keys
#define key_destructor       pthread_kern.k_key_destructor
#define pthread_attr_default pthread_kern.k_pthread_attr_default

/*
 * Errno is mapped on process' _errno and swapped upon context switch
 */
#define set_errno(e) (errno = (e))
#define get_errno()  (errno)
extern int errno;


/****************************/
/*    Enter/Leave Kernel    */
/****************************/

#define DISABLE_INTERRUPTS asm ("xio r0,dsbl; stc 0,_enbl")
#define ENABLE_INTERRUPTS  asm ("xio r0,enbl; stc 1,_enbl")

#define SET_KERNEL_FLAG DISABLE_INTERRUPTS
#define CLEAR_KERNEL_FLAG pthread_clear_kernel_flag()

extern void pthread_switch_handler (int i);
extern void pthread_clear_kernel_flag (void);


/***************************/
/*    Mutex Lock/Unlock    */
/***************************/
/*
 * precondition: SET_KERNEL_FLAG
 * postcondition: call CLEAR_KERNEL_FLAG
 */

/*
 * locking mutex doesn't need test_and_set; it's protected by kernel flag
 */
#define mac_mutex_lock(mutex, p) \
  { \
    if (!mutex->lock) { \
      mutex->lock = TRUE; \
      mutex->owner = p; \
    } \
    else { \
      pthread_q_sleep_thread(&mutex->queue, p); \
    } \
  }

/*
 * third parameter is any C statement to be executed before pthread_q_wakeup()
 * preconditions: current thread owns the mutex, SET_KERNEL_FLAG
 * postcondition: call CLEAR_KERNEL_FLAG
 */
#define mac_mutex_unlock(mutex, p, cmd) \
  { \
    if (mutex->queue.head != NO_PTHREAD) { \
      cmd; \
      mutex->owner = mutex->queue.head; \
      pthread_q_wakeup(&mutex->queue); \
    } \
    else { \
      cmd; \
      mutex->owner = NO_PTHREAD; \
      mutex->lock = FALSE; \
    } \
  }


#endif /* !_pthread_pthread_internals_h */

