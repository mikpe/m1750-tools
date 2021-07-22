/* Definitions of target machine for GNU compiler.  MIL-STD-1750 version.
   Copyright (C) 1987, 1988, 1993, 1994, 1995 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC for the MIL-STD-1750 was developed by Chris Nettleton Software,
Farnborough, UK,  cnettleton@acm.org, under contract with the European
Space Agency. It is based on the earlier 1750 GCC configuration written
by Oliver Kellogg, DASA (kellogg@space.otn.dasa.de).

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
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
 * $Log: m1750-coff.h,v $
 * Revision 1.5  1997/07/23 11:54:11  nettleto
 * Simplified CAN_ELIMINATE, and added option "movsi" to work
 * round bug compiling libgcc.
 *
 * Revision 1.4  1997/07/18 10:50:26  nettleto
 * Made changes to do with byte/word addressing in debug
 * symbol tables, and made a start on long addressing.
 *
 * Revision 1.3  1997/05/06 17:27:05  nettleto
 * Changed PREFERRED_RELOAD_CLASS.
 *
 * Revision 1.2  1997/04/28 20:45:18  nettleto
 * Fixed problem with structures passed by value.
 *
 * Revision 1.1  1997/02/14 10:48:56  nettleto
 * Initial revision
 *
 */

/* Print subsidiary information on the compiler version in use.  */
#define TARGET_VERSION fprintf (stderr, " (GCC-1750-1.0)");


/* Define this for experimental 32-bit addressing. Only supported on 1750B with
   long loads and stores. (Broken on MA31750) */
/* #define M1750B_LONG_ADDRESSING */


#define CC1_SPEC "-fno-force-mem"

#define ASM_SPEC \
"%{mmmu:-Ammu} %{mb1:-Ab1} %{mb2:-Ab2} %{mb3:-Ab3} %{mno-b1:-Ano-b1} %{mno-b2:-Ano-b2} %{mno-b3:-Ano-b3} %{mno-mmu:-Ano-mmu}"

#define LIB_SPEC \
"%{g*:-lg} %{!p:%{!pg:-lc}}%{p:-lc_p}%{pg:-lc_p}"

#define STARTFILE_SPEC "crt0.o%s"


/* Names to predefine in the preprocessor for this target machine.  */
#define CPP_PREDEFINES ""

/* Run-time compilation parameters selecting different hardware subsets.  */
extern int target_flags;

/* Macros used in the machine description to test the flags.  */

/* Compile for a MIL-STD-1750A.  */
#define TARGET_1750A ((target_flags & 0x7) == 0)

/* Compile for a MIL-STD-1750B.  */
#define TARGET_1750B ((target_flags & 0x7) != 0)

/* Compiler for expanded memory */
#define TARGET_MMU (target_flags & 0x8)

/* Compile for 1750B Option 1 */
#define TARGET_B1 ((target_flags & 0x1) != 0)

/* Compile for 1750B Option 2 */
#define TARGET_B2 ((target_flags & 0x2) != 0)

/* Compile for 1750B Option 3 */
#define TARGET_B3 ((target_flags & 0x4) != 0)

/* Pass parameters in register */
#define TARGET_REGPARM (target_flags & 0x10)

/* 24 bit data addressing (experimental) */
#define TARGET_D24 (target_flags & 0x20)

/* MOVSI -- temporary option */
#define MOVSI (target_flags & 0x40)


/* Macro to define tables used to set the flags.
   This is a list in braces of pairs in braces,
   each pair being { "NAME", VALUE }
   where VALUE is the bits to set or minus the bits to clear.
   An empty string NAME is used to identify the default VALUE.  */

#define TARGET_SWITCHES  \
  { {"b1", 1}, \
    {"b2", 2}, \
    {"b3", 4}, \
    {"mmu", 8}, \
    {"regparam", 16}, \
    {"d24", 32}, \
    {"movsi", 64}, \
    {"no-b1", -1}, \
    {"no-b2", -2}, \
    {"no-b3", -4}, \
    {"no-mmu",-8}, \
    {"no-regparam", -16}, \
    {"no-d24", -32}, \
    {"no-movsi", -64}, \
    { "", TARGET_DEFAULT}}

/* TARGET_DEFAULT is defined here, as 1750, no mmu, reg params */
#ifndef TARGET_DEFAULT
#define TARGET_DEFAULT 0x50
#endif

/* Show we can debug even without a frame pointer.  */
#define CAN_DEBUG_WITHOUT_FP

/* This is meant to be redefined in the host dependent files */
#define SUBTARGET_SWITCHES


/* Target machine storage layout */

/* Define for XFmode extended real floating point support.
   This will automatically cause REAL_ARITHMETIC to be defined.  */
/* #define LONG_DOUBLE_TYPE_SIZE 96 */

/* Define if you don't want extended real, but do want to use the
   software floating point emulator for REAL_ARITHMETIC and
   decimal <-> binary conversion. */
/* #define REAL_ARITHMETIC */

/* Define this if most significant bit is lowest numbered
   in instructions that operate on numbered bit-fields.
   We make it true always by avoiding using the single-bit insns
   except in special cases with constant bit numbers.  */
#define BITS_BIG_ENDIAN 1

/* Define this if most significant byte of a word is the lowest numbered.  */
#define BYTES_BIG_ENDIAN 1

/* Define this if most significant word of a multiword number is the lowest
   numbered.  */
#define WORDS_BIG_ENDIAN 1

/* number of bits in an addressable storage unit */
#define BITS_PER_UNIT 16

/* Width in bits of a "word", which is the contents of a machine register.
   Note that this is not necessarily the width of data type `int';
   if using 16-bit ints on a 68000, this would still be 32.
   But on a machine with 16-bit registers, this would be 16.  */
#define BITS_PER_WORD 16

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD 1

/* Width in bits of a pointer.
   See also the macro `Pmode' defined below.  */
#ifdef M1750B_LONG_ADDRESSING
#define POINTER_SIZE (TARGET_D24? 32 : 16)
#else
#define POINTER_SIZE 16
#endif

#define POINTERS_EXTEND_UNSIGNED 1


#ifdef M1750B_LONG_ADDRESSING
#define PTRDIFF_TYPE "long int"
#else
#define PTRDIFF_TYPE "int"
#endif

/* Type to use for `size_t'. If undefined, uses `long unsigned int'. */
/*
*/
#define SIZE_TYPE "unsigned int"

/* 1750a preliminary
#define TARGET_FLOAT_FORMAT UNKNOWN_FLOAT_FORMAT
*/

/* Allocation boundary (in *bits*) for storing pointers in memory.  */
#define POINTER_BOUNDARY     16

/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY 16

/* Boundary (in *bits*) on which stack pointer should be aligned.  */
#define STACK_BOUNDARY 16

/* Allocation boundary (in *bits*) for the code of a function.  */
#define FUNCTION_BOUNDARY 16

/* Alignment of field after `int : 0' in a structure.  */
#define EMPTY_FIELD_BOUNDARY 16

/* No data type wants to be aligned rounder than this.  */
#define BIGGEST_ALIGNMENT 16

/* Set this nonzero if move instructions will actually fail to work
   when given unaligned data.  */
#define STRICT_ALIGNMENT 0

/* Define number of bits in most basic integer type.
   (If undefined, default is BITS_PER_WORD).
*/
#define INT_TYPE_SIZE  16 

/* Define number of bits in short integer type.
   (If undefined, default is half of BITS_PER_WORD). */
#define SHORT_TYPE_SIZE 16

/* Define number of bits in long integer type.
   (If undefined, default is BITS_PER_WORD). */
#define LONG_TYPE_SIZE  32

/* Define number of bits in long long integer type.
   (If undefined, default is twice BITS_PER_WORD). */
#define LONG_LONG_TYPE_SIZE  64

/* Define number of bits in char type.
   (If undefined, default is one fourth of BITS_PER_WORD). */
#define CHAR_TYPE_SIZE  16

/* Define number of bits in float type.
   (If undefined, default is BITS_PER_WORD). */
#define FLOAT_TYPE_SIZE  32

/* Define number of bits in double type.
   (If undefined, default is twice BITS_PER_WORD). */
#define DOUBLE_TYPE_SIZE  48

/* Long double is not supported as a wider type */
#define LONG_DOUBLE_TYPE_SIZE   DOUBLE_TYPE_SIZE

/* Define these to avoid dependence on meaning of `int'.
   Note that WCHAR_TYPE_SIZE is used in cexp.y,
   where TARGET_SHORT is not available.  */

#define WCHAR_TYPE "int"
#define WCHAR_TYPE_SIZE 16

/* Standard register usage.  */

/* Number of actual hardware registers.
   The hardware registers are assigned numbers for the compiler
   from 0 to just below FIRST_PSEUDO_REGISTER.
   All registers that the compiler knows about must be given numbers,
   even those that are not normally considered general registers.
   For the 1750, we give the general registers numbers 0 .. 15 */
#define FIRST_PSEUDO_REGISTER 16

/* 1 for registers that have pervasive standard uses
   and are not available for the register allocator.
   R15 is the 1750 stack pointer. R14 is the frame pointer. */

#define FIXED_REGISTERS  \
 { 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 1, 1 }

/* 1 for registers not available across function calls.
   These must include the FIXED_REGISTERS and also any
   registers that can be used without being saved.
   The latter must include the registers where values are returned
   and the register where structure-value addresses are passed.
   Aside from that, you can include as many other registers as you like.
   1750: return value in R0 foll. (depending on size of retval).
   Should be possible to refine this (how many regs are actually used) */

#define CALL_USED_REGISTERS \
 { 1, 1, 1, 1, 1, 1, 1, 1, \
   1, 1, 1, 1, 1, 1, 1, 1 }

/* Order in which to allocate registers.  Each register must be
   listed once, even those in FIXED_REGISTERS.  List frame pointer
   late and fixed registers last.  Note that, in general, we prefer
   registers listed in CALL_USED_REGISTERS, keeping the others
   available for storage of persistent values.  */

#define REG_ALLOC_ORDER \
   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }

/* Return number of consecutive hard regs needed starting at reg R
   to hold something of mode MODE.
   This is ordinarily the length in words of a value of mode MODE
   but can be less for certain modes in special long registers.
   All 1750 registers are one word long. */
#define HARD_REGNO_NREGS(REGNO, MODE) (GET_MODE_SIZE (MODE))

/* Value is 1 if hard register REGNO can hold a value of machine-mode */
#define HARD_REGNO_MODE_OK(REGNO, MODE) 1

/* Value is 1 if it is a good idea to tie two pseudo registers
   when one has mode MODE1 and one has mode MODE2.
   If HARD_REGNO_MODE_OK could produce different values for MODE1 
   for any hard reg, then this must be 0 for correct output. */
#define MODES_TIEABLE_P(MODE1, MODE2)   1

/* Specify the registers used for certain standard purposes.
   The values of these macros are register numbers.  */

/* 1750A pc isn't overloaded on a register.  */
/* #define PC_REGNUM  */

/* Register to use for pushing function arguments.  */
#define STACK_POINTER_REGNUM 15

/* Base register for access to local variables of the function.  */
#define FRAME_POINTER_REGNUM 14

/* Value should be nonzero if functions must have frame pointers.
   Zero means the frame pointer need not be set up (and parms
   may be accessed via the stack pointer) in functions that seem s
   This is computed in `reload', in reload1.c. */
#define FRAME_POINTER_REQUIRED (! leaf_function_p ())

/* Base register for access to arguments of the function.  Note,
   because we've defined ELIMINABLE_REGS, ARG_POINTER_REGNUM will
   always be elminated.  */
#define ARG_POINTER_REGNUM 12

/* Define this macro if successive arguments to a function occupy
   decreasing addresses on the stack.

   #define ARGS_GROW_DOWNWARD
*/

/* Register in which static-chain is passed to a function. */
#define STATIC_CHAIN_REGNUM 13

/* Structures passed by value are not passed in register. Instead
   they are saved in memory, and the address of the save area is
   passed as in the usual way (i.e. in reg or on the stack) 
   as an "invisible" first argument */
/*
#define STRUCT_VALUE_REGNUM 0
*/
#define STRUCT_VALUE 0


#define STRUCT_VALUE_INCOMING 0

/* Define this to be 1 if all structure return values must be in memory */
#define DEFAULT_PCC_STRUCT_RETURN 0


/* Define the classes of registers for register constraints in the
   machine description.  Also define ranges of constants.

   One of the classes must always be named ALL_REGS and include all registers.
   If there is more than one class, another class must be named NO_REGS
   and contain no registers.

   The name GENERAL_REGS must be the name of a class (or an alias 
   another name such as ALL_REGS).  This is the class of registers
   that is allowed by "g" or "r" in a register constraint.
   Also, registers outside this class are allocated only when
   instructions express preferences for them.

   The classes must be numbered in nondecreasing order; that is,
   a larger-numbered class must never be contained completely
   in a smaller-numbered class.

   For any two classes, it is very desirable that there be another
   class that represents their union.  */

enum reg_class { NO_REGS, R2, R0_1, R0123, BASE_REGS, INDEX_REGS, ALL_REGS, LIM_REG_CLASSES };

#define N_REG_CLASSES (int) LIM_REG_CLASSES

/* Since GENERAL_REGS is the same class as ALL_REGS,
   don't give it a different class number; just make it an alias. */

#define GENERAL_REGS ALL_REGS

#define REG_CLASS_NAMES \
 { "NO_REGS", "R2", "R0_1", "R0123", "BASE_REGS", "INDEX_REGS", "ALL_REGS" }

/* Define which registers fit in which classes.
   This is an initializer for a vector of HARD_REG_SET of length N_REG_CLASSES.
   The only 1750 register not usable as INDEX_REG is R0.

   NO_REGS    = []
   R2         = [r2]
   R0_1       = [r0, r1]
   R0123      = [r0, r1, r2, r3]
   BASE_REGS  = [r12, r13, r14, r15]
   INDEX_REGS = [r4 .. r15]     -- don't use r1..r3
   ALL_REGS   = [r0 .. r15]
*/
#define REG_CLASS_CONTENTS {0, 0x0004, 0x0003, 0x000f, 0xf000, 0xfff0, 0xffff}

/* The same information, inverted:
   Return the class number of the smallest class containing
   reg number REGNO.  This could be a conditional expression
   or could index an array.  */
#define REGNO_REG_CLASS(REGNO) ((REGNO) == 2 ? R2 : (REGNO) == 0 ? R0_1 : \
  (REGNO) >= 12 ? BASE_REGS : (REGNO) >  3 ? INDEX_REGS : ALL_REGS)

/* The class value for index registers, and the one for base regs. */
/* On the 1750, there is negligible difference between GCC's base register
   and GCC's index registers
*/
#define INDEX_REG_CLASS  INDEX_REGS
#define BASE_REG_CLASS INDEX_REGS

/* Get reg_class from a letter such as appears in the machine desciption
   For the 1750, we have 'z' for R0_1, 't' for R2, 'b' for gcc Base
   and 'x' for gcc Index regs. */

#define REG_CLASS_FROM_LETTER(C) ((C) == 't' ? R2 : \
                                  (C) == 'z' ? R0_1 : \
                                  (C) == 'y' ? R0123 : \
                                  (C) == 'x' ? INDEX_REGS : \
                                  (C) == 'b' ? BASE_REGS : NO_REGS)

/* The letters I,J,K,.. to P in a register constraint string
   can be used to stand for particular ranges of immediate operand
   This macro defines what the ranges are.
   C is the letter, and VALUE is a constant value.
   Return 1 if VALUE is in the range specified by C.

   For the 1750, 
   `I' is used for ISP mode instructions,
   `J' is used for ISN mode instructions,
   `K' is used for the STC instruction's constant range,
   `L' is used for unsigned 8-bit address displacements in instructions
       of address mode relative",
   `M' is for IM mode instructions et al.,
   'N' is for double length shifts,
   `O' is a synonym for (const_int 0). */

#define CONST_OK_FOR_LETTER_P(VALUE, C)                         \
  ((C) == 'I' ? (VALUE) > 0 && (VALUE) <=  16 :                 \
   (C) == 'J' ? (VALUE) < 0 && (VALUE) >= -16 :                 \
   (C) == 'K' ? (VALUE) >= 0 && (VALUE) <= 15 :                 \
   (C) == 'N' ? (VALUE) > 0 && (VALUE) <= 32 :                  \
   (C) == 'P' ? (VALUE) < 0 && (VALUE) >= -32 :                 \
   (C) == 'L' ? (VALUE) >= 0 && (VALUE) <= 0xFF :               \
   (C) == 'M' ? (VALUE) >= -0x8000 && (VALUE) <= 0x7FFF :       \
   (C) == 'O' ? (VALUE) == 0 : 0)

/* Similar, but for floating constants, and defining letter 'G'.
   Here VALUE is the CONST_DOUBLE rtx itself.  */
#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C)  0

/* Optional extra constraints for this machine.

   For the 1750, `Q' means that this is a memory operand consisting
   of the sum of an Index Register (in the GCC sense, i.e. R12..R15)
   and a constant in the range 0..255. This constraint is used for
   the Base Register with Offset address mode instructions (LB,STB,AB,..)  */

/* and 'q' means BX mode */
#define EXTRA_CONSTRAINT(OP, C) \
  (((C) == 'Q' && b_mode_operand_p (OP)) \
    || ((C) == 'q' && bx_mode_operand_p (OP)))

/* Given an rtx X being reloaded into a reg required to be
   in class CLASS, return the class of reg to actually use.
   In general this is just CLASS; but on some machines
   in some cases it is preferable to use a more restrictive class. */

#define PREFERRED_RELOAD_CLASS(X,CLASS) \
  (GET_MODE (X) == SImode ? ALL_REGS : (CLASS))

#define SMALL_REGISTER_CLASSES

/* Return the maximum number of consecutive registers
   needed to represent mode MODE in a register of class CLASS.
   On the 1750A, this is the size of MODE in words,
   since class doesn't make any difference. */
#define CLASS_MAX_NREGS(CLASS,MODE)  GET_MODE_SIZE(MODE)


/* Stack layout; function entry, exit and calling.  */

/* Define this if pushing a word on the stack
   makes the stack pointer a smaller address.  */
#define STACK_GROWS_DOWNWARD 1

/* Define this if the nominal address of the stack frame
   is at the high-address end of the local variables;
   goes at a more negative offset in the frame. 
   #define FRAME_GROWS_DOWNWARD
*/

/* Offset within stack frame to start allocating local variables a
   If FRAME_GROWS_DOWNWARD, this is the offset to the END of the
   first local allocated.  Otherwise, it is the offset to the BEGI
   of the first local allocated.
*/
#define STARTING_FRAME_OFFSET 1

/* This is the default anyway:
   #define DYNAMIC_CHAIN_ADDRESS(FRAMEADDR) FRAMEADDR
*/

/* If we generate an insn to push BYTES bytes,
   this says how many the stack pointer really advances by.
   1750 note: what GCC calls a "byte" is really a 16-bit word,
   because BITS_PER_UNIT is 16. */

#define PUSH_ROUNDING(BYTES) (BYTES)

/* Define this macro if functions should assume that stack space has
   been allocated for arguments even when their values are passed 
   registers.
   Size, in bytes, of the area reserved for arguments passed in
   registers for the function represented by FNDECL. 
   #define REG_PARM_STACK_SPACE(FNDECL) 14 */

/* Define this if it is the responsibility of the caller to alloca
   the area reserved for arguments passed in registers. 
   #define OUTGOING_REG_PARM_STACK_SPACE */

/* We cannot work out the offset until spill temps are allocated, and
   by then it's too late for this macro. Instead we try to eliminate
   the ARG_POINTER.  */
 
#define FIRST_PARM_OFFSET(FNDECL) 0

/*
#define FIRST_PARM_OFFSET(FNDECL) \
   ((TARGET_MMU && far_function_p ()? 3 : 1) + 1)
*/

/* Value is 1 if returning from a function call automatically
   pops the arguments described by the number-of-args field in the
   FUNDECL is the declaration node of the function (as a tree),
   FUNTYPE is the data type of the function (as a tree),
   or for a library call it is an identifier node for the subroutine */

#define RETURN_POPS_ARGS(FUNDECL,FUNTYPE,SIZE) 0

/* Define how to find the value returned by a function.
   VALTYPE is the data type of the value (as a tree).
   If the precise function being called is known, FUNC is its FUNC
   otherwise, FUNC is 0. */

#define FUNCTION_VALUE(VALTYPE, FUNC)  \
  gen_rtx(REG,TYPE_MODE(VALTYPE),0)

/* Define how to find the value returned by a library function
   assuming the value has mode MODE. */

#define LIBCALL_VALUE(MODE)  gen_rtx (REG, MODE, 0)

/* 1 if N is a possible register number for a function value. */

#define FUNCTION_VALUE_REGNO_P(N)  ((N) == 0)

/* 1 if the tree TYPE should be returned in memory instead of in r
   #define RETURN_IN_MEMORY(TYPE) \
   (int_size_in_bytes(TYPE) > 12)
*/

/* Force aggregates and objects larger than 8 words to be returned in memory,
   since we only have 4 registers available for return values.  */

#define RETURN_IN_MEMORY(TYPE) \
  (TYPE_MODE (TYPE) == BLKmode || int_size_in_bytes (TYPE) > 16)

/* Define this if PCC uses the nonreentrant convention for returning
   structure and union values. 
   #define PCC_STATIC_STRUCT_RETURN  */

/* 1 if N is a possible register number for function argument pass */

#define FUNCTION_ARG_REGNO_P(N)  ((N) < 12)

/* Define this to be true when FUNCTION_VALUE_REGNO_P is true for
   more than one register.  */

/* #define NEEDS_UNTYPED_CALL 0 */



/* Define a data type for recording info about an argument list
   during the scan of that argument list.  This data type should
   hold all necessary information about the function itself
   and about the args processed so far, enough to enable macros
   such as FUNCTION_ARG to determine where the next arg should go.

   On the m1750, this is a single integer, which is a number of bytes
   of arguments scanned so far.  */

#define CUMULATIVE_ARGS int

/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.

   On the m1750, the offset starts at 0.  */

#define INIT_CUMULATIVE_ARGS(CUM,FNTYPE,LIBNAME) ((CUM) = 0)

/* Update the data in CUM to advance over an argument
   of mode MODE and data type TYPE.
   (TYPE is null for libcalls where that information may not be available.)  */

#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED)	\
 ((CUM) += ((MODE) != BLKmode		\
	    ? GET_MODE_SIZE (MODE) 	\
	    : int_size_in_bytes (TYPE) ))

/* Define where to put the arguments to a function.
   Value is zero to push the argument on the stack,
   or a hard register in which to store the argument.

   MODE is the argument's machine mode.
   TYPE is the data type of the argument (as a tree).
    This is null for libcalls where that information may
    not be available.
   CUM is a variable of type CUMULATIVE_ARGS which gives info about
    the preceding args and about the function being called.
   NAMED is nonzero if this argument is a named parameter
    (otherwise it is an extra parameter matching an ellipsis).  */

#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) \
((TARGET_REGPARM && (CUM) + GET_MODE_SIZE (MODE) <= 11) ? \
  gen_rtx (REG, (MODE), (CUM)) : 0)

#define FUNCTION_ARG_PASS_BY_REFERENCE(CUM, MODE, TYPE, NAMED) \
  ((MODE) == BLKmode ? 1 : 0)

/* Definitions for register eliminations.

   This is an array of structures.  Each structure initializes one pair
   of eliminable registers.  The "from" register number is given first,
   followed by "to".  Eliminations of the same "from" register are listed
   in order of preference.

   We have two registers that can be eliminated on the m1750.  First, the
   frame pointer register can often be eliminated in favor of the stack
   pointer register.  Secondly, the argument pointer register can always be
   eliminated; it is replaced with either the stack or frame pointer. */

#define ELIMINABLE_REGS                         \
{{ ARG_POINTER_REGNUM, STACK_POINTER_REGNUM},   \
 { ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM},   \
 { FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}

/* Given FROM and TO register numbers, say whether this elimination is allowed.
   Frame pointer elimination is automatically handled.

   For the m1750, if frame pointer elimination is being done, we would like to
   convert ap into sp, not fp.

   All other eliminations are valid.  */

#define CAN_ELIMINATE(FROM, TO)  1

/* Define the offset between two registers, one to be eliminated, and the other
   its replacement, at the start of a routine.  */

#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET) \
  OFFSET = initial_offset (FROM, TO)

/* Define the following macro if function calls on the target machine
   do not preserve any registers; in other words, if `CALL_USED_REGISTERS'
   has 1 for all registers. This macro enables `-fcaller-saves' by
   default. Eventually that option will be enabled by default on all
   machines and both the option and this macro will be eliminated. */

/* Perform any needed actions needed for a function that is receiving a
   variable number of arguments. 

   CUM is as above.

   MODE and TYPE are the mode and type of the current parameter.

   PRETEND_SIZE is a variable that should be set to the amount of stack
   that must be pushed by the prolog to pretend that our caller pushed
   it.

   Normally, this macro will push all remaining incoming registers on the
   stack and set PRETEND_SIZE to the length of the registers pushed.  */

#define OLD_SETUP_INCOMING_VARARGS(CUM,MODE,TYPE,PRETEND_SIZE,NO_RTL) \
{ if ((CUM) < 11)                                                       \
    {                                                                   \
      int first_reg_offset = (CUM);                                     \
                                                                        \
      if (!MUST_PASS_IN_STACK (MODE, TYPE))                              \
        first_reg_offset += GET_MODE_SIZE (TYPE_MODE (TYPE));           \
                                                                        \
      if (first_reg_offset > 11)                                        \
        first_reg_offset = 11;                                          \
                                                                        \
      if (! (NO_RTL) && first_reg_offset != 11)                         \
        move_block_from_reg                                             \
          (first_reg_offset,                                 \
           gen_rtx (MEM, BLKmode, virtual_incoming_args_rtx),           \
           11 - first_reg_offset, (11 - first_reg_offset) * UNITS_PER_WORD); \
      PRETEND_SIZE = (11 - first_reg_offset) * UNITS_PER_WORD;          \
    }                                                                   \
}


#define DEFAULT_CALLER_SAVES

/* This macro generates the assembly code for function entry.
   FILE is a stdio stream to output the code to.
   SIZE is an int: how many units of temporary storage to allocate.
   Refer to the array `regs_ever_live' to determine which registers
   to save; `regs_ever_live[I]' is nonzero if register number I
   is ever used in the function.  This macro is responsible for
   knowing which registers should not be saved even if used.  */

#define FUNCTION_PROLOGUE(FILE, SIZE) output_function_prologue(FILE, SIZE)

/* Output assembler code to FILE to increment profiler label # LABELNO
   for profiling a function entry.  */

#define FUNCTION_PROFILER(FILE, LABELNO)  \
  asm_fprintf (FILE, "\tlim    r12,%LLP%d\n\tsjs    r15,mcount\n", (LABELNO))

/* Output assembler code to FILE to initialize this source file's
   basic block profiling info, if that has not already been done.  */

#define FUNCTION_BLOCK_PROFILER(FILE, LABELNO)  \
  asm_fprintf (FILE, "\
  \ttb     15,%LLPBX0\n\
  \tbnz    %LLPI%d\n\
  \tpshm   r0,r0\n\
  \tlim    r0,%LLPBX0\n\
  \tsjs    r15,%U__bb_init_func\n\
  \tpopm   r0,r0\n\
%LLPI%d:\n", LABELNO, LABELNO);

/* Output assembler code to FILE to increment the entry-count for
   the BLOCKNO'th basic block in this source file.  */

#define BLOCK_PROFILER(FILE, BLOCKNO)	\
  asm_fprintf (FILE, "\tincm   1,%LLPBX2+%d\n", 2 * BLOCKNO)

/* EXIT_IGNORE_STACK should be nonzero if, when returning from a function,
   the stack pointer does not matter.  The value is tested only in
   functions that have frame pointers.
   No definition is equivalent to always zero.  */

#define EXIT_IGNORE_STACK 1

/* Generate the assembly code for function exit. */
#define FUNCTION_EPILOGUE(FILE, SIZE) output_function_epilogue (FILE, SIZE)
  
/* This is a hook for other tm files to change.  */
/* #define FUNCTION_EXTRA_EPILOGUE(FILE, SIZE) */

/* Determine if the epilogue should be output as RTL.
   You should override this if you define FUNCTION_EXTRA_EPILOGUE.  */
#define USE_RETURN_INSN use_return_insn ()

/* Store in the variable DEPTH the initial difference between the
   frame pointer reg contents and the stack pointer reg contents,
   as of the start of the function body.  This depends on the layout
   of the fixed parts of the stack frame and on how registers are saved.

   On the 1750, if we have a frame, we must add one word to its length
   to allow for the place that r14 is stored when we do have a frame pointer.
   Otherwise, we would need to compute the offset from the frame pointer
   of a local variable as a function of frame_pointer_needed, which
   is hard.  */

#define INITIAL_FRAME_POINTER_OFFSET(DEPTH) DEPTH = 0


/* Output assembler code for a block containing the constant parts
   of a trampoline, leaving space for the variable parts.  */

/*
   FIXME: trampolines for the 1750
*/

#define TRAMPOLINE_TEMPLATE(FILE)					\
{									\
}

/* Length in units of the trampoline for entering a nested function.  */

#define TRAMPOLINE_SIZE 26

/* Alignment required for a trampoline.  16 is used to find the
   beginning of a line in the instruction cache.  */

#define TRAMPOLINE_ALIGN 16

/* Emit RTL insns to initialize the variable parts of a trampoline.
   FNADDR is an RTX for the address of the function's pure code.
   CXT is an RTX for the static chain value for the function.  */

#define INITIALIZE_TRAMPOLINE(TRAMP, FNADDR, CXT)			\
{									\
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant (TRAMP, 2)), TRAMP); \
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant (TRAMP, 18)), CXT); \
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant (TRAMP, 22)), FNADDR); \
}

/* This is the library routine that is used
   to transfer control from the trampoline
   to the actual nested function.  */

/* A colon is used with no explicit operands
   to cause the template string to be scanned for %-constructs.  */
/* The function name __transfer_from_trampoline is not actually used.
   The function definition just permits use of "asm with operands"
   (though the operand list is empty).  */
#define TRANSFER_FROM_TRAMPOLINE				\
void								\
__transfer_from_trampoline ()					\
{								\
  register char *a0 asm ("%a0");				\
  asm (GLOBAL_ASM_OP " ___trampoline");				\
  asm ("___trampoline:");					\
  asm volatile ("move%.l %0,%@" : : "m" (a0[22]));		\
  asm volatile ("move%.l %1,%0" : "=a" (a0) : "m" (a0[18]));	\
  asm ("rts":);							\
}

/* Addressing modes, and classification of registers for them.  */

/* #define HAVE_POST_DECREMENT */

/* #define HAVE_PRE_INCREMENT */


/* Generate necessary RTL for __builtin_saveregs().
   ARGLIST is the argument list; see expr.c.  */
extern struct rtx_def *m1750_builtin_saveregs ();

#define EXPAND_BUILTIN_SAVEREGS(ARGLIST) m1750_builtin_saveregs (ARGLIST)


/* Add any extra modes needed to represent the condition code.

   For the M1750, we need separate modes when unsigned (logical) comparisons
   are being done.
*/

#define EXTRA_CC_MODES CCUNSmode

/* Define the names for the modes specified above.  */
#define EXTRA_CC_NAMES "CCUNS"

/* Given a comparison code (EQ, NE, etc.) and the first operand of a COMPARE,
   return the mode to be used for the comparison. CCUNSmode should be used 
   for unsigned comparisons.
   CCmode should be used in all other cases.  */

#define SELECT_CC_MODE(OP,X,Y) \
   ((OP) == GTU || (OP) == LTU || (OP) == GEU || (OP) == LEU ? \
    CCUNSmode : CCmode)

/* Define the information needed to generate branch and scc insns.  This is
   stored from the compare operation.  Note that we can't use "rtx" here
   since it hasn't been defined!  */

extern struct rtx_def *m1750_compare_op0, *m1750_compare_op1;
extern enum machine_mode m1750_compare_mode;
extern int m1750_compare_flag;

/* Macros to check register numbers against specific register classes.  */

/* These assume that REGNO is a hard or pseudo reg number.
   They give nonzero only if REGNO is a hard reg of the suitable class
   or a pseudo reg currently allocated to a suitable hard reg.
   Since they use reg_renumber, they are safe only once reg_renumber
   has been allocated, which happens in local-alloc.c.  */

#define REGNO_OK_FOR_INDEX_P(REGNO)  \
 ((REGNO) >= 1 && (REGNO) <= 15 ||   \
  reg_renumber[REGNO] >= 1 && reg_renumber[REGNO] <= 15)
#define REGNO_OK_FOR_BASE_P(REGNO) \
 ((REGNO) >= 1 && (REGNO) <= 15 || \
  reg_renumber[REGNO] >= 1 && reg_renumber[REGNO] <= 15)
#define REGNO_OK_FOR_DATA_P(REGNO) \
 ((REGNO) < 15 || (unsigned) reg_renumber[REGNO] < 15)
#define REGNO_OK_FOR_FP_P(REGNO) \
 ((REGNO) < 11 || (unsigned) reg_renumber[REGNO] < 11)


/* Now macros that check whether X is a register and also,
   strictly, whether it is in a specified class.

   These macros are specific to the 1750, and may be used only
   in code for printing assembler insns and in conditions for
   define_optimization.  */

/* 1 if X is a data register.  */

#define DATA_REG_P(X) (REG_P (X) && REGNO_OK_FOR_DATA_P (REGNO (X)))

/* 1 if X is an fp register.  */

#define FP_REG_P(X) (REG_P (X) && REGNO_OK_FOR_FP_P (REGNO (X)))

/* 1 if X is an address register  */

#define ADDRESS_REG_P(X) (REG_P (X) && REGNO_OK_FOR_INDEX_P (REGNO (X)))


/* Maximum number of registers that can appear in a valid memory address.  */
#define MAX_REGS_PER_ADDRESS 1

/* Recognize any constant value that is a valid address.  */

#define CONSTANT_ADDRESS_P(X)   \
  (GET_CODE (X) == LABEL_REF || GET_CODE (X) == SYMBOL_REF              \
   || GET_CODE (X) == CONST_INT || GET_CODE (X) == CONST                \
   || GET_CODE (X) == HIGH)

/* Nonzero if the constant value X is a legitimate general operand.
   It is given that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */

#define LEGITIMATE_CONSTANT_P(X) 1

/* Nonzero if the constant value X is a legitimate general operand
   when generating PIC code.  It is given that flag_pic is on and 
   that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */

#define LEGITIMATE_PIC_OPERAND_P(X)     \
  ((! symbolic_operand (X, VOIDmode)                            \
    && ! (GET_CODE (X) == CONST_DOUBLE && CONST_DOUBLE_MEM (X)  \
          && GET_CODE (CONST_DOUBLE_MEM (X)) == MEM             \
          && symbolic_operand (XEXP (CONST_DOUBLE_MEM (X), 0),  \
                               VOIDmode)))                      \
   || (GET_CODE (X) == SYMBOL_REF && SYMBOL_REF_FLAG (X)))


#ifdef REG_OK_STRICT
/* Nonzero if X is a hard reg that can be used as an index.  */
#define REG_OK_FOR_BASE_P(X) (REGNO (X) > 0 && REGNO (X) <= 15)
/* Nonzero if X is a hard reg that can be used as a base reg.  */
#define REG_OK_FOR_INDEX_P(X)  (REGNO (X) > 0 && REGNO (X) <= 15)

#else

/* Nonzero if X is a hard reg that can be used as an index
   or if it is a pseudo reg.  */
#define REG_OK_FOR_BASE_P(X) (REGNO (X) > 0)
/* Nonzero if X is a hard reg that can be used as a base reg
   or if it is a pseudo reg.  */
#define REG_OK_FOR_INDEX_P(X) (REGNO (X) > 0)

#endif



/* GO_IF_LEGITIMATE_ADDRESS recognizes an RTL expression
   that is a valid memory address for an instruction.
   The MODE argument is the machine mode for the MEM expression
   that wants to use this address.

   The other macros defined here are used only in GO_IF_LEGITIMATE_ADDRESS.  */

/* 
 * addressing modes are:
 *  direct   (constant_addreess_p)
 *  indirect
 *  direct indexed  (based_address)
 *  indirect indexed
 */
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, ADDR) {                       \
        if (CONSTANT_ADDRESS_P(X)) goto ADDR;                           \
        GO_IF_BASED_ADDRESS(X,ADDR) }

#define GO_IF_BASED_ADDRESS(X, ADDR) {                                     \
   if ((GET_CODE (X) == REG && REG_OK_FOR_INDEX_P(X)))                     \
     goto ADDR;                                                            \
   if (GET_CODE (X) == PLUS)                                               \
    { register rtx x0 = XEXP(X,0), x1 = XEXP(X,1);                         \
      if ((REG_P(x0) && REG_OK_FOR_INDEX_P(x0) && CONSTANT_ADDRESS_P(x1))  \
       || (REG_P(x1) && REG_OK_FOR_INDEX_P(x1) && CONSTANT_ADDRESS_P(x0))) \
     goto ADDR; } }


/* Allow SUBREG everywhere we allow REG.  This results in better code.  It
   also makes function inlining work when inline functions are called with
   arguments that are SUBREGs.  */

/*
   the switch offset.  This address is ok as it stands (see above),
   but memory_address_noforce would alter it.  */
#define PIC_CASE_VECTOR_ADDRESS(index) index

/* Try machine-dependent ways of modifying an illegitimate address
   to be legitimate.  If we find one, return the new, valid address.
   This macro is used in only one place: `memory_address' in explow.c.

   OLDX is the address as it was before break_out_memory_refs was called.
   In some cases it is useful to look at this to decide what needs to be done.

   MODE and WIN are passed so that this macro can use
   GO_IF_LEGITIMATE_ADDRESS.

   It is always safe for this macro to do nothing.  It exists to recognize
   opportunities to optimize the output.

   For the 68000, we handle X+REG by loading X into a register R and
   using R+REG.  R will go in an address reg and indexing will be used.
   However, if REG is a broken-out memory address or multiplication,
   nothing needs to be done because REG can certainly go in an address reg.  */

#define LEGITIMIZE_ADDRESS(X,OLDX,MODE,WIN)

/* Go to LABEL if ADDR (a legitimate address expression)
   has an effect that depends on the machine mode it is used for.
   On the 68000, only predecrement and postincrement address depend thus
   (the amount of decrement or increment being the length of the operand).  */

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL)

/* Specify the machine mode that this machine uses
   for the index in the tablejump instruction.  */
#define CASE_VECTOR_MODE QImode

/* Define this if the tablejump instruction expects the table
   to contain offsets from the address of the table.
   Do not define this if the table should contain absolute addresses.  */
/* #define CASE_VECTOR_PC_RELATIVE */

/* Specify the tree operation to be used to convert reals to integers.  */
#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR

/* This is the kind of divide that is easiest to do in the general case.  */
#define EASY_DIV_EXPR TRUNC_DIV_EXPR

/* Define this as 1 if `char' should by default be signed; else as 0.  */
#define DEFAULT_SIGNED_CHAR 1

/* Don't cse the address of the function being compiled.  */
#define NO_RECURSIVE_FUNCTION_CSE

/* Max number of bytes we can move from memory to memory
   in one reasonably fast instruction.  */
#define MOVE_MAX 16384

/* Define this if zero-extension is slow (more than one real instruction).  */
/* #define SLOW_ZERO_EXTEND */

/* Nonzero if access to memory by bytes is slow and undesirable.  */
#define SLOW_BYTE_ACCESS 0

/* Define if shifts truncate the shift count
   which implies one can omit a sign-extension or zero-extension
   of a shift count. */
/* #define SHIFT_COUNT_TRUNCATED 1 */

/* Value is 1 if truncating an integer of INPREC bits to OUTPREC bits
   is done just by pretending it is already truncated.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1

/* We assume that the store-condition-codes instructions store 0 for false
   and some other value for true.  This is the value stored for true.  */

#define STORE_FLAG_VALUE 1

/* When a prototype says `char' or `short', really pass an `int'.  */
/* 1750: for now, `char' is 16 bits wide anyway. */

#define PROMOTE_PROTOTYPES

/* Specify the machine mode that pointers have.
   After generation of rtl, the compiler makes no further distinction
   between pointers and any other objects of this machine mode.  */
#ifdef M1750B_LONG_ADDRESSING
#define Pmode (TARGET_D24? HImode : QImode)
#else
#define Pmode QImode
#endif

/* another experiment... */
/* #define FUNCTION_MODE (TARGET_MMU? HImode : Pmode) */
#define FUNCTION_MODE Pmode


/* Compute the cost of computing a constant rtl expression RTX
   whose rtx-code is CODE.  The body of this macro is a portion
   of a switch statement.  If the code is computed here,
   return it with a return statement.  Otherwise, break from the switch.  */

#define CONST_COSTS(RTX,CODE,OUTER_CODE)                        \
  case CONST_INT:                                               \
    return (INTVAL(RTX) >= -16 && INTVAL(RTX) <= 16) ? 1 : 3;   \
  case CONST:                                                   \
  case LABEL_REF:                                               \
  case SYMBOL_REF:                                              \
    return 5;                                                   \
  case CONST_DOUBLE:                                            \
    if (OUTER_CODE == COMPARE && constant_zero_p (RTX))         \
      return 1;                                                 \
    else                                                        \
      return 7;

#define REGISTER_MOVE_COST(FROM,TO)     2

#define MEMORY_MOVE_COST(M)             5

/* Tell final.c how to eliminate redundant test instructions.  */

/* Here we define machine-dependent flags and fields in cc_status
   (see `conditions.h').  */

/* Store in cc_status the expressions that the condition codes will
   describe after execution of an instruction whose pattern is EXP.
   Do not alter them if the instruction would not alter the cc's.  */

/* Store in cc_status the expressions
   that the condition codes will describe
   after execution of an instruction whose pattern is EXP.
   Do not alter them if the instruction would not alter the cc's.
   1750: See file out-1750a.c for notice_update_cc().  */

#define NOTICE_UPDATE_CC(EXP, INSN) notice_update_cc(EXP)


/* Control the assembler format that we output.  */

#define ASM_COMMENT_START "\t\t!"

/* Output at beginning of assembler file.  */

#undef ASM_FILE_START
#define ASM_FILE_START(FILE)                                    \
  do { fprintf (FILE, "\t.file  ");                             \
       output_quoted_string (FILE, main_input_filename);        \
       fprintf (FILE, "\n");                                    \
       if (optimize)                                            \
          ASM_FILE_START_1 (FILE);                              \
       else                                                     \
          fprintf (FILE, "\t.noopt\n");                         \
     } while (0)

/* Do use .optim by default on this machine.  */
#undef ASM_FILE_START_1
#define ASM_FILE_START_1(FILE) fprintf (FILE, "\t.optim\n")


/* Output to assembler file text saying following lines
   may contain character constants, extra white space, comments, etc.  */

#define ASM_APP_ON "#APP\n"

/* Output to assembler file text saying following lines
   no longer contain unusual constructs.  */

#define ASM_APP_OFF "#NO_APP\n"

/* A list of other sections which the compiler might be "in" at any
   given time.  */

#undef EXTRA_SECTIONS
#define EXTRA_SECTIONS in_rodata, in_ctors, in_dtors
#define READONLY_DATA_SECTION rodata_section

/* A list of extra section function definitions.  */

#undef EXTRA_SECTION_FUNCTIONS
#define EXTRA_SECTION_FUNCTIONS                                         \
  RODATA_SECTION_FUNCTION                                               \
  CTORS_SECTION_FUNCTION                                                \
  DTORS_SECTION_FUNCTION

#define RODATA_SECTION_FUNCTION                                         \
void                                                                    \
rodata_section ()                                                       \
{                                                                       \
  if (in_section != in_rodata)                                          \
    {                                                                   \
      fprintf (asm_out_file, "%s\n", RODATA_SECTION_ASM_OP);            \
      in_section = in_rodata;                                           \
    }                                                                   \
}

#define CTORS_SECTION_FUNCTION                                          \
void                                                                    \
ctors_section ()                                                        \
{                                                                       \
  if (in_section != in_ctors)                                           \
    {                                                                   \
      fprintf (asm_out_file, "%s\n", CTORS_SECTION_ASM_OP);             \
      in_section = in_ctors;                                            \
    }                                                                   \
}

#define DTORS_SECTION_FUNCTION                                          \
void                                                                    \
dtors_section ()                                                        \
{                                                                       \
  if (in_section != in_dtors)                                           \
    {                                                                   \
      fprintf (asm_out_file, "%s\n", DTORS_SECTION_ASM_OP);             \
      in_section = in_dtors;                                            \
    }                                                                   \
}

/* Output before read-only data.  */

#define RODATA_SECTION_ASM_OP "\t.rodata"

#define TEXT_SECTION_ASM_OP "\t.text"

/* Output before writable data.  */

#define DATA_SECTION_ASM_OP "\t.data"

#define CTORS_SECTION_ASM_OP    ".section .ctors,\"x\""
#define DTORS_SECTION_ASM_OP    ".section .dtors,\"x\""
#define INIT_SECTION_ASM_OP     ".section .init,\"x\""

/* Here are four prefixes that are used by asm_fprintf to
   facilitate customization for alternate assembler syntaxes.
   Machines with no likelihood of an alternate syntax need not
   define these and need not use asm_fprintf.  */

/* The prefix for register names.  Note that REGISTER_NAMES
   is supposed to include this prefix.  */

#define REGISTER_PREFIX ""

/* The prefix for local labels.  You should be able to define this as
   an empty string, or any arbitrary string (such as ".", ".L%", etc)
   without having to make any other changes to account for the specific
   definition.  Note it is a string literal, not interpreted by printf
   and friends. */

#define LOCAL_LABEL_PREFIX "."

/* Generate sdb debugging information.  */

#undef DBX_DEBUGGING_INFO
#define SDB_DEBUGGING_INFO

/* Output DBX (stabs) debugging information if using -gstabs.  */

#define DBX_DEBUGGING_INFO

#undef PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE SDB_DEBUG

/* The prefix to add to user-visible assembler symbols.  */

#define USER_LABEL_PREFIX ""

/* The prefix for immediate operands.  */

#define IMMEDIATE_PREFIX "#"

/* How to refer to registers in assembler output.
   This sequence is indexed by compiler's hard-register-number (see above).  */

#define REGISTER_NAMES \
 { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", \
   "r8", "r9","r10","r11","r12","r13","r14","r15" }

/* How to renumber registers for dbx and gdb. */

#define DBX_REGISTER_NUMBER(REGNO) (REGNO)

/* This is how to output the definition of a user-level label named NAME,
   such as the label on a static function or variable NAME.  */

#define ASM_OUTPUT_LABEL(FILE,NAME)     \
  do { assemble_name (FILE, NAME); fputs (":\n", FILE); } while (0)

/* This is how to output a command to make the user-level label named NAME
   defined for reference from other files.  */

#define GLOBAL_ASM_OP ".globl"
#define ASM_GLOBALIZE_LABEL(FILE,NAME)                  \
  do { fprintf (FILE, "%s ", GLOBAL_ASM_OP);            \
       assemble_name (FILE, NAME);                      \
       fputs ("\n", FILE);} while (0)

/* This is how to output a reference to a user-level label named NAME.
   `assemble_name' uses this.  */

#define ASM_OUTPUT_LABELREF(FILE,NAME)  \
  asm_fprintf (FILE, "%U%s", NAME)

/* This is how to output an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.  */

#define ASM_OUTPUT_INTERNAL_LABEL(FILE,PREFIX,NUM)	\
  asm_fprintf (FILE, "%0L%s%d:\n", PREFIX, NUM)

#define ASM_GENERATE_INTERNAL_LABEL(LABEL,PREFIX,NUM)	\
  sprintf (LABEL, "*%s%s%d", LOCAL_LABEL_PREFIX, PREFIX, NUM)

/* This is how to output a `long double' extended real constant. */
/* 1750: long double not supported */
  
#define ASM_OUTPUT_LONG_DOUBLE(FILE,VALUE)  			\
do {                                                            \
       fprintf (FILE, "\t.err\n");	                	\
   } while (0)
  
/* This is how to output an assembler line defining a `double' constant.  */
/* 1750: note a double has 11 digits */

#define ASM_OUTPUT_DOUBLE(FILE,VALUE)				\
  do { char dstr[30];						\
       REAL_VALUE_TO_DECIMAL (VALUE, "%-.20g", dstr);		\
       fprintf (FILE, "\t.double 0r%s\n", dstr);		\
     } while (0)

/* This is how to output an assembler line defining a `float' constant.  */

#define ASM_OUTPUT_FLOAT(FILE,VALUE)			\
do { long l;						\
     REAL_VALUE_TO_TARGET_SINGLE (VALUE, l);		\
     if (sizeof (int) == sizeof (long))			\
       fprintf (FILE, "\t.long  0x%x\n", l);		\
     else						\
       fprintf (FILE, "\t.long  0x%lx\n",l);		\
   } while (0)

#define ASM_OUTPUT_SHORT_FLOAT(FILE,VALUE)                     \
  do { char dstr[30];                                          \
       REAL_VALUE_TO_DECIMAL (VALUE, "%.9g", dstr);            \
       fprintf (FILE, "\t.float 0r%s\n", dstr);                \
     } while (0)

/* This is how to output an assembler line defining a 1750A `double'
    constant. */

#define ASM_OUTPUT_THREE_QUARTER_FLOAT(FILE,VALUE)              \
  do { char dstr[30];                                           \
       REAL_VALUE_TO_DECIMAL (VALUE, "%.14g", dstr);            \
       fprintf (FILE, "\t.double 0r%s\n", dstr);                \
     } while (0)


/* This is how to output an assembler line defining an `int' constant.  */
/* 1750: Oddly this is called to output a long long int */
#define ASM_OUTPUT_INT(FILE,VALUE)              \
( fprintf (FILE, "\t.quad  "),	        	\
  output_addr_const (FILE, (VALUE)),		\
  fprintf (FILE, "\n"))

/* Likewise for `char' and `short' constants.  */
/* 1750: Oddly this outputs a long int */
#define ASM_OUTPUT_SHORT(FILE,VALUE)            \
( fprintf (FILE, "\t.long  "),			\
  output_addr_const (FILE, (VALUE)),		\
  fprintf (FILE, "\n"))

#define ASM_OUTPUT_CHAR(FILE,VALUE)             \
( fprintf (FILE, "\t.word  "),			\
  output_addr_const (FILE, (VALUE)),		\
  fprintf (FILE, "\n"))

/* This is how to output an assembler line for a numeric constant byte.  */

#define ASM_OUTPUT_BYTE(FILE,VALUE)  \
  fprintf (FILE, "\t.byte  0x%x\n", (VALUE))

/* This is how to output an insn to push a register on the stack.
   It need not be very fast code.  */

#define ASM_OUTPUT_REG_PUSH(FILE,REGNO)  \
  asm_fprintf (FILE, "\tmovel %s,%Rsp@-\n", reg_names[REGNO])

/* This is how to output an insn to pop a register from the stack.
   It need not be very fast code.  */

#define ASM_OUTPUT_REG_POP(FILE,REGNO)  \
  asm_fprintf (FILE, "\tmovel %Rsp@+,%s\n", reg_names[REGNO])

/* This is how to output an element of a case-vector that is absolute.
   (The 1750 does not use such vectors,
   but we must define this macro anyway.)  */

#define ASM_OUTPUT_ADDR_VEC_ELT(FILE, VALUE)  \
  asm_fprintf (FILE, "\t.word  %LL%d\n", VALUE)

/* This is how to output an element of a case-vector that is relative.  */

#define ASM_OUTPUT_ADDR_DIFF_ELT(FILE, VALUE, REL)  \
  asm_fprintf (FILE, "\t.word  %LL%d-%LL%d\n", VALUE, REL)

/* This is how to output an assembler line
   that says to advance the location counter
   to a multiple of 2**LOG bytes.  */

/* We don't have a way to align to more than a two-byte boundary, so do the
   best we can and don't complain.  */
#define ASM_OUTPUT_ALIGN(FILE,LOG)	\
  if ((LOG) >= 1)			\
    fprintf (FILE, "\t.even\n");

#define ASM_OUTPUT_SKIP(FILE,SIZE)  \
  fprintf (FILE, "\t.skip    %u\n", 2 * (SIZE))

/* This says how to output an assembler line
   to define a global common symbol.  */

#define ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED)      \
( fputs ("\n\t.comm  ", (FILE)),		          \
  assemble_name ((FILE), (NAME)),                         \
  fprintf ((FILE), ",%u\n", 2 * (ROUNDED)))

/* This says how to output an assembler line
   to define a local common symbol.  */

#define ASM_OUTPUT_LOCAL(FILE, NAME, SIZE, ROUNDED)  \
( fputs ("\n\t.lcomm ", (FILE)),			\
  assemble_name ((FILE), (NAME)),		\
  fprintf ((FILE), ",%u\n", 2 * (ROUNDED)))

/* Store in OUTPUT a string (made with alloca) containing
   an assembler-name for a local static variable named NAME.
   LABELNO is an integer which is different for each call.  */

#define ASM_FORMAT_PRIVATE_NAME(OUTPUT, NAME, LABELNO)	\
( (OUTPUT) = (char *) alloca (strlen ((NAME)) + 10),	\
  sprintf ((OUTPUT), "%s.%d", (NAME), (LABELNO)))

/* Define the parentheses used to group arithmetic operations
   in assembler code.  */

#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"

/* Define results of standard character escape sequences.  */
#define TARGET_BELL 007
#define TARGET_BS 010
#define TARGET_TAB 011
#define TARGET_NEWLINE 012
#define TARGET_VT 013
#define TARGET_FF 014
#define TARGET_CR 015


/* This is how to output an assembler line defining a string constant.  */

#define ASM_OUTPUT_ASCII(FILE, PTR, LEN)            \
  do {                                              \
    int i;                                          \
    for (i = 0; i < LEN; i++) {                     \
      if ((i % 8) == 0) {                           \
        if (i != 0)                                 \
          fprintf(FILE,"\n");                       \
        fprintf(FILE,"\t.word    ");                \
      }                                             \
      else                                          \
        fprintf(FILE,",");                          \
      if (PTR[i] >= 32 && PTR[i] < 127)             \
        fprintf(FILE,"'%c'",PTR[i]);                \
      else if (PTR[i] == 10)                        \
        fprintf(FILE,"'\\n'");                      \
      else                                          \
        fprintf(FILE,"%d",PTR[i]);                  \
    }                                               \
    fprintf(FILE,"\n");                             \
  } while (0)


/* Output a float value (represented as a C double) as an immediate operand.
   This macro is a 1750-specific macro.  */

#define ASM_OUTPUT_FLOAT_OPERAND(CODE,FILE,VALUE)		\
 do {								\
      if (CODE == 'f')						\
        {							\
          char dstr[30];					\
          REAL_VALUE_TO_DECIMAL (VALUE, "%.9g", dstr);		\
          asm_fprintf ((FILE), "%I0r%s", dstr);			\
        }							\
      else							\
        {							\
          long l;						\
          REAL_VALUE_TO_TARGET_SINGLE (VALUE, l);		\
          if (sizeof (int) == sizeof (long))			\
            asm_fprintf ((FILE), "%I0x%x", l);			\
          else							\
            asm_fprintf ((FILE), "%I0x%lx", l);			\
        }							\
     } while (0)


/* Output a double value (represented as a C double) as an immediate operand.
   This macro is a 1750-specific macro.  */
#define ASM_OUTPUT_DOUBLE_OPERAND(FILE,VALUE)				\
 do { char dstr[30];							\
      REAL_VALUE_TO_DECIMAL (VALUE, "%.15g", dstr);			\
      asm_fprintf (FILE, "%I0r%s", dstr);				\
    } while (0)

/* Note, long double immediate operands are not actually
   generated by m1750.md.  */
#define ASM_OUTPUT_LONG_DOUBLE_OPERAND(FILE,VALUE)			\
 do { char dstr[30];							\
      REAL_VALUE_TO_DECIMAL (VALUE, "%.15g", dstr);			\
      asm_fprintf (FILE, "%I0r%s", dstr);				\
    } while (0)

/* Print operand X (an rtx) in assembler syntax to file FILE.
   CODE is a letter or dot (`z' in `%z0') or 0 if no letter was specified.
   For `%' followed by punctuation, CODE is the punctuation and X is null.

   On the 1750, we use several CODE characters:
   '#' for an immediate operand prefix */


#define INT_ASM_OP ".word"

/* A C statement (sans semicolon) to output an element in the table of
   global constructors.  */
#define ASM_OUTPUT_CONSTRUCTOR(FILE,NAME)                               \
  do {                                                                  \
    ctors_section ();                                                   \
    fprintf (FILE, "\t%s  ", INT_ASM_OP);                              \
    assemble_name (FILE, NAME);                                         \
    fprintf (FILE, "\n");                                               \
  } while (0)

/* A C statement (sans semicolon) to output an element in the table of
   global destructors.  */
#define ASM_OUTPUT_DESTRUCTOR(FILE,NAME)                                \
  do {                                                                  \
    dtors_section ();                                                   \
    fprintf (FILE, "\t%s  ", INT_ASM_OP);                              \
    assemble_name (FILE, NAME);                                         \
    fprintf (FILE, "\n");                                               \
  } while (0)

#define PRINT_OPERAND_PUNCT_VALID_P(CODE)				\
  ((CODE) == '#')

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

   See m1750.c for the m1750 specific codes.  */

#define PRINT_OPERAND(FILE, X, CODE) print_operand (FILE, X, CODE)

/* A C compound statement to output to stdio stream STREAM the
   assembler syntax for an instruction operand that is a memory
   reference whose address is ADDR.  ADDR is an RTL expression.

   On some machines, the syntax for a symbolic address depends on
   the section that the address refers to.  On these machines,
   define the macro `ENCODE_SECTION_INFO' to store the information
   into the `symbol_ref', and then check for it here.  */

#define PRINT_OPERAND_ADDRESS(FILE, ADDR) print_operand_address (FILE, ADDR)


/* debugger stuff */
#define DEBUGGER_AUTO_OFFSET(X) \
  (GET_CODE (X) == PLUS ? INTVAL (XEXP (X, 1)) << 1 : 0)

#define DEBUGGER_ARG_OFFSET(OFFSET, X) \
  m1750_debugger_arg_offset(X, OFFSET)

/* END OF m1750-coff.h */

