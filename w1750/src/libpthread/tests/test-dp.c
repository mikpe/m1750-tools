/*
 * test-dp.c - sanity test based on the dining philosophers problem
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
 * $Log: test-dp.c,v $
 * Revision 1.2  1997/08/11 14:18:04  nettleto
 * Fixed stack size
 *
 * Revision 1.1  1997/07/27 10:29:12  nettleto
 * Initial revision
 *
 */

#include <pthread.h>
#include <report.h>
#include <stddef.h>
#include <math.h>

/*
 * This is the dining philophers problem expressed using POSIX Threads.
 * There are N philosophers, who are only prevented from deadlock
 * by having a limit on the number of philosophers in the dining
 * room of N - 1.
 */

/* define number of philosophers */
#define N 4

static pthread_mutex_t room;
static pthread_cond_t room_cond;
static int pcnt;  /* number of phils in the room */
static int fcnt;  /* number of times the room was full */

static pthread_mutex_t forks [N];
static int eat_counts [N];


struct
{
  int x, y, z;
} key = { 10001, 20001, 30001 };


double
ran ()
{
  double w;

  key.x = 171 * (key.x % 177) - 2 * (key.x / 177);
  if ( key.x < 0 ) key.x += 30269;
  key.y = 172 * (key.y % 176) - 35 * (key.y / 176);
  if ( key.y < 0 ) key.y += 30307;
  key.z = 170 * (key.z % 178) - 63 * (key.z / 178);
  if ( key.z < 0 ) key.z += 30323;
  w = (double) (key.x) / 30269.0
    + (double) (key.y) / 30307.0
    + (double) (key.z) / 30323.0;
  while ( w >= 1.0 ) w -= 1.0;

  return w;
}


/*
 * Function to delay the calling thread by the given number of
 * seconds. This is equivalent to the Ada delay statement.
 */
void
delay (double s)
{
  struct timespec rqtp, rmtp;
  double i;
  double nsec = modf (s, &i) * 1.0e9;
  int ans;

  rqtp.tv_sec = (long)i; 
  rqtp.tv_nsec = (long)nsec;

  ans = nanosleep (&rqtp, &rmtp);
  if (ans < 0)
    failed ("nanosleep returned %d, sec = %ld, nsec = %ld", 
             ans, rmtp.tv_sec, rmtp.tv_nsec);
}


static void
enter (int n)
{
  pthread_mutex_lock (&room);

  while (pcnt >= N - 1)
    {
      fcnt++;
      comment ("p%d waiting to enter room", n);
      pthread_cond_wait (&room_cond, &room);
      comment ("p%d trying to enter room again", n);
    }

  pcnt++;
  pthread_mutex_unlock (&room);
}


static void
leave (int n)
{
  pthread_mutex_lock (&room);

  comment ("p%d leaving room", n);
  pcnt--;
  pthread_cond_signal (&room_cond);

  pthread_mutex_unlock (&room);
}


static void *
philosopher (void *arg)
{
  int n = (int)arg;
  int n1 = n - 1;
  int cnt;

  pthread_mutex_t *left, *right;

  comment ("philosopher %d started", arg);

  left = &forks [n1];
  right = &forks [(n == N? 0: n)]; 
 
  for (cnt = 1; cnt <= 10; cnt++)
    {
      /* enter room */
      enter (n);

      /* pickup left fork */
      pthread_mutex_lock (left);
      comment ("p%d got left fork", n);

      /* pickup right fork */
      pthread_mutex_lock (right);
      comment ("p%d got right fork", n);

      /* now eat */
      comment ("p%d eat %d", n, cnt);
      delay (ran ());

      eat_counts [n - 1]++;

      /* put down left fork */
      pthread_mutex_unlock (left);
      comment ("p%d put down left fork", n);

      /* put down right fork */
      pthread_mutex_unlock (right);
      comment ("p%d put down right fork", n);

      /* leave room */
      leave (n);

      /* wait outside */
      delay (ran ());
    }

  comment ("philosopher %d finished", arg);
}


int
main ()
{
  int i;
  pthread_t phils [N];
  int status;
  pthread_attr_t attr;

  test ("dp", "pthreads dining philosophers");

  pthread_init ();

  pthread_attr_init (&attr);
  pthread_attr_setstacksize (&attr, 4096);

  pthread_mutex_init (&room, NULL);
  pthread_cond_init (&room_cond, NULL);
  pcnt = 0;
  fcnt = 0;

  for (i = 0; i < N; i++)
    pthread_mutex_init (&forks [i], NULL);

  for (i = 0; i < N; i++)
    pthread_create (&phils [i], &attr, philosopher, (void *)(i + 1));

  for (i = 0; i < N; i++)
    pthread_join (phils [i], (void *)&status);

  for (i = 0; i < N; i++)
    if (eat_counts [i] != 10)
      failed ("eat count %d = %d", i, eat_counts [i]);

  comment ("fcnt = %d", fcnt);
  result ();

  pthread_exit (NULL);
}
