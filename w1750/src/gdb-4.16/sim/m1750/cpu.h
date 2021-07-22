/* cpu.h  --  exports of cpu.c */

#include "arch.h"

extern void   init_cpu (void);
extern int    execute (void);
/* return value of execute() is either the number of cycles, or: */
#define BREAKPT  -1
#define MEMERR   -2
#define WATCHPT  -3

/* extern struct regs simreg;
   (should be here but it's so ubiquitous that it is mentioned in arch.h) */
extern struct mmureg pagereg[2][16][16];
extern bool   executed_bpt;
extern ulong  instcnt;
extern int    bpindex;
extern double total_time_in_us;
extern long total_cycles;

extern ulong watch_addr1;
extern ulong watch_addr2;
extern int watch_mode1;
extern int watch_mode2;
#define WATCH_READ 0x1
#define WATCH_WRITE 0x2
extern int watching;
extern int watch_hit1, watch_hit2;

extern ftrace;

#define BT_SIZE (200)
extern struct regs bt_buff [BT_SIZE];
extern int bt_next;
extern int bt_cnt;

