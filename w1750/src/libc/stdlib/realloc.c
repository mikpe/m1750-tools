/*
 * ANSI Standard C: 7.10.3.4
 * 
 * #include <stdlib.h>
 * void *realloc (void *ptr, size_t size);
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
 * $Log: realloc.c,v $
 * Revision 1.2  1997/05/12 13:53:08  nettleto
 * Major rewrite
 *
 * Revision 1.1  1997/05/09 16:55:42  nettleto
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
struct header
  {
    size_t size;                /* size of data space in 1750 words */
    struct header *next;
    /* and size chars of data space */
  };

#define MAGIC 0xBEAD


void *
realloc (void *ap, size_t nbytes)
{
  struct header *b;
  char *res;
  size_t old_size;

  if (ap == NULL)
    return malloc (nbytes);

  b = (struct header *) ((unsigned char *) ap - sizeof (struct header));
  old_size = b->size;

  if ((res = malloc (nbytes)) == NULL)
    return (NULL);

  memcpy (res, ap, (old_size < nbytes? old_size: nbytes));
  free (ap);

  return res;
}


