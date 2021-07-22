/*
 * ANSI Standard C: 7.10.3.2
 * 
 * #include <stdlib.h>
 * void free (void *ptr);
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
 * $Log: free.c,v $
 * Revision 1.1  1997/05/12 13:35:04  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

/*
 * malloc and free maintain a list of blocks that have been allocated then
 * freed. Sometimes a newly freed block will occupy a place in memory next to
 * a block that is already in the list. In this case the newly freed block
 * is not added to the list; rather the adjacent block is extended.
 */
extern struct header
  {
    size_t size;		/* size of data space in 1750 words */
    struct header *next;
    /* and size chars of data space */
  }
 *_mfirst, *_mlast;

#define MAGIC 0xBEAD


/*
 * Return a block of memory to the free block list, but try merging it
 * with any adjacent free blocks _mfirst. TODO: case where freed block
 * can be merged with upper lower adjacent blocks.
 */
void
free (void *ptr)
{
  if (ptr != NULL)
    {
      struct header *b =
      (struct header *) ((unsigned char *) ptr - sizeof (struct header));

      /* ignore blocks returned without the magic number */
      if (b->next != (struct header *)MAGIC)
        return;

      if (_mfirst == NULL)
	{
	  b->next = NULL;
	  _mfirst = b;
	  _mlast = b;
	}
      else
	{
	  /* look for adjacent block in free list */
	  struct header **b2 = &_mfirst;
	  struct header *bf = _mfirst;
	  unsigned char *pb = (unsigned char *) b;

	  while (bf != NULL)
	    {
	      if ((unsigned char *) bf + bf->size + sizeof (struct header) == pb)
		{
		  /* freed block goes on end of this one, just increase
		     size by the size of the freed block */
		  bf->size += sizeof (struct header) + b->size;
		  return;
		}
	      else if (pb + sizeof (struct header) + b->size == (unsigned char *) bf)
		{
		  /* put freed block in free block chain, and increase 
		     its size by the size of the block we have just found 
		     in the free block chain */
		  b->size += sizeof (struct header) + bf->size;
		  b->next = bf->next;
		  *b2 = b;
		  return;
		}
	      b2 = &bf->next;
	      bf = bf->next;
	    }

	  /* no adjacent block found, add to end of free list */
	  b->next = _mlast;
	  _mlast = b;
	}
    }
}

