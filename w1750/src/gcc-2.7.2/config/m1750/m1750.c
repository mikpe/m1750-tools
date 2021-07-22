/* Subroutines for insn-output.c for MIL-STD-1750.
   Copyright (C) 1994, 1995 Free Software Foundation, Inc.
   Contributed by O.M.Kellogg, DASA (kellogg@space.otn.dasa.de)
   Updated by Chris Nettleton, (cnettleton@acm.org)

   This file is part of GNU CC.

   GNU CC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   GNU CC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GNU CC; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */


/*
 * $Log: m1750.c,v $
 * Revision 1.4  1997/08/13 14:02:01  nettleto
 * Changed size of expanded memory frame.
 *
 * Revision 1.3  1997/07/18 10:51:42  nettleto
 * Made changes for the debug symbol tables.
 *
 * Revision 1.2  1997/05/06 17:24:23  nettleto
 * Expanded memory mods
 *
 * Revision 1.1  1997/02/14 10:47:50  nettleto
 * Initial revision
 *
 */

#include <string.h>

#include <stdio.h>
#include "config.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "conditions.h"
#include "insn-flags.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"

#define __datalbl
#include "tree.h"
#include "expr.h"

void
abort_with_insn (reason, insn)
     char *reason;
     rtx insn;
{
  error (reason);
  debug_rtx (insn);
  abort ();
}

/*
 * Stuff to do with saving argument registers on entry to function that
 * calls va_start etc. The idea is that once all the args are in place on
 * the stack, they can be accessed as if they had been passed on the stack
 * in the first place. Of course it makes functions that call va_start 
 * just as inefficent as others that use the stack passing mechanism.
 */
rtx
m1750_builtin_saveregs (arglist)
     tree arglist;
{
  rtx block, addr, argsize;
  tree fntype = TREE_TYPE (current_function_decl);
  int argadj = ((!(TYPE_ARG_TYPES (fntype) != 0
		   && (TREE_VALUE (tree_last (TYPE_ARG_TYPES (fntype)))
		       != void_type_node)))
		? -UNITS_PER_WORD : 0);
  int fixed;

  /* current_function_arg_offset_rtx is the offset from the arg pointer
     to the place where the first anonymous arg can be found, if there is one.  */
  if (CONSTANT_P (current_function_arg_offset_rtx))
    {
      fixed = (XINT (current_function_arg_offset_rtx, 0) + argadj);
      argsize = gen_rtx (CONST_INT, VOIDmode, fixed);
    }
  else
    {
      fixed = 0;
      argsize = plus_constant (current_function_arg_offset_rtx, argadj);
    }

  /* Allocate the va_list constructor (3 words ) */
  block = assign_stack_local (BLKmode, 3, BITS_PER_WORD);
  RTX_UNCHANGING_P (block) = 1;
  RTX_UNCHANGING_P (XEXP (block, 0)) = 1;

  /* Allocate the register space, and store the incoming registers r<fixed> .. r10.
     Note, fixed may be >= 11 */
  addr = assign_stack_local (BLKmode, 11, -1);
  if (fixed < 11)
    move_block_from_reg
      (fixed,
       change_address (addr, Pmode,
		       plus_constant (XEXP (addr, 0),
				      fixed)),
       11 - fixed, 11 - fixed);

  /* Store address of register space as the __va_reg member.  */
  MEM_IN_STRUCT_P (addr) = 1;
  RTX_UNCHANGING_P (addr) = 1;
  RTX_UNCHANGING_P (XEXP (addr, 0)) = 1;
  emit_move_insn (change_address (block, Pmode,
				  plus_constant (XEXP (block, 0),
						 2)),
		  copy_to_reg (XEXP (addr, 0)));

  /* Return the address of the va_list constructor, but don't put it in a
     register.  This fails when not optimizing and produces worse code when
     optimizing.  */
  return XEXP (block, 0);
}

/* Function for INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET).
   Define the offset between two registers, one to be eliminated, and the other
   its replacement, at the start of a routine.  */

int
initial_offset (from, to)
     int from;
     int to;
{
  int offset = 0;
  int fsize = 0;

  if (frame_needed ())
    {
      fsize = get_frame_size ();
      offset = 1;
    }

  if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    {
      offset = 0;
    }
  else if (from == ARG_POINTER_REGNUM && to == FRAME_POINTER_REGNUM)
    {
      offset += (TARGET_MMU ? 2 : 1) + fsize;
    }
  else if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    {
      offset += (TARGET_MMU ? 2 : 1) + fsize;
    }
  else
    abort ();

  return offset;
}


rtx m1750_compare_op0, m1750_compare_op1;
enum machine_mode m1750_compare_mode;
int m1750_compare_flag = 0;


int
symbolic_operand (op, mode)
     register rtx op;
     enum machine_mode mode;
{
  /*
   * Returns 1 if 'op' is either a symbol reference or a sum of a symbol
   * reference and a constant.
   */

  switch (GET_CODE (op))
    {
    case SYMBOL_REF:
    case LABEL_REF:
      return 1;

    case CONST:
      op = XEXP (op, 0);
      return ((GET_CODE (XEXP (op, 0)) == SYMBOL_REF
	       || GET_CODE (XEXP (op, 0)) == LABEL_REF)
	      && GET_CODE (XEXP (op, 1)) == CONST_INT);

    default:
      return 0;
    }
}


int
notice_update_cc (exp)
     rtx exp;
{
  /*
   * Returns non zero for instructions that update the condition code
   * register.
   */

  if (GET_CODE (exp) == SET)
    {
      enum rtx_code src_code = GET_CODE (SET_SRC (exp));

      /* extended floating load register may not set cc
         correctly */
      if (GET_MODE (SET_SRC (exp)) == TQFmode
	  && GET_CODE (SET_SRC (exp)) == REG
	  && GET_CODE (SET_DEST (exp)) == REG)
	{
	  CC_STATUS_INIT;
	  return;
	}

      /* Jumps do not alter the cc's.  */
      if (SET_DEST (exp) == pc_rtx)
	return;

      /* Moving a register or constant into memory doesn't alter the cc's. */
      if (GET_CODE (SET_DEST (exp)) == MEM
	  && (src_code == REG || src_code == CONST_INT))
	return;

      /* Function calls clobber the cc's.  */
      if (src_code == CALL)
	{
	  CC_STATUS_INIT;
	  return;
	}

      /* Tests and compares set the cc's in predictable ways.  */
      if (SET_DEST (exp) == cc0_rtx)
	{
	  CC_STATUS_INIT;
	  cc_status.value1 = SET_SRC (exp);
	  return;
	}

      /* Anything else will set cc_status. */
      cc_status.flags = CC_NO_OVERFLOW;
      cc_status.value1 = SET_SRC (exp);
      cc_status.value2 = SET_DEST (exp);
      return;
    }
  else if (GET_CODE (exp) == PARALLEL
	   && GET_CODE (XVECEXP (exp, 0, 0)) == SET)
    {
      if (SET_DEST (XVECEXP (exp, 0, 0)) == pc_rtx)
	return;
      if (SET_DEST (XVECEXP (exp, 0, 0)) == cc0_rtx)
	{
	  CC_STATUS_INIT;
	  cc_status.value1 = SET_SRC (XVECEXP (exp, 0, 0));
	  return;
	}
      CC_STATUS_INIT;
    }
  else
    {
      CC_STATUS_INIT;
    }
}


rtx
function_arg (cum, mode, type, named)
     int cum;
     enum machine_mode mode;
     tree type;
     int named;
{
  int size;
  rtx result;

  if (MUST_PASS_IN_STACK (mode, type))
    return (rtx) 0;
  if (mode == BLKmode)
    size = int_size_in_bytes (type);
  else
    size = GET_MODE_SIZE (mode);
  if (cum + size < 12)
    return gen_rtx (REG, mode, cum);
  else
    return (rtx) 0;
}


/* Predicate for floating comparisons against zero */
int
constant_zero_p (op)
     rtx op;
{
  return (GET_CODE (op) == CONST_DOUBLE
	  && CONST_DOUBLE_LOW (op) == 0
	  && CONST_DOUBLE_LOW (op) == 0);
}


/* predicate for 1750 `B' addressing mode (Base Register with Offset)
   memory operand */
int
b_mode_operand_p (op)
     rtx op;
{
  if (GET_CODE (op) == MEM)
    {
      rtx inner = XEXP (op, 0);
      if (GET_CODE (inner) == PLUS)
	{
	  rtx plus_op0 = XEXP (inner, 0);

	  if (GET_CODE (plus_op0) == REG
	      && (REGNO (plus_op0) >= 12 && REGNO (plus_op0) <= 15))
	    {
	      rtx plus_op1 = XEXP (inner, 1);
	      if (GET_CODE (plus_op1) == CONST_INT
		  && INTVAL (plus_op1) >= 0
		  && INTVAL (plus_op1) <= 255)
		return 1;
	    }
	}
    }
  return 0;
}

/* predicate for 1750 `B' addressing mode (Base Register with Offset)
   memory operand */
int
bx_mode_operand_p (op)
     rtx op;
{
  /* 
   * Predicate for BX addressing mode. This requires a base register
   * R11, R12, R13, R14 or R15, and an index register R1 .. R15.
   */
  if (GET_CODE (op) == MEM)
    {
      rtx inner = XEXP (op, 0);
      if (GET_CODE (inner) == PLUS)
	{
	  rtx plus_op0 = XEXP (inner, 0);
	  if (GET_CODE (plus_op0) == REG
	      && (REGNO (plus_op0) >= 12 && REGNO (plus_op0) <= 15))
	    {
	      rtx plus_op1 = XEXP (inner, 1);
	      if (GET_CODE (plus_op1) == REG
		  && REG_OK_FOR_INDEX_P (plus_op1))
		return 1;
	    }
	}
    }
  return 0;
}


/* A C compound statement to output to stdio stream STREAM the
   assembler syntax for an instruction operand X.  X is an RTL
   expression.

   CODE is a value that can be used to specify one of several ways
   of printing the operand.  It is used when identical operands
   must be printed differently depending on the context.  CODE
   comes from the `%' specification that was used to request
   printing of the operand.  If the specification was just `%DIGIT'
   then CODE is 0; if the specification was `%LTR DIGIT' then CODE
   is the ASCII code for LTR.

   If X is a register, this macro should print the register's name.
   The names can be found in an array `reg_names' whose type is
   `char *[]'.  `reg_names' is initialized from `REGISTER_NAMES'.

   When the machine description has a specification `%PUNCT' (a `%'
   followed by a punctuation character), this macro is called with
   a null pointer for X and the punctuation character for CODE.

   The 1750 specific codes are:
   'j' for the branch instruction opcode
   'J' for the commuted branch instruction opcode
   '#' for an immediate operand prefix 
   'd' for the second register in a pair (HI or HF mode)
   't' for the third register in a triple (TQF mode)
   'q' for the fourth register in a quad (SI mode)
   'b' for the bit number (using 1750 test bit convention)
   'B' for the bit number of the 1's complement (for bit clear)
   'w' for int - 16
 */

void
print_operand (file, op, letter)
     FILE *file;		/* file to write to */
     rtx op;			/* operand to print */
     int letter;		/* %<letter> or 0 */
{
  switch (GET_CODE (op))
    {
    case REG:
      if (letter == 'd')
	fprintf (file, "%s", reg_names[REGNO (op) + 1]);
      else if (letter == 't')
	fprintf (file, "%s", reg_names[REGNO (op) + 2]);
      else if (letter == 'q')
	fprintf (file, "%s", reg_names[REGNO (op) + 3]);
      else
	fprintf (file, "%s", reg_names[REGNO (op)]);
      break;

    case SYMBOL_REF:
      assemble_name (file, XSTR (op, 0));
      break;

    case LABEL_REF:
    case CONST:
    case MEM:
      if (letter == 'Q')
	fprintf (file, "%s,%d",
		 reg_names[REGNO (XEXP (XEXP (op, 0), 0))],
		 INTVAL (XEXP (XEXP (op, 0), 1)));
      else
	output_address (XEXP (op, 0));
      break;

    case CONST_DOUBLE:
      print_operand_address (file, force_const_mem (GET_MODE (op), op));
      break;

    case CONST_INT:
      if (letter == 'b')
	fprintf (file, "%d", which_bit (INTVAL (op)));
      else if (letter == 'B')
	fprintf (file, "%d", which_bit (~INTVAL (op)));
      else if (letter == 'H')
	fprintf (file, "0x%04X", (INTVAL (op) >> 16) & 0xFFFF);
      else if (letter == 'h')
	fprintf (file, "0x%04X", INTVAL (op) & 0xFFFF);
      else if (letter == 'w')
	fprintf (file, "%d", INTVAL (op) - 16);
      else if (INTVAL (op) > 0x7FFF)
	fprintf (file, "%d",
		 INTVAL (op) - 0x10000);
      else
	fprintf (file, "%d", INTVAL (op));
      break;

    case CODE_LABEL:
      asm_fprintf (file, "%LL%d", XINT (op, 3));
      break;

    case PLUS:
      {
	rtx op0 = XEXP (op, 0), op1 = XEXP (op, 1);
	int op0code = GET_CODE (op0), op1code = GET_CODE (op1);

	if (op1code == CONST_INT)
	  switch (op0code)
	    {
	    case REG:
	      fprintf (file, "%d,%s", INTVAL (op1), reg_names[REGNO (op0)]);
	      break;
	    case SYMBOL_REF:
	      assemble_name (file, XSTR (op0, 0));
	      fprintf (file, "+%d", INTVAL (op1) << 1);
	      break;
	    default:
	      abort_with_insn ("illegal operand (1)", op);
	    }
	else if (op1code == SYMBOL_REF && op0code == REG)
	  {
	    assemble_name (file, XSTR (op1, 0));
	    fprintf (file, ",%s", reg_names[REGNO (op0)]);
	  }
	else
	  abort_with_insn ("illegal operand (2)", op);
      }
      break;

    default:
      abort_with_insn ("illegal operand (3)", op);
    }
}

print_operand_address (file, addr)
     FILE *file;
     rtx addr;
{
  switch (GET_CODE (addr))
    {
    case REG:
      fprintf (file, "0,%s", reg_names[REGNO (addr)]);
      break;

    case PLUS:
      {
	register rtx x = XEXP (addr, 0), y = XEXP (addr, 1);

	switch (GET_CODE (x))
	  {
	  case REG:
	    switch (GET_CODE (y))
	      {
	      case CONST:
		output_address (XEXP (y, 0));
		fprintf (file, ",%s", reg_names[REGNO (x)]);
		break;
	      case CONST_INT:
		fprintf (file, "%d,%s", INTVAL (y), reg_names[REGNO (x)]);
		break;
	      case SYMBOL_REF:
		assemble_name (file, XSTR (y, 0));
		fprintf (file, ",%s", reg_names[REGNO (x)]);
		break;
	      case LABEL_REF:
		output_address (XEXP (y, 0));
		fprintf (file, ",%s", reg_names[REGNO (x)]);
		break;
	      default:
		abort_with_insn ("illegal operand address (1)", addr);
	      }
	    break;
	  case LABEL_REF:
	    output_address (XEXP (x, 0));
	    break;
	  case SYMBOL_REF:
	    switch (GET_CODE (y))
	      {
	      case CONST_INT:
		assemble_name (file, XSTR (x, 0));
		fprintf (file, "+%d", INTVAL (y) << 1);
		break;
	      case REG:
		assemble_name (file, XSTR (x, 0));
		fprintf (file, ",%s", reg_names[REGNO (y)]);
		break;
	      default:
		abort_with_insn ("illegal operand address (2)", addr);
	      }
	    break;
	  case CONST:
	    output_address (XEXP (x, 0));
	    if (GET_CODE (y) == REG)
	      fprintf (file, ",%s", reg_names[REGNO (y)]);
	    else
	      abort_with_insn ("illegal operand address (3)", addr);
	    break;
	  case MEM:
	    output_address (y);
	    break;
	  default:
	    abort_with_insn ("illegal operand address (4)", addr);
	  }
      }
      break;

    case CONST_INT:
      if (INTVAL (addr) < 0x10000 && INTVAL (addr) >= -0x10000)
	fprintf (file, "%d", INTVAL (addr));
      else
	{
	  fprintf (file, "?");
	  output_addr_const (file, addr);
	}
      break;

    case LABEL_REF:
      fprintf (file, "%s", XSTR (addr, 0));
      break;

    case SYMBOL_REF:
      assemble_name (file, XSTR (addr, 0));
      break;

    case MEM:
      output_address (XEXP (addr, 0));
      break;

    case CONST:
      output_address (XEXP (addr, 0));
      fprintf (file, "");
      break;

    case CODE_LABEL:
      asm_fprintf (file, "%LL%d", XINT (addr, 3));
      break;

    default:
      /* print_rtl (stderr, addr); */
      abort_with_insn ("illegal operand address (5)", addr);
      break;
    }
}


int
frame_needed ()
{
  /*
   * A stack frame is not required if it is not used. Conditions 
   * are (approx and pessimistic):
   * 1. No local data on the stack (i.e. frame size == 0)
   * 2. Its a leaf function
   * 3. Optimize level >= 2 (therefore debugging will be tricky anyway)
   */

  if (optimize >= 2
      && (!frame_pointer_needed)
      && leaf_function_p ()
      && get_frame_size () == 0)
    return 0;
  return 1;
}

int
far_function_p ()
{
  /*
   * A near function is declared as static, or is nested, and has not
   * had its address taken. All others are far.
   */
  if (!TARGET_MMU)
    return 0;

  return TREE_PUBLIC (current_function_decl);
}


int
far_call_p (f)
     tree f;
{
  /* Check of the function given in rtl operand op must be called
     using the far call convention */

  if (!TARGET_MMU)
    return 0;

  /* check for call to libgcc function */
  if (!TREE_PUBLIC (f) && !TREE_STATIC (f) && !DECL_EXTERNAL (f))
    return 1;

  return TREE_PUBLIC (f);
}


int
taking_address_ok (f)
     tree f;
{
  /* If we are compiling for expanded memory, then only functions that
     are called with a 16-bit PC may be called indirectly. */
  if (TARGET_MMU && TREE_PUBLIC (current_function_decl))
    return 0;

  return 1;
}



/*
 * This function generates the code for function entry.
 * STREAM is a stdio stream to output the code to.
 *
 * SIZE is an int: how many units of temporary storage to allocate.
 * Refer to the array `regs_ever_live' to determine which registers
 * to save; `regs_ever_live[I]' is nonzero if register number I
 * is ever used in the function.  This function is responsible for
 * knowing which registers should not be saved even if used.
 */
void
output_function_prologue (stream, size)
     FILE *stream;
     int size;
{
  if (flag_verbose_asm)
    {
      int addr_taken = TREE_ADDRESSABLE (current_function_decl);
      int is_public = TREE_PUBLIC (current_function_decl);

      int regs_modified = 0;
      int regno;

      fprintf (stream, "\t! addr_taken = %d\n", addr_taken);
      fprintf (stream, "\t! is_public = %d\n", is_public);

      /* check if any registers (except sp) are modified in this function */
      for (regno = 0; regno < 14; regno++)
	if (regs_ever_live[regno])
	  {
	    regs_modified++;
	  }

      if (regs_modified > 0)
	{
	  fprintf (stream, "\t! registers used:");
	  for (regno = 0; regno < 14; regno++)
	    if (regs_ever_live[regno])
	      {
		fprintf (stream, " %s", reg_names[regno]);
	      }
	  fprintf (stream, "\n");
	}
    }

  if (TARGET_MMU)
    {
      if (!frame_needed ())
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog not needed\n");
	  if (!far_function_p ())
	    fprintf (stream, "\tsisp   r15,1\n");
	}
      else if (size == 0)
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog, frame size = %d words\n", size);
	  if (!far_function_p ())
	    fprintf (stream, "\tsisp   r15,1\n");
	  fprintf (stream, "\tpshm   r14,r14\n");
	  fprintf (stream, "\tlr     r14,r15\n");
	  if (flag_verbose_asm)
	    fprintf (stream, "\t!\n");
	}
      else if (size <= 16)
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog, frame size = %d words\n", size);
	  if (!far_function_p ())
	    {
	      if (size + 1 > 16)
		fprintf (stream, "\tsim    r15,%d\n", size + 1);
	      else
		fprintf (stream, "\tsisp   r15,%d\n", size + 1);
	    }
	  else
	    fprintf (stream, "\tsisp   r15,%d\n", size);
	  fprintf (stream, "\tpshm   r14,r14\n");
	  fprintf (stream, "\tlr     r14,r15\n");
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! end of prolog\n");
	}
      else
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog, frame size = %d words\n", size);
	  if (!far_function_p ())
	    fprintf (stream, "\tsim    r15,%d\n", size + 1);
	  else
	    fprintf (stream, "\tsim    r15,%d\n", size);
	  fprintf (stream, "\tpshm   r14,r14\n");
	  fprintf (stream, "\tlr     r14,r15\n");
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! end of prolog\n");
	}
    }
  else
    {
      if (!frame_needed ())
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog not needed\n");
	}
      else if (size == 0)
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog, frame size = %d words\n", size);
	  fprintf (stream, "\tpshm   r14,r14\n");
	  fprintf (stream, "\tlr     r14,r15\n");
	  if (flag_verbose_asm)
	    fprintf (stream, "\t!\n");
	}
      else if (size <= 16)
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog, frame size = %d words\n", size);
	  fprintf (stream, "\tsisp   r15,%d\n", size);
	  fprintf (stream, "\tpshm   r14,r14\n");
	  fprintf (stream, "\tlr     r14,r15\n");
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! end of prolog\n");
	}
      else
	{
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! function prolog, frame size = %d words\n", size);
	  fprintf (stream, "\tsim    r15,%d\n", size);
	  fprintf (stream, "\tpshm   r14,r14\n");
	  fprintf (stream, "\tlr     r14,r15\n");
	  if (flag_verbose_asm)
	    fprintf (stream, "\t! end of prolog\n");
	}
    }

}


void
output_function_epilogue (stream, size)
     FILE *stream;
     int size;
{
  /*
   * This function generates the code for function exit,
   * on machines that need it.  Args are same as for FUNCTION_PROLOGUE.
   * 
   * The function epilogue should not depend on the current stack pointer!
   * It should use the frame pointer only, if there is a frame pointer.
   * This is mandatory because of alloca; we also take advantage of it to
   * omit stack adjustments before returning.
   */

  rtx insn = get_last_insn ();

  /* If the last insn was a BARRIER, we don't have to write any code.  */
  if (GET_CODE (insn) == NOTE)
    insn = prev_nonnote_insn (insn);
  if (insn && GET_CODE (insn) == BARRIER)
    return;

  if (!frame_needed ())
    {
      if (flag_verbose_asm)
	fprintf (stream, "\t! function epilog, no frame\n", size);
      if (TARGET_MMU)
	{
	  if (!far_function_p ())
	    {
	      fprintf (stream, "\taisp   r15,1\n");
	      fprintf (stream, "\turs    r15\n");
	    }
	  else
	    {
	      fprintf (stream, "\tlurs   r15\n");
	    }
	}
      else
	{
	  fprintf (stream, "\turs    r15\n");
	}
      if (flag_verbose_asm)
	fprintf (stream, "\t!\n");
    }
  else if (size == 0)
    {
      if (flag_verbose_asm)
	fprintf (stream, "\t! function epilog, frame size = %d words\n", size);
      if (TARGET_MMU)
	{
	  if (!far_function_p ())
	    {
	      fprintf (stream, "\tlr     r15,r14\n");
	      fprintf (stream, "\tpopm   r14,r14\n");
	      fprintf (stream, "\taisp   r15,1\n");
	      fprintf (stream, "\turs    r15\n");
	    }
	  else
	    {
	      fprintf (stream, "\tlr     r15,r14\n");
	      fprintf (stream, "\tpopm   r14,r14\n");
	      fprintf (stream, "\tlurs   r15\n");
	    }
	}
      else
	{
	  fprintf (stream, "\tlr     r15,r14\n");
	  fprintf (stream, "\tpopm   r14,r14\n");
	  fprintf (stream, "\turs    r15\n");
	}

      if (flag_verbose_asm)
	fprintf (stream, "\t!\n");
    }
  else if (size <= 16)
    {
      if (flag_verbose_asm)
	fprintf (stream, "\t! function epilog, frame size = %d words\n", size);
      if (TARGET_MMU)
	{
	  if (!far_function_p ())
	    {
	      fprintf (stream, "\tlr     r15,r14\n");
	      fprintf (stream, "\tpopm   r14,r14\n");
	      if (size + 1 <= 16)
		fprintf (stream, "\taisp   r15,%d\n", size + 1);
	      else
		fprintf (stream, "\taim    r15,%d\n", size + 1);
	      fprintf (stream, "\turs    r15\n");
	    }
	  else
	    {
	      fprintf (stream, "\tlr     r15,r14\n");
	      fprintf (stream, "\tpopm   r14,r14\n");
	      fprintf (stream, "\taisp   r15,%d\n", size);
	      fprintf (stream, "\tlurs   r15\n");
	    }
	}
      else
	{
	  fprintf (stream, "\tlr     r15,r14\n");
	  fprintf (stream, "\tpopm   r14,r14\n");
	  fprintf (stream, "\taisp   r15,%d\n", size);
	  fprintf (stream, "\turs    r15\n");
	}
      if (flag_verbose_asm)
	fprintf (stream, "\t!\n");
    }
  else
    {
      if (flag_verbose_asm)
	fprintf (stream, "\t! function epilog, frame size = %d words\n", size);
      if (TARGET_MMU)
	{
	  if (!far_function_p ())
	    {
	      fprintf (stream, "\tlr     r15,r14\n");
	      fprintf (stream, "\tpopm   r14,r14\n");
	      fprintf (stream, "\taim    r15,%d\n", size + 1);
	      fprintf (stream, "\turs    r15\n");
	    }
	  else
	    {
	      fprintf (stream, "\tlr     r15,r14\n");
	      fprintf (stream, "\tpopm   r14,r14\n");
	      fprintf (stream, "\taim    r15,%d\n", size);
	      fprintf (stream, "\tlurs   r15\n");
	    }
	}
      else
	{
	  fprintf (stream, "\tlr     r15,r14\n");
	  fprintf (stream, "\tpopm   r14,r14\n");
	  fprintf (stream, "\taim    r15,%d\n", size);
	  fprintf (stream, "\turs    r15\n");
	}
      if (flag_verbose_asm)
	fprintf (stream, "\t!\n");
    }

}


int
one_bit_set_p (int x)
{
  /*
   *  Return non zero if the LS 16 bits of the given value has just one bit set,
   *  otherwise return zero. Note this function may be used to detect one
   *  bit clear by inverting the param.
   */

  x &= 0xffff;
  return x && (x & (x - 1)) == 0;
}


int
which_bit (int x)
{
  /*
   * Return the number of the least significant bit set, using the  same
   * convention for bit numbering as in the MIL-STD-1750 sb instruction.
   */
  int b = 15;

  while (b > 0 && (x & 1) == 0)
    {
      b--;
      x >>= 1;
    }

  return b;
}


/* Compute the offset of the given arg from the frame pointer. This is
   normally R14, but if the frame is omitted, then references to
   args on the stack are relative to R15.  */
int
m1750_debugger_arg_offset (reg, offset)
     rtx reg;
     int offset;
{
  if (GET_CODE (reg) == PLUS)
    {
      offset = INTVAL (XEXP (reg, 1));
      reg = XEXP (reg, 0);
    }

  if ((reg != frame_pointer_rtx) && (reg != stack_pointer_rtx))
    {
      offset += initial_offset (ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM);
    }

  return offset << 1;
}


