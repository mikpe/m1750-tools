/*  This file is part of the program psim.

    Copyright (C) 1994-1996, Andrew Cagney <cagney@highland.com.au>

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


#include <stdarg.h>
#include <stdio.h>

#include "psim.h"
#include "options.h"
#include "device.h" /* FIXME: psim should provide the interface */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

extern char **environ;

static psim *simulation;


void
printf_filtered(const char *msg, ...)
{
  va_list ap;
  va_start(ap, msg);
  vprintf(msg, ap);
  va_end(ap);
}

void
flush_stdoutput(void)
{
  fflush (stdout);
}

void
error (char *msg, ...)
{
  va_list ap;
  va_start(ap, msg);
  vprintf(msg, ap);
  va_end(ap);

  /* any final clean up */
  if (ppc_trace[trace_print_info])
    psim_print_info (simulation, ppc_trace[trace_print_info]);

  exit (1);
}

void *
zalloc(long size)
{
  void *memory = malloc(size);
  if (memory == NULL)
    error("zmalloc failed\n");
  memset(memory, 0, size);
  return memory;
}

void
zfree(void *chunk)
{
  free(chunk);
}

int
main(int argc, char **argv)
{
  const char *name_of_file;
  char *arg_;
  psim_status status;
  device *root = psim_tree();

  /* parse the arguments */
  argv = psim_options(root, argv + 1);
  if (argv[0] == NULL)
    psim_usage(0);
  name_of_file = argv[0];

  if (ppc_trace[trace_opts])
    print_options ();

  /* create the simulator */
  simulation = psim_create(name_of_file, root);

  /* fudge the environment so that _=prog-name */
  arg_ = (char*)zalloc(strlen(argv[0]) + strlen("_=") + 1);
  strcpy(arg_, "_=");
  strcat(arg_, argv[0]);
  putenv(arg_);

  /* initialize it */
  psim_init(simulation);
  psim_stack(simulation, argv, environ);

  psim_run(simulation);

  /* any final clean up */
  if (ppc_trace[trace_print_info])
    psim_print_info (simulation, ppc_trace[trace_print_info]);

  /* why did we stop */
  status = psim_get_status(simulation);
  switch (status.reason) {
  case was_continuing:
    error("psim: continuing while stoped!\n");
    return 0;
  case was_trap:
    error("psim: no trap insn\n");
    return 0;
  case was_exited:
    return status.signal;
  case was_signalled:
    printf ("%s: Caught signal %d at address 0x%lx\n",
 	    name_of_file, (int)status.signal,
 	    (long)status.program_counter);
    return status.signal;
  default:
    error("unknown halt condition\n");
    return 0;
  }
}
