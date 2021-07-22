/* ==== test_pthread_join.c =================================================
 * Copyright (c) 1993 by Chris Provenzano, proven@athena.mit.edu
 *
 * Description : Test pthread_join(). Run this after test_create()
 *
 *  1.23 94/05/04 proven
 *      -Started coding this file.
 * 
 *  May 1996 Chris Nettleton
 *      -Updated for GCC-1750
 */

#define PTHREAD_KERNEL
#include <pthread.h>

#include <report.h>


/* This thread yields so the creator has a live thread to wait on */
void *
new_thread_1 (void *new_buf)
{
  int i;

  sprintf ((char *) new_buf, "New thread %%d stack at %x", &i);
  sched_yield ();
  return (new_buf);
}

/* This thread doesn't yield so the creator has a dead thread to wait on */
void *
new_thread_2 (void *new_buf)
{
  int i;

  sprintf ((char *) new_buf, "New thread %%d stack at %x", &i);
  return (new_buf);
}

main ()
{
  char buf1[256];
  char buf2[256];
  char *status;
  pthread_t thread;
  int debug = 1;
  int i = 0;

  memset (buf1, 256, 0);
  memset (buf2, 256, 0);

  pthread_init ();

  test ("test_pthread_join", "POSIX Threads test");

  comment ("Original thread stack at %x", &i);

  if (pthread_create (&thread, NULL, new_thread_1, (void *) buf1) == 0)
    {
      if (pthread_join (thread, (void **) (&status)) == 0)
	{
	  if (debug)
	    {
	      comment (status, ++i);
	    }
	}
      else
	{
	  comment ("ERROR: Joining with new thread #1.");
	  failed ("FAILED: test_pthread_join");
          goto end;
	}
    }
  else
    {
      comment ("ERROR: 	Creating new thread #1");
      failed ("FAILED: test_pthread_join");
      goto end;
    }


  /* Now have the created thread finishing before the join. */
  if (pthread_create (&thread, NULL, new_thread_2, (void *) buf2) == 0)
    {
      sched_yield ();
      if (pthread_join (thread, (void **) (&status)) == 0)
	{
	  if (debug)
	    {
	      comment (status, ++i);
	    }
	}
      else
	{
	  comment ("ERROR: Joining with new thread #2.");
	  failed ("FAILED: test_pthread_join");
	}
    }
  else
    {
      comment ("ERROR: 	Creating new thread #2");
      failed ("FAILED: test_pthread_join");
    }

end:
  result ();

  pthread_exit (NULL);
}

