/*  This file is part of the program sim1750.

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include <signal.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

#include <ansidecl.h>
#include "../../gdb/remote-sim.h"
#include "../../gdb/callback.h"
#include "../../gdb/defs.h"

#include "arch.h"
#include "cpu.h"
#include "phys_mem.h"
#include "status.h"


void
sim_open (char *args)
{
  int argc = 0;
  char **argv = NULL;

  sim_main (argc, argv);
  verbose = FALSE;
}


void
sim_close (int quitting)
{
}


int
sim_load (prog, from_tty)
     char *prog;
     int from_tty;
{
  /* Return non-zero so gdb will handle it.  */
  return 1;
}



void
sim_kill (void)
{
}


/*
 * Transfer 8-bit bytes from the simulated 1750 memory to
 * the debugger's memory. Return the number of 8-bit
 * bytes transfered.
 */
int
sim_read (SIM_ADDR addr, unsigned char *buf, int length)
{
  int cnt = 0;

  while (length > 0)
    {
      unsigned byte_no = addr & 0x00000001;
      unsigned page = (addr >> 13) & 0x00000fff;
      unsigned offset = (addr >> 1) & 0x00000fff;
      mem_t *memptr = mem[page];

      int was_written = 0;
      unsigned word = 0xdead;

      if (memptr != MNULL)
	{
	  was_written = memptr->was_written[offset / 32] & (1L << (offset % 32));

	  if (was_written)
	    word = memptr->word[offset];
	}

      if (byte_no == 0)
	{
	  *buf++ = (word >> 8);
	  addr++;
	  length--;
	  cnt++;
	}
      else
	{
	  *buf++ = (word & 0xff);
	  addr++;
	  length--;
	  cnt++;
	}
    }

  return cnt;
}


/*
 * Transfer 8-bit bytes from the simulated 1750 memory to
 * the debugger's memory. Return the number of 8-bit
 * bytes transfered.
 */
int
sim_write (SIM_ADDR addr, unsigned char *buf, int length)
{
  int cnt = 0;

  while (length > 0)
    {
      unsigned byte_no = addr & 0x00000001;
      unsigned page = (addr >> 13) & 0x00000fff;
      unsigned offset = (addr >> 1) & 0x00000fff;
      mem_t *memptr = mem[page];
      unsigned word;

      if (memptr == MNULL)
	{
	  if ((memptr = mem[page] = (mem_t *) xalloc (1, sizeof (mem_t))) == MNULL)
	    break;
	}
      word = memptr->word[offset];

      if (byte_no == 0)
	{
	  word = (word & 0x00ff) | (*buf++ << 8);
	  addr++;
	  length--;
	  cnt++;
	}
      else
	{
	  word = (word & 0xff00) | (*buf++ & 0xff);
	  addr++;
	  length--;
	  cnt++;
	}

      memptr->word[offset] = word;
      memptr->was_written[offset / 32] |= 1L << (offset % 32);
    }

  return cnt;
}


void
sim_fetch_register (int regno, unsigned char *buf)
{
  unsigned long value;

  switch (regno)
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
    case 12:
    case 13:
    case 14:
    case 15:
      value = simreg.r[regno] & 0xffff;
      break;

    case 16:
      value = simreg.pir & 0xffff;
      break;

    case 17:
      value = simreg.mk & 0xffff;
      break;

    case 18:
      value = simreg.ft & 0xffff;
      break;

    case 19:
      value = simreg.ic & 0xffff;
      break;

    case 20:
      value = simreg.sw & 0xffff;
      break;

    case 21:
      value = simreg.ta & 0xffff;
      break;

    case 22:
      value = simreg.tb & 0xffff;
      break;

    case 23:
      value = simreg.go & 0xffff;
      break;

    case 24:
      value = simreg.sys & 0xffff;
      break;

    case 25:
      value = total_cycles;
      break;

    case 26:
      value = instcnt;
      break;

    case 27:
      /* time in 1/60 secs */
      value = (unsigned) (total_time_in_us * 60.0 / 1.0e6);
      break;

    case 28:
      /* hardware watchpoint address */
      value = ((watch_mode1 << 30) & 0xc0000000) | 
              ((watch_addr1 & 0x00ffffff)) |
              ((watch_hit1 << 28) & 0x30000000);
      break;

    case 29:
      /* hardware watchpoint address */
      value = ((watch_mode2 << 30) & 0xc0000000) | 
              ((watch_addr2 & 0x00ffffff)) |
              ((watch_hit2 << 28) & 0x30000000);
      break;

    default:
      value = 0;
      break;
    }

  if (regno <= 24)
    {
      /* 16-bit register */
      buf[0] = (value >> 8) & 0xff;
      buf[1] = (value >> 0) & 0xff;
    }
  else
    {
      /* 32-bit register */
      buf[0] = (value >> 24) & 0xff;
      buf[1] = (value >> 16) & 0xff;
      buf[2] = (value >> 8) & 0xff;
      buf[3] = value & 0xff;
    }
}


void
sim_store_register (int regno, unsigned char *buf)
{
  unsigned value;

  if (regno <= 24)
    {
      /* 16-bit register */
      value = (buf[0] << 8) | buf[1];
    }
  else
    {
      /* 32-bit register */
       value = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    }

  switch (regno)
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
    case 12:
    case 13:
    case 14:
    case 15:
      simreg.r[regno] = value;
      break;

    case 16:
      simreg.pir = value;
      break;

    case 17:
      simreg.mk = value;
      break;

    case 18:
      simreg.ft = value;
      break;

    case 19:
      simreg.ic = value;
      break;

    case 20:
      simreg.sw = value;
      break;

    case 21:
      simreg.ta = value;
      break;

    case 22:
      simreg.tb = value;
      break;

    case 23:
      simreg.go = value;
      break;

    case 24:
      simreg.sys = value;
      break;

    case 25:
      total_cycles = value;
      break;

    case 26:
      instcnt = value;
      break;

    case 27:
      /* time in 1/60 secs */
      total_time_in_us  = (double)value * 1.0e6 / 60.0;
      break;

    case 28:
      /* hardware watchpoint address */
      watch_addr1 = value & 0x00ffffff;
      watch_mode1 = (value >> 30) & 0x00000003;
      break;

    case 29:
      /* hardware watchpoint address */
      watch_addr2 = value & 0x00ffffff;
      watch_mode2 = (value >> 30) & 0x00000003;
      break;

    default:
      break;
    }
}


void
sim_info (int verbose)
{
  ulong addr = 0L, end_addr;
  int i;
  bool seen_start = FALSE;

  printf ("\tAllocation:\t%ld words of simulation memory\n", allocated / 2);
  printf ("\tInstruction Count:\t%ld\n", instcnt);
  printf ("\tClock Cycles:\t%ld\n", total_cycles);
  printf ("\tExecution time (uSec):\t%0.3f\n", total_time_in_us);

  printf ("\tMemory regions used:\n");

  for (i = 0; i < N_PAGES; i++)
    {
      if (mem[i] == MNULL)
	{
	  if (seen_start)
	    {
	      seen_start = FALSE;
	      printf ("%05lX\n", addr - 1);
	    }
	  continue;
	}
      addr = (ulong) i << 12;
      end_addr = (((ulong) i + 1L) << 12) - 1L;
      do
	{
	  if (was_written (addr))
	    {
	      if (!seen_start)
		{
		  seen_start = TRUE;
		  printf ("\t\t\t%05lX - ", addr);
		}
	      while (addr < end_addr && was_written (++addr))
		;
	      if (addr < end_addr)
		{
		  seen_start = FALSE;
		  printf ("%05lX\n", addr - 1);
		}
	    }
	}
      while (addr++ < end_addr);
    }
}


void
sim_create_inferior (SIM_ADDR start_address, char **argv, char **envp)
{
  unsigned long entry_point = start_address >> 1;

  init_cpu ();
  simreg.ic = entry_point;
}


static volatile int sim_should_run;
static int last_status;
static int exit_code;


void
sim_stop_reason (enum sim_stop *reason, int *sigrc)
{
#define SIM_DIV_ZERO -5
#define SIM_INTERRUPT -6
#define SIM_BAD_INST -7
#define SIM_BREAKPOINT -1
#define SIM_SINGLE_STEP -8
#define SIM_BAD_SYSCALL -9
#define SIM_BAD_ALIGN -10
#define SIM_DONE 0

#define SIM_BREAKPT  -1
#define SIM_MEMERR   -2
#define SIM_WATCHPT  -3

#ifdef DEBUG
  printf ("sim_stop_reason(reason=0x%lx(%ld), sigrc=0x%lx(%ld))\n",
	  (long) reason, (long) *reason, (long) sigrc, (long) *sigrc);
#endif

  switch (last_status)
    {
    case SIM_DIV_ZERO:
      *sigrc = SIGFPE;
      break;
    case SIM_INTERRUPT:
      *sigrc = SIGINT;
      break;
    case SIM_BAD_INST:
      *sigrc = SIGILL;
      break;
    case SIM_BREAKPOINT:
      *sigrc = SIGTRAP;
      break;
    case SIM_WATCHPT:
      *sigrc = SIGTRAP;
      break;
    case SIM_SINGLE_STEP:
      *sigrc = SIGTRAP;
      break;
    case SIM_BAD_SYSCALL:
      *sigrc = SIGILL;
      break;
    case MEMERR:
      *sigrc = SIGSEGV;
      break;
    case SIM_BAD_ALIGN:
      *sigrc = SIGSEGV;
      break;
    case SIM_DONE:
      *sigrc = exit_code;
      *reason = sim_exited;
      return;
    default:
      abort ();
    }
  *reason = sim_stopped;
}



static void
sim_ctrl_c ()
{
  sim_should_run = 0;
}


static bool
at_final_bpt_instruction ()
{
  ushort opcode1;
  ushort opcode2;

  if (!get_raw (CODE, simreg.sw & 0xF, simreg.ic, &opcode1))
    return FALSE;
  if (!get_raw (CODE, simreg.sw & 0xF, simreg.ic + 1, &opcode2))
    return FALSE;
  return (opcode1 == 0xFFFF) && (opcode2 == 0xFF00);
}

void
sim_resume (int step, int siggnal)
{
  void (*prev) ();

#ifdef DEBUG
  printf ("sim_resume (step=%d, siggnal=%d)\n", step, siggnal);
#endif

  sim_should_run = 1;
  prev = signal (SIGINT, sim_ctrl_c);
  last_status = SIM_DONE;

  {
#ifdef MAS281
    int stat;
    stat = set_input ();
#endif /* */

  watching = 1;
  watch_hit1 = 0;
  watch_hit2 = 0;

    if (step)
      {
        if (last_status == SIM_WATCHPT)
          watching = 0;
	last_status = execute ();
	if (!sim_should_run)
	  last_status = SIM_INTERRUPT;
	else if (last_status >= 0)
	  last_status = SIM_SINGLE_STEP;
      }
    else
      {
	while (sim_should_run)
	  {
	    int ans = execute ();
            extern int n_breakpts;

            if (ans == SIM_BREAKPOINT && at_final_bpt_instruction ())
              {
		last_status = SIM_DONE;
                exit_code = simreg.r [0];
		break;
              }

	    if (ans >= 0)
	      {
		last_status = SIM_DONE;
	      }
	    else
	      {
		last_status = ans;
		break;
	      }
	  }
      }

  watching = 0;

#ifdef MAS281
    reset_input (stat);
#endif /* */
  }

  signal (SIGINT, prev);

  if (last_status == SIM_DONE && !sim_should_run)
    last_status = SIM_INTERRUPT;
}


void
sim_do_command (char *cmd)
{
#ifdef DEBUG
  printf ("sim_do_commands (cmd=%s) called\n",
	  cmd ? cmd : "(null)");
#endif

  if (cmd != NULL)
    sim_obey (cmd);
}


void
sim_set_callbacks (host_callback * callback)
{
#ifdef DEBUG
  printf ("sim_set_callbacks called\n");
#endif

}
