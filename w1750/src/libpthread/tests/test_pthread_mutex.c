/* ==== test_pthread_cond.c =========================================
 * Copyright (c) 1993 by Chris Provenzano, proven@athena.mit.edu
 *
 * Description : Test pthread_cond(). Run this after test_create()
 *
 *  1.23 94/05/04 proven
 *      -Started coding this file.
 *
 *  May 19, 1997, Chris Nettleton
 *  Updated for GCC-1750
 */

#include <pthread.h>

#include <errno.h>
#include <report.h>

#define	OK     0
#define NOTOK  -1

volatile int contention_variable;

void *
thread_contention (void *arg)
{
  pthread_mutex_t *mutex = arg;

  if (pthread_mutex_lock (mutex))
    {
      failed ("pthread_mutex_lock() ERROR");
      pthread_exit (NULL);
    }

  if (contention_variable != 1)
    {
      failed ("contention_variable != 1 ERROR");
      pthread_exit (NULL);
    }
  contention_variable = 2;

  if (pthread_mutex_unlock (mutex))
    {
      failed ("pthread_mutex_unlock() ERROR");
      pthread_exit (NULL);
    }
  pthread_exit (NULL);
}

int 
test_contention_lock (pthread_mutex_t *mutex)
{
  pthread_t thread;

  comment ("test_contention_lock()");

  if (pthread_mutex_lock (mutex))
    {
      failed ("test_contention_lock, pthread_mutex_lock() ERROR");
      return (NOTOK);
    }
  contention_variable = 0;

  if (pthread_create (&thread, NULL, thread_contention, mutex))
    {
      failed ("test_contention_lock, pthread_create() FAILED");
      return (NOTOK);
    }

  sched_yield ();

  contention_variable = 1;

  if (pthread_mutex_unlock (mutex))
    {
      failed ("pthread_mutex_unlock() ERROR");
      return (NOTOK);
    }

  if (pthread_mutex_lock (mutex))
    {
      failed ("pthread_mutex_lock() ERROR");
      return (NOTOK);
    }

  if (contention_variable != 2)
    {
      failed ("contention_variable != 2 ERROR");
      return (NOTOK);
    }

  if (pthread_mutex_unlock (mutex))
    {
      failed ("pthread_mutex_unlock() ERROR");
      return (NOTOK);
    }

  return (OK);
}

int 
test_nocontention_lock (pthread_mutex_t *mutex)
{
  comment ("test_nocontention_lock()");

  if (pthread_mutex_lock (mutex))
    {
      failed ("pthread_mutex_lock() ERROR");
      return (NOTOK);
    }

  if (pthread_mutex_unlock (mutex))
    {
      failed ("pthread_mutex_unlock() ERROR");
      return (NOTOK);
    }

  return (OK);
}

int 
test_debug_double_lock (pthread_mutex_t *mutex)
{
  int ans;

  comment ("test_debug_double_lock()");

  ans = pthread_mutex_lock (mutex);
  if (ans != 0)
    {
      failed ("pthread_mutex_lock() ERROR, ans = %d", ans);
      return (NOTOK);
    }

  ans = pthread_mutex_lock (mutex);
  if (ans != -1 || errno != EDEADLK)
    {
      failed ("double lock error not detected ERROR, ans = %d, errno = %d", ans, errno);
      return (NOTOK);
    }

  ans = pthread_mutex_unlock (mutex);
  if (ans != 0)
    {
      failed ("pthread_mutex_unlock() ERROR, ans = %d", ans);
      return (NOTOK);
    }

  return (OK);
}

int 
test_debug_double_unlock (pthread_mutex_t *mutex)
{
  int ans;

  comment ("test_debug_double_unlock()");

  ans = pthread_mutex_lock (mutex);
  if (ans != 0)
    {
      failed ("pthread_mutex_lock() ERROR, ans = %d", ans);
      return (NOTOK);
    }

  ans = pthread_mutex_unlock (mutex);
  if (ans != 0)
    {
      failed ("pthread_mutex_unlock() ERROR, ans = %d", ans);
      return (NOTOK);
    }

  ans = pthread_mutex_unlock (mutex);
  if (ans != -1)
    {
      failed ("double unlock error not detected ERROR, ans = %d", ans);
      return (NOTOK);
    }
//  if (errno != EPERM)
  if (errno != EINVAL)
    {
      failed ("errno for double unlock error wrong ERROR, errno = %d", errno);
      return (NOTOK);
    }

  return (OK);
}

int 
test_nocontention_trylock (pthread_mutex_t *mutex)
{
  comment ("test_nocontention_trylock()");

  if (pthread_mutex_trylock (mutex))
    {
      failed ("pthread_mutex_trylock() ERROR");
      return (NOTOK);
    }

  if (pthread_mutex_unlock (mutex))
    {
      failed ("pthread_mutex_unlock() ERROR");
      return (NOTOK);
    }

  return (OK);
}

int 
test_mutex_static (void)
{
  pthread_mutex_t mutex_static;

  comment ("test_mutex_static()");

  if (pthread_mutex_init (&mutex_static, NULL))
    {
      failed ("test_mutex_static, pthread_mutex_init() ERROR");
      return (NOTOK);
    }

  if (test_nocontention_lock (&mutex_static) ||
      test_contention_lock (&mutex_static))
    {
      failed ("test_mutex_static, test_contention_lock");
      return (NOTOK);
    }

  return (OK);
}

int 
test_mutex_fast (void)
{
  pthread_mutex_t mutex_fast;

  comment ("test_mutex_fast()");

  if (pthread_mutex_init (&mutex_fast, NULL))
    {
      failed ("test_mutex_fast, pthread_mutex_init() ERROR");
      return (NOTOK);
    }

  if (test_nocontention_lock (&mutex_fast) ||
      test_contention_lock (&mutex_fast))
    {
      failed ("test_mutex_fast, test_nocontention_lock() ERROR");
      return (NOTOK);
    }

  if (pthread_mutex_destroy (&mutex_fast))
    {
      failed ("test_mutex_fast, pthread_mutex_destroy() ERROR");
      return (NOTOK);
    }

  return (OK);
}

int 
test_mutex_debug ()
{
  pthread_mutexattr_t mutex_debug_attr;
  pthread_mutex_t mutex_debug;

  comment ("test_mutex_debug()");

  if (pthread_mutex_init (&mutex_debug, NULL))
    {
      failed ("test_mutex_debug, pthread_mutex_init() ERROR");
      return (NOTOK);
    }

  if (test_nocontention_lock (&mutex_debug) ||
      test_contention_lock (&mutex_debug) ||
      test_debug_double_lock (&mutex_debug) ||
      test_debug_double_unlock (&mutex_debug))
    {
      failed ("test_mutex_debug, test_debug_double_lock etc() ERROR");
      return (NOTOK);
    }

  if (pthread_mutex_destroy (&mutex_debug))
    {
      failed ("test_mutex_debug, pthread_mutex_destroy() ERROR");
      return (NOTOK);
    }

  return (OK);
}

main ()
{
  pthread_init ();

  test ("test-mutex", "POSIX Threads mutex tests");

  test_mutex_static ();
  test_mutex_fast ();
  test_mutex_debug ();

  result ();
}


