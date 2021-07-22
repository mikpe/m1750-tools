/***************************************************************************/
/*                                                                         */
/* Project   :        sim1750 -- Mil-Std-1750 Software Simulator           */
/*                                                                         */
/* Component :     phys_mem.c -- low-level implementation of memory        */
/*                                                                         */
/* Copyright :         (C) Daimler-Benz Aerospace AG, 1994-97              */
/*                                                                         */
/* Author    :      Oliver M. Kellogg, Dornier Satellite Systems,          */
/*                     Dept. RST13, D-81663 Munich, Germany.               */
/* Contact   :            oliver.kellogg@space.otn.dasa.de                 */
/*                                                                         */
/* Disclaimer:                                                             */
/*                                                                         */
/*  This program is free software; you can redistribute it and/or modify   */
/*  it under the terms of the GNU General Public License as published by   */
/*  the Free Software Foundation; either version 2 of the License, or      */
/*  (at your option) any later version.                                    */
/*                                                                         */
/*  This program is distributed in the hope that it will be useful,        */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/*  GNU General Public License for more details.                           */
/*                                                                         */
/*  You should have received a copy of the GNU General Public License      */
/*  along with this program; if not, write to the Free Software            */
/*  Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.   */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phys_mem.h"

/*
 * This is the page table. It is indexed by the 12 most significant 12 bits of 
 * the 24 bit word address. On the 1750A, only 1M word is supported.
 */
mem_t *mem[N_PAGES];

ulong allocated = 0;		/* statistic of total amount allocated by xalloc() */


void
init_mem ()
{
  int i;

  /* Free any memory already allocated. */
  for (i = 0; i < N_PAGES; i++)
    if (mem[i] != MNULL)
      {
	free (mem[i]);
      }

  /* zeroize mem */
  memset ((void *) mem, 0, sizeof mem);

  /* Allocate the first 4K word page (just for convenience). */
  if (mem[0] == MNULL)
    {
      mem[0] = (mem_t *) xalloc (1, sizeof (mem_t));
    }
}


bool
was_written (ulong phys_address)
{
  unsigned page = (unsigned) (phys_address >> 12);
  unsigned address = (unsigned) (phys_address & 0x0FFF);

  if (mem[page] == MNULL)
    return 0;
  return (mem[page]->was_written[address / 32] & (1L << (address % 32))) != 0;
}


void *
xalloc (ulong number, ulong size)
{
  void *retval;

  if ((retval = calloc (number, size)) != (void *) 0)
    allocated += number * size;	/* count up the `allocated' statistic */

  return (retval);
}
