/* Target dependent code for the MIL-STD-1750.
   Copyright (C) 1990, 1992 Free Software Foundation, Inc.

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

#include <math.h>

#include "defs.h"
#include "frame.h"
#include "symtab.h"
#include "gdbtypes.h"
#include "inferior.h"
#include "remote-utils.h"


/* Check if stopped by a watchpoint.  */

CORE_ADDR
m1750_stopped_by_watchpoint (struct target_waitstatus w)
{
  if (w.kind == TARGET_WAITKIND_STOPPED
      && w.value.sig == TARGET_SIGNAL_TRAP)
    {
      int hit1, hit2;

      hit1 = (read_register (WATCH1_REGNUM) >> 28) & 0x3;
      hit2 = (read_register (WATCH2_REGNUM) >> 28) & 0x3;

      return hit1 || hit2;
    }

  return 0;
}


CORE_ADDR
m1750_stopped_data_address ()
{
  CORE_ADDR addr1, addr2;
  int hit1, hit2;

  hit1 = (read_register (WATCH1_REGNUM) >> 28) & 0x3;
  hit2 = (read_register (WATCH2_REGNUM) >> 28) & 0x3;
  addr1 = ADDR_BITS_REMOVE (read_register (WATCH1_REGNUM));
  addr2 = ADDR_BITS_REMOVE (read_register (WATCH2_REGNUM));

  if (hit1)
    return addr1;
  else if (hit2)
    return addr2;
  else
    return 0;
}


int
m1750_check_watch_resources (type, cnt, ot)
     int type;
     int cnt;
     int ot;
{
  if (type == bp_hardware_breakpoint)
    {
      if (TARGET_HW_BREAK_LIMIT == 0)
	return 0;
      else if (cnt <= TARGET_HW_BREAK_LIMIT)
	return 1;
    }
  else
    {
      if (TARGET_HW_WATCH_LIMIT == 0)
	return 0;
//      else if (ot)
      //      return -1;
      else if (cnt <= TARGET_HW_WATCH_LIMIT)
	return 1;
    }
  return -1;
}


int
m1750_insert_watchpoint (addr, len, type)
     CORE_ADDR addr;
     int len;
     int type;
{
  int mode;
  int mode1, mode2;

  /* get current modes */
  mode1 = (read_register (WATCH1_REGNUM) >> 30) & 0x3;
  mode2 = (read_register (WATCH2_REGNUM) >> 30) & 0x3;

  /* map type to mode */
  if (type == 1)
    {
      /* read watch */
      mode = 1;
    }
  else if (type == 0)
    {
      /* write watch */
      mode = 2;
    }
  else
    {
      /* read/write watch */
      mode = 3;
    }

  /* select watch 1 or 2 */
  if (!mode1)
    write_register (WATCH1_REGNUM,
		  ((mode << 30) & 0xc0000000) | ((addr >> 1) & 0x00ffffff));
  else if (!mode2)
    write_register (WATCH2_REGNUM,
		  ((mode << 30) & 0xc0000000) | ((addr >> 1) & 0x00ffffff));
  else
    return -1;

  return 0;
}


int
m1750_remove_watchpoint (addr, len, type)
     CORE_ADDR addr;
     int len;
     int type;
{
  CORE_ADDR addr1, addr2;
  int mode1, mode2;

  mode1 = (read_register (WATCH1_REGNUM) >> 30) & 0x3;
  mode2 = (read_register (WATCH2_REGNUM) >> 30) & 0x3;
  addr1 = ADDR_BITS_REMOVE (read_register (WATCH1_REGNUM));
  addr2 = ADDR_BITS_REMOVE (read_register (WATCH2_REGNUM));

  if (mode1 && (addr == addr1))
    write_register (WATCH1_REGNUM, 0x00000000);
  else if (mode2 && (addr == addr2))
    write_register (WATCH2_REGNUM, 0x00000000);
  else
    return -1;

  return 0;
}


/* 
 * Given a 1750 16-bit word address and the relevant status word, return the
 * gdb CORE_ADDR.
 */
CORE_ADDR
m1750_extend_address (unsigned sw, unsigned waddr)
{
  unsigned pb = (sw >> 8) & 0xf;	/* page bank number (4 bits) */
  unsigned as = (sw) & 0xf;	/* address state (4 bits) */

  /* FIXME: we assume a flat address space, and no special mapping */
  return ((waddr << 1) & 0x1fffe) | (pb << 21) | (as << 17);
}



/* Push an empty stack frame, to record the current PC, etc.  */

void
m1750_push_dummy_frame ()
{
  register CORE_ADDR sp = read_sp ();

  sp = push_word (sp, read_register (PC_REGNUM));
  sp = push_word (sp, read_fp ());
  write_register (FP_REGNUM, sp);

}

/* Discard from the stack the innermost frame,
   restoring all saved registers.  */

void
m1750_pop_frame ()
{
  register struct frame_info *frame = get_current_frame ();
  struct frame_saved_regs fsr;
  CORE_ADDR fp;
  CORE_ADDR pc;
  unsigned sw = read_register (20);

  get_frame_saved_regs (frame, &fsr);

  fp = read_memory_integer (fsr.regs[FP_REGNUM], 2);
  pc = read_memory_integer (fsr.regs[PC_REGNUM], 2);

  if (frame->has_frame)
    write_register (FP_REGNUM, fp);
  write_register (PC_REGNUM, pc);
  write_register (SP_REGNUM, fsr.regs[SP_REGNUM] >> 1);

  flush_cached_frames ();
}


/* Given an ip value corresponding to the start of a function,
   return the ip of the first instruction after the function 
   prologue. 

   Some instructions which typically may appear in a function
   prologue include:

   9FEE         pshm   r14,r14
   81EF         lr     r14,r15

   B2F0         sisp   r15,1
   9FEE         pshm   r14,r14
   81EF         lr     r14,r15

   4AF2 0065    sim    r15,101
   9FEE         pshm   r14,r14
   81EF         lr     r14,r15

 */

CORE_ADDR
m1750_skip_prologue (ip)
     CORE_ADDR ip;
{
  int op;

  op = read_memory_integer (ip, 2);
  op &= 0xFFFF;

  if ((op & 0xfff0) == 0xb2f0)
    {
      ip += 2;			/* Skip sisp r15,xx */
      op = read_memory_integer (ip, 2);
      op &= 0xFFFF;
    }
  else if (op == 0x4af2)
    {
      ip += 4;			/* Skip sim r15,xx */
      op = read_memory_integer (ip, 2);
      op &= 0xFFFF;
    }

  if (op == 0x9fee)
    {
      ip += 2;			/* Skip pshm r14,r14 */
      op = read_memory_integer (ip, 2);
      op &= 0xFFFF;
      if (op == 0x81ef)
	{
	  ip += 2;		/* Skip lr r14,r15 */
	}

    }
  return (ip);
}


CORE_ADDR
m1750_args_address (fi)
     struct frame_info *fi;
{
  m1750_validate_frame_size (fi);

  if (fi->has_frame)
    return fi->frame;
  else
    return read_sp ();
}


/*
 * Determine the size of the given frame by inspecting the prolog
 * code generated to set up the frame. If no prolog code is found
 * then assume the function does not have a stack frame.
 */
int
m1750_validate_frame_size (fi)
     struct frame_info *fi;
{
  int op;
  int frame_size;
  int has_frame = 0;
  CORE_ADDR ip;

  if (fi->frame_size_valid)
    return;

  ip = (get_pc_function_start (fi->pc) + FUNCTION_START_OFFSET);

  /* get frame size by decoding function prolog (if any) */
  op = read_memory_integer (ip, 2);
  op &= 0xFFFF;

  if ((op & 0xfff0) == 0xb2f0)
    {
      /* SISP r15,xx */
      frame_size = ((op & 0x000f) + 1) << 1;
      ip += 2;
      op = read_memory_integer (ip, 2);
      op &= 0xFFFF;
    }
  else if (op == 0x4af2)
    {
      /* SIM r15,xx */
      ip += 2;
      op = read_memory_integer (ip, 2);
      frame_size = (op &= 0xFFFF) << 1;
      ip += 2;
      op = read_memory_integer (ip, 2);
      op &= 0xFFFF;
    }
  else
    {
      frame_size = 0;
    }

  /* confirm that the function has a frame */
  if (op == 0x9fee)
    {
      /* pshm r14,r14 */
      ip += 2;
      op = read_memory_integer (ip, 2);
      op &= 0xFFFF;
      if (op == 0x81ef)
	{
	  /* lr r14,r15 */
	  ip += 2;
	  has_frame = 1;
	}
    }

  fi->frame_size_valid = 1;
  fi->has_frame = has_frame;
  fi->frame_size = frame_size;
}


/* Put here the code to store, into a struct frame_saved_regs,
   the addresses of the saved registers of frame described by FRAME_INFO.
   This includes special registers such as pc and fp saved in special
   ways in the stack frame.  sp is even more special:
   the address we return for it IS the sp for the next frame.
 */

void
m1750_find_saved_regs (frame_info, saved_regs)
     struct frame_info *frame_info;
     struct frame_saved_regs *saved_regs;
{
  m1750_validate_frame_size (frame_info);

  /* FIXME: get the values of the other registers */
  memset (saved_regs, 0, sizeof (*saved_regs));

  /* FIXME: link is 3 words for expanded memory */
  if ((frame_info)->has_frame)
    {
      saved_regs->regs[SP_REGNUM] = (frame_info)->frame + (frame_info)->frame_size + 4;
      saved_regs->regs[FP_REGNUM] = (frame_info)->frame;
      saved_regs->regs[PC_REGNUM] = (frame_info)->frame + (frame_info)->frame_size + 2;
    }
  else
    {
      saved_regs->regs[SP_REGNUM] = (frame_info)->frame;
      saved_regs->regs[FP_REGNUM] = (frame_info)->frame;
      saved_regs->regs[PC_REGNUM] = (frame_info)->frame - 2;
    }
}


#ifdef GET_LONGJMP_TARGET
/* On the 1750, jmpbuf is defined as follows:
   typedef struct
   {
   short im, sw, ic;  
   short r14, r15;
   } jmp_buf [1];

   On entry to the function longjmp, register R0 contains the address of 
   the jmp_buf.  This routine returns true on success. */

int
get_longjmp_target (pc)
     CORE_ADDR *pc;
{
  char buf[10];
  CORE_ADDR jb_addr;

  jb_addr = m1750_extend_address (read_register (20), read_register (0));

  /* Get entire jmp_buf */
  if (target_read_memory (jb_addr, buf, 10))
    return 0;

  /* extract sw and ic */
  *pc = m1750_extend_address (
			       extract_unsigned_integer (buf + 2, 2),
			       extract_unsigned_integer (buf + 4, 2));

  return 1;
}
#endif /* GET_LONGJMP_TARGET */


/* Immediately after a function call, return the saved pc before the frame
   is setup. */

CORE_ADDR
m1750_saved_pc_after_call (frame)
     struct frame_info *frame;
{
  unsigned sw = read_register (20);

  /* FIXME: uses wrong sw, but how can we tell if the caller made a long call? */

  return m1750_extend_address (sw, read_memory_integer (read_sp (), 2));
}

void
m1750_do_registers_info (regnum, fpregs)
     int regnum;
     int fpregs;
{
  register int i;
  int numregs = ARCH_NUM_REGS;

  for (i = 0; i < numregs; i++)
    {
      char raw_buffer[MAX_REGISTER_RAW_SIZE];
      char virtual_buffer[MAX_REGISTER_VIRTUAL_SIZE];
      unsigned val;

      /* Decide between printing all regs, nonfloat regs, or specific reg.  */
      if (regnum != -1)
	{
	  if (i != regnum)
	    continue;
	}

      if (i >= 28)
	continue;

      fputs_filtered (reg_names[i], gdb_stdout);
      print_spaces_filtered (15 - strlen (reg_names[i]), gdb_stdout);

      /* Get the data in raw format.  */
      if (read_relative_register_raw_bytes (i, raw_buffer))
	{
	  printf_filtered ("Invalid register contents\n");
	  continue;
	}

      if (i <= 24)
	{
	  val = ((raw_buffer[0] << 8) & 0x0000ff00) + (raw_buffer[1] & 0x000000ff);
	  printf_filtered ("0x%04x\t", val);
	}
      else
	{
	  val = ((raw_buffer[0] << 24) & 0xff000000) + ((raw_buffer[1] << 16) & 0x00ff0000)
	    + ((raw_buffer[2] << 8) & 0x0000ff00) + (raw_buffer[3] & 0x000000ff);
	  printf_filtered ("0x%08x\t", val);
	}

      switch (i)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	  /* data registers, print as a signed int in decimal */
	  printf_filtered ("%d", val);
	  break;
	case 12:
	case 13:
	case 14:
	case 15:
	  /* base registers, print as a hex byte address */
	  printf_filtered ("byte addr: %05x", (val & 0xffff) << 1);
	  break;
	case 16:
	case 17:
	case 18:
	  /* PIR, MK and FT print as 16 bits */
	  {
	    int i;
	    for (i = 0; i <= 15; i++)
	      {
		printf_filtered ("%d", (val >> (15 - i)) & 0x0001);
		if (i % 4 == 3 && i < 15)
		  printf_filtered ("_");
	      }
	  }
	  break;
	case 19:
	  /* program counter, print as a hex byte address */
	  printf_filtered ("byte addr: %05x", (val & 0xffff) << 1);
	  break;
	case 20:
	  /* status register, print names of bits */
	  printf_filtered ("CS=[");
	  if (val & 0x8000)
	    printf_filtered ("C");
	  if (val & 0x4000)
	    printf_filtered ("P");
	  if (val & 0x2000)
	    printf_filtered ("Z");
	  if (val & 0x1000)
	    printf_filtered ("N");
	  printf_filtered ("], PB=%d, PS=%d, AS=%d",
			   (val >> 8) & 0xf, (val >> 4) & 0xf, val & 0xf);
	  break;
	case 21:
	case 22:
	case 23:
	  /* Timers A, B and GO, print in unsigned decimal */
	  printf_filtered ("%uU", val & 0xffff);
	  break;
	case 24:
	  /* sys register, print in hex */
	  printf_filtered ("0x%04x", val & 0xffff);
	  break;
	case 25:
	  /* simulator statistics register, cycles */
	  printf_filtered ("%u cycles", val);
	  break;
	case 26:
	  /* simulator statistics register, insts */
	  printf_filtered ("%u instructions", val);
	  break;
	case 27:
	  /* simulator statistics register, time */
	  printf_filtered ("%u 1/60 secs", val);
	  break;
	default:
	  break;
	}

      printf_filtered ("\n");
    }
}


#define pow2(exp)  pow(2.0,(double)exp)

#define FLOATING_TWO_TO_THE_FIFTEEN            32768.0
#define FLOATING_TWO_TO_THE_TWENTYTHREE      8388608.0
#define FLOATING_TWO_TO_THE_THIRTYONE     2147483648.0
#define FLOATING_TWO_TO_THE_THIRTYNINE  549755813888.0


DOUBLEST
m1750_extract_floating (addr, len)
     PTR addr;
     int len;
{
  unsigned char *input = (unsigned char *) addr;
  double ans;

  if (len == 4)
    {
      signed char int_exp = (signed char) (input[3]);
      long int_mant = (long) ((input[0] << 24) | (input[1] << 16) | (input[2] << 8));

      double flt_mant = (double) int_mant / FLOATING_TWO_TO_THE_THIRTYONE;

      ans = ldexp (flt_mant, int_exp);

      if (sr_get_debug ())
	printf_filtered ("m1750_extract_floating: %02x %02x %02x %02x, mant=%08x, exp=%d, ans=%e\n",
	    input[0], input[1], input[2], input[3], int_mant, int_exp, ans);

    }
  else if (len == 6)
    {
      signed char int_exp = (signed char) (input[3]);
      long int_mant_hi = (long) ((input[0] << 24) | (input[1] << 16) | (input[2] << 8));
      long int_mant_lo = (long) ((input[4] << 8) | (input[5]));
      double flt_mant;

      if (int_mant_hi < 0)
        int_mant_lo = - int_mant_lo;

      flt_mant = (double) int_mant_hi / FLOATING_TWO_TO_THE_THIRTYONE
      + (double) int_mant_lo / FLOATING_TWO_TO_THE_THIRTYNINE;

      ans = ldexp (flt_mant, int_exp);

      if (sr_get_debug ())
	printf_filtered ("m1750_extract_floating: %02x %02x %02x %02x %02x %02x, mant=%08x %08x, exp=%d, ans=%e\n",
			 input[0], input[1], input[2], input[3], input[4], input[5], int_mant_hi, int_mant_lo, int_exp, ans);

    }
  else
    {
      error ("Can't deal with a floating point number of %d bytes.", len);
      ans = 0.0;
    }

  return (DOUBLEST) ans;
}

/*
 * Convert a host double or long double to 1750 float or extended precision. Assuming
 * the host supports IEEE floating, and host double has 15 digits of precision
 * then there is sufficient host precision and range to express any target floating
 * point number.
 */
void
m1750_store_floating (addr, len, val)
     PTR addr;
     int len;
     DOUBLEST val;
{
  unsigned char *output = (unsigned char *) addr;
  int exp;
  double flt_mant = frexp ((double) val, &exp);

  int word1, word2, word3;

  if (exp > 127)
    {
      error ("Floating point number too big, exp = %d.", exp);

      if (val < 0)
	{
	  word1 = 0x8000;
	  word2 = 0x007f;
	  word3 = 0x0000;
	}
      else
	{
	  word1 = 0x7fff;
	  word2 = 0xff7f;
	  word3 = 0xffff;
	}
    }
  else if (exp < -128)
    {
      error ("Floating point number too small, exp = %d.", exp);

      if (val < 0)
	{
	  word1 = 0x8000;
	  word2 = 0x0080;
	  word3 = 0x0000;
	}
      else
	{
	  word1 = 0x7fff;
	  word2 = 0xff80;
	  word3 = 0xffff;
	}
    }
  else
    {
      long ms_mant;
      long ls_mant;

      ms_mant = (long) (flt_mant * FLOATING_TWO_TO_THE_THIRTYONE);
      flt_mant -= (double) ms_mant / FLOATING_TWO_TO_THE_THIRTYONE;
      ls_mant = (long) (flt_mant * FLOATING_TWO_TO_THE_THIRTYNINE);

      word1 = ms_mant >> 16;
      word2 = (ms_mant & 0x0000ff00) | (exp & 0xff);
      word3 = ((ms_mant << 8) & 0xff00) | ((ls_mant >> 24) & 0xff);
    }

  output[0] = word1 >> 8;
  output[1] = word1 & 0xff;
  output[2] = word2 >> 8;
  output[3] = word2 & 0xff;

  if (len == 6)
    {
      output[4] = word3 >> 8;
      output[5] = word3 & 0xff;
    }

}


/* Given a stack frame, get the program counter returned to when
   the function returns.
 */

CORE_ADDR
m1750_frame_saved_pc (struct frame_info *fi)
{
  CORE_ADDR pc_addr;		/* address where the PC is saved */

  m1750_validate_frame_size (fi);

  pc_addr = fi->frame + fi->frame_size + 2;
  return ADDR_BITS_REMOVE (read_memory_integer (pc_addr, 2));
}


void
_initialize_m1750_tdep ()
{
  tm_print_insn = print_insn_m1750;
}
