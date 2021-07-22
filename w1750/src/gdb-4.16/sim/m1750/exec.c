/***************************************************************************/
/*                                                                         */
/* Project   :        sim1750 -- Mil-Std-1750 Software Simulator           */
/*                                                                         */
/* Component :         exec.c -- control over simulator execution          */
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


#include <stdio.h>
#include <ctype.h>

#include "arch.h"
#include "status.h"
#include "cpu.h"
#include "smemacc.h"
#include "break.h"

/* Imports */

extern void dis_reg ();		/* cmd.c */
extern int sys_int (long);	/* cmd.c */
extern char *disassemble ();	/* sdisasm.c */
extern int set_input ();	/* asyncio.c */
extern void reset_input ();	/* asyncio.c */


static bool
at_bpt_instruction ()
{
  ushort opcode;
  if (!get_raw (CODE, simreg.sw & 0xF, simreg.ic, &opcode))
    return FALSE;
  return (opcode == 0xFFFF);
}

static int
execute_without_breakpt ()
{
  int status;
  int bpi = bpindex;

  bpindex = -1;
  set_inactive (bpi);
  status = execute ();
  set_active (bpi);
  return status;
}


int
si_go (int argc, char *argv[])
{
  unsigned next;

  if (argc > 1)
    {
      sscanf (argv[1], "%x", &next);
      simreg.ic = (ushort) next;
    }

  if (at_bpt_instruction ())
    simreg.ic++;
  else if (bpindex >= 0)
    execute_without_breakpt ();

  watching = 1;

#ifdef MAS281
  {
    
      int stat;
    
      
      stat = set_input ();
    
#endif	/*  */

      while (1)
      {
	int ans;

	if (sys_int (1L))
	  return INTERRUPT;
	if ((ans = execute ()) == MEMERR)
	  break;

	if (ans == WATCHPT)
	  {
	    sim1750_info ("\tWatchpoint at %04hX : %s",
		  simreg.ic, disassemble ());
	    break;
	  }

	if (at_bpt_instruction ())
	  {
	    sim1750_info ("\tBPT at %04hX", simreg.ic);
	    break;
	  }
	else if (bpindex >= 0)
	  {
	    sim1750_info ("\tBreakpoint at %04hX : %s",
		  simreg.ic, disassemble ());
	    break;
	  }
      }
#ifdef MAS281
    reset_input (stat);
    
  }
  
#endif	/*  */

  watching = 0;

  return OKAY;
}


int
si_snglstp (int argc, char *argv[])
{
  int count = 1;
  bool step_over = FALSE;
  ushort target_addr;

  if (argc > 1)
    {
      if (*argv[1] == '*')
	{
	  step_over = TRUE;
	  target_addr = simreg.ic + 2;
	}
      else
	sscanf (argv[1], "%d", &count);
    }

  if (at_bpt_instruction ())
    simreg.ic++;

  if (step_over)
    {
      if (bpindex >= 0)
	{
	  sim1750_info ("\tStepping past breakpoint at IC : %04hX   %s",
		simreg.ic, disassemble ());
	  execute_without_breakpt ();
	}
      while (simreg.ic != target_addr)
	{
	  int ans;

	  if (sys_int (1L))
	    return (INTERRUPT);
	  if ((ans = execute ()) == MEMERR)
	    break;

	  if (ans == WATCHPT)
	    {
	      sim1750_info ("\tWatchpoint at %04hX : %s",
		    simreg.ic, disassemble ());
	      break;
	    }

	  if (at_bpt_instruction ())
	    {
	      sim1750_lprintf ("\tBPT at %04hX", simreg.ic);
	      break;
	    }
	  else if (bpindex >= 0)
	    {
	      sim1750_info ("\tBreakpoint at %04hX : %s",
		    simreg.ic, disassemble ());
	      break;
	    }
	}
      if (!at_bpt_instruction () && bpindex < 0)
	sim1750_info ("\tStep at %04hX : %s", simreg.ic, disassemble ());
    }
  else
    {
      while (count-- > 0)
	{
	  int ans;

	  if (sys_int (1L))
	    return (INTERRUPT);
	  if (at_bpt_instruction ())
	    {
	      sim1750_info ("\tStepping past BPT at IC : %04hX", simreg.ic);
	      simreg.ic++;
	    }
	  else if (bpindex >= 0)
	    {
	      sim1750_info ("\tStepping past breakpoint at IC : %04hX   %s",
		    simreg.ic, disassemble ());
	      execute_without_breakpt ();
	    }
	  else
	    {
	      if ((ans = execute ()) == MEMERR)
		break;

	      if (ans == WATCHPT)
		{
		  sim1750_info ("\tWatchpoint at %04hX : %s",
			simreg.ic, disassemble ());
		  break;
		}

	    }

	  sim1750_info ("\tIC : %04hX   %s", simreg.ic, disassemble ());
	}
    }

  return (OKAY);
}


int
si_trace (int argc, char *argv[])
{
  int count = 1;

  if (argc > 1)
    {
      if (argc > 2)
	sim1750_error ("excess arguments ignored");
      else
	sscanf (argv[1], "%x", &count);
    }

  while (count-- > 0)
    {
      if (sys_int (1L))
	return (INTERRUPT);

      if (at_bpt_instruction ())
	simreg.ic++;
      else if (bpindex >= 0)
	execute_without_breakpt ();
      else if (execute () == MEMERR)
	break;
      sim1750_lprintf ("\tIC : %04hX   %s\n", simreg.ic, disassemble ());
      dis_reg (0);
    }

  return (OKAY);
}


int
si_bt (int argc, char *argv[])
{
  /* Backtrace the given number of instructions */

  int count = 10;
  int back = 10;
  struct regs save;
  int t;
  int tt;

  if (argc > 0)
    {
      sscanf (argv[1], "%x", &back);
      count = back;
      if (argc > 1)
        sscanf (argv[2], "%x", &count);
    }

  if (count > bt_cnt)
    count = bt_cnt;

  if (back > bt_cnt)
    back = bt_cnt;
  tt = -back;

  /* save current regs */
  save = simreg;

  /* step back through backtrace buffer */
  t = bt_next - back;
  if (t < 0)
    t += BT_SIZE;

  while (count-- >= 0)
    {
      simreg = bt_buff[t];
      sim1750_lprintf ("%d:\tIC : %04hX   %s\n", tt++, simreg.ic, disassemble ());
      dis_reg (0);

      t++;
      if (t >= BT_SIZE)
	t = 0;
    }

  /* restore old regs */
  simreg = save;

  return (OKAY);
}
