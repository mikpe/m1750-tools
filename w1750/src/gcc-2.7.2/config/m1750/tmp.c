;; Machine description for GCC-1750
;;
;; Copyright (C) 1994, 1995, 1997 Free Software Foundation, Inc.
;; Written 1997 by Chris Nettleton, cnettleton@acm.org
;; Based on 1750.md by O.M.Kellogg, DASA (kellogg@space.otn.dasa.de).
;;
;; This file is part of GNU CC.
;;
;; GNU CC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 1, or (at your option)
;; any later version.
;;
;; GNU CC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GNU CC; see the file COPYING.  If not, write to
;; the Free Software Foundation, 59 Temple Place - Suite 330,
;; Boston, MA 02111-1307, USA.
;;
;; $Log: m1750.md,v $
;; Revision 1.1  1997/02/17 20:39:43  nettleto
;; Initial revision
;;
;;

;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; The 1750 is a military standard 16-bit computer specified in
;; MIL-STD-1750A (July 1980) and MIL-STD-1750B (July 1988). There are many
;; implementations of the specification (IBM, McDonnell Douglas M281,
;; Honeywell GVSC, GEC Plessey MA31750 etc), and most of these are
;; intended for aerospace applications that must be reliable in hostile
;; environments (extremes of temperature, radiation etc).
;;  
;; Space payload applications may need to operate of long
;; periods of time with low power, as well as being physically small. 
;; This means the primary objective of optimization must be to minimise
;; the size of the generated code. However there is the additional 
;; consideration for safety related applications that the generated code
;; must be readable, so that each generated instruction can be traced
;; back to the corresponding line of source.
;;  
;; A further consideration for code generation is the worst case execution
;; time. For many real-time systems, it the worst case execution time that
;; matters, rather than the average execution time. This is quite 
;; different from the usual case with GCC where the objective is to make
;; a program get through as much work as possible. So when generating code
;; we always bear in mind the worst case, and hardly ever go out of our
;; way to optimize the typical case.
;;
;; For most of these applications the 1750's basic 64K by 16-bit word
;; address space is more than adequate. But for some applications we need
;; more space for intructions -- data space can always be fudged. This is
;; where expanded memory comes in and where most compilers head for the
;; door. That is not to say that expanded memory is unsupported, but
;; rather the way that expanded memory is presented to the programmer
;; varies widely among compiler vendors and no one implementation is ideal.
;;  
;; The 1750 is a word addressed architecture, but for GCC we have tried to
;; make it look byte addressed with a few quirky relocation types. However
;; this is not 100% successful so as a 1750 programmer you must watch out.
;;  
;; The mapping of 1750 data types to GCC data types is as follows:
;;
;;  QI  (quarter integer)     int, short, char          16 bits or 1 reg
;;  HI  (double integer)      long                      32 bits or 2 regs
;;  SI  (single integer)      long long                 64 bits or 4 regs
;;  HF  (half float)          single precision float    32 bits or 2 regs
;;  TQF (three quarter float) extended precision float  48 bits or 3 regs
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;

;; 
;; Immediate integer operands Constraints:
;;    'I'  1 .. 16
;;    'J' -1 ..-16
;;    'K'  0 .. 15  // as used in store constant, test bit etc
;;    'L'  0 .. 255
;;    'M' -32768 .. 32767
;;    'N'  1 .. 32  // as used in double length shifts
;;    'O' => 0  (for optimizations and GCC quirks)
;;
;; Register class letters are:
;;     z    R0_1
;;     t    R2
;;     b    base regs (1750 base regs r12 .. r15)
;;     x    index regs (GCC index regs r1 .. r15)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;

;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; `insv'
;;
;; Store operand 3 (which must be valid for `word_mode') into a bit
;; field in operand 0, where operand 1 specifies the width in bits and
;; operand 2 the starting bit.  Operand 0 may have mode `byte_mode' or
;; `word_mode'; often `word_mode' is allowed only for registers.
;; Operands 1 and 2 must be valid for `word_mode'.
;;
;; The RTL generation pass generates this instruction only with
;; constants for operands 1 and 2.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "insv"
  [(set (zero_extract:QI (match_operand:QI 0 "general_operand" "")
                         (match_operand:QI 1 "general_operand" "")
                         (match_operand:QI 2 "general_operand" ""))
        (match_operand:QI 3 "register_operand" "r"))]
  ""
  "
  if (GET_CODE (operands[0]) != MEM
      || GET_CODE (operands[1]) != CONST_INT
      || GET_CODE (operands[2]) != CONST_INT)
    FAIL;

  if (INTVAL (operands [1]) == 8) 
    {
      if (INTVAL (operands [2]) == 0)
        {
          emit_insn (gen_stub (operands[0], operands[3]));
          DONE;
        }
      else if (INTVAL (operands [2]) == 8)
        {
          emit_insn (gen_stlb (operands[0], operands[3]));
          DONE;
        }
    }
  FAIL;

  ")

;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; `extv'
;;
;; Extract a bit field from operand 1 (a register or memory operand),
;; where operand 2 specifies the width in bits and operand 3 the
;; starting bit, and store it in operand 0.  Operand 0 must have mode
;; `word_mode'.  Operand 1 may have mode `byte_mode' or `word_mode';
;; often `word_mode' is allowed only for registers.  Operands 2 and 3
;; must be valid for `word_mode'.
;;
;; The RTL generation pass generates this instruction only with
;; constants for operands 2 and 3.
;;
;; The bit-field value is sign-extended to a full word integer before
;; it is stored in operand 0.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "extv"
  [(set (match_operand:QI 0 "general_operand" "")
        (sign_extract:QI (match_operand:QI 1 "general_operand" "")
                         (match_operand:QI 2 "general_operand" "")
                         (match_operand:QI 3 "general_operand" "")))]
  ""
  "
  if (GET_CODE (operands[0]) != REG
      || GET_CODE (operands[1]) != MEM
      || GET_CODE (operands[2]) != CONST_INT
      || GET_CODE (operands[3]) != CONST_INT)
    FAIL;

  if (INTVAL (operands [2]) == 8) 
    {
      if (INTVAL (operands [3]) == 0)
        {
          rtx addr = force_reg (QImode, XEXP (operands[1], 0));

          emit_insn (gen_ashrqi3 (operands[0], addr, operands[2]));
          DONE;
        }
      else if (INTVAL (operands [3]) == 8)
        {
          rtx addr = force_reg (QImode, XEXP (operands[1], 0));
          rtx temp = gen_reg_rtx (QImode);

          emit_insn (gen_rotlqi3 (temp, addr, operands [2]));
          emit_insn (gen_ashrqi3 (operands[0], temp, operands[2]));
          DONE;
        }
    }
  FAIL;

  ")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; `extzv'
;; Like `extv' except that the bit-field value is zero-extended.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "extzv"
  [(set (match_operand:QI 0 "general_operand" "")
        (zero_extract:QI (match_operand:QI 1 "memory_operand" "")
                         (match_operand:QI 2 "general_operand" "")
                         (match_operand:QI 3 "general_operand" "")))]
  ""
  "
  if (GET_CODE (operands[0]) != REG
      || GET_CODE (operands[1]) != MEM
      || GET_CODE (operands[2]) != CONST_INT
      || GET_CODE (operands[3]) != CONST_INT)
    FAIL;

  if (INTVAL (operands [2]) == 8) 
    {
      if (INTVAL (operands [3]) == 0)
        {
          emit_insn (gen_lub (operands[0], operands[1]));
          DONE;
        }
      else if (INTVAL (operands [3]) == 8)
        {
          emit_insn (gen_llb (operands[0], operands[1]));
          DONE;
        }
    }
  FAIL;

  ")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 'lshrqi3' 'lshrhi3' 'ashrqi3' 'ashrhi3'
;;
;; These right shifts are not supported by the 1750 "Count in Register"
;; instructions so negate the shift count and do a left shift. Constant 
;; right shifts are supported so leave them alone.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "lshrqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (lshiftrt:QI (match_operand:QI 1 "register_operand" "0")
                   (match_operand:QI 2 "nonmemory_operand" "g")))]
  ""
  "
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      int places = INTVAL (operands [2]);
      rtx tmp;

      if (places > 16)
        places = 16;
      else if (places < -16)
        places = -16;

      if (places > 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, places);
          emit_insn (gen_srl (operands[0], operands[1], tmp));
        }
      else if (places < 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, -places);
          emit_insn (gen_sll (operands[0], operands[1], tmp));
        }
    }
  else 
    {
      emit_insn (gen_slr (operands[0], operands[1],
                          negate_rtx (QImode, operands[2])));
    }
    DONE;
")

(define_expand "lshrhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (lshiftrt:HI (match_operand:HI 1 "register_operand" "0")
                   (match_operand:QI 2 "nonmemory_operand" "g")))]
  ""
  "
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      int places = INTVAL (operands [2]);
      rtx tmp;

      if (places > 32)
        places = 32;
      else if (places < -32)
        places = -32;

      if (places > 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, places);
          emit_insn (gen_dsrl (operands[0], operands[1], tmp));
        }
      else if (places < 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, -places);
          emit_insn (gen_ashlhi3 (operands[0], operands[1], tmp));
        }
    }
  else
    {
      emit_insn (gen_dslr (operands[0], operands[1],
                           negate_rtx (QImode, operands[2])));
    }
  DONE;

")

(define_expand "ashrqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ashiftrt:QI (match_operand:QI 1 "register_operand" "0")
                   (match_operand:QI 2 "nonmemory_operand" "g")))]
  ""
  "
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      int places = INTVAL (operands [2]);
      rtx tmp;

      if (places > 16)
        places = 16;
      else if (places < -16)
        places = -16;

      if (places > 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, places);
          emit_insn (gen_sra (operands[0], operands[1], tmp));
        }
      else if (places < 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, -places);
          emit_insn (gen_sll (operands[0], operands[1], tmp));
        }
    }
  else
    {
      emit_insn (gen_sar (operands[0], operands[1],
                          negate_rtx (QImode, operands[2])));
    }
  DONE;
")

(define_expand "ashrhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ashiftrt:HI (match_operand:HI 1 "register_operand" "0")
                     (match_operand:QI 2 "nonmemory_operand" "g")))]
  ""
  "
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      int places = INTVAL (operands [2]);
      rtx tmp;

      if (places > 32)
        places = 32;
      else if (places < -32)
        places = -32;

      if (places > 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, places);
          emit_insn (gen_dsra (operands[0], operands[1], tmp));
        }
      else if (places < 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, -places);
          emit_insn (gen_ashlhi3 (operands[0], operands[1], tmp));
        }
    }
  else
    {
      emit_insn (gen_dsar (operands[0], operands[1],
                           negate_rtx (QImode, operands[2])));
    }
  DONE;
")

(define_expand "ashlqi3"
  [(set (match_operand:QI 0 "register_operand" "")
        (ashift:QI (match_operand:QI 1 "register_operand" "")
                   (match_operand:QI 2 "nonmemory_operand" "")))]
  ""
  "
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      int places = INTVAL (operands [2]);
      rtx tmp;

      if (places > 16)
        places = 16;
      else if (places < -16)
        places = -16;

      if (places > 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, places);
          emit_insn (gen_sll (operands[0], operands[1], tmp));
        }
      else if (places < 0)
        {
          tmp = gen_rtx (CONST_INT, VOIDmode, -places);
          emit_insn (gen_sra (operands[0], operands[1], tmp));
        }
    }
  else
    {
      emit_insn (gen_sar (operands[0], operands[1], operands[2]));
    }
  DONE;
")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; The 1750 has no extended floating negate, so subtract from zero instead.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "negtqf2"
  [(set (match_operand:TQF 0 "register_operand" "=&r")
        (neg:TQF (match_operand:TQF 1 "register_operand" "r")))]
  ""
  "
   emit_insn (gen_rtx (SET, VOIDmode, operands [0], 
                                      force_const_mem (TQFmode, CONST0_RTX (TQFmode))));
   emit_insn (gen_rtx (SET, VOIDmode, operands [0],
                       gen_rtx (MINUS, TQFmode, operands [0], operands [1])));
   DONE;
 ")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 'divqi3' 'modqi3' 'udivqi3'
;;
;; Special handling for divide and modulo, which require two adjacent
;; regs in QI mode. Note that "umodqi3" is taken care of by the target-
;; independent part of the code generator.
;;
;; Note: divqi3 and modqi3 are much too complicated, and generate no better
;; code than the simple patterns we had before. However, divide is a low
;; priority for improvement. What we want to avoid is killing the ls half
;; of the HI register before the divide instruction. It is killed by the
;; divide and it is OK for this register to be used for the divisor. Where
;; the dividend and divisor are in adjacent regs we have to generate an
;; extra move.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "divqi3"
  [(set (match_operand:QI 0 "register_operand" "")
        (div:QI (match_operand:QI 1 "register_operand" "")
                (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  rtx reg1 = gen_reg_rtx (HImode);
  rtx subreg0 = gen_rtx (SUBREG, QImode, reg1, 0);

  emit_insn (
    gen_rtx (PARALLEL, VOIDmode,
             gen_rtvec (2,
               gen_rtx (SET, VOIDmode,
                        gen_rtx (SUBREG, QImode, reg1, 0),
                        gen_rtx (DIV, QImode, operand1, operand2)),
               gen_rtx (SET, VOIDmode,
                        gen_rtx (SUBREG, QImode, reg1, 1),
                        gen_rtx (MOD, QImode, operand1, operand2)))));

  emit_insn (gen_rtx (SET, VOIDmode, operands[0], subreg0));
  DONE;
}")

(define_expand "modqi3"
  [(set (match_operand:QI 0 "register_operand" "")
        (mod:QI (match_operand:QI 1 "register_operand" "")
                (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  rtx reg1 = gen_reg_rtx (HImode);
  rtx subreg0 = gen_rtx (SUBREG, QImode, reg1, 0);
  rtx subreg1 = gen_rtx (SUBREG, QImode, reg1, 1);

  emit_insn (
    gen_rtx (PARALLEL, VOIDmode,
             gen_rtvec (2,
               gen_rtx (SET, VOIDmode,
                        gen_rtx (SUBREG, QImode, reg1, 0),
                        gen_rtx (DIV, QImode, operand1, operand2)),
               gen_rtx (SET, VOIDmode,
                        gen_rtx (SUBREG, QImode, reg1, 1),
                        gen_rtx (MOD, QImode, operand1, operand2)))));

  emit_insn (gen_rtx (SET, VOIDmode, operands[0], subreg1));
  DONE;
}")

(define_expand "udivqi3"
  [(set (match_operand:QI 0 "register_operand" "")
        (udiv:QI (match_operand:QI 1 "register_operand" "")
                (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  rtx rx = gen_reg_rtx (HImode);
  rtx ry = gen_reg_rtx (HImode);

  if (GET_CODE (operands [1]) == CONST_INT) 
    operands [1] = force_const_mem (QImode, operands [1]);

  if (GET_CODE (operands [2]) == CONST_INT) 
    operands [2] = force_const_mem (QImode, operands [2]);

  emit_insn (gen_zero_extendqihi2 (rx, operands[1]));
  emit_insn (gen_zero_extendqihi2 (ry, operands[2]));
  emit_insn (gen_rtx (SET, VOIDmode, rx,
                        gen_rtx (DIV, HImode, rx, ry)));
  emit_insn (gen_rtx (SET, VOIDmode, operands[0],
                        gen_rtx (SUBREG, QImode, rx, 1)));
  DONE;
}")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; mulhisi3 umulhisi3 umodhi3 udivhi3
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "xxxmulhisi3"
  [(set (match_operand:SI 0 "general_operand" "")
        (mult:SI (sign_extend:SI (match_operand:HI 1 "general_operand" ""))
                 (sign_extend:SI (match_operand:HI 2 "general_operand" ""))))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__mulhisi3\"), 
    operands [0],
    0,
    SImode, 2,
    operands[1], HImode,
    operands[2], HImode);

  DONE;
}")

(define_expand "umulhisi3"
  [(set (match_operand:SI 0 "general_operand" "")
        (mult:SI (zero_extend:SI (match_operand:HI 1 "general_operand" ""))
                 (zero_extend:SI (match_operand:HI 2 "general_operand" ""))))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__umulhisi3\"), 
    operands [0],
    0,
    SImode, 2,
    operands[1], HImode,
    operands[2], HImode);

  DONE;
}")

(define_expand "umodhi3"
  [(set (match_operand:HI 0 "general_operand" "")
        (umod:HI (match_operand:HI 1 "general_operand" "")
                 (match_operand:HI 2 "general_operand" "")))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__umodhi3\"), 
    operands [0],
    0,
    HImode, 2,
    operands[1], HImode,
    operands[2], HImode);

  DONE;
}")


(define_expand "udivhi3"
  [(set (match_operand:HI 0 "general_operand" "")
        (udiv:HI (match_operand:HI 1 "general_operand" "")
                 (match_operand:HI 2 "general_operand" "")))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__udivhi3\"), 
    operands [0],
    0,
    HImode, 2,
    operands[1], HImode,
    operands[2], HImode);

  DONE;
}")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 64-bit int to/from extended float conversions
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "fix_trunctqfsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (fix:SI (fix:TQF (match_operand:TQF 1 "register_operand" "r"))))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__fix_trunctqfsi2\"), 
    operands [0],
    0,
    SImode, 1,
    operands[1], TQFmode);

  DONE;
}")

(define_expand "fixuns_trunctqfsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (fix:SI (fix:TQF (match_operand:TQF 1 "register_operand" "r"))))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__fixuns_trunctqfsi2\"), 
    operands [0],
    0,
    SImode, 1,
    operands[1], TQFmode);

  DONE;
}")

(define_expand "floatsitqf2"
  [(set (match_operand:TQF 0 "register_operand" "=r")
        (float:TQF (match_operand:SI 1 "register_operand" "r")))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__floatsitqf2\"), 
    operands [0],
    0,
    TQFmode, 1,
    operands[1], SImode);

  DONE;
}")

(define_expand "floatunssitqf2"
  [(set (match_operand:TQF 0 "register_operand" "=r")
        (float:TQF (match_operand:SI 1 "register_operand" "r")))]
  ""
  "
{
  emit_library_call_value (
    gen_rtx (SYMBOL_REF, Pmode, \"__floatunssitqf2\"), 
    operands [0],
    0,
    TQFmode, 1,
    operands[1], SImode);

  DONE;
}")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Integer and floating compare.
;;
;; All scalar comparisions are deferred until we see the conditional branch 
;; instruction. This is because for integer comparisons, the conditional 
;; branch may be unsigned, in which case the compare need to be done 
;; differently. For floating compares it is not necessary to use a floating
;; compare instruction is one of the operands is zero. This is because we
;; can tell if a floating number is zero, negative or greater than zero by
;; testing just the most significant word.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "cmpqi"
    [(set (cc0)
          (compare (match_operand:QI 0 "register_operand" "")
                   (match_operand:QI 1 "general_operand" "")))]
  ""
  "
  m1750_compare_op0 = operands[0];
  m1750_compare_op1 = operands[1];
  m1750_compare_mode = QImode;
  m1750_compare_flag = 1;
  DONE;
  ")

(define_expand "cmphi"
    [(set (cc0)
          (compare (match_operand:HI 0 "register_operand" "")
                   (match_operand:HI 1 "general_operand" "")))]
  ""
  "
  m1750_compare_op0 = operands[0];
  m1750_compare_op1 = operands[1];
  m1750_compare_mode = HImode;
  m1750_compare_flag = 1;
  DONE;
  ")

(define_expand "cmphf"
    [(set (cc0)
          (compare (match_operand:HF 0 "register_operand" "")
                   (match_operand:HF 1 "nonimmediate_operand" "")))]
  ""
  "
  m1750_compare_op0 = operands[0];
  m1750_compare_op1 = operands[1];
  m1750_compare_mode = HFmode;
  m1750_compare_flag = 1;
  DONE;
  ")

(define_expand "cmptqf"
    [(set (cc0)
          (compare (match_operand:TQF 0 "register_operand" "")
                   (match_operand:TQF 1 "nonimmediate_operand" "")))]
  ""
  "
  m1750_compare_op0 = operands[0];
  m1750_compare_op1 = operands[1];
  m1750_compare_mode = TQFmode;
  m1750_compare_flag = 1;
  DONE;
  ")

;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Conditional branch instructions
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "beq"
  [(set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if ((m1750_compare_mode == HFmode || m1750_compare_mode == TQFmode)
          && constant_zero_p (m1750_compare_op1))
        emit_insn (
          gen_rtx (SET, QImode,
            cc0_rtx,
            m1750_compare_op0));
      else
        emit_insn (
          gen_rtx (SET, VOIDmode,
            cc0_rtx,
            gen_rtx (COMPARE, VOIDmode, m1750_compare_op0, m1750_compare_op1)));
    }
  ")

(define_expand "bne"
  [(set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if ((m1750_compare_mode == HFmode || m1750_compare_mode == TQFmode)
          && constant_zero_p (m1750_compare_op1))
        emit_insn (
          gen_rtx (SET, QImode,
            cc0_rtx,
            m1750_compare_op0));
      else
        emit_insn (
          gen_rtx (SET, VOIDmode,
            cc0_rtx,
            gen_rtx (COMPARE, VOIDmode, m1750_compare_op0, m1750_compare_op1)));
    }
  ")

(define_expand "blt"
  [(set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if ((m1750_compare_mode == HFmode || m1750_compare_mode == TQFmode)
          && constant_zero_p (m1750_compare_op1))
        emit_insn (
          gen_rtx (SET, QImode,
            cc0_rtx,
            m1750_compare_op0));
      else
        emit_insn (
          gen_rtx (SET, VOIDmode,
            cc0_rtx,
            gen_rtx (COMPARE, VOIDmode, m1750_compare_op0, m1750_compare_op1)));
    }
  ")

(define_expand "bgt"
  [(set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if ((m1750_compare_mode == HFmode || m1750_compare_mode == TQFmode)
          && constant_zero_p (m1750_compare_op1))
        emit_insn (
          gen_rtx (SET, QImode,
            cc0_rtx,
            m1750_compare_op0));
      else
        emit_insn (
          gen_rtx (SET, VOIDmode,
            cc0_rtx,
            gen_rtx (COMPARE, VOIDmode, m1750_compare_op0, m1750_compare_op1)));
    }
  ")

(define_expand "ble"
  [(set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if ((m1750_compare_mode == HFmode || m1750_compare_mode == TQFmode)
          && constant_zero_p (m1750_compare_op1))
        emit_insn (
          gen_rtx (SET, QImode,
            cc0_rtx,
            m1750_compare_op0));
      else
        emit_insn (
          gen_rtx (SET, VOIDmode,
            cc0_rtx,
            gen_rtx (COMPARE, VOIDmode, m1750_compare_op0, m1750_compare_op1)));
    }
  ")

(define_expand "bge"
  [(set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if ((m1750_compare_mode == HFmode || m1750_compare_mode == TQFmode)
          && constant_zero_p (m1750_compare_op1))
        emit_insn (
          gen_rtx (SET, QImode,
            cc0_rtx,
            m1750_compare_op0));
      else
        emit_insn (
          gen_rtx (SET, VOIDmode,
            cc0_rtx,
            gen_rtx (COMPARE, VOIDmode, m1750_compare_op0, m1750_compare_op1)));
    }
  ")

(define_expand "bltu"
  [(set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  rtx target = NULL;
  rtx r1, r2;
  rtx top_bit;

  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if (m1750_compare_mode == QImode)
        top_bit = GEN_INT(0x8000);
      else
        top_bit = GEN_INT(0x80000000);

      r1 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op0,
                             top_bit, target, 0, OPTAB_DIRECT);

      r2 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op1,
                             top_bit, target, 0, OPTAB_DIRECT);

      emit_insn (
        gen_rtx (SET, VOIDmode,
          cc0_rtx,
          gen_rtx (COMPARE, m1750_compare_mode, r1, r2)));
    }    
}")

(define_expand "bgtu"
  [(set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  rtx target = NULL;
  rtx r1, r2;
  rtx top_bit;

  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if (m1750_compare_mode == QImode)
        top_bit = GEN_INT(0x8000);
      else
        top_bit = GEN_INT(0x80000000);

      r1 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op0,
                             top_bit, target, 0, OPTAB_DIRECT);

      r2 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op1,
                             top_bit, target, 0, OPTAB_DIRECT);

      emit_insn (
        gen_rtx (SET, VOIDmode,
          cc0_rtx,
          gen_rtx (COMPARE, m1750_compare_mode, r1, r2)));
    }
}")

(define_expand "bleu"
  [(set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  rtx target = NULL;
  rtx r1, r2;
  rtx top_bit;

  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;

      if (m1750_compare_mode == QImode)
        top_bit = GEN_INT(0x8000);
      else
        top_bit = GEN_INT(0x80000000);

      r1 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op0,
                             top_bit, target, 0, OPTAB_DIRECT);

      r2 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op1,
                             top_bit, target, 0, OPTAB_DIRECT);

      emit_insn (
        gen_rtx (SET, VOIDmode,
          cc0_rtx,
          gen_rtx (COMPARE, m1750_compare_mode, r1, r2)));
    }
}")

(define_expand "bgeu"
  [(set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  rtx target = NULL;
  rtx r1, r2;
  rtx top_bit;

  if (m1750_compare_flag)
    {
      m1750_compare_flag = 0;
  
      if (m1750_compare_mode == QImode)
        top_bit = GEN_INT(0x8000);
      else
        top_bit = GEN_INT(0x80000000);

      r1 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op0,
                             top_bit, target, 0, OPTAB_DIRECT);

      r2 = expand_binop (m1750_compare_mode, xor_optab,
                             m1750_compare_op1,
                             top_bit, target, 0, OPTAB_DIRECT);

      emit_insn (
        gen_rtx (SET, VOIDmode,
          cc0_rtx,
          gen_rtx (COMPARE, m1750_compare_mode, r1, r2)));
    }
}")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 'load_multiple' 'store_multiple'
;;
;; Note: The 1750 instructions can only load and store starting at 
;; register R0.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "load_multiple"
  [(set (match_operand 0 "" "")
        (match_operand 1 "" ""))
   (use (match_operand 2 "" ""))]
  ""
  "
  if (GET_CODE (operands[2]) != CONST_INT
      || INTVAL (operands[2]) > 16
      || GET_CODE (operands[1]) != MEM
      || GET_CODE (operands[0]) != REG
      || REGNO (operands[0]) != 0)
    FAIL;

   emit_insn (
     gen_lm (
       operands [0], 
       operands [1], 
       GEN_INT (INTVAL (operands[2]) - 1)));
   DONE;
")

(define_expand "store_multiple"
  [(set (match_operand 0 "" "")
        (match_operand 1 "" ""))
   (use (match_operand 2 "" ""))]
  ""
  "
  if (GET_CODE (operands[2]) != CONST_INT
     || INTVAL (operands[2]) > 16
     || GET_CODE (operands[0]) != MEM
     || GET_CODE (operands[1]) != REG
     || REGNO (operands[1]) != 0)
   FAIL;

   emit_insn (
     gen_stm (
       operands [0], 
       operands [1], 
       GEN_INT (INTVAL (operands[2]) - 1)));
   DONE;
")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.1 Execute Input/Output
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.2 Vectored Input/Output
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.3 Set bit
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "setbit1"
  [(set (zero_extract:QI (match_operand:QI 0 "general_operand" "=m,r")
                         (const_int 1)
                         (match_operand:QI 1 "const_int_operand" "K,K"))
        (const_int 1))]
  ""
  "@
    sb     %1,%0
    sbr    %1,%0")

(define_insn "setbit2"
  [(set (mem:QI  (match_operand:QI 0 "memory_operand" "m"))
        (ior:QI  (mem:QI (match_operand:QI 1 "memory_operand" "0"))
                 (match_operand:QI 2 "const_int_operand" "i")))]
  "one_bit_set_p (INTVAL (operands [2]))"
  "sbi    %b2,%0")

(define_insn "setbit3"
  [(set (match_operand:QI 0 "general_operand" "=m,r")
        (ior:QI  (match_operand:QI 1 "general_operand" "0,0")
                 (match_operand:QI 2 "const_int_operand" "i,i")))]
  "one_bit_set_p (INTVAL (operands [2]))"
  "@
    sb     %b2,%0
    sbr    %b2,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.4 Reset bit
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "resetbit1"
  [(set (zero_extract:QI (match_operand:QI 0 "memory_operand" "=r,m")
                         (const_int 1)
                         (match_operand:QI 1 "const_int_operand" "K,K"))
        (const_int 0))]
  ""
  "@
    rbr    %1,%0
    rb     %1,%0")

(define_insn "resetbit2"
  [(set (mem:QI  (match_operand:QI 0 "memory_operand" "m"))
        (and:QI  (mem:QI (match_operand:QI 1 "memory_operand" "0"))
                 (match_operand:QI 2 "const_int_operand" "i")))]
  "one_bit_set_p ((~INTVAL (operands [2])) & 0xffff)"
  "rbi    %B2,%0")

(define_insn "resetbit3"
  [(set (match_operand:QI 0 "general_operand" "=m,r")
        (and:QI  (match_operand:QI 1 "general_operand" "0,0")
                 (match_operand:QI 2 "const_int_operand" "i,i")))]
  "one_bit_set_p ((~INTVAL (operands [2])) & 0xffff)"
  "@
    rb     %B2,%0
    rbr    %B2,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.5 Test bit
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "testbit1"
  [(set (cc0) 
        (zero_extract (mem:QI (match_operand:QI 0 "memory_operand" "m"))
                      (const_int 1)
                      (match_operand:QI 1 "const_int_operand" "K")))]
  ""
  "tbi    %1,%0")

(define_insn "testbit2"
  [(set (cc0) 
        (zero_extract (match_operand:QI 0 "general_operand" "r,m")
                      (const_int 1)
                      (match_operand:QI 1 "const_int_operand" "K,K")))]
  ""
  "@
    tbr    %1,%0
    tb     %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.6 Test and set bit
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.7 Set variable bit in register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "svbr"
  [(set (match_operand:QI 0 "general_operand" "=r")
        (ior:QI  (match_operand:QI 1 "general_operand" "0")
                 (lshiftrt:QI (const_int 0x8000)
                      (match_operand:QI 2 "register_operand" "r"))))]
  ""
  "svbr   %2,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.8 Reset variable bit in register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "rvbrqi"
  [(set (match_operand:QI 0 "general_operand" "=r")
        (and:QI  (match_operand:QI 1 "general_operand" "0")
            (not:QI (lshiftrt:QI (const_int 0x8000)
                        (match_operand:QI 2 "register_operand" "r")))))]
  ""
  "rvbr   %2,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.9 Test variable bit in register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "tvbrqi"
  [(set (cc0) 
        (zero_extract (match_operand:QI 0 "register_operand" "r")
                      (const_int 1)
                      (match_operand:QI 1 "register_operand" "r")))]
  ""
  "tvbr   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.10 Shift Left Logical
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "sll"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (ashift:QI (match_operand:QI 1 "register_operand" "0,0")
                   (match_operand:QI 2 "const_int_operand" "I,i")))]
  ""
  "@
    sll    %0,%2
    sll    %0,16")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.11 Shift Right Logical
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "srl"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (lshiftrt:QI (match_operand:QI 1 "register_operand" "0,0")
                     (match_operand:QI 2 "immediate_operand" "I,i")))]
  ""
  "@
    srl    %0,%2
    srl    %0,16")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.12 Shift Right Arithmetic
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "sra"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (ashiftrt:QI (match_operand:QI 1 "register_operand" "0,0")
                     (match_operand:QI 2 "immediate_operand" "I,i")))]
  ""
  "@
    sra    %0,%2
    sra    %0,16")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.13 Shift Left Cyclic
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "rotlqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (rotate:QI (match_operand:QI 1 "register_operand" "0")
                   (match_operand:QI 2 "immediate_operand" "I")))]
  ""
  "*
    if (INTVAL (operands [2]) == 8)
      return \"xbr    %0\";
    else
      return \"slc    %0,%2\";
")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.14 Double Shift Left Logical
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "ashlhi3"
  [(set (match_operand:HI 0 "register_operand" "=r,r,r")
        (ashift:HI (match_operand:HI 1 "register_operand" "0,0,0")
                   (match_operand:QI 2 "immediate_operand" "I,N,i")))]
  ""
  "@
    dsll   %0,%2
    dsll   %0,16\;dsll   %0,%w2
    dsll   %0,16\;dsll   %0,16")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.15 Double Shift Right Logical
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "dsrl"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (lshiftrt:HI (match_operand:HI 1 "register_operand" "0,0")
                     (match_operand:QI 2 "immediate_operand" "I,N")))]
  ""
  "@
    dsrl   %0,%2
    dsrl   %0,16\;dsrl   %0,%w2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.16 Double Shift Right Arithmetic
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "dsra"
  [(set (match_operand:HI 0 "register_operand" "=r,r,r")
        (ashiftrt:HI (match_operand:HI 1 "register_operand" "0,0,0")
                     (match_operand:QI 2 "immediate_operand" "I,N,i")))]
  ""
  "@
    dsra   %0,%2
    dsra   %0,16\;dsra   %0,%w2
    dsra   %0,16\;dsra   %0,16")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.17 Double Shift Left Cyclic
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "rotlhi3"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (rotate:HI (match_operand:HI 1 "register_operand" "0,0")
                     (match_operand:QI 2 "immediate_operand" "I,N")))]
  ""
  "@
    dslc   %0,%2
    xwr    %0,%d0\;dslc   %0,%w2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.18 Shift Logical, Count in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "slr"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (lshiftrt:QI (match_operand:QI 1 "register_operand" "0")
                   (neg:QI (match_operand:QI 2 "register_operand" "r"))))]
  ""
  "slr    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.19 Shift Arithmetic, Count in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "sar"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ashift:QI (match_operand:QI 1 "register_operand" "0")
                   (match_operand:QI 2 "register_operand" "r")))]
  ""
  "sar    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.20 Shift Cyclic, Count in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "scr"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (rotate:QI (match_operand:QI 1 "register_operand" "0")
                   (match_operand:QI 2 "register_operand" "r")))]
  ""
  "scr    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.21 Double Shift Logical, Count in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "dslr"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (lshiftrt:HI (match_operand:HI 1 "register_operand" "0")
                   (neg:QI (match_operand:QI 2 "general_operand" "r"))))]
  ""
  "dslr   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.22 Double Shift Arithmetic, Count in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "dsar"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ashift:HI (match_operand:HI 1 "register_operand" "0")
                     (match_operand:QI 2 "register_operand" "r")))]
  ""
  "dsar   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.23 Double Shift Cyclic, Count in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "dscr"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (rotate:HI (match_operand:HI 1 "register_operand" "0")
                   (match_operand:QI 2 "register_operand" "r")))]
  ""
  "dscr   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.27 Branch unconditionally
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jump"
  [(set (pc)
        (label_ref (match_operand 0 "" "")))]
  ""
  "j      %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.24 Conditional Jump Instructions
;;
;; Note: jc instructions are also generated by the assembler where a branch
;; instruction needs to reach more than +/- 127 words.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "tablejump"
  [(set (pc)
        (match_operand:QI 0 "general_operand" "x,m"))
   (use (label_ref (match_operand 1 "" "")))]
  ""
  "@
    jc     15,0,%0
    jci    15,%0")

(define_insn "indirect_jump"
  [(set (pc) (match_operand:QI 0 "nonimmediate_operand" "m,x"))]
  ""
  "@
    jci    15,%0
    jc     15,0,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.25 Jump to Subroutine
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used. We use sjs instead


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.26 Subtract One and Jump
;;
;; We generate "soj" for readability since it is no smaller than the
;; equivalent sequence "sisp r,1; bnz L". 
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "soj"
  [(set (pc)
        (if_then_else
         (ne (compare (plus:QI (match_operand:QI 0 "register_operand" "=r")
                               (const_int -1))
                      (const_int -1))
             (const_int 0))
         (label_ref (match_operand 1 "" ""))
         (pc)))
   (set (match_dup 0)
        (plus:QI (match_dup 0)
                 (const_int -1)))]
  ""
  "soj    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.28 Branch if equal to zero
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jez"
  [(set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jez    %0")

(define_insn ""
  [(set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "jez    %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.29 Branch if less than zero
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jlt"
  [(set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jlt    %0")


(define_insn ""
  [(set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "jlt    %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.30 Branch to executive
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.31 Branch if Less Than or Equal to Zero
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jle"
  [(set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jle    %0")

(define_insn ""
  [(set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "jle    %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.32 Branch if Greater than Zero
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jgt"
  [(set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jgt    %0")

(define_insn ""
  [(set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "jgt    %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.33 Branch if not Equal to Zero
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jnz"
  [(set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jnz    %0")

(define_insn ""
  [(set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "jnz    %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.34 Branch if Greater than or Equal to Zero
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "jge"
  [(set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jge    %0")

(define_insn ""
  [(set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "jge    %0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.35 Load Status
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler, but generated by the assembler for a long URS


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.36 Stack IC and Jump to Subroutine
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;
(define_insn "call"
  [(call (match_operand:QI 0 "general_operand" "mp,x")
         (match_operand:QI 1 "general_operand" ""))]
  ""
  "@
    sjs    r15,%0
    sjs    r15,0,%0")

(define_insn "call_value"
  [(set (match_operand 0 "register_operand" "r,r")
        (call (match_operand:QI 1 "general_operand" "mp,x")
              (match_operand:QI 2 "general_operand" "")))]
  ""
  "@
    sjs    r15,%1
    sjs    r15,0,%1")

(define_insn "far_call"
  [(call (match_operand:HI 0 "general_operand" "mp,x")
         (match_operand 1 "" ""))]
  ""
  "@
    lsjs   r15,%0
    lsjs   r15,0,%0")

(define_insn "far_call_value"
  [(set (match_operand 0 "register_operand" "r,r")
        (call (match_operand:HI 1 "general_operand" "m,x")
              (match_operand 2 "" "")))]
  ""
  "@
    lsjs   r15,%1
    lsjs   r15,0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.37 Return from Subroutine
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Only generated at the end of function (see 'output_function_epilogue' in 
;; file m1750.c)


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.38 Single Precision Load
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "tstqi"
  [(set (cc0)
        (match_operand:QI 0 "register_operand" "r"))]
  ""
  "lr     %0,%0")

(define_insn "tsthf"
  [(set (cc0)
        (match_operand:HF 0 "register_operand" "r"))]
  ""
  "lr     %0,%0")

(define_insn "tsttqf"
  [(set (cc0)
        (match_operand:TQF 0 "register_operand" "r"))]
  ""
  "lr     %0,%0")

(define_insn "movqi"
  [(set (match_operand:QI 0 "general_operand" "=r,t,t,t,r,r,r,r,r,r,Q,q,m,m")
        (match_operand:QI 1 "general_operand"  "r,Q,q,t,I,J,O,M,i,m,t,t,K,r"))]
  ""
  "@
     lr     %0,%1
     lb     %Q1
     lbx    %Q1
     lr     %0,%1
     lisp   %0,%1
     lisn   %0,%n1
     xorr   %0,%0
     lim    %0,%1
     lim    %0,%1
     l      %0,%1
     stb    %Q0
     stbx   %Q0
     stc    %1,%0  
     st     %1,%0")

(define_insn "movqii"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (mem:QI (match_operand 1 "memory_operand"  "m")))]
  ""
  "li     %0,%1")

(define_insn "trunchiqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (truncate:QI
         (match_operand:HI 1 "register_operand" "r")))]
  ""
  "lr     %1,%d0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.39 Double Precision Load
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;
(define_insn "tsthi"
  [(set (cc0)
        (match_operand:HI 0 "register_operand" "r"))]
  ""
  "dlr    %0,%0")

(define_expand "movhi"
  [(set (match_operand:HI 0 "general_operand" "")
        (match_operand:HI 1 "general_operand" ""))]
  ""
  "
  if (GET_CODE (operands [1]) == CONST_INT 
      || GET_CODE (operands [1]) == CONST_DOUBLE)
    operands [1] = force_const_mem (HImode, operands [1]);
  ")

(define_insn ""
  [(set (match_operand:HI 0 "general_operand" "=r,z,z,r,Q,q,m")
        (match_operand:HI 1 "general_operand"  "r,Q,q,m,z,z,r"))]
  ""
  "@
    dlr    %0,%1
    dlb    %Q1
    dlbx   %Q1
    dl     %0,%1
    dstb   %Q0
    dstx   %Q0
    dst    %1,%0")

(define_insn "movhii"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (mem:HI (match_operand 1 "memory_operand"  "m")))]
  ""
  "dli    %0,%1")

(define_expand "movhf"
  [(set (match_operand:HF 0 "general_operand" "")
        (match_operand:HF 1 "general_operand" ""))]
  ""
  "
  if (GET_CODE (operands [1]) == CONST_DOUBLE)
    operands [1] = force_const_mem (HFmode, operands [1]);
  ")

(define_insn ""
  [(set (match_operand:HF 0 "general_operand" "=r,z,z,r,r,Q,q,m")
        (match_operand:HF 1 "general_operand"  "r,Q,q,m,i,z,z,r"))]
  ""
  "@
    dlr    %0,%1
    dlb    %Q1
    dlbx   %Q1
    dl     %0,%1
    dl     %0,%1
    dstb   %Q0
    dstx   %Q0
    dst    %1,%0")

(define_insn "movhfi"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (mem:HF (match_operand 1 "memory_operand"  "m")))]
  ""
  "dli    %0,%1")

(define_expand "movsi"
  [(set (match_operand:SI 0 "general_operand" "")
        (match_operand:SI 1 "general_operand" ""))]
  ""
  "
  if (GET_CODE (operands [1]) == CONST_INT
      || GET_CODE (operands [1]) == CONST_DOUBLE)
    {
      operands [1] = force_const_mem (SImode, operands [1]);
    }

  ")

(define_insn "movsi_insn"
  [(set (match_operand:SI 0 "general_operand" "=y,m,r,r,o")
        (match_operand:SI 1 "general_operand"  "m,y,r,o,r"))]
  ""
  "*
  switch (which_alternative)
    {
    case 0:
      /* memory to r0/1/2/3 */
      output_asm_insn (\"lm     3,%1\", operands);
      break;
    case 1:
      /* r0/1/2/3 to memory */
      output_asm_insn (\"stm    3,%0\", operands);
      break;
    case 2:
      /* register to register */
      if (REGNO (operands [0]) != REGNO (operands [1]))
        {
          output_asm_insn (\"dlr    %0,%1\", operands);
          output_asm_insn (\"dlr    %t0,%t1\", operands);
        }
      break;
    case 3:
      /* offsetable memory ref to register */
      output_asm_insn (\"dl     %0,%1\", operands);
      operands[1] = adj_offsettable_operand (operands[1], 4);
      output_asm_insn (\"dl     %t0,%1\", operands);
      break;
    case 4:
      /* register to offsetable memory ref */
      output_asm_insn (\"dst    %1,%0\", operands);
      operands[0] = adj_offsettable_operand (operands[0], 4);
      output_asm_insn (\"dst    %t1,%0\", operands);
      break;
    }
  return \"\";
  ")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.40 Load Multiple
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "lm"
  [(set (match_operand:QI 0 "register_operand" "=r") 
        (match_operand:QI 1 "memory_operand" "m"))
   (use (match_operand 2 "immediate_operand" ""))]
  ""
  "lm     %2,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.41 Extended Precision Floating Point Load
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "movtqf"
  [(set (match_operand:TQF 0 "general_operand" "")
        (match_operand:TQF 1 "general_operand" ""))]
  ""
  "
  if (GET_CODE (operands [1]) == CONST_INT
      || GET_CODE (operands [1]) == CONST_DOUBLE)
    operands [1] = force_const_mem (TQFmode, operands [1]);
  ")

(define_insn ""
  [(set (match_operand:TQF 0 "general_operand" "=r,r,r,m")
        (match_operand:TQF 1 "general_operand"  "r,m,m,r"))]
  ""
  "@
    eflr   %0,%1
    efl    %0,%1
    efl    %0,%1
    efst   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.42 Load from Upper Byte
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "lub"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (zero_extract:QI (match_operand:QI 1 "memory_operand" "m")
                         (const_int 8)
                         (const_int 0)))]
  ""
  "lub    %0,%1")

(define_insn ""
  [(set (match_operand:QI 0 "register_operand" "=r")
        (lshiftrt:QI (match_operand:QI 1 "memory_operand" "m")
                     (const_int 8)))]
  ""
  "lub    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.43 Load from Lower Byte
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "llb"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (zero_extract:QI (match_operand:QI 1 "memory_operand" "m")
                         (const_int 8)
                         (const_int 8)))]
  ""
  "llb    %0,%1")

(define_insn ""
  [(set (match_operand:QI 0 "register_operand" "=r")
        (and:QI (match_operand:QI 1 "memory_operand" "m")
                (const_int 255)))]
  ""
  "llb    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.44 Pop Multiple Registers off the Stack
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn ""
  [(set (match_operand:QI 0 "register_operand" "=r")
        (match_operand:QI 1 "push_operand" ">"))]
  ""
  "popm    %1,%1")

(define_insn ""
  [(set (match_operand:HI 0 "register_operand" "=r")
        (match_operand:HI 1 "push_operand" ">"))]
  ""
  "popm    %1,%d1")

(define_insn ""
  [(set (match_operand:SI 0 "register_operand" "=r")
        (match_operand:SI 1 "push_operand" ">"))]
  ""
  "popm    %1,%q1")

(define_insn ""
  [(set (match_operand:HF 0 "register_operand" "=r")
        (match_operand:HF 1 "push_operand" ">"))]
  ""
  "popm    %1,%d1")

(define_insn ""
  [(set (match_operand:TQF 0 "register_operand" "=r")
        (match_operand:TQF 1 "push_operand" ">"))]
  ""
  "popm    %1,%t1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.45 Single Precision Store
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "storeqi"
  [(set (match_operand:QI 0 "memory_operand" "=Q,q,m,m")
        (match_operand:QI 1 "nonmemory_operand"  "t,t,r,K"))]
  ""
  "@
     stb    %Q0
     stbx   %Q0
     st     %1,%0
     stc    %1,%0")

(define_insn "storeqii"
  [(set (mem:QI (match_operand 0 "memory_operand" "=m,m"))
        (match_operand:QI 1 "nonmemory_operand"  "r,K"))]
  ""
  "@
     sti    %1,%0
     stci   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.46 Store a Non-Negative Constant
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "storec"
  [(set (match_operand:QI 0 "memory_operand" "=m")
        (match_operand:QI 1 "const_int_operand"  "K"))]
  ""
  "stc    %1,%0")

(define_insn "storeci"
  [(set (mem:QI (match_operand 0 "memory_operand" "=m"))
        (match_operand:QI 1 "const_int_operand"  "K"))]
  ""
  "stci   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.47 Move Multiple Words, Memory to Memory
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Block move instruction.  The addresses of the destination and
;; source strings are the first two operands, and both are in mode
;; `Pmode'.  The number of bytes to move is the third operand, in
;; mode M.
;;
;; The fourth operand is the known shared alignment of the source and
;; destination, in the form of a `const_int' rtx.  Thus, if the
;; compiler knows that both source and destination are word-aligned,
;; it may provide the value 4 for this operand.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_expand "movstrqi"
  [(set (match_operand:BLK 0 "general_operand" "")
        (match_operand:BLK 1 "general_operand" ""))
   (use (match_operand:QI 2 "general_operand" ""))
   (match_operand 3 "" "")]
   ""
   "
{
  rtx addr0 = copy_to_mode_reg (Pmode, XEXP (operands[0], 0));
  rtx addr1 = copy_to_mode_reg (Pmode, XEXP (operands[1], 0));

  rtx reg1 = gen_reg_rtx (HImode);
  rtx subreg0 = gen_rtx (SUBREG, QImode, reg1, 0);
  rtx subreg1 = gen_rtx (SUBREG, QImode, reg1, 1);

  emit_insn (gen_rtx (SET, VOIDmode, subreg0, addr0));
  emit_insn (gen_rtx (SET, VOIDmode, subreg1, operands[2]));

  emit_insn (gen_rtx (PARALLEL, VOIDmode, gen_rtvec (5,
                    gen_rtx (SET, VOIDmode, operands [0], operands [1]),
                    gen_rtx (USE, VOIDmode, reg1),
                    gen_rtx (USE, VOIDmode, addr1),
                    gen_rtx (CLOBBER, VOIDmode, reg1),
                    gen_rtx (CLOBBER, VOIDmode, addr1))));
  DONE;
}")

(define_insn "mov"
  [(set (match_operand:BLK 0 "general_operand" "=m")
        (match_operand:BLK 1 "general_operand" "m"))
   (use (match_operand:HI 2 "register_operand" "r"))
   (use (match_operand:QI 3 "register_operand" "r"))
   (clobber (match_dup 2))
   (clobber (match_dup 3))]
  ""
  "mov    %2,%3")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.48 Double Precision Store
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "storehi"
  [(set (match_operand:HI 0 "memory_operand" "=Q,q,m")
        (match_operand:HI 1 "register_operand"  "z,z,r"))]
  ""
  "@
    dstb   %Q0
    dstx   %Q0
    dst    %1,%0")

(define_insn "storehf"
  [(set (match_operand:HF 0 "memory_operand" "=Q,q,m")
        (match_operand:HF 1 "register_operand"  "z,z,r"))]
  ""
  "@
    dstb   %Q0
    dstx   %Q0
    dst    %1,%0")

(define_insn "storehii"
  [(set (mem:HI (match_operand 0 "memory_operand" "=m"))
        (match_operand:HI 1 "register_operand"  "r"))]
  ""
  "@
    dsti   %1,%0")

(define_insn "storehfi"
  [(set (mem:HF (match_operand 0 "memory_operand" "=m"))
        (match_operand:HF 1 "register_operand"  "r"))]
  ""
  "@
    dsti   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.49 Store Register though Mask
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;(define_insn "srm"
;  [(set (zero_extract:QI (match_operand:QI 0 "memory_operand" "=m"))
;        (match_operand:HI 1 "register_operand" "r"))]
;  ""
;  "srm    %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.50 Store Multiple Registers
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "stm"
  [(set (match_operand:QI 0 "memory_operand" "=m") 
        (match_operand:QI 1 "register_operand" "r"))
   (use (match_operand 2 "immediate_operand" ""))]
  ""
  "stm    %2,%0")

(define_insn "stm2"
  [(set (match_operand:BLK 0 "memory_operand" "=m") 
        (match_operand:QI 1 "register_operand" "r"))
   (use (match_operand 2 "immediate_operand" ""))]
  ""
  "stm    %2,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.51 Extended Precision Floating Point Store
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "efst"
  [(set (match_operand:TQF 0 "memory_operand" "=m")
        (match_operand:TQF 1 "register_operand" "r"))]
  ""
  "efst   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.52 Store into Upper Byte
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "stub"
  [(set (zero_extract:QI (match_operand:QI 0 "memory_operand" "=m")
                         (const_int 8)
                         (const_int 0))
        (match_operand:QI 1 "register_operand" "r"))]
  ""
  "stub   %1,%0")

(define_insn "stub2"
  [(set (match_operand:QI 0 "memory_operand" "=m")
        (ior:QI (and:QI (match_operand:QI 2 "memory_operand" "0")
                        (const_int 0x00ff))
                (ashift:QI (match_operand:QI 1 "register_operand" "r")
                           (const_int 8))))]
  ""
  "stub   %1,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.53 Store into Lower Byte
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "stlb"
  [(set (zero_extract:QI (match_operand:QI 0 "memory_operand" "=m")
                         (const_int 8)
                         (const_int 8))
        (match_operand:QI 1 "register_operand" "r"))]
  ""
  "stlb   %1,%0")

(define_insn "stlb2"
  [(set (match_operand:QI 0 "memory_operand" "=m")
        (ior:QI (and:QI (match_operand:QI 1 "memory_operand" "0")
                        (const_int -256))
                (and:QI (match_operand:QI 2 "register_operand" "r")
                        (const_int 255))))]
  ""
  "stlb   %2,%0")

;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.54 Push Multiple Registers onto the Stack
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "pushqi"
  [(set (match_operand:QI 0 "push_operand" "=<")
        (match_operand:QI 1 "general_operand" "r"))]
  ""
  "pshm   %1,%1")

(define_insn "pushhi"
  [(set (match_operand:HI 0 "push_operand" "=<")
        (match_operand:HI 1 "general_operand" "r"))]
  ""
  "pshm   %1,%d1")

(define_insn "pushsi"
  [(set (match_operand:SI 0 "push_operand" "=<")
        (match_operand:SI 1 "general_operand" "r"))]
  ""
  "pshm   %1,%q1")

(define_insn "pushhf"
  [(set (match_operand:HF 0 "push_operand" "=<")
        (match_operand:HF 1 "general_operand" "r"))]
  ""
  "pshm   %1,%d1")

(define_insn "pushtqf"
  [(set (match_operand:TQF 0 "push_operand" "=<")
        (match_operand:TQF 1 "general_operand" "r"))]
  ""
  "pshm   %1,%t1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.55 Single Precision Integer Add
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "addqi3"
  [(set (match_operand:QI 0 "general_operand" "=r,t,t,r,r,r,r,m,m")
        (plus:QI (match_operand:QI 1 "general_operand" "%0,0,0,0,0,0,0,0,0")
                 (match_operand:QI 2 "general_operand"  "r,Q,q,I,J,m,i,I,J")))]
  ""
  "@
    ar     %0,%2
    ab     %Q2
    abx    %Q2
    aisp   %0,%2
    sisp   %0,%n2
    a      %0,%2
    aim    %0,%2
    incm   %2,%0
    decm   %n2,%0") 


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.56 Increment Memory by a Positive Integer
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; see 16-bit add and subtract


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.57 Single Precision Absolute Value of a Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "absqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (abs:QI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "abs    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.58 Double Precision Absolute Value of a Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "abshi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (abs:HI (match_operand:HI 1 "register_operand" "r")))]
  ""
  "dabs   %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.59 Double Precision Integer Add
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "addhi3"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (plus:HI (match_operand:HI 1 "register_operand" "%0,0")
                 (match_operand:HI 2 "general_operand" "r,m")))]
  ""
  "@
    dar    %0,%2
    da     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.60 Floating Point Add
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "addhf3"
  [(set (match_operand:HF 0 "register_operand" "=r,z,z,r")
        (plus:HF (match_operand:HF 1 "register_operand" "%0,0,0,0")
                 (match_operand:HF 2 "general_operand" "r,Q,q,m")))]
  ""
  "@
    far    %0,%2
    fab    %Q2
    fabx   %Q2
    fa     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.61 Extended Precision Floating Point Add
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "addtqf3"
  [(set (match_operand:TQF 0 "register_operand" "=r,r")
        (plus:TQF (match_operand:TQF 1 "register_operand" "%0,0")
                 (match_operand:TQF 2 "general_operand" "r,m")))]
  ""
  "@
    efar   %0,%2
    efa    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.62 Floating Point Absolute Value of a Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "abshf2"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (abs:HF (match_operand:HF 1 "register_operand" "r")))]
  ""
  "fabs   %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.63 Single Precision Integer Subtract
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "subqi3"
  [(set (match_operand:QI 0 "general_operand" "=r,t,t,r,r,r,r,m,m")
        (minus:QI (match_operand:QI 1 "general_operand" "0,0,0,0,0,0,0,0,0")
                  (match_operand:QI 2 "general_operand"  "r,Q,q,I,J,m,i,I,J")))]
  ""
  "@
    sr     %0,%2
    sbb    %Q2
    sbbx   %Q2
    sisp   %0,%2
    aisp   %0,%n2
    s      %0,%2
    sim    %0,%2
    decm   %2,%0
    incm   %n2,%0")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.64 Decrement Memory by a Positive Integer
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; see 16-bit add and subtract


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.65 Single Precision Negate Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "negqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (neg:QI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "neg    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.66 Double Precision Negate Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "neghi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (neg:HI (match_operand:HI 1 "register_operand" "r")))]
  ""
  "dneg   %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.67 Double Precision Integer Subtract
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "subhi3"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (minus:HI (match_operand:HI 1 "register_operand" "0,0")
                  (match_operand:HI 2 "general_operand" "r,m")))]
  ""
  "@
    dsr    %0,%2
    ds     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.68 Floating Point Subtract
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "subhf3"
  [(set (match_operand:HF 0 "register_operand" "=r,z,z,r")
        (minus:HF (match_operand:HF 1 "register_operand" "0,0,0,0")
                  (match_operand:HF 2 "general_operand" "r,Q,q,m")))]
  ""
  "@
    fsr    %0,%2
    fsb    %Q2
    fsbx   %Q2
    fs     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.69 Extended Precision Floating Point Subtract
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "subtqf3"
  [(set (match_operand:TQF 0 "register_operand" "=r,r")
        (minus:TQF (match_operand:TQF 1 "register_operand" "0,0")
                  (match_operand:TQF 2 "general_operand" "r,m")))]
  ""
  "@
    efsr   %0,%2
    efs    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.70 Floating Point Negate
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "neghf2"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (neg:HF (match_operand:HF 1 "register_operand" "r")))]
  ""
  "fneg   %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.71 Single Precision Integer Multiply with 16-bit Product
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "mulqi3"
  [(set (match_operand:QI 0 "register_operand" "=r,r,r,r,r")
        (mult:QI (match_operand:QI 1 "register_operand" "%0,0,0,0,0")
                 (match_operand:QI 2 "general_operand"  "r,I,J,m,i")))]
  ""
  "@
     msr    %0,%2
     misp   %0,%2
     misn   %0,%n2
     ms     %0,%2 
     msim   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.72 Single Precision Integer Multiply with 32-bit Product
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "mulqihi3"
  [(set (match_operand:HI 0 "register_operand" "=r,t,t,r,r")
        (mult:HI (match_operand:QI 1 "register_operand" "%r,r,r,r,r")
                 (match_operand:QI 2 "general_operand" "r,Q,q,m,i")))]
  ""
  "@
    lr     %0,%1\;mr     %0,%2
    lr     %0,%1\;mb     %Q2
    lr     %0,%1\;mbx    %Q2
    lr     %0,%1\;m      %0,%2
    lr     %0,%1\;mim    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.73 Double Precision Integer Multiply
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "mulhi3"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (mult:HI (match_operand:HI 1 "register_operand" "%0,0")
                 (match_operand:HI 2 "general_operand" "r,m")))]
  ""
  "@
    dmr    %0,%2
    dm     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.74 Floating Point Multiply
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "mulhf3"
  [(set (match_operand:HF 0 "register_operand" "=r,z,z,r,r")
        (mult:HF (match_operand:HF 1 "register_operand" "%0,0,0,0,0")
                 (match_operand:HF 2 "general_operand" "r,Q,q,m,i")))]
  ""
  "@
    fmr    %0,%2
    fmb    %Q2
    fmbx   %Q2
    fm     %0,%2
    fm     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.75 Extended Precision Floating Multiply
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "multqf3"
  [(set (match_operand:TQF 0 "register_operand" "=r,r")
        (mult:TQF (match_operand:TQF 1 "register_operand" "%0,0")
                 (match_operand:TQF 2 "general_operand" "r,m")))]
  ""
  "@
    efmr   %0,%2
    efm    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
;; 5.76 Single Precision Integer Divide with 16-bit Dividend 
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
(define_insn "dv"
  [(parallel
    [(set (subreg:QI (match_operand:HI 0 "register_operand" "=r,r,r,r,r") 0) 
          (div:QI (match_operand:QI 1 "register_operand" "r,r,r,r,r") 
                  (match_operand:QI 2 "general_operand"  "r,I,J,m,i")))
     (set (subreg:QI (match_dup 0) 1)
          (mod:QI (match_dup 1)
                  (match_dup 2)))] )]
  ""
  "@
     lr     %0,%1\;dvr    %0,%2
     lr     %0,%1\;disp   %0,%2
     lr     %0,%1\;disn   %0,%n2
     lr     %0,%1\;dv     %0,%2
     lr     %0,%1\;dvim   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.77 Single Precision Integer Divide with 32-bit Dividend
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "divmodhiqi4"
  [(set (match_operand:QI 0 "general_operand" "=r")
        (div:QI (match_operand:HI 1 "general_operand" "r")
                (match_operand:QI 2 "general_operand" "r")))
   (set (match_operand:QI 3 "general_operand" "=r")
        (mod:QI (match_dup 1) (match_dup 2)))
   (clobber (match_dup 1)) ]
  ""
  "*
{
  output_asm_insn (\"dr     %1,%2\", operands);

  if (!find_reg_note (insn, REG_UNUSED, operands[0]))
    output_asm_insn (\"lr     %0,%1\", operands);

  if (!find_reg_note (insn, REG_UNUSED, operands[3]))
    output_asm_insn (\"lr     %3,%d1\", operands);

  return \"\";
}")


;;(define_insn "divmodhiqi4"
;;  [(set (match_operand:QI 0 "register_operand" "=r,t,t,r,r")
;;        (div:QI (match_operand:HI 1 "register_operand" "0,0,0,0,0")
;;                 (match_operand:QI 2 "general_operand"  "r,Q,q,m,i")))
;;   (set (match_operand:QI 3 "register_operand" "=r,r,r,r,r")
;;        (mod:QI (match_dup 1) (match_dup 2)))]
;;  ""
;;  "@
;;     dr     %0,%2
;;     db     %Q2
;;     dbx    %Q2
;;     d      %0,%2
;;     dim    %0,%2")
;;

;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.78 Double Precision Integer Divide 
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "divhi3"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (div:HI (match_operand:HI 1 "register_operand" "0,0")
                (match_operand:HI 2 "general_operand" "r,m")))]
  ""
  "@
    ddr    %0,%2
    dd     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.79 Floating point divide
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "divhf3"
  [(set (match_operand:HF 0 "register_operand" "=r,z,z,r")
        (div:HF (match_operand:HF 1 "register_operand" "0,0,0,0")
                (match_operand:HF 2 "general_operand" "r,Q,q,m")))]
  ""
  "@
    fdr    %0,%2
    fdb    %Q2
    fdbx   %Q2
    fd     %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.80 Extended Precision Floating Point Divide 
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "divtqf3"
  [(set (match_operand:TQF 0 "register_operand" "=r,r")
        (div:TQF (match_operand:TQF 1 "register_operand" "0,0")
                (match_operand:TQF 2 "general_operand" "r,m")))]
  ""
  "@
    efdr   %0,%2
    efd    %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.81 Inclusive Logical OR
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "iorqi3"
  [(set (match_operand:QI 0 "register_operand" "=r,t,t,r,r")
        (ior:QI  (match_operand:QI 1 "register_operand" "%0,0,0,0,0")
                 (match_operand:QI 2 "general_operand" "r,Q,q,m,i")))]
  ""
  "@
    orr    %0,%2
    orb    %Q2
    orbx   %Q2
    or     %0,%2
    orim   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.82 Inclusive Logical AND
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "andqi3"
  [(set (match_operand:QI 0 "register_operand" "=r,t,t,r,r")
        (and:QI  (match_operand:QI 1 "register_operand" "%0,0,0,0,0")
                 (match_operand:QI 2 "general_operand" "r,Q,q,m,i")))]
  ""
  "@
    andr   %0,%2
    andb   %Q2
    andbx  %Q2
    and    %0,%2
    andm   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.83 Exclusive Logical OR
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "xorqi3"
  [(set (match_operand:QI 0 "register_operand" "=r,r,r")
        (xor:QI (match_operand:QI 1 "register_operand" "%0,0,0")
                (match_operand:QI 2 "general_operand"  "r,m,i")))]
  ""
  "@
    xorr   %0,%2
    xor    %0,%2
    xorm   %0,%2")

(define_insn ""
  [(set (match_operand:HI 0 "register_operand" "=r,r,r")
        (xor:HI (match_operand:HI 1 "register_operand" "%0,0,0")
                (match_operand:QI 2 "general_operand"  "r,m,i")))]
  ""
  "@
    xorr   %0,%2
    xor    %0,%2
    xorm   %0,%2")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.84 Exclusive Logical NAND
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "nand1qi3"
  [(set (match_operand:QI 0 "register_operand" "=r,r,r")
        (not:QI (and:QI (match_operand:QI 1 "register_operand" "%0,0,0")
                        (match_operand:QI 2 "general_operand"  "r,m,i"))))]
  ""
  "@
    nr     %0,%2
    n      %0,%2
    nim    %0,%2")

(define_insn "one_cmplqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (not:QI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "@
    nr     %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.85 Convert Floating Point to 16-bit Integer
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "fix_trunchfqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (fix:QI (fix:HF (match_operand:HF 1 "register_operand" "r"))))]
  ""
  "fix    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.86 Convert 16-bit Integer to Floating Point
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "floatqihf2"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (float:HF (match_operand:QI 1 "register_operand" "r")))]
  ""
  "flt    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.87 Convert Extended Precision Floating Point to 32-bit Integer
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "fix_trunctqfhi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (fix:HI (fix:TQF (match_operand:TQF 1 "register_operand" "r"))))]
  ""
  "efix   %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.87 Convert 32-bit Integer to Extended Precision Floating Point
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "floathitqf2"
  [(set (match_operand:TQF 0 "register_operand" "=r")
        (float:TQF (match_operand:HI 1 "register_operand" "r")))]
  ""
  "eflt   %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.89 Exchange Bytes in Register
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; See 5.13, shift left cyclic


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.90 Exchange Words in Registers
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "xwr"
  [(set (match_operand:QI 0 "register_operand" "r")
        (match_operand:QI 1 "register_operand" "r"))
   (set (match_dup 1)
        (match_dup 0))]
  ""
  "xwr    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.91 Single Precision Compare
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "rm_5_91"
  [(set (cc0)
        (compare (match_operand:QI 0 "register_operand" "r,t,t,r,r,r,r")
                 (match_operand:QI 1 "general_operand"  "r,Q,q,I,J,m,i")))]
  ""
  "@
    cr     %0,%1
    cb     %Q1
    cbx    %Q1
    cisp   %0,%1
    cisn   %0,%n1
    c      %0,%1
    cim    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.92 Compare between Limits
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; TBD


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.93 Double Precision Compare
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "dc"
  [(set (cc0)
        (compare (match_operand:HI 0 "general_operand" "r,r")
                 (match_operand:HI 1 "general_operand" "r,m")))]
  ""
  "@
    dcr    %0,%1
    dc     %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.94 Floating Point Compare
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "fc"
  [(set (cc0)
        (compare (match_operand:HF 0 "general_operand" "r,z,z,r")
                 (match_operand:HF 1 "general_operand" "r,Q,q,m")))]
  ""
  "@
    fcr    %0,%1
    fcb    %Q1
    fcbx   %Q1
    fc     %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.95 Extended Precision Floating Point Compare
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "efc"
  [(set (cc0)
        (compare (match_operand:TQF 0 "register_operand" "r,r")
                 (match_operand:TQF 1 "general_operand" "r,m")))]
  ""
  "@
    efcr   %0,%1
    efc    %0,%1")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.96 No Operation
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "nop"
  [(const_int 0)]
  ""
  "nop")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.97 Break Point
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.98 Built-In Function
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.99.1 Sine
;; 5.99.2 Extended Precision Sine
;; 5.99.3 Cosine
;; 5.99.4 Extended Precision Cosine
;; 5.99.5 Sine/Cosine Pair
;; 5.99.6 Extended Precision Sine/Cosine Pair
;; 5.99.7 Arctangent
;; 5.99.8 Extended Precision Arctangent
;; 5.99.9 Square Root
;; 5.99.10 Extended Precision Square Root
;; 5.99.11 Exponential
;; 5.99.12 Extended Precision Exponential
;; 5.99.13 Natural Log
;; 5.99.14 Extended Precision Natural Log
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not supported by C


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.100.1 Long Load Single
;; 5.100.2 Long Load Double
;; 5.100.3 Long Load Extended Precision Floating Point
;; 5.100.4 Long Store Single
;; 5.100.5 Long Store Double
;; 5.100.6 Long Store Extended Precision Floating Point
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used in this version, may be used later


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.1 Unsigned Integer Add
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; TBD

  
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.2 Unsigned Integer Subtract
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; TBD

  
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.3 Unsigned Integer Compare
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn ""
  [(set (match_operand:CCUNS 0 "" "")
        (compare:CCUNS (match_operand:QI 1 "register_operand" "r,r,r")
                       (match_operand:QI 2 "general_operand"  "r,m,i")))]
  ""
  "@
    ucr    %1,%2
    uc     %1,%2
    ucim   %1,%2")

  
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.4 Search First Bit Set
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; FIXME:
(define_insn "ffsqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ffs:QI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "sfbs   %1,%0;neg    %1;aisp   %1,16")


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.5 Load Byte with Increment
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.6 Load Byte
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.7 Store Byte with Increment
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler


;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; 5.101.8 Store Byte
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Not used by the compiler



;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Miscellaneous Instructions
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
(define_insn "zero_extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "=r,r,r")
        (zero_extend:HI (match_operand:QI 1 "general_operand" "i,m,r")))]
  ""
  "*
  if (which_alternative == 0)
    {
      output_asm_insn (\"lim    %0,%1\", operands);
    }
  else if (which_alternative == 1)
    {
      output_asm_insn (\"l      %0,%1\", operands);
    }
  else 
    {
      if (REGNO (operands [0]) != REGNO (operands [1]))
        output_asm_insn (\"lr     %0,%1\", operands);
    }

  output_asm_insn (\"dsrl   %0,16\", operands);
  return \"\";
")

(define_insn "extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (sign_extend:HI (match_operand:QI 1 "register_operand" "r")) )]
  ""
  "*
  if (REGNO (operands [0]) != REGNO (operands [1]))
    output_asm_insn (\"lr     %0,%1\", operands);
  return \"dsra   %0,16\";
")

(define_insn "extendhftqf2"
  [(set (match_operand:TQF 0 "register_operand" "=r,r")
        (float_extend:TQF (match_operand:HF 1 "general_operand" "r,m")))]
  ""
  "*
  output_asm_insn (\"xorr   %t0,%t0\", operands);

  if (which_alternative == 0)
    {
      if (REGNO (operands [0]) != REGNO (operands [1]))
        output_asm_insn (\"dlr    %0,%1\", operands);
    }
  else
    {
      output_asm_insn (\"dl     %0,%1\", operands);
    }
  return \"\";
")


(define_insn "trunctqfhf2"
  [(set (match_operand:HF 0 "register_operand" "=r,r")
        (float_truncate:HF
          (match_operand:TQF 1 "general_operand" "r,m")))]
  ""
  "*
  if (which_alternative == 0)
    {
      if (REGNO (operands [0]) != REGNO (operands [1]))
        output_asm_insn (\"dlr    %0,%1\", operands);
    }
  else
    {
      output_asm_insn (\"dl     %0,%1\", operands);
    }
  return \"\";
")


;; Subtract One and Jump (if non-zero)
;;
(define_peephole 
  [(set (match_operand:QI 0 "register_operand" "=r")
        (plus:QI (match_operand:QI 1 "register_operand" "%0")
                 (const_int -1)))
   (set (cc0) (match_dup 0))
   (set (pc)
        (if_then_else (ne (cc0) (const_int 0))
         (label_ref (match_operand 3 "" ""))
         (pc)))
   ]
  ""
  "soj    %0,%3")


;; Combine a Load Register with subsequent increment/decrement into a LIM
;; The code seems rather bizare - lim where you would expect to see an add
;; No gain if constant can be represented in an aisp instruction, so use
;; the aisp instead. Note sisp can be used for small -ve constants.

(define_peephole 
  [(set (match_operand:QI 0 "register_operand" "=r")
        (match_operand:QI 1 "register_operand" "r"))
   (set (match_dup 0)
        (plus:QI (match_dup 0)
                 (match_operand:QI 2 "immediate_operand" "i")))]
  "REGNO(operands[1]) > 0 && REGNO(operands[0]) != REGNO(operands[1])"
  "lim    %0,%2,%1")

;; Eliminate the redundant load in a store/load sequence
(define_peephole 
  [(set (mem:QI (plus:QI (match_operand:QI 0 "register_operand" "r")
                          (match_operand:QI 1 "immediate_operand" "i")))
        (match_operand:QI 2 "register_operand" "r"))
   (set (match_operand:QI 3 "register_operand" "=r")
        (mem:QI (plus:QI (match_dup 0)
                         (match_dup 1))))
   ]
  "REGNO(operands[2]) == REGNO(operands[3])"
  "st     %2,%1,%0")


;; Single bit and followed by conditional jump
;;
(define_peephole 
  [(set (match_operand:QI 0 "register_operand" "=r")
        (and:QI (match_operand:QI 1 "register_operand" "%0")
                 (match_operand:QI 2 "immediate_operand" "i")))
   (set (cc0) (match_dup 0))
   (set (pc)
        (if_then_else (ne (cc0) (const_int 0))
         (label_ref (match_operand 3 "" ""))
         (pc)))
   ]
  "one_bit_set_p (INTVAL(operands[2]))"
  "tbr    %b2,%0\;jnz    %3")

(define_peephole 
  [(set (match_operand:QI 0 "register_operand" "=r")
        (and:QI (match_operand:QI 1 "register_operand" "%0")
                 (match_operand:QI 2 "immediate_operand" "i")))
   (set (cc0) (match_dup 0))
   (set (pc)
        (if_then_else (eq (cc0) (const_int 0))
         (label_ref (match_operand 3 "" ""))
         (pc)))
   ]
  "one_bit_set_p (INTVAL(operands[2]))"
  "tbr    %b2,%0\;jez    %3")

