/* do_xio.c -- user definable external IO call interface for sim1750 */

#include <stdio.h>
#if defined (WIN32)
#include <io.h>
#elif defined (__VMS)
#include <unixio.h>
#else
#include <unistd.h>
#endif

#include "arch.h"
#include "status.h"
#include "utils.h"
#include "targsys.h"


/* Import */
extern int nodelay_getchar (); /* asyncio.c */

/* Export */

void  do_xio (ushort address, ushort *value)
{
#ifdef MAS281
  /*
   * Code to support ERA MA281 board's serial interface
   */
  static char ch = 0;
  char buf[1];

  if (address == 0x8501)
    {
      /* read from serial interface 1 status register */
/****
      ch = nodelay_getchar();
      if (ch > 0) {
        *value = 0x06;
      } else {
         *value = 0x04;
      }
****/
      *value = 0x06;
    }
  else if (address == 0x0500)
    {
      /* write to serial interface 1 data register */
      buf[0] = *value;
      write (1, buf, 1);
      fflush(stdout);
    }
  else if (address == 0x8500)
    {
      /* read from serial interface 1 data register */
      if (ch == 0) {
        ch = nodelay_getchar();
      }
      *value = ch;
      ch = 0;
    }
  else
#endif

  if (address & 0x8000)  /* XIO read */
    {
      unsigned input_value;

      sim1750_info ("IO from %04hX < == ", address);
      if (scanf ("%i", &input_value) <= 0)
	{                     /* check for input redirection */
	  if (!isatty (fileno (stdin)))
	    problem ("Reading past end of input file !");
	}
      *value = (ushort) input_value;
      if (!isatty (fileno (stdin)))
        sim1750_info ("0x%04hX\n", value);
    }
  else			/* XIO write */
    sim1750_info ("IO  to  %04hX == > 0x%04hX\n", address, *value);
}

