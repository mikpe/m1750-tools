/*
 * pthead.h
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
 * $Log: pthread.h,v $
 * Revision 1.2  1997/07/18 16:27:04  nettleto
 * pthread fields added to support intwait
 *
 * Revision 1.1  1997/07/17 18:23:31  nettleto
 * Initial revision
 *
 */

#ifndef _pthread_pthread_h
#define _pthread_pthread_h

/*********************************/
/* Pthreads Interface Definition */
/*********************************/

#ifndef _POSIX_THREADS

#include <stdlib.h>
#include <time.h>
#include <errno.h>

/* pthread limits */
#define _POSIX_DATAKEYS_MAX 8

/* sched attribute values */
#define SCHED_FIFO  0

/* inheritsched attribute values */
#define PTHREAD_INHERIT_SCHED 0
#define PTHREAD_DEFAULT_SCHED 1

/* Allow variable stack sizes */
#ifndef _POSIX_THREAD_ATTR_STACKSIZE
#define _POSIX_THREAD_ATTR_STACKSIZE
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


/*************************/
/*    Timer Functions    */
/*************************/

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0

struct timespec {
  time_t tv_sec;
  long   tv_nsec;
};
#endif /* CLOCK_REALTIME */

extern int nanosleep      (const struct timespec *__rqtp,
                           struct timespec *__rmtp);
extern unsigned int sleep (unsigned int __seconds);
extern int clock_gettime  (int __clock_id,
                           struct timespec *__tp);


/***********************/
/*    Mutex Objects    */
/***********************/

typedef struct pthread_queue {
  struct pthread *head;
  struct pthread *tail;
} *pthread_queue_t;

typedef struct {
  struct pthread_queue queue;
  char lock;
  struct pthread *owner;
  int flags;
} pthread_mutex_t;

#define PTHREAD_MUTEX_INITIALIZER {{NULL,NULL},FALSE,NULL,TRUE}

typedef struct {
  int flags;
} pthread_mutexattr_t;


/*************************/
/*    Mutex Functions    */
/*************************/

extern int pthread_mutex_lock    (pthread_mutex_t *__mutex);
extern int pthread_mutex_trylock (pthread_mutex_t *__mutex);
extern int pthread_mutex_unlock  (pthread_mutex_t *__mutex);
extern int pthread_mutex_init    (pthread_mutex_t *__mutex,
                                  pthread_mutexattr_t *__attr);
extern int pthread_mutex_destroy (pthread_mutex_t *__mutex);


/**********************/
/*    Once Objects    */
/**********************/

typedef struct {
  short init;
  short exec;
  pthread_mutex_t mutex;
} pthread_once_t;

#define PTHREAD_ONCE_INIT {FALSE,FALSE,0, };

extern int pthread_once (pthread_once_t *__once_c,
                         void (*__func) (void));


/*****************************/
/*    Condition Variables    */
/*****************************/

typedef struct {
  struct pthread_queue queue;
  int flags;
  int waiters;
  pthread_mutex_t *mutex;
} pthread_cond_t;

#define PTHREAD_COND_INITIALIZER {{NULL,NULL},TRUE,0,NULL}

typedef struct {
  int flags;
} pthread_condattr_t;


/*****************************/
/*    Condition Functions    */
/*****************************/

extern int pthread_cond_destroy   (pthread_cond_t *__cond);
extern int pthread_cond_init      (pthread_cond_t *__cond,
                                   pthread_condattr_t *__attr);
extern int pthread_cond_wait      (pthread_cond_t *__cond,
                                   pthread_mutex_t *__mutex);
extern int pthread_cond_timedwait (pthread_cond_t *__cond,
                                   pthread_mutex_t *__mutex,
                                   struct timespec *__timeout);
extern int pthread_cond_signal    (pthread_cond_t *__cond);
extern int pthread_cond_broadcast (pthread_cond_t *__cond);


/************************/
/*    Thread Objects    */
/************************/

typedef void *any_t;
typedef any_t (*pthread_func_t) (any_t __arg);

typedef struct {
  int flags;
  int stacksize;
  int inheritsched;
  int detachstate;
  int sched;
  int prio;                      /* (Active) priority of Thread */
} pthread_attr_t;

struct sched_param {
  int sched_priority;
};

typedef int pthread_key_t;

struct cleanup {
  void (*func)();
  any_t arg;
  struct cleanup *next;
};

typedef struct cleanup *cleanup_t;

typedef struct pthread {
  void *sp;                          /* stack ptr at context switch    */
  volatile int errno;                /* thread-specific errno          */
  volatile int ret;                  /* return value (EINTR --> -1)    */
  char *stack_base;                  /* bottom of run-time stack       */
  int state;                         /* thread state                   */
  struct pthread *next_in_primary_q; /* links for queues               */
  struct pthread *next_in_timer_q;   /* links for queues               */
  struct pthread_queue joinq;        /* queue to await termination     */
  pthread_cond_t *cond;              /* cond var. if in cond_wait      */
  pthread_queue_t queue;             /* primary queue thread is in     */
  pthread_func_t func;               /* function to call on activation */
  any_t arg;                         /* argument to above function     */
  any_t result;                      /* return value of above function */
  any_t key[_POSIX_DATAKEYS_MAX];    /* thread specific data           */
  cleanup_t cleanup_top;             /* stack of cleanup handlers      */
  pthread_attr_t attr;               /* attributes                     */
  struct timespec tp;                /* wake-up time                   */
  int intwait_mask;                  /* interrupts being waited for    */
  int intwait_code;                  /* interrupt received             */
} *pthread_t;


/******************************/
/* Thread Attribute Functions */
/******************************/

extern int pthread_attr_init            (pthread_attr_t *__attr);
extern int pthread_attr_destroy         (pthread_attr_t *__attr);
extern int pthread_attr_setstacksize    (pthread_attr_t *__attr,
                                         size_t __stacksize);
extern int pthread_attr_getstacksize    (pthread_attr_t *__attr,
                                         size_t *__stacksize);
extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
                                         int __inherit);
extern int pthread_attr_setschedpolicy  (pthread_attr_t *__attr,
                                         int __policy);
extern int pthread_attr_setschedparam   (pthread_attr_t *__attr,
                                         struct sched_param *__param);
extern int pthread_attr_getinheritsched (pthread_attr_t *__attr,
                                         int *__inherit);
extern int pthread_attr_getschedpolicy  (pthread_attr_t *__attr,
                                         int *__policy);
extern int pthread_attr_getschedparam   (pthread_attr_t *__attr,
                                         struct sched_param *__param);
extern int pthread_attr_setdetachstate  (pthread_attr_t *__attr,
                                         int __detachstate);
extern int pthread_attr_getdetachstate  (pthread_attr_t *__attr,
                                         int *__detachstate);


/**************************/
/*    Thread Functions    */
/**************************/

extern pthread_t pthread_self        (void);
extern void pthread_init             (void);
extern int pthread_create            (pthread_t *__thread,
                                      pthread_attr_t *__attr,
                                      pthread_func_t __func,
                                      any_t __arg);
extern int pthread_equal             (pthread_t __t1,
                                      pthread_t __t2);
extern int pthread_detach            (pthread_t *__thread);
extern int pthread_join              (pthread_t __thread,
                                      any_t *__status);
extern int sched_yield               (void);
extern void pthread_exit             (any_t __status);
extern int pthread_getschedparam     (pthread_t __thread,
                                      int *__policy,
                                      struct sched_param *__param);
extern int pthread_setschedparam     (pthread_t __thread,
                                      int __policy,
                                      struct sched_param *__param);

extern int pthread_key_create        (pthread_key_t *__key,
                                      void (*__func) (any_t __value));
extern int pthread_setspecific       (pthread_key_t __key,
                                      any_t __value);
extern any_t pthread_getspecific     (pthread_key_t __key);

extern int pthread_cleanup_push_body (void (*__func) (any_t __value),
                                      any_t __arg,
                                      cleanup_t __new);
extern int pthread_cleanup_pop_body  (int __execute);

#define pthread_cleanup_push(func, arg) \
{                                        \
  struct cleanup new;                    \
  pthread_cleanup_push_body (func, arg, &new);

#define pthread_cleanup_pop(execute) \
  pthread_cleanup_pop_body (execute); \
}

extern int sched_get_priority_max    (int __policy);
extern int sched_get_priority_min    (int __policy);


#endif _POSIX_THREADS

#endif !_pthread_pthread_h
