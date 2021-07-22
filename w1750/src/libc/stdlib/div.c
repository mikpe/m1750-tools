/*
 * ANSI Standard C: 7.10.6.2
 * 
 * #include <stdlib.h>
 * div_t div (int _numer, int _denom);
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
 * $Log: div.c,v $
 * Revision 1.1  1997/05/09 16:55:38  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

div_t
div (int num, int denom)
{
  div_t ans;

  ans.quot = num / denom;
  ans.rem = num % denom;

  if (num >= 0 && ans.rem < 0) 
    {
      ans.quot++;
      ans.rem -= denom;
    }

  return ans;
}
