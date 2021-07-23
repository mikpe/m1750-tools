#ifdef  L__addsi3
/*
 * gcc-1750/libgcc/__addsi3
 * 
 * long long
 * __addsi3 (long long, long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

long long
__addsi3 (long long x, long long y)
{
  asm volatile (
       "xorr   r12,r12   ! clear MS carry
!
! Add ls 16 bits, no carry in
!
        lr     r8,r3     ! get 16 bits of left
        lr     r10,r7    ! get 16 bits of right
        dsrl   r8,16     ! extend to 32 bits
        dsrl   r10,16    ! extend to 32 bits
        dar    r8,r10    ! do 16 bit unsigned add
        lr     r13,r8    ! save carry for next time
        lr     r3,r9     ! save sum
!
! Add next 16 bits, use carry in and generate carry out
!
        lr     r8,r2     ! get 16 bits of left
        lr     r10,r6    ! get 16 bits of right
        dsrl   r8,16     ! extend to 32 bits
        dsrl   r10,16    ! extend to 32 bits
        dar    r8,r10    ! do 16 bit unsigned add
        dar    r8,r12    ! add carry
        lr     r13,r8    ! save carry for next time
        lr     r2,r9     ! save sum
!
! Add next 16 bits, use carry in and generate carry out
!
        lr     r8,r1     ! get 16 bits of left
        lr     r10,r5    ! get 16 bits of right
        dsrl   r8,16     ! extend to 32 bits
        dsrl   r10,16    ! extend to 32 bits
        dar    r8,r10    ! do 16 bit unsigned add
        dar    r8,r12    ! add carry
        lr     r13,r8    ! save carry for next time
        lr     r1,r9     ! save sum
!
! Add MS 16 bit, use carry in, discard carry out
!
        lr     r8,r0     ! get 16 bits of left
        lr     r10,r4    ! get 16 bits of right
        dsrl   r8,16     ! extend to 32 bits
        dsrl   r10,16    ! extend to 32 bits
        dar    r8,r10    ! do 16 bit unsigned add
        dar    r8,r12    ! add carry
        lr     r0,r9     ! save sum
!");
}

#endif /* L__addsi3 */

#ifdef  L__ashlsi3
/*
 * gcc-1750/libgcc/__ashlsi3
 * 
 * long long
 * __ashlsi3 (long long, int);
 * 
 * Copyright (c) 1997, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef unsigned int UHItype    __attribute__ ((mode (HI)));
typedef unsigned int USItype    __attribute__ ((mode (SI)));

USItype
__ashlsi3 (uh, ul, n)
    UHItype uh, ul;
    int n;
{
  asm (
       "sim    r4,64
        jlt    .L2
        xorr   r0,r0
        xorr   r1,r1
        xorr   r2,r2
        xorr   r3,r3
        j      .L6
.L2:
        aim    r4,32
        jge    .L3
        dlr    r5,r2
        dslr   r5,r4
        aim    r4,32 
        dslr   r0,r4
        dslr   r2,r4
        orr    r0,r5
        orr    r1,r6
        j      .L6
.L3:
        dlr    r0,r2
        dslr   r0,r4
        xorr   r2,r2
        xorr   r3,r3
.L6:
");
}

#endif /* L__ashlsi3 */

#ifdef  L__ashrsi3
/*
 * gcc-1750/libgcc/__ashrsi3
 * 
 * long long
 * __ashrsi3 (long long, int);
 * 
 * Copyright (c) 1997, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef int HItype __attribute__ ((mode (HI)));
typedef int SItype __attribute__ ((mode (SI)));

SItype
__ashrsi3 (uh, ul, n)
    HItype uh, ul;     /* high and low parts of u */
    int n;             /* number of places to shift */
{
  /* 64-bit arithmetic shift
   *
   * On entry, registers r0..r3 hold the 64-bit number to shift
   * and register r4 holds the number of places. There are four
   * cases to consider.
   *   1: n >= 63
   *   2: 32 <= n < 63
   *   3: 0 < n < 32
   *   4: n <= 0
   *
   * In case 1, the results consists of the sign bit of u propagated
   * into the other 63 bits. The value is either 1 or -1.
   *
   * In case 2, we shift 32 places by register copy, then shift the
   * remainder using a DSAR instruction.
   *
   * In case 3, we save the least significant n bits of uh for 
   * intersion in the most signficant n bits of the lower result. We
   * use an arithmetic shift on uh, and a logical shift on ul.
   *
   * In case 4, we return the number as given.
   */

  asm ("" ::: "r0", "r1", "r2", "r3", "r4");

  if (n >= 63)
    {
      /* Case 1: return 0 or -1.  */
      asm (
       "dsra   r0,16
        dsra   r0,15
        dlr    r2,r0");
    }
  else if (n >= 32)
    {
      /* Case 2: Shift 32 bits by copy, then shift n - 32.  */
      asm (
       "dlr    r2,r0
        dsra   r0,16
        dsra   r0,16
        sim    r4,32
        neg    r4,r4
        dsar   r2,r4");
    }
  else if (n > 0)
    {
      /* Case 3: Save ls n bits of uh, shift uh, ul then
         merge with saved bits.  */
      asm (
       "neg    r5,r4 
        aim    r5,32
        dlr    r6,r0
        dslr   r6,r5
        neg    r4,r4
        dsar   r0,r4
        dslr   r2,r4
        orr    r2,r6
        orr    r3,r7");
    }
}

#endif /* L__ashrsi3 */

#ifdef  L__bb_init
/*
 * gcc-1750/libgcc/__bb_init
 * 
 * void
 * __bb_init ();
 * 
 * Copyright (c) 1997, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

/* Structure emitted by -a  */
static struct bb
{
  int zero_word;
  const char *filename;
  unsigned *counts;
  unsigned ncounts;
  struct bb *next;
  const unsigned *addresses;
  unsigned nwords;
  const char **functions;
  const unsigned *line_nums;
  const char **filenames;
} *bb_head;


/* Return the number of digits needed to print a value */
static int 
num_digits (int value, int base)
{
  int minus = (value < 0 && base != 16);
  unsigned v = (minus) ? -value : value;
  int ret = minus;

  do
    {
      v /= base;
      ret++;
    }
  while (v);

  return ret;
}

void
__bb_exit_func (void) __attribute__ ((destructor));

void
__bb_exit_func (void)
{
  struct bb *ptr;

  /* This is somewhat type incorrect, but it avoids worrying about
     exactly where time.h is included from.  It should be ok unless
     a void * differs from other pointer formats, or if sizeof(long)
     is < sizeof (time_t).  It would be nice if we could assume the
     use of rationale standards here.  */

  printf ("Basic block profile\n");

  /* We check the length field explicitly in order to allow compatibility
     with older GCC's which did not provide it.  */

  for (ptr = bb_head; ptr != (struct bb *)0; ptr = ptr->next)
    {
      int i;
      int func_p    = (ptr->nwords >= sizeof (struct bb) && ptr->nwords <= 1000);
      int line_p    = (func_p && ptr->line_nums);
      int file_p    = (func_p && ptr->filenames);
      int ncounts  = ptr->ncounts;
      int cnt_max  = 0;
      int line_max = 0;
      int file_len  = 0;
      int func_len  = 0;
      int blk_len   = num_digits (ncounts, 10);
      int cnt_len;

      int line_len;
      int addr_len;

      printf ("File %s, %u basic blocks \n\n",
               ptr->filename, ncounts);

      /* Get max values for each field.  */
      for (i = 0; i < ncounts; i++)
        {
          const char *p;
          int len;

          if (cnt_max < ptr->counts[i])
            cnt_max = ptr->counts[i];

          if (line_p && line_max < ptr->line_nums[i])
            line_max = ptr->line_nums[i];

          if (func_p)
            {
              p = (ptr->functions[i]) ? (ptr->functions[i]) : "<none>";
              len = strlen (p);
              if (func_len < len)
                func_len = len;
            }

          if (file_p)
            {
              p = (ptr->filenames[i]) ? (ptr->filenames[i]) : "<none>";
              len = strlen (p);
              if (file_len < len)
                file_len = len;
            }
        }

      cnt_len  = num_digits (cnt_max, 10);
      line_len = num_digits (line_max, 10);

      /* Now print out the basic block information.  */
      for (i = 0; i < ncounts; i++)
        {
          printf ("    Block #%*d: executed %*u time(s) address= 0x%.5lx",
                   blk_len, i+1,
                   cnt_len, ptr->counts[i],
                   (unsigned long)(ptr->addresses[i]) << 1);

          if (func_p)
            printf (" function= %-*s", func_len,
                     (ptr->functions[i]) ? ptr->functions[i] : "<none>");

          if (line_p)
            printf (" line= %*u", line_len, ptr->line_nums[i]);

          if (file_p)
            printf (" file= %s",
                     (ptr->filenames[i]) ? ptr->filenames[i] : "<none>");

          printf ("\n");
        }

      printf ("\n");
    }
}

void
__bb_init_func (struct bb *blocks)
{
  asm volatile (
       "pshm   r1,r2
        lr     r1,r0
        l      r0,0,r1
        jnz    L44
        stc    1,0,r1  
        l      r2,_bb_head
        st     r2,4,r1
        st     r1,_bb_head
L44:
        popm   r1,r2 ");
}


#endif /* L__bb_init */

#ifdef  L__builtin_delete
/*
 * gcc-1750/libgcc/__builtin_delete
 * 
 * void
 * __builtin_delete ();
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

void
__builtin_delete (void *ptr)
{
  if (ptr)
    free (ptr);
}

#endif /* L__builtin_delete */

#ifdef  L__builtin_new
/*
 * gcc-1750/libgcc/__builtin_new
 * 
 * void *
 * __builtin_new ();
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

void *
__builtin_new (size_t sz)
{
  void *p;

  if (sz == 0)
    sz = 1;
  p = (void *) malloc (sz);
  
  return p;
}

#endif /* L__builtin_new */

#ifdef  L__divsi3
/*
 * gcc-1750/libgcc/__divsi3
 * 
 * long long
 * __divsi3 (long long, long long);
 * 
 * Copyright (c) 1997, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef int SItype  __attribute__ ((mode (SI)));

unsigned long long
__udivmodsi4 (unsigned long long, unsigned long long, unsigned long long*);

struct SIstruct {long high, low;};

typedef union
{
  struct SIstruct s;
  SItype ll;
} SIunion;

SItype
__divsi3 (u, v)
     SItype u, v;
{
  int c = 0;
  SIunion uu, vv;
  SItype w;

  uu.ll = u;
  vv.ll = v;

  if (uu.s.high < 0)
    c = ~c,
    uu.ll = -uu.ll;
  if (vv.s.high < 0)
    c = ~c,
    vv.ll = -vv.ll;

  w = __udivmodsi4 (uu.ll, vv.ll, (SItype *)0);
  if (c)
    w = -w;

  return w;
}

#endif /* L__divsi3 */

#ifdef  L__fix_trunctqfsi2
/*
 * gcc-1750/libgcc/__fix_trunctqfsi2
 * 
 * long long
 * __fix_trunctqfsi2 (double);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

long long
__fix_trunctqfsi2 (double d)
{
  long long ll;
  int e2;
  int places;

  if (d == 0.0)
    return 0LL;

  /* get mantissa in top 40 bits of of ll, and exponent in e2 */
  asm volatile (
       "lr     %0,%2
        dlr    %d0,%d2
        xorr   %q0,%q0
        lr     %1,%d0
        sll    %1,8
        sra    %1,8
        srl    %d0,8
        dsll   %d0,8" : "=r" (ll), "=r" (e2) : "r" (d));

  places = 63 - e2;

  /* shifting left would cause overflow, so saturate instead */
  if (places < 0)
    {
      if (d > 0)
        ll = 0x7fffffffffffffffLL;
      else
        ll = 0x8000000000000000LL;
    }

  /* shift right and maybe lose ls bits, truncate */
  if (places > 0)
    ll >>= places;

  return ll;
}

#endif /* L__fix_trunctqfsi2 */

#ifdef  L__fixuns_trunctqfsi2
/*
 * gcc-1750/libgcc/__fixuns_trunctqfsi2
 * 
 * unsigned long long
 * __fixuns_trunctqfsi2 (double);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef int SItype __attribute__ ((mode (SI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));

USItype
__fixuns_trunctqfsi2 (double d)
{
  SItype ll;
  int e2;
  int places;

  if (d == 0.0)
    return 0LL;

  /* Get 40-bit mantissa in top of ll, and exponent in e2 */
  asm volatile (
       "lr     %0,%2
        dlr    %d0,%d2
        xorr   %q0,%q0
        lr     %1,%d0
        sll    %1,8
        sra    %1,8
        srl    %d0,8
        dsll   %d0,8" : "=r" (ll), "=r" (e2) : "r" (d));

  places = 63 - e2;

  /* Shifting left would cause overflow, so saturate instead */
  if (places < -1)
    ll = 0xffffffffffffffffLL;
  else if (places < 0)
    ll <<= 1;
  else
    ll >>= places;

  return ll;
}


#endif /* L__fixuns_trunctqfsi2 */

#ifdef  L__floatsitqf2
/*
 * gcc-1750/libgcc/__floatsitqf2
 * 
 * double
 * __floatsitqf2 (long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

double 
__floatsitqf2 (long long ll)
{
  int e2 = 63;
  double d;

  if (ll == 0)
    return 0.0;

  /* normalize the 64-bit number by shifting left until
     the top 2 bits are different */
  while (1) {
    int top2;
 
    asm volatile (
       "lr     %0,%1
        srl    %0,14": "=r" (top2) : "r" (ll));

    if (top2 == 1 || top2 == 2)
      break;

    e2--;
    ll <<= 1;
  }

  e2 &= 0xff;

  /* build the floating number */
  asm volatile (
       "dlr    %0,%1
        lr     %t0,%t1
        dsrl   %d0,8
        sll    %d0,8
        orr    %d0,%2" : "=r" (d) : "r" (ll), "r" (e2));

  return d;
}

#endif /* L__floatsitqf2 */

#ifdef  L__floatunssitqf2
/*
 * gcc-1750/libgcc/__floatunssitqf2
 * 
 * double
 * __floatunssitqf2 (unsigned long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

double 
__floatunssitqf2 (unsigned long long ll)
{
  int e2 = 64;
  double d;

  if (ll == 0)
    return 0.0;

  /* normalize the 64-bit number by shifting left until
     the top bit is set */
  while (1) {
    int top;
 
    asm volatile (
       "lr     %0,%1": "=r" (top) : "r" (ll));

    if (top & 0x8000)
      break;

    e2--;
    ll <<= 1;
  }

  /* and now shift back one, the sign bit becomes zero */
  ll >>= 1;

  /* and assemble the floating point number */
  e2 &= 0xff;

  asm volatile (
       "dlr    %0,%1
        lr     %t0,%t1
        dsrl   %d0,8
        sll    %d0,8
        orr    %d0,%2" : "=r" (d) : "r" (ll), "r" (e2));

  return d;
}

#endif /* L__floatunssitqf2 */

#ifdef  L__lshrsi3
/*
 * gcc-1750/libgcc/__lshrsi3
 * 
 * unsigned long long
 * __lshrsi3 (unsigned long long, int);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef unsigned int UHItype    __attribute__ ((mode (HI)));
typedef unsigned int USItype    __attribute__ ((mode (SI)));

USItype
__lshrsi3 (uh, ul, n)
    UHItype uh, ul;
    int n;
{
  /* Shift 64 bits right logical */

  asm volatile (
       "lr     r5,r4
        jle    L1 
        cim    r5,64
        jlt    L3

! number of places >= 64
        xorr   r0,r0
        xorr   r1,r1
        xorr   r2,r2
        xorr   r3,r3
        j      L1
L3:
        sim    r5,32
        jlt    L2

! number of places >= 32
        dlr    r2,r0
        xorr   r0,r0
        xorr   r1,r1
        neg    r5,r5
        dslr   r2,r5
        j      L1

! number of places 1 to 31 
L2:
        neg    r4,r4
        neg    r5,r5
        dlr    r6,r0
        dslr   r0,r4
        dslr   r2,r4
        dslr   r6,r5
        orr    r2,r6
        orr    r3,r7
L1:
");
}

#endif /* L__lshrsi3 */

#ifdef  L__modsi3
/*
 * gcc-1750/libgcc/__modsi3
 * 
 * long long
 * __modsi3 (long long, long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef int SItype  __attribute__ ((mode (SI)));

struct SIstruct {long high, low;};

typedef union
{
  struct SIstruct s;
  SItype ll;
} SIunion;

SItype
__modsi3 (u, v)
     SItype u, v;
{
  int c = 0;
  SIunion uu, vv;
  SItype w;

  uu.ll = u;
  vv.ll = v;

  if (uu.s.high < 0)
    c = ~c,
    uu.ll = -uu.ll;
  if (vv.s.high < 0)
    vv.ll = -vv.ll;

  (void) __udivmodsi4 (uu.ll, vv.ll, &w);
  if (c)
    w = -w;

  return w;
}

#endif /* L__modsi3 */

#ifdef  L__mulsi3
/*
 * gcc-1750/libgcc/__mulsi3
 * 
 * long long
 * __mulsi3 (long long, long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef int HItype __attribute__ ((mode (HI)));
typedef int SItype __attribute__ ((mode (SI)));

SItype
__mulsi3 (uh, ul, vh, vl)
    HItype uh, ul, vh, vl;
{
  asm (
       "dlr    r8,r2
        dlr    r2,r6
        dmr    r4,r8
        dmr    r0,r2
        dar    r4,r0
        pshm   r4,r5
        dlr    r0,r8
        lsjs   r15,__umulhisi3
        popm   r4,r5
        dar    r0,r4");
}

#endif /* L__mulsi3 */

#ifdef  L__negsi2
/*
 * gcc-1750/libgcc/__negsi2
 * 
 * long long
 * __negsi2 (long long, long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

long long
__negsi2 (long long x)
{
  asm volatile (
       "dneg   r0,r0
        dlr    r4,r2
        xorr   r2,r2
        xorr   r3,r3
        dsr    r2,r4
        jc     cy,.+10
        xorr   r4,r4
        lisp   r5,1
        dsr    r0,r4");
}

#endif /* L__negsi2 */

#ifdef  L__subsi3
/*
 * gcc-1750/libgcc/__subsi3
 * 
 * long long
 * __subsi3 (long long, long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

long long
__subsi3 (long long x, long long y)
{
  asm volatile (
       "dsr    r0,r4       ! subtract MS 32 bits
        dsr    r2,r6       ! subtract LS 32 bits 
        jc     cy,.+10
        xorr   r8,r8
        lisp   r9,1
        dsr    r0,r8       ! subtract carry
       ");
}

#endif /* L__subsi3 */

#ifdef  L__ucmpsi2
/*
 * gcc-1750/libgcc/__ucmpsi2
 * 
 * int
 * __ucmpsi2 (long long, long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef int SItype  __attribute__ ((mode (SI)));
typedef unsigned int UHItype    __attribute__ ((mode (HI)));

struct SIstruct {long high, low;};

typedef union
{
  struct SIstruct s;
  SItype ll;
} SIunion;


int
__ucmpsi2 (a, b)
     SItype a, b;
{
  SIunion au, bu;

  au.ll = a, bu.ll = b;

  if ((UHItype) au.s.high < (UHItype) bu.s.high)
    return 0;
  else if ((UHItype) au.s.high > (UHItype) bu.s.high)
    return 2;
  if ((UHItype) au.s.low < (UHItype) bu.s.low)
    return 0;
  else if ((UHItype) au.s.low > (UHItype) bu.s.low)
    return 2;
  return 1;
}

#endif /* L__ucmpsi2 */

#ifdef  L__udivhi3
/*
 * gcc-1750/libgcc/__udivhi3
 * 
 * unsigned long long
 * __udivhi3 (unsigned long long, unsigned long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

/*
 * Unsigned division with 32-bit dividend, 32-bit divisor, giving a 32-bit
 * quotient and 32-bit remainder.
 */
unsigned long
__udivhi3 (unsigned long x, unsigned long y)
{
  asm volatile (
       "dlr    r4,r0
        tbr    0,r2
        jez    L1
        xorr   r0,r0
        xorr   r1,r1
        tbr    0,r4
        jez    L4
        j      L2
L1:
        dsrl   r0,1
        ddr    r0,r2
        dlr    r6,r2
        dmr    r6,r0
        dsll   r6,1
        dsr    r4,r6
        dsll   r0,1
        tbr    0,r4
        jnz    L3
L2:
        dlr    r8,r4
        dlr    r10,r2
        xorm   r8,-32768
        xorm   r10,-32768
        dcr    r8,r10
        jlt    L4
L3:
        sbr    15,r1
        dsr    r4,r2
L4:");

  /* the 32-bit quotient is in r0:r1, and the remainder is
     in r4:r5 */
}

#endif /* L__udivhi3 */

#ifdef  L__udivmodsi4
#if 0 /* m1750-coff ICEs on this */
/*
 * gcc-1750/libgcc/__udivmodsi4
 * 
 * unsigned long long
 * __udivmodsi4 (unsigned long long, unsigned long long, unsigned long long *);
 * 
 * Copyright (c) 1997, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

typedef          int HItype     __attribute__ ((mode (HI)));
typedef unsigned int UHItype    __attribute__ ((mode (HI)));
typedef          int SItype     __attribute__ ((mode (SI)));
typedef unsigned int USItype    __attribute__ ((mode (SI)));

#define HI_TYPE_SIZE 32
#define SI_TYPE_SIZE 62

struct SIstruct {long high, low;};
typedef union
{
  struct SIstruct s;
  SItype ll;
} SIunion;


/* Define auxiliary asm macros.

   sub_ddmmss(high_difference, low_difference, high_minuend,
   low_minuend, high_subtrahend, low_subtrahend) subtracts two
   two-word unsigned integers, composed by HIGH_MINUEND_1 and
   LOW_MINUEND_1, and HIGH_SUBTRAHEND_2 and LOW_SUBTRAHEND_2
   respectively.  The result is placed in HIGH_DIFFERENCE and
   LOW_DIFFERENCE.  Overflow (i.e. carry out) is not stored anywhere,
   and is lost.
   */

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
  do {                                     \
    unsigned long __x;                           \
    __x = (al) - (bl);                     \
    (sh) = (ah) - (bh) - (__x > (al));     \
    (sl) = __x;                            \
  } while (0)

extern SItype __umulhisi3 (unsigned long, unsigned long);


/*
 * __udiv_qrnnd divides the 64-bit unsigned number (n1,n0) by the
 * 32-bit unsigned number d, and returns the 32-bit quotient and
 * remainder. The number d must be scaled such that its top bit
 * is set.
 */
static void
udiv_qrnnd (
    unsigned long *qp,  /* 32-bit quotient */  
    unsigned long *rp,  /* 32-bit remainder */
    unsigned long n1,   /* most sig 32 bits of the numerator */
    unsigned long n0,   /* least sig 32 bits of the numerator */
    unsigned long d)    /* 32-bit denominator */
{
  unsigned long d1, d0, q1, q0;
  unsigned long r, m, ru;
  long ds, qs, rs;

  d1 = d >> 16;
  d0 = d & 0xFFFF;
  ds = (long) d1;

  ru = n1 >> 1;
  rs = (long) ru;
  qs = rs / ds;
  rs = rs % ds;
  q1 = (unsigned long) qs;
  ru = (unsigned long) rs;
  q1 = q1 << 1;
  r = (ru << 1) | (n1 & 1);
  if (r >= d1)
    q1++, r -= d1;

  m = (unsigned long) q1 * d0;
  r = (r << 16) | (n0 >> 16);
  if (r < m)
    {
      q1--, r += d;
      if (r >= d) /* i.e. we didn't get carry when adding to r */
        if (r < m)
          q1--, r += d;
    }
  r -= m;

  ru = r >> 1;
  rs = (long) ru;
  qs = rs / ds;
  rs = rs % ds;
  q0 = (unsigned long) qs;
  ru = (unsigned long) rs;
  q0 = q0 << 1;
  r = (ru << 1) | (r & 1);
  if (r >= d1)
    q0++, r -= d1;

  m = (unsigned long) q0 * d0;
  r = (r << 16) | (n0 & 0xFFFF);
  if (r < m)
    {
      q0--, r += d;
      if (r >= d) /* i.e. we didn't get carry when adding to r */
        if (r < m)
          q0--, r += d;
    }
  r -= m;

  *qp = (unsigned long) (q1 << 16) | q0;
  *rp = r;
}


unsigned long long
__udivmodsi4 (n, d, rp)
     USItype n, d;
     USItype *rp;
{
  SIunion ww;
  SIunion nn, dd;
  SIunion rr;
  unsigned long d0, d1, n0, n1, n2;
  unsigned long q0, q1;
  unsigned long b;
  int bm;

  nn.ll = n;
  dd.ll = d;

  d0 = dd.s.low;
  d1 = dd.s.high;
  n0 = nn.s.low;
  n1 = nn.s.high;

  if (d1 == 0)
    {
      /* 64/32 bit division will do */
      if (d0 > n1)
        {
          /* 0q = nn / 0D */

          /* Normalize, i.e. make the most significant bit of the
             denominator set.  */
          bm = 0;
          while ((d0 & 0x80000000) == 0)
            {
              bm++;
              d0 <<= 1;
            }

          if (bm != 0)
            {
              /* normalize the denominator */
              n1 = (n1 << bm) | (n0 >> (HI_TYPE_SIZE - bm));
              n0 = n0 << bm;
            }

          udiv_qrnnd (&q0, &n0, n1, n0, d0);
          q1 = 0;

          /* Remainder in n0 >> bm.  */
        }
      else
        {
          /* qq = NN / 0d */

          if (d0 == 0)
            d0 = 1 / (int)d0;        /* Divide intentionally by zero.  */

          bm = 0;
          while ((d0 & 0x80000000) == 0)
            {
              bm++;
              d0 <<= 1;
            }

          if (bm == 0)
            {
              /* From (n1 >= d0) /\ (the most significant bit of d0 is set),
                 conclude (the most significant bit of n1 is set) /\ (the
                 leading quotient sigit q1 = 1).

                 This special case is necessary, not an optimization.
                 (Shifts counts of HI_TYPE_HIZE are undefined.)  */

              n1 -= d0;
              q1 = 1;
            }
          else
            {
              /* Normalize.  */

              b = HI_TYPE_SIZE - bm;

              n2 = n1 >> b;
              n1 = (n1 << bm) | (n0 >> b);
              n0 = n0 << bm;

              udiv_qrnnd (&q1, &n1, n2, n1, d0);
            }

          /* n1 != d0... */

          udiv_qrnnd (&q0, &n0, n1, n0, d0);

          /* Remainder in n0 >> bm.  */
        }

      if (rp != 0)
        {
          rr.s.low = n0 >> bm;
          rr.s.high = 0;
          *rp = rr.ll;
        }
    }

  else
    {
      if (d1 > n1)
        {
          /* 00 = nn / DD */

          q0 = 0;
          q1 = 0;

          /* Remainder in n1n0.  */
          if (rp != 0)
            {
              rr.s.low = n0;
              rr.s.high = n1;
              *rp = rr.ll;
            }
        }
      else
        {
          /* 0q = NN / dd */

          bm = 0;
          while ((d1 & 0x80000000) == 0)
            {
              bm++;
              d1 <<= 1;
            }

          if (bm == 0)
            {
              /* From (n1 >= d1) /\ (the most significant bit of d1 is set),
                 conclude (the most significant bit of n1 is set) /\ (the
                 quotient sigit q0 = 0 or 1).

                 This special case is necessary, not an optimization.  */

              /* The consition on the next line takes advantage of that
                 n1 >= d1 (true due to program flow).  */
              if (n1 > d1 || n0 >= d0)
                {
                  q0 = 1;
                  sub_ddmmss (n1, n0, n1, n0, d1, d0);
                }
              else
                q0 = 0;

              q1 = 0;

              if (rp != 0)
                {
                  rr.s.low = n0;
                  rr.s.high = n1;
                  *rp = rr.ll;
                }
            }
          else
            {
              unsigned long m1, m0;
              SIunion m1m0;

              /* Normalize.  */

              b = HI_TYPE_SIZE - bm;

              d1 = d1 | (d0 >> b);
              d0 = d0 << bm;
              n2 = n1 >> b;
              n1 = (n1 << bm) | (n0 >> b);
              n0 = n0 << bm;

              udiv_qrnnd (&q0, &n1, n2, n1, d1);
              m1m0.ll = __umulhisi3 (q0, d0);
              m1 = m1m0.s.high;
              m0 = m1m0.s.low;

              if (m1 > n1 || (m1 == n1 && m0 > n0))
                {
                  q0--;
                  sub_ddmmss (m1, m0, m1, m0, d1, d0);
                }

              q1 = 0;

              /* Remainder in (n1n0 - m1m0) >> bm.  */
              if (rp != 0)
                {
                  sub_ddmmss (n1, n0, n1, n0, m1, m0);
                  rr.s.low = (n1 << b) | (n0 >> bm);
                  rr.s.high = n1 >> bm;
                  *rp = rr.ll;
                }
            }
        }
    }

  ww.s.low = q0;
  ww.s.high = q1;
  return ww.ll;
}

#endif /* 0 */
#endif /* L__udivmodsi4 */

#ifdef  L__udivsi3
/*
 * gcc-1750/libgcc/__udivsi3
 * 
 * unsigned long long
 * __udivsi3 (unsigned long long, unsigned long long);
 * 
 * Copyright (c) 1997, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

unsigned long long
__udivsi3 (unsigned long long x, unsigned long long y)
{
  asm volatile (
       "xorr   r8,r8
        lsjs   r15,__udivmodsi4");
}

#endif /* L__udivsi3 */

#ifdef  L__umodhi3
/*
 * gcc-1750/libgcc/__umodhi3
 * 
 * unsigned long long
 * __umodhi3 (unsigned long long, unsigned long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

unsigned long
__umodhi3 (unsigned long x, unsigned long y)
{
  asm volatile (
       "lsjs   r15,__udivhi3
        dlr    r0,r4");
}

#endif /* L__umodhi3 */

#ifdef  L__umodsi3
/*
 * gcc-1750/libgcc/__umodsi3
 * 
 * unsigned long long
 * __umodsi3 (unsigned long long, unsigned long long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

unsigned long long
__umodsi3 (unsigned long long x, unsigned long long y)
{
  asm volatile (
       "sisp   r15,4
	pshm   r14,r14
	lr     r14,r15
	lim    r8,1,r14
	lsjs   r15,__udivmodsi4
	lm     3,1,r14
	lr     r15,r14
	popm   r14,r14
	aisp   r15,4");
}

#endif /* L__umodsi3 */

#ifdef  L__umulhisi3
/*
 * gcc-1750/libgcc/__umulhisi3
 * 
 * unsigned long long
 * __umulhisi3 (unsigned long, unsigned long);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

unsigned long long
__umulhisi3 (unsigned long x, unsigned long y)
{
  asm volatile (
       "lr      r8,r3
        dsrl    r8,16
        lr      r6,r1
        dsrl    r6,16
        dmr     r6,r8      ! r1*r3 : x.low * y.low
        lr      r4,r0
        dsrl    r4,16
        dmr     r4,r8      ! r0*r3 : y.low * x.hi
        lr      r10,r2
        dsrl    r10,16
        lr      r2,r1 
        dsrl    r2,16
        dmr     r2,r10     ! r1*r2 : x.low * y.hi
        dsrl    r0,16
        dmr     r0,r10     ! r0*r2 : x.hi * y.hi

! r0,r1 = x.hi * y.hi
! r2,r3 = x.low * y.hi
! r4,r5 = y.low * x.hi
! r6,r7 = x.low * y.low

        xorr    r10,r10
        lr      r11,r6
        dar     r4,r10    
        lisp    r11,1
        dar     r2,r4      ! may overflow
        jc      cy,L1
        lr      r11,r10
L1:
        xwr     r10,r11
        dar     r0,r10     ! add carry, may overflow
        xorr    r10,r10
        lr      r11,r2
        dar     r0,r10     ! may overflow
        lr      r2,r3
        lr      r3,r7 
");
}

#endif /* L__umulhisi3 */

#ifdef  Lbcopy
/*
 * gcc-1750/libgcc/bcopy
 * 
 * void
 * bcopy (char *, int);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

void 
bcopy (const void *src, void *dest, int n)
{
  asm ("mov    r1,r0");
}

#endif /* Lbcopy */

#ifdef  Lbzero
/*
 * gcc-1750/libgcc/bzero
 * 
 * void
 * bzero (char *, int, int);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
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
 * $Log: libgcc2.c,v $
 * Revision 1.3  1997/08/06 16:20:54  nettleto
 * Fixed sjs for expanded memory.
 *
 * Revision 1.2  1997/07/23 11:53:17  nettleto
 * Updated for GCC-1750 Version 1.0
 *
 * Revision 1.1  1997/05/06 17:28:22  nettleto
 * Initial revision
 *
 */

void
bzero (char *b, unsigned length)
{
  while (length)
    {
      *b++ = 0;
      length--;
    }
}

#endif /* Lbzero */

