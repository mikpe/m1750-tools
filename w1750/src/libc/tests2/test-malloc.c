/*
 * Test for ANSI Standard C: 7.10.3.3
 * 
 * #include <stdlib.h>
 * void *malloc (size_t size);
 * 
 * Copyright (c) 1996, Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute, 
 * and license this software and its documentation for any purpose, 
 * provided that existing copyright notices are retained in all copies 
 * and that this notice is included verbatim in any distributions. No 
 * written agreement, license, or royalty fee is required for any of the 
 * authorized uses. Modifications to this software may be copyrighted by 
 * their authors and need not follow the licensing terms described here, 
 * provided that the new terms are clearly indicated on the first page 
 * of each file where they apply. 
 *
 * $Log: test-malloc.c,v $
 * Revision 1.1  1997/08/01 16:05:38  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <stdlib.h>


extern unsigned char _end[];


/*
 * sanity check
 */
void
t1 ()
{
  unsigned long size;
  char *s;

  /* print size of heap */
  size = 0xffffL - (unsigned)_end;
  comment ("heap size = %ld words", size);

  s = (char *)malloc (100);

  free (s);
}


/*
 * Check that calloc returns a clear block 
 */
void
t2 ()
{
  int i;
  char *s;

  s = calloc (1, 100);

  for (i = 0; i < 100; i++)
    if (s [i] != 0)
      failed ("s1 [%d] != %x", i, s [i]);

  free (s);
}


/*
 * check blocks are distinct 
 */
void 
t3 ()
{
  int i;

  char *s1 = (char *)malloc (100);
  char *s2 = (char *)malloc (100);
  char *s3 = (char *)malloc (100);
  char *s4 = (char *)malloc (100);

  comment ("s1 = %p", s1);
  comment ("s2 = %p", s2);
  comment ("s3 = %p", s3);
  comment ("s4 = %p", s4);

  memset (s1, '1', 100);
  memset (s2, '2', 100);
  memset (s3, '3', 100);
  memset (s4, '4', 100);

  for (i = 0; i < 100; i++)
    if (s1 [i] != '1')
      failed ("s1 [%d] != '%c'", i, s1 [i]);

  for (i = 0; i < 100; i++)
    if (s2 [i] != '2')
      failed ("s2 [%d] != '%c'", i, s1 [i]);

  for (i = 0; i < 100; i++)
    if (s3 [i] != '3')
      failed ("s3 [%d] != '%c'", i, s1 [i]);

  for (i = 0; i < 100; i++)
    if (s4 [i] != '4')
      failed ("s4 [%d] != '%c'", i, s1 [i]);

  free (s1);
  free (s2);
  free (s3);
  free (s4);
}

void
t4 ()
{
  /* get largest power of 2 */

  unsigned long p2 = 1 << 14;
  int n = 14;

  while (p2 != 0)
    {
      void *m = malloc ((size_t)p2);

      if (m)
        {
          comment ("Largest block is 2**%d, at address %p", n, m);
          free (m);
          return;
        }
      p2 >>= 1;
      n--;
    }

  failed ("no block allocated at all");

}


void
t5 ()
{
  int i;
  int cnt1, cnt2;

  struct rec {
    struct rec *next;
  } *r, *fst, *lst;

  fst = NULL;
  lst = NULL;


  /* allocate as many blocks as possible */
  for (cnt1 = 0; ; cnt1++)
    {
      struct rec *r = (struct rec *)malloc (sizeof (struct rec));

      if (r == NULL)
        break;

      r->next = NULL;
      if (fst == NULL)
        fst = r;
      else
        lst->next = r;

      lst = r;
    }

  comment ("cnt1 = %d", cnt1);

  /* free the blocks */
  r = fst;
  while (r != NULL)
    {
      struct rec *next = r->next;

      free (r);
      r = next;
    }

  /* allocate as many blocks as possible */
  fst = NULL;
  for (cnt2 = 0; ; cnt2++)
    {
      struct rec *r = (struct rec *)malloc (sizeof (struct rec));

      if (r == NULL)
        break;

      r->next = NULL;
      if (fst == NULL)
        fst = r;
      else
        lst->next = r;

      lst = r;
    }

  /* free the blocks */
  r = fst;
  while (r != NULL)
    {
      struct rec *next = r->next;

      free (r);
      r = next;
    }

  if (cnt1 != cnt2)
    failed ("cnt1 = %d, cnt2 = %d", cnt1, cnt2);

}


/*
 * test realloc
 */
void
t6 ()
{
  int *s1;
  int *s2;
  int i;
  int *s3;
  int *s4;

  s1 = (int *)malloc (100 * sizeof (int));
  if (s1 == NULL)
    failed ("cannot malloc s1");

  s2 = (int *)malloc (1000 * sizeof (int));
  if (s2 == NULL)
    failed ("cannot malloc s2");

  /* initialise s1 and s2 */
  for (i = 0; i < 100; i++)
    s1 [i] = i;

  for (i = 0; i < 1000; i++)
    s2 [i] = 1000 - i;

  /* increase size of s1 */
  s3 = realloc (s1, 1000);

  /* check first 100 words */
  for (i = 0; i < 100; i++)
    if (s3 [i] != i)
      failed ("s3 [%d] != %d", i, s3 [i]);

  /* decrease size of s2 */
  s4 = realloc (s2, 100);

  /* check first 100 words */
  for (i = 0; i < 100; i++)
    if (s4 [i] != 1000 - i)
      failed ("s4 [%d] != %d", i, s4 [i]);

  free (s3);
  free (s4);
} 
  

/*
 * tests for zero size blocks
 */
void
t7 ()
{
  int i = 0;

  comment ("zero size blocks at %p %p", malloc(0), malloc (0));

  while (malloc (0) != NULL)
    i++;

  comment ("number of zero size blocks = %d", i);
}


void
main ()
{

  test ("test-malloc", "test for malloc, free etc");

  t1 ();
  t2 ();
  t3 ();
  t4 ();
  t5 ();
  t6 ();
  t7 ();

  result ();
}


