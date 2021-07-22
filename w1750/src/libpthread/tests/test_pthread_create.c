/*
 * test-create.c - tests creation of one thread
 *
 * Copyright (c) 1997 Chris Nettleton Software
 *
 * This file is part of the GCC-1750 test suite. It was developed under 
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
 * $Log: test_pthread_create.c,v $
 * Revision 1.1  1997/07/27 10:29:13  nettleto
 * Initial revision
 *
 */

#include <pthread.h>


void *
new_thread (void *arg)
{
  int i;

  comment ("New thread was passed arg address %p", arg);
  if (arg != (void *)0xbeef)
    failed ("arg incorrect");

  comment ("New thread stack at %p", &i);

  pthread_exit ((void *)0xabcd);
}

int
main ()
{
  pthread_t thread;
  int i;
  int ans;
  int s;

  pthread_init ();

  test ("test_pthread_create", "create one thread");

  comment ("Original thread stack at %p", &i);

  if (ans = pthread_create (&thread, NULL, new_thread, (void *) 0xdeadbeef))
    {
      failed ("Error: creating new thread, ans = %d", ans);
    }

  pthread_join (thread, (void *) &s);

  if (s != 0xabcd)
    failed ("exit code wrong");

  result ();
}
