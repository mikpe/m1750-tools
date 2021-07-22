/* status.h  --  exports of status.c */

#ifndef _STATUS_H
#define _STATUS_H

#include <stdio.h>
#include "type.h"

/* return codes */
#define OKAY        0
#define ERROR       1
#define WARNING     2
#define INFO        3
#define INTERRUPT   1704  /* returnvalue if function has been interrupted */
#define SIM_QUIT        -999

/* exports */
extern FILE  *logfile;
extern void  sim1750_lprintf (char *layout, ...);   /* printf with logfile output */
extern int   sim1750_info (char *layout, ...);
extern int   sim1750_warning (char *layout, ...);
extern int   sim1750_error (char *layout, ...);
extern char  global_message[];

/* command line switches of global relevance (defined in main.c) */
extern bool verbose;
extern bool need_speed;

#endif
