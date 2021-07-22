/*
 * ANSI Standard C: 7.10.3.3
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
 * $Log: malloc.c,v $
 * Revision 1.3  1997/07/17 18:54:26  nettleto
 * Removed leading underscore from sbrk.
 *
 * Revision 1.2  1997/05/12 13:52:19  nettleto
 * Complete rewrite
 *
 * Revision 1.1  1997/05/09 16:55:40  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>


/*
 * If a block is >= MIN larger than required, then it gets split
 * into a block that is just the right size, and another that is
 * large enough to be useful some other time. 
 */
#define MIN 4

#define MAGIC 0XBEAD


/*
 * malloc and free maintain a list of blocks that have been allocated then
 * freed. Sometimes a newly freed block will occupy a place in memory next to
 * a block that is already in the list. In this case the newly freed block
 * is not added to the list; rather the adjacent block is extended.
 */
struct header {
  size_t size;   /* size of data space in 1750 words */
  struct header *next;
  /* and size chars of data space */
} *_mfirst, *_mlast;



/*
 * Allocate n bytes of dynamic memory and return the start address
 */
void *
malloc (size_t n)
{
  struct header *b = NULL;

  /* First check if free list contains a block that is big enough. If
     so then use this block, splitting it into two if appropriate. */
  if (_mfirst != NULL)
    {
      if (_mfirst->size >= n)
        {
          /* use _mfirst block */
          if (_mfirst->size - n > MIN)
            {
              /* split block, allocate top half */
              unsigned char *next = 
                (unsigned char *)_mfirst + _mfirst->size + sizeof (struct header);
              size_t bsize = n + sizeof (struct header);

              b = (struct header *)(next - bsize);
              b->size = n;
              _mfirst->size -= bsize;
            }
          else
            {
              /* allocate whole block (bigger than asked for) */
              b = _mfirst;
              _mfirst = _mfirst->next;
              if (_mfirst == NULL)
                _mlast = NULL;
            }
        }
      else 
        {
          /* scan rest of list looking for a block that is big enough */
          struct header *b2 = _mfirst;
    
          b = _mfirst->next;
          while (b && b->size < n)
            {
              b2 = b;
              b = b->next;
            }
    
          if (b != NULL)
            {
              if (b->size - n > MIN)
                {
                  /* split block, allocate top half */
                  unsigned char *next = 
                    (unsigned char *)_mfirst + _mfirst->size + sizeof (struct header);
                  size_t bsize = n + sizeof (struct header);
    
                  b->size -= bsize;
                  b = (struct header *)(next - bsize);
                  b->size = n;
                }
              else
                {
                  /* use whole block, remove from list */
                  b2->next = b->next;
                }
            }
        }
    }

 
  if (b == NULL)
    {
      /* get some more memory from the heap */
      size_t size = n + sizeof (struct header);
      struct header *sbrk (size_t);

      b = sbrk (size);
      if (b == (struct header *)-1)
        return NULL;

      b->size = n;
    }

  b->next = (struct header *)MAGIC;
  return (void *)((unsigned char *)b + sizeof (struct header));
}

