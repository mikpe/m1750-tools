/***************************************************************************/
/*                                                                         */
/* Project   :        sim1750 -- Mil-Std-1750 Software Simulator           */
/*                                                                         */
/* Component :     arith.c -- simulate 1750A arithmetic operations         */
/*                                                                         */
/* Copyright :         (C) Daimler-Benz Aerospace AG, 1994-97              */
/*                                                                         */
/* Author    :      Oliver M. Kellogg, Dornier Satellite Systems,          */
/*                     Dept. RST13, D-81663 Munich, Germany.               */
/* Contact   :           oliver.kellogg@space.otn.dasa.de                  */
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

#include "arch.h"
#include "status.h"
#include "utils.h"
#include "flt1750.h"

#define FLT_1750_EPSILON     1.1920928955078125000E-7
#define FLT_1750_MAX         1.70141163178059628080016879768632819712E38
#define FLT_1750_MIN         \
 1.469367938527859384960920671527807097273331945965109401885939632848E-39

#define DBL_1750_EPSILON     1.818989403545856475830078125000E-12
#define DBL_1750_MAX         1.70141183460159746721865958647159324672E38
#define DBL_1750_MIN         \
 1.469367938527859384960920671527807097273331945965109401885939632848E-39


/************* utilities for Condition Status in the Status Word *************/

void
update_cs (short *operand, datatype data_type)
{
  bool is_zero;
  ushort sw_save = simreg.sw & 0x8FFF;

  switch (data_type)
    {
    case VAR_INT:
      is_zero = (operand[0] == 0);
      break;
    case VAR_LONG:
    case VAR_FLOAT:
      is_zero = (operand[0] == 0 && operand[1] == 0);
      break;
    case VAR_DOUBLE:
      is_zero = (operand[0] == 0 && operand[1] == 0 && operand[2] == 0);
      break;
    }
  if (is_zero)
    simreg.sw = sw_save | CS_ZERO;
  else if (*operand & 0x8000)  /* Check sign bit. Same for all data types. */
    simreg.sw = sw_save | CS_NEGATIVE;
  else
    simreg.sw = sw_save | CS_POSITIVE;
}


void
compare (datatype data_type, short *operand0, short *operand1)
{
  ushort sw_save = simreg.sw & 0x0FFF;
  short op0, op1;
  long lop0, lop1;
  double fop0, fop1;

  switch (data_type)
    {
    case VAR_INT:
      op0 = operand0[0];
      op1 = operand1[0];
      if (op0 < op1)
        simreg.sw = sw_save | CS_NEGATIVE;
      else if (op0 > op1)
        simreg.sw = sw_save | CS_POSITIVE;
      else
        simreg.sw = sw_save | CS_ZERO;
      break;
    case VAR_LONG:
      lop0 = ((long) operand0[0] << 16) | ((long) operand0[1] & 0xFFFFL);
      lop1 = ((long) operand1[0] << 16) | ((long) operand1[1] & 0xFFFFL);
      if (lop0 < lop1)
        simreg.sw = sw_save | CS_NEGATIVE;
      else if (lop0 > lop1)
        simreg.sw = sw_save | CS_POSITIVE;
      else
        simreg.sw = sw_save | CS_ZERO;
      break;
    case VAR_FLOAT:
      fop0 = from_1750flt (operand0);
      fop1 = from_1750flt (operand1);
      if (fop0 < fop1)
        simreg.sw = sw_save | CS_NEGATIVE;
      else if (fop0 > fop1)
        simreg.sw = sw_save | CS_POSITIVE;
      else
        simreg.sw = sw_save | CS_ZERO;
      break;
    case VAR_DOUBLE:
      fop0 = from_1750eflt (operand0);
      fop1 = from_1750eflt (operand1);
      if (fop0 < fop1)
        simreg.sw = sw_save | CS_NEGATIVE;
      else if (fop0 > fop1)
        simreg.sw = sw_save | CS_POSITIVE;
      else
        simreg.sw = sw_save | CS_ZERO;
      break;
    }
}


/*****************************************************************************/

/* See enum operation_kind in file arch.h :   */
static char *operation_name[] = { "ADD", "SUB", "MULS", "MUL", "DIVV", "DIV" };

/* add,subtract,multiply,divide -- for all 1750A data types.
   operand0 and operand1 are the input operands (vectors of shorts).
   The `vartyp' argument determines how the input vectors are interpreted.
   The result is stored in operand0.
   The condition code bits (CPZN) in simreg.sw are updated accordingly.
   The Pending Interrupt Register (simreg.pir) is also updated in case of
   under/overflow conditions during computation.
 */

void
arith (operation_kind operation,
       datatype vartyp,    /* Always specify data type of SECOND operand! */
       short *operand0, short *operand1)
{
  simreg.sw &= ~CS_CARRY;

  switch (vartyp)
    {
    case VAR_INT:
      switch (operation)
        {                /* Nice and easy, just use a larger data type. */
        case ARI_ADD:
          {
            ulong lop0 = *(ushort *)operand0;
            ulong lop1 = *(ushort *)operand1;
            ulong laccu;

            laccu = lop0 + lop1;

            if (laccu & 0x10000L)
              simreg.sw |= CS_CARRY;

            if ((lop0 & 0x8000L) == (lop1 & 0x8000L) &&
                (lop1 & 0x8000L) != (laccu & 0x8000L))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on ADD, op0=%ld op1=%ld res=%ld\n",
                      lop0, lop1, laccu);
              }

            operand0[0] = (ushort) laccu;
            update_cs (operand0, VAR_INT);
          }

        elsecase ARI_SUB:
          {
            ulong lop0 = *(ushort *)operand0;
            ulong lop1 = *(ushort *)operand1;
            ulong laccu;

            laccu = lop0 - lop1;

            if (laccu & 0x10000L)
              simreg.sw |= CS_CARRY;

            if ((lop0 & 0x8000L) != (lop1 & 0x8000L)
             && (lop0 & 0x8000L) != (laccu & 0x8000L))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on SUB, op0=%ld op1=%ld res=%ld\n",
                    lop0, lop1, laccu);
              }

            operand0[0] = (ushort) laccu;
            update_cs (operand0, VAR_INT);
          }

        elsecase ARI_MUL:
          {
            /* Single precision integer multiply with 32-bit result */
            long lop0 = (long) *operand0;
            long lop1 = (long) *operand1;
            long laccu;

            laccu = lop0 * lop1;

            operand0[0] = (ushort) ((laccu >> 16) & 0xFFFFL);
            operand0[1] = (ushort) (laccu & 0xFFFFL);
            update_cs (operand0, VAR_LONG);
          }

        elsecase ARI_MULS:
          {
            long lop0 = (long) *operand0;
            long lop1 = (long) *operand1;
            long laccu;
            bool overflow = FALSE;

            laccu = lop0 * lop1;

            if (lop0 != 0L && lop1 != 0L)
              {
                if ((lop0 & 0x8000L) == (lop1 & 0x8000L))
                  {
                    if ((laccu & 0xFFFF8000L) != 0)
                      overflow = TRUE;
                  }
                else
                  {
                    if ((laccu & 0xFFFF8000L) != 0xFFFF8000L)
                      overflow = TRUE;
                  }
              }

            if (overflow)
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on MULS, op0=%ld op1=%ld res=%ld\n",
                      lop0, lop1, laccu);
              }

            operand0[0] = (short) laccu;
            update_cs (operand0, VAR_INT);
          }

        elsecase ARI_DIV:
          {
            /* 16 bit divide with 32-bit dividend */
            long lop0 = ((long) operand0[0] << 16)
                      | ((long) operand0[1] & 0xFFFFL);
            long lop1 = (long) *operand1;
            long laccu;
            long rem;

            if (lop1 != 0L)
              {
                laccu = lop0 / lop1;
                rem = lop0 % lop1;
              }

            if (lop1 == 0L || (lop0 == 0x8000L && lop1 == 0xFFFFL))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on DIV, op0=%ld op1=%ld res=%ld\n",
                      lop0, lop1, laccu);
              }
            else        /* Put this in an "else" part because */
              {         /* laccu and rem are otherwise undefined */
                operand0[0] = (short) laccu;
                operand0[1] = (short) rem;
                update_cs (operand0, VAR_INT);
              }
          }

        elsecase ARI_DIVV:
          {
            /* 16 bit signed divide with 16-bit dividend */
            long lop0 = (long) *operand0;
            long lop1 = (long) *operand1;
            long laccu;
            long rem;

            if (lop1 != 0L)
              {
                laccu = lop0 / lop1;
                rem = lop0 % lop1;
              }

            if (lop1 == 0L || (lop0 == 0x8000L && lop1 == 0xFFFFL))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on DIVV, op0=%ld op1=%ld res=%ld\n",
                      lop0, lop1, laccu);
              }
            else        /* Put this in an "else" part because */
              {         /* laccu and rem are otherwise undefined */
                operand0[0] = (short) laccu;
                operand0[1] = (short) rem;
                update_cs (operand0, VAR_INT);
              }
          }
        }

    elsecase VAR_LONG:
#ifdef LONGLONG
      switch (operation)
        {                /* Nice and easy, just use a larger data type. */
        case ARI_ADD:
          {
            unsigned long long lop0 = ((ulong) operand0[0] << 16)
                                    | ((ulong) operand0[1] & 0xFFFFL);
            unsigned long long lop1 = ((ulong) operand1[0] << 16)
                                    | ((ulong) operand1[1] & 0xFFFFL);
            unsigned long long laccu;

            laccu = lop0 + lop1;

            if (laccu & 0x100000000LL)
              simreg.sw |= CS_CARRY;

            if ((lop0 & 0x80000000LL) == (lop1 & 0x80000000LL)
             && (lop1 & 0x80000000LL) != (laccu & 0x80000000LL))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on long ADD, op0=%lld op1=%lld res=%lld\n",
                    lop0, lop1, laccu);
              }

            operand0[0] = (short) (laccu >> 16);
            operand0[1] = (short) (laccu & 0xFFFFLL);
            update_cs (operand0, VAR_LONG);
          }

        elsecase ARI_SUB:
          {
            unsigned long long lop0 = ((ulong) operand0[0] << 16)
                                    | ((ulong) operand0[1] & 0xFFFFL);
            unsigned long long lop1 = ((ulong) operand1[0] << 16)
                                    | ((ulong) operand1[1] & 0xFFFFL);
            unsigned long long laccu;

            laccu = lop0 - lop1;

            if (laccu & 0x100000000LL)
              simreg.sw |= CS_CARRY;

            if ((lop0 & 0x80000000LL) != (lop1 & 0x80000000LL)
             && (lop0 & 0x80000000LL) != (laccu & 0x80000000LL))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on long SUB, op0=%lld op1=%lld res=%lld\n",
                    lop0, lop1, laccu);
              }

            operand0[0] = (short) (laccu >> 16);
            operand0[1] = (short) (laccu & 0xFFFFLL);
            update_cs (operand0, VAR_LONG);
          }

        elsecase ARI_MUL:
          {
            /* Double precision integer multiply with 32-bit result */
            long long lop0 = ((long long) operand0[0] << 16)
                           | ((long long) operand0[1] & 0xFFFFLL);
            long long lop1 = ((long long) operand1[0] << 16)
                           | ((long long) operand1[1] & 0xFFFFLL);
            long long laccu;
            bool overflow = FALSE;

            laccu = lop0 * lop1;

            if (lop0 != 0LL && lop1 != 0LL)
              {
                if ((lop0 & 0x80000000LL) == (lop1 & 0x80000000LL))
                  {
                    if ((laccu & 0xFFFFFFFF80000000LL) != 0LL)
                      overflow = TRUE;
                  }
                else
                  {
                    if ((laccu & 0xFFFFFFFF80000000LL) != 0xFFFFFFFF80000000LL)
                      overflow = TRUE;
                  }
              }

            if (overflow)
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on long MUL, op0=%lld op1=%lld res=%lld\n",
                    lop0, lop1, laccu);
              }

            operand0[0] = (short) (laccu >> 16);
            operand0[1] = (short) (laccu & 0xFFFFLL);
            update_cs (operand0, VAR_LONG);
          }

        elsecase ARI_DIV:
          {
            /* 32 bit divide with 32-bit dividend */
            long long lop0 = ((long long) operand0[0] << 16)
                           | ((long long) operand0[1] & 0xFFFFLL);
            long long lop1 = ((long long) operand1[0] << 16)
                           | ((long long) operand1[1] & 0xFFFFLL);
            long long laccu;
            long long rem;

            if (lop1 != 0LL)
              {
                laccu = lop0 / lop1;
                rem = lop0 % lop1;
                if (rem < 0LL && lop0 >= 0LL)
                  laccu--;
                else if (rem > 0LL && lop0 < 0LL)
                  laccu++;
              }

            if (lop1 == 0LL ||
                ((unsigned long long) lop0 == 0xFFFFFFFF80000000LL
                 && lop1 == -1LL))
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on long DIV, op0=%lld op1=%lld res=%lld\n",
                    lop0, lop1, laccu);
              }
            else        /* Put this in an "else" part because */
              {         /* laccu is otherwise undefined */
                operand0[0] = (short) (laccu >> 16);
                operand0[1] = (short) (laccu & 0xFFFFLL);
                update_cs (operand0, VAR_LONG);
              }
          }
          break;

        default:
          problem ("illegal operation code supplied to arith VAR_LONG");
        }
#else
#define MIN_LONG -0x80000000
#define MAX_LONG  0x7FFFFFFF
      {  /* Not so nice and easy if we don't have a larger data type. */
        long lop0 = ((long) operand0[0] << 16) | ((long) operand0[1] & 0xFFFFL);
        long lop1 = ((long) operand1[0] << 16) | ((long) operand1[1] & 0xFFFFL);
        long laccu;
        int opsign;
        bool ari_interrupt = FALSE;

        if (operation == ARI_ADD ? opsign = 1 :
            operation == ARI_SUB ? opsign = -1 : 0)
          {
            if (lop0 > 0)                /* check for positive overflow */
              {
                if ((opsign == 1 && lop1 > 0 || opsign == -1 && lop1 < 0)
                    && opsign * lop1 > MAX_LONG - lop0)
                  ari_interrupt = TRUE;
              }
            else                        /* check for negative overflow */
              {
                if ((opsign == 1 && lop1 < 0 || opsign == -1 && lop1 > 0)
                    && opsign * lop1 < MIN_LONG - lop0)
                  ari_interrupt = TRUE;
              }
            if (ari_interrupt)
              simreg.sw |= CS_CARRY;
            else
              laccu = (operation == ARI_ADD) ? lop0 + lop1 : lop0 - lop1;
          }
        else
          /* MUL or DIV */
          {
            if (lop0 == 0 || lop1 == 0)
              {
                if (lop1 == 0 && operation == ARI_DIV)
                  ari_interrupt = TRUE;
                else
                  laccu = 0;
              }
            else if (operation == ARI_MUL)
              {                        /* (integer division doesn't need any checks) */
                if (lop0 < 0 && lop1 < 0)        /* check for pos. overflow */
                  {
                    if (lop0 < MAX_LONG / lop1)
                      ari_interrupt = TRUE;
                  }
                else if (lop0 > 0 && lop1 > 0)
                  {
                    if (lop0 > MAX_LONG / lop1)
                      ari_interrupt = TRUE;
                  }
                else if (lop0 < 0 && lop1 > 0)        /* check for neg. overflow */
                  {
                    if (lop0 < MIN_LONG / lop1)
                      ari_interrupt = TRUE;
                  }
                else if (lop0 > 0 && lop1 < 0)
                  {
                    if (lop0 > MIN_LONG / -lop1)
                      ari_interrupt = TRUE;
                  }
                if (!ari_interrupt)
                  laccu = lop0 * lop1;
              }
            else
              laccu = lop0 / lop1;
            if (ari_interrupt)
              {
                simreg.pir |= INTR_FIXOFL;
                info ("FIXOFL on long %s,  op0=%ld op1=%ld res=%ld\n",
                        operation_name[operation], lop0, lop1, laccu);
              }
          }
        operand0[0] = (short) (laccu >> 16);
        operand0[1] = (short) (laccu & 0xFFFFL);
        update_cs (operand0, VAR_LONG);
      }
#endif

    elsecase VAR_FLOAT:
      {
        bool overflow = FALSE;
        const double fop0 = from_1750flt (operand0);
        const double fop1 = from_1750flt (operand1);
        double faccu;

        switch (operation)
          {
          case ARI_ADD:
            faccu = fop0 + fop1;
          elsecase ARI_SUB:
            faccu = fop0 - fop1;
          elsecase ARI_MUL:
            faccu = fop0 * fop1;
          elsecase ARI_DIV:
            if ((fop1 < 0.0 && -fop1 < FLT_1750_MIN)
             || (fop1 >= 0.0 && fop1 < FLT_1750_MIN))
              overflow = TRUE;
            else
              faccu = fop0 / fop1;
            break;
          default:
            problem ("illegal operation code supplied to arith VAR_FLOAT");
          }

        if (overflow)
          {
            simreg.pir |= INTR_FLTOFL;
            operand0[0] = 0x0000;
            operand0[1] = 0x0000;

            info ("arith: FLT zero divide during %s,  op0=%g op1=%g res=%g\n",
                  operation_name[(int) operation], fop0, fop1, faccu);
          }
        else
          {
            int stat = to_1750flt (faccu, operand0);

            if (stat > 0)
              {
                simreg.pir |= INTR_FLTOFL;
                operand0[0] = 0x7FFF;
                operand0[1] = 0xFF7F;
              }
            else if (stat < 0)
              {
                simreg.pir |= INTR_FLTUFL;
                operand0[0] = 0x4000;
                operand0[1] = 0x0080;
              }

            if (stat != 0)
              info ("arith: FLT%cFL during %s,  op0=%g op1=%g res=%g\n",
                    (stat > 0 ? 'O' : 'U'),
                    operation_name[(int) operation], fop0, fop1, faccu);

            update_cs (operand0, VAR_FLOAT);
          }
      }

    elsecase VAR_DOUBLE:
      {
        bool overflow = FALSE;
        const double fop0 = from_1750eflt (operand0);
        const double fop1 = from_1750eflt (operand1);
        double faccu;

        switch (operation)
          {
          case ARI_ADD:
            faccu = fop0 + fop1;
          elsecase ARI_SUB:
            faccu = fop0 - fop1;
          elsecase ARI_MUL:
            faccu = fop0 * fop1;
          elsecase ARI_DIV:
            if ((fop1 < 0.0 && -fop1 < DBL_1750_MIN)
             || (fop1 >= 0.0 && fop1 < DBL_1750_MIN))
              overflow = TRUE;
            else
              faccu = fop0 / fop1;
            break;
          default:
            problem ("illegal operation code supplied to arith VAR_DOUBLE");
          }

        if (overflow)
          {
            simreg.pir |= INTR_FLTOFL;
            operand0[0] = 0x0000;
            operand0[1] = 0x0000;
            operand0[2] = 0x0000;

            info ("arith: FLT zero divide during %s,  op0=%g op1=%g res=%g\n",
                  operation_name[(int) operation], fop0, fop1, faccu);
          }
        else
          {
            int stat = to_1750eflt (faccu, operand0);

            if (stat > 0)
              {
                simreg.pir |= INTR_FLTOFL;
                operand0[0] = 0x7FFF;
                operand0[1] = 0xFF7F;
                operand0[2] = 0xFFFF;
              }
            else if (stat < 0)
              {
                simreg.pir |= INTR_FLTUFL;
                operand0[0] = 0x0000;
                operand0[1] = 0x0000;
                operand0[2] = 0x0000;
              }

            if (stat != 0)
              info ("arith: FLT%cFL during %s,  op0=%g op1=%g res=%g\n",
                    (stat > 0 ? 'O' : 'U'),
                    operation_name[(int) operation], fop0, fop1, faccu);

            update_cs (operand0, VAR_DOUBLE);
          }
      }
  }

}

