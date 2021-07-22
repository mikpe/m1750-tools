/* Parameters for execution on a MIL-STD-1750.
   Copyright 1986, 1987, 1989, 1990, 1992 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* Generic 1750 stuff, to be included by other tm-*.h files.  */

/* #define IEEE_FLOAT 1 */

/* Define the bit, byte, and word ordering of the machine.  */
#define TARGET_BYTE_ORDER BIG_ENDIAN

/* Offset from address of function to start of its code.
   Zero on most machines.  */

#define FUNCTION_START_OFFSET 0

/* Advance PC across any function entry prologue instructions
   to reach some "real" code.  */

#if !defined(SKIP_PROLOGUE)
#define SKIP_PROLOGUE(ip)   {(ip) = m1750_skip_prologue(ip);}
extern CORE_ADDR m1750_skip_prologue PARAMS ((CORE_ADDR ip));
#endif

/* Figure out where the longjmp will land.  The pc is copied into ADDR.
   This routine returns true on success */

#define GET_LONGJMP_TARGET(ADDR) get_longjmp_target(ADDR)


/* Immediately after a function call, return the saved pc.
   Can't always go through the frames for this because on some machines
   the new frame is not set up until the new function executes
   some instructions.  */

#ifdef __STDC__
struct frame_info;
#endif

extern CORE_ADDR m1750_saved_pc_after_call PARAMS ((struct frame_info *));

#define SAVED_PC_AFTER_CALL(frame) \
  m1750_saved_pc_after_call(frame)

/* Stack grows downward.  */

#define INNER_THAN <

/* Sequence of bytes for breakpoint instruction. */
#define BREAKPOINT {0xff, 0xff}

/* We default to vector 1 for the "remote" target, but allow targets
   to override.  */
#define REMOTE_BREAKPOINT {0xff, 0xff}

/* If your kernel resets the pc after the trap happens you may need to
   define this before including this file.  */

#if !defined (DECR_PC_AFTER_BREAK)
#define DECR_PC_AFTER_BREAK 0
#endif

/* Nonzero if instruction at PC is a return instruction.  */
/* Allow any of the return instructions, including a trapv and a return
   from interupt.  */

/* This is the URS instruction */
#define ABOUT_TO_RETURN(pc) (read_memory_integer (pc, 2) == 0x7ff0)

/* Say how long (ordinary) registers are.  This is a piece of bogosity
   used in push_word and a few other places; REGISTER_RAW_SIZE is the
   real way to know how big a register is.  */

#define REGISTER_SIZE 2

#define REGISTER_BYTES_FP (0)
#define REGISTER_BYTES_NOFP (30*4+6*4)

#ifndef NUM_REGS
#define NUM_REGS 30
#endif

#ifndef REGISTER_BYTES_OK
#define REGISTER_BYTES_OK(b) \
   ((b) == REGISTER_BYTES_FP \
    || (b) == REGISTER_BYTES_NOFP)
#endif

#ifndef REGISTER_BYTES
#define REGISTER_BYTES (24*2+6*4)
#endif

/* Index within `registers' of the first byte of the space for
   register N.  */

#define REGISTER_BYTE(N)  (N <= 24? N * 2: 48 + ((N - 24) * 4))

/* Number of bytes of storage in the actual machine representation
   for register N.  On the 1750, all regs are 2 bytes.  The simulators
   statistics registers are 32 bits wide. */

#define REGISTER_RAW_SIZE(N) (N <= 24? 2: 4)

/* Number of bytes of storage in the program's representation
   for register N.  On the 1750, all regs are 2 bytes.  */

#define REGISTER_VIRTUAL_SIZE(N) (N <= 24? 2: 4)

/* Largest value REGISTER_RAW_SIZE can have.  */

#define MAX_REGISTER_RAW_SIZE 4

/* Largest value REGISTER_VIRTUAL_SIZE can have.  */

#define MAX_REGISTER_VIRTUAL_SIZE 4

/* Nonzero if register N requires conversion
   from raw format to virtual format.  */
/* For the 1750 we do not convert the general-purpose registers r0 to r11,
   but we do convert the base registers and some of the 1750's private registers */
#define REGISTER_CONVERTIBLE(N) (0)

/* Convert data from raw format for register REGNUM in buffer FROM
   to virtual format with type TYPE in buffer TO.  */

#define REGISTER_CONVERT_TO_VIRTUAL(REGNUM,TYPE,FROM,TO) \
{ \
}

/* Convert data from virtual format with type TYPE in buffer FROM
   to raw format for register REGNUM in buffer TO.  */

#define REGISTER_CONVERT_TO_RAW(TYPE,REGNUM,FROM,TO)	\
{ \
}

/* Return the GDB type object for the "standard" data type
   of data in register N.  */
/* Note, for registers which contain addresses return
   pointer to void, not pointer to char, because we don't
   want to attempt to print the string after printing the address.  */
#define REGISTER_VIRTUAL_TYPE(N) \
  ((N) == PC_REGNUM || (N) == FP_REGNUM || (N) == SP_REGNUM ?         \
  lookup_pointer_type (builtin_type_void) : \
  (N <= 24? builtin_type_int: builtin_type_unsigned_long))

/* Initializer for an array of names of registers.
   Entries beyond the first NUM_REGS are ignored.  */

#define REGISTER_NAMES  {\
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", \
  "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", \
  "pir", "mk", "ft", "ic", "sw", "ta", "tb", "go", "sys", \
  "cycles", "insts", "time", "", ""};

/* Register numbers of various important registers.
   Note that some of these values are "real" register numbers,
   and correspond to the general registers of the machine,
   and some are "phony" register numbers which are too large
   to be actual register numbers as far as the user is concerned
   but do serve to get the desired values when passed to read_register.  */

#define FP0_REGNUM 0
#define A1_REGNUM 1  
#define FP_REGNUM 14		/* Contains address of executing stack frame */
#define SP_REGNUM 15		/* Contains address of top of stack */
#define PS_REGNUM 20		/* Contains processor status */
#define PC_REGNUM 19		/* Contains program counter */
#define WATCH1_REGNUM 28
#define WATCH2_REGNUM 29


#define DO_REGISTERS_INFO(regnum, fp) m1750_do_registers_info(regnum, fp)

/* Store the address of the place in which to copy the structure the
   subroutine will return.  This is called from call_function. */

#define STORE_STRUCT_RETURN(ADDR, SP) \
  { write_register (A1_REGNUM, (ADDR)); }

/* Extract from an array REGBUF containing the (raw) register state
   a function return value of type TYPE, and copy that, in virtual format,
   into VALBUF.  This is assuming that floating point values are returned
   as doubles in d0/d1.  */

#if !defined (EXTRACT_RETURN_VALUE)
#define EXTRACT_RETURN_VALUE(TYPE,REGBUF,VALBUF) \
  memcpy ((VALBUF),							\
	  (char *)(REGBUF) +						\
	         (TYPE_LENGTH(TYPE) >= 4 ? 0 : 4 - TYPE_LENGTH(TYPE)),	\
	  TYPE_LENGTH(TYPE))
#endif

/* Write into appropriate registers a function return value
   of type TYPE, given in virtual format.  Assumes floats are passed
   in d0/d1.  */

#if !defined (STORE_RETURN_VALUE)
#define STORE_RETURN_VALUE(TYPE,VALBUF) \
  write_register_bytes (0, VALBUF, TYPE_LENGTH (TYPE))
#endif

/* Extract from an array REGBUF containing the (raw) register state
   the address in which a function should return its structure value,
   as a CORE_ADDR (or an expression that can be used as one).  */

#define EXTRACT_STRUCT_VALUE_ADDRESS(REGBUF) (*(CORE_ADDR *)(REGBUF))

/* Describe the pointer in each stack frame to the previous stack frame
   (its caller).  */

/* FRAME_CHAIN takes a frame's nominal address and produces the frame's
   chain-pointer.
   In the case of the 1750, the frame's nominal address
   is the address of a 2-byte word containing the calling frame's address.  */
#define FRAME_CHAIN(thisframe) \
     (ADDR_BITS_REMOVE (read_memory_integer ((thisframe)->frame, 2)))

#define EXTRA_FRAME_INFO  \
    int has_frame; \
    int frame_size_valid; \
    unsigned frame_size; 

/* Zero the frame_saved_regs pointer when the frame is initialized,
   so that FRAME_FIND_SAVED_REGS () will know to allocate and
   initialize a frame_saved_regs struct the first time it is called.
   indicate real, cached values.  */

#define INIT_EXTRA_FRAME_INFO(fromleaf, fi) \
        ((fi)->has_frame = 0, (fi)->frame_size_valid = 0, (fi)->frame_size = 0)

/* Define other aspects of the stack frame.  */

/* A macro that tells us whether the function invocation represented
   by FI does not have a frame on the stack associated with it.  If it
   does not, FRAMELESS is set to 1, else 0.  */
#define FRAMELESS_FUNCTION_INVOCATION(FI, FRAMELESS) \
  do { \
      (FRAMELESS) = frameless_look_for_prologue(FI); \
  } while (0)

#define FRAME_SAVED_PC(FRAME) m1750_frame_saved_pc(FRAME)

#define FRAME_ARGS_ADDRESS(fi) (m1750_args_address (fi))

#define FRAME_LOCALS_ADDRESS(fi) ((fi)->frame)

/* Set VAL to the number of args passed to frame described by FI.
   Can set VAL to -1, meaning no way to tell.  */

/* We can't tell how many args there are
   now that the C compiler delays popping them.  */
#if !defined (FRAME_NUM_ARGS)
#define FRAME_NUM_ARGS(val,fi) (val = -1)
#endif

/* Return number of bytes at start of arglist that are not really args.  */

#define FRAME_ARGS_SKIP 0

/* Put here the code to store, into a struct frame_saved_regs,
   the addresses of the saved registers of frame described by FRAME_INFO.
   This includes special registers such as pc and fp saved in special
   ways in the stack frame.  sp is even more special:
   the address we return for it IS the sp for the next frame.  */

#if !defined (FRAME_FIND_SAVED_REGS)
#define FRAME_FIND_SAVED_REGS(fi,fsr) m1750_find_saved_regs ((fi), &(fsr))
#endif /* no FIND_FRAME_SAVED_REGS.  */


/* Things needed for making the inferior call functions.  */

/* FIXME: implement CALL_DUMMY */

#define CALL_DUMMY_TMP {0xf227e0ff, 0x48e7fffc, 0x426742e7, 0x4eb93232, 0x3232dffc, 0x69696969, (0x4e404e71 | (16))}
#define CALL_DUMMY_LENGTH 28		/* Size of CALL_DUMMY */
#define CALL_DUMMY_START_OFFSET 12	/* Offset to jsr instruction*/
#define CALL_DUMMY_BREAKPOINT_OFFSET (CALL_DUMMY_START_OFFSET + 12)

/* Insert the specified number of args and function address
   into a call sequence of the above form stored at DUMMYNAME.
   We use the BFD routines to store a big-endian value of known size.  */

#define FIX_CALL_DUMMY(dummyname, pc, fun, nargs, args, type, gcc_p)     \
{ bfd_putb32 (fun,     (unsigned char *) dummyname + CALL_DUMMY_START_OFFSET + 2);  \
  bfd_putb32 (nargs*4, (unsigned char *) dummyname + CALL_DUMMY_START_OFFSET + 8); }

/* Push an empty stack frame, to record the current PC, etc.  */

#define PUSH_DUMMY_FRAME	{ m1750_push_dummy_frame (); }

extern void m1750_push_dummy_frame PARAMS ((void));

extern void m1750_pop_frame PARAMS ((void));

/* Discard from the stack the innermost frame, restoring all registers.  */

#define POP_FRAME		{ m1750_pop_frame (); }

/* Offset from SP to first arg on stack at first instruction of a function */

#define SP_ARG0 (1 * 2)


#define TARGET_WRITE_PC(val,inferior_pid) write_register_pid (PC_REGNUM, val >> 1, inferior_pid)

#define TARGET_READ_SP() (ADDR_BITS_REMOVE (read_register (SP_REGNUM)))
#define TARGET_WRITE_SP(val) write_register (SP_REGNUM, val >> 1)

#define TARGET_READ_FP() (ADDR_BITS_REMOVE (read_register (FP_REGNUM)))
#define TARGET_WRITE_FP(val) write_register (FP_REGNUM, val >> 1)

#define ADDR_BITS_REMOVE(addr) ((addr << 1) & 0x1fffe)


/* Number of bits in a char or unsigned char for the target machine.
   Just like CHAR_BIT in <limits.h> but describes the target machine.  */

/* GCC-1750 has 16-bit character types in C. However setting TARGET_CHAR_BIT
   to anything but 8 requires big gdb changes. */
#define TARGET_CHAR_BIT 8

/* Number of bits in a short or unsigned short for the target machine. */
#define TARGET_SHORT_BIT (16)

/* Number of bits in an int or unsigned int for the target machine. */
#define TARGET_INT_BIT (16)

/* Number of bits in a long or unsigned long for the target machine. */
#define TARGET_LONG_BIT (32)

/* Number of bits in a long long or unsigned long long for the target machine. */
#define TARGET_LONG_LONG_BIT (2 * TARGET_LONG_BIT)

/* Number of bits in a float for the target machine. */
#define TARGET_FLOAT_BIT (32)

/* Number of bits in a double for the target machine. */
#define TARGET_DOUBLE_BIT (48)

/* Number of bits in a long double for the target machine.  */
#if !defined (TARGET_LONG_DOUBLE_BIT)
#define TARGET_LONG_DOUBLE_BIT (TARGET_DOUBLE_BIT)
#endif

/* Number of bits in a pointer for the target machine.  Although
   24 bit is probably enough, gdb expects a number from 8,16,32,64 */
#define TARGET_PTR_BIT 32

/* The bit byte-order has to do just with numbering of bits in
   debugging symbols and such.  Conceptually, it's quite separate
   from byte/word byte order.  */

#define BITS_BIG_ENDIAN 1


/* Hardware watchpoint stuff */

#define HAVE_NONSTEPPABLE_WATCHPOINT

#define TARGET_HW_BREAK_LIMIT 0
#define TARGET_HW_WATCH_LIMIT 2

#define TARGET_HAS_HARDWARE_WATCHPOINTS

#define TARGET_CAN_USE_HARDWARE_WATCHPOINT(type, cnt, ot) \
        m1750_check_watch_resources (type, cnt, ot)

/* When a hardware watchpoint fires off the PC will be left at the
   instruction which caused the watchpoint.  It will be necessary for
   GDB to step over the watchpoint. */

/* Use these macros for watchpoint insertion/deletion. */
#define target_insert_watchpoint(addr, len, type) \
    m1750_insert_watchpoint (addr, len, type)
#define target_remove_watchpoint(addr, len, type) \
    m1750_remove_watchpoint (addr, len, type)

#define target_stopped_data_address() \
    m1750_stopped_data_address()

#define STOPPED_BY_WATCHPOINT(W)  \
  m1750_stopped_by_watchpoint (W)

