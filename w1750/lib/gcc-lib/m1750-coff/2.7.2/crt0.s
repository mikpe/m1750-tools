/*
 * crt0.s 
 *
 * GCC-1750 C/C++ Run-Time, with optional 1750 expanded memory support
 *
 * Copyright (c) 1996 Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 *
 * $Log: crt0.s,v $
 * Revision 1.4  1997/05/09 17:44:50  nettleto
 * Updated signal values
 *
 * Revision 1.3  1997/05/09 12:10:28  nettleto
 * Rearranged __exit
 *
 * Revision 1.2  1997/05/07 21:14:31  nettleto
 * Changed environ to _environ
 *
 * Revision 1.1  1997/02/14 09:23:39  nettleto
 * Initial revision
 *
 */

        .title "$Id: crt0.s,v 1.4 1997/05/09 17:44:50 nettleto Exp nettleto $"

/* 
 * These values are set in the linker script.
 */
        .global  __stack
        .global  __bss_start
	.global  _end

/*
 * This is the interrupt vector. It gets copied into place
 * when the program is started up, and before any interrupts
 * are enabled.
 */
	.rdata
iv:
	.word  power_down_old
	.word  power_down_new
	.word  machine_error_old
	.word  machine_error_new
	.word  spare1_old
	.word  spare1_new
	.word  floating_overflow_old
	.word  floating_overflow_new
	.word  fixed_overflow_old
	.word  fixed_overflow_new
	.word  bex_old
	.word  bex_new
	.word  floating_underflow_old
	.word  floating_underflow_new
	.word  timer_a_old
	.word  timer_a_new
	.word  spare2_old
	.word  spare2_new
	.word  timer_b_old
	.word  timer_b_new
	.word  spare3_old
	.word  spare3_new
	.word  spare4_old
	.word  spare4_new
	.word  level1_old
	.word  level1_new
	.word  spare5_old
	.word  spare5_new
	.word  level2_old
	.word  level2_new
	.word  spare6_new
	.word  spare6_old

/*
 * These are where the old mask, old status and old instruction counter
 * are saved when the processor handles an interrupt. Only number 5
 * the BEX instruction is re-entrant, in which case the contents of the
 * old area should be saved before any further BEX instructions are
 * executed.
 */
	.bss
power_down_old:
	.space 6 
machine_error_old:
	.space 6
spare1_old:
	.space 6
floating_overflow_old:
	.space 6
fixed_overflow_old:
	.space 6
bex_old:
	.space 6
floating_underflow_old:
	.space 6
spare2_old:
	.space 6
timer_a_old:
	.space 6
spare3_old:
	.space 6
timer_b_old:
	.space 6
spare4_old:
	.space 6
spare5_old:
	.space 6
level1_old:
	.space 6
spare6_old:
	.space 6
level2_old:
	.space 6

/*
 * These are the new mask, new status and new instruction counters
 * for each of the 16 interrupt numbers. Note that number 5, for the
 * BEX instruction has an array of 16 instruction counters
 */
	default_mask = 0x0000    ! i.e. inhibit all non-maskable interrupts

	.data
power_down_new:
	.word  default_mask, 0, power_down_handler

machine_error_new:
	.word  default_mask, 0, machine_error_handler

spare1_new:
	.word  default_mask, 0, spare1_handler

floating_overflow_new:
	.word  default_mask, 0, floating_overflow_handler

fixed_overflow_new:
	.word  default_mask, 0, fixed_overflow_handler

bex_new:
	.word  default_mask, 0 
	.word  bex_handler0
	.word  bex_handler1
	.word  bex_handler2
	.word  bex_handler3
	.word  bex_handler4
	.word  bex_handler5
	.word  bex_handler6
	.word  bex_handler7
	.word  bex_handler8
	.word  bex_handler9
	.word  bex_handler10
	.word  bex_handler11
	.word  bex_handler12
	.word  bex_handler13
	.word  bex_handler14
	.word  bex_handler15

floating_underflow_new:
	.word  default_mask, 0, floating_underflow_handler

spare2_new:
	.word  default_mask, 0, spare2_handler

timer_a_new:
	.word  default_mask, 0, timer_a_handler

spare3_new:
	.word  default_mask, 0, spare3_handler

timer_b_new:
	.word  default_mask, 0, timer_b_handler

spare4_new:
	.word  default_mask, 0, spare4_handler

spare5_new:
	.word  default_mask, 0, spare5_handler

level1_new:
	.word  default_mask, 0, level1_handler

spare6_new:
	.word  default_mask, 0, spare6_handler

level2_new:
	.word  default_mask, 0, level2_handler


/*
 * Define argv (gets set to zero)
 */
        .bss
argv:
        .space  2

/*
 * Define null environment (delete if you don't ever call getenv)
 */
        .data
        .globl _environ
_environ:
        .word  envdata
envdata:
        .word  envstring1   ! followed by other asciiz strings
        .word  0
envstring1:
        .word  'c','p','u','=','m','a','s','2','8','1','\0'

        .text
/*
 * start -- initialize data areas and stack, then call main
 */
        .global start
start:
/* 
 * Zero out the bss section
 */
        lim    r1,__bss_start
        lim    r0,_end
        sr     r0,r1
        bez    L2
L1:
        stc    0,0,r1
	aisp   r1,1
        soj    r0,L1
L2:

/*
 * Copy the interrupt vector into place at word 20 onward
 */
	lim    r0,0x20    ! to address
	lim    r2,iv      ! from address
	lim    r1,32      ! word count
	mov    r0,r2

/*
 * Init the operand page registers so that all 16 address
 * states share the first 64K words of data
 */
.ifdef MMU
        xorr   r0,r0
L5:
        xorr   r2,r2
        lr     r1,r0
        sll    r1,4
L9:
        lr     r12,r1
        ar     r12,r2
        xio    r2,wopr,r12
        aisp   r2,1
        cisp   r2,15
        jle    L9
        aisp   r0,1
        cisp   r0,15
        jle    L5
.endif

/* 
 * Set up stack pointer, to highest stack address
 */        
        lim    r15,__stack

/*
 * Set up initial stack frame
 */
	xorr   r14,r14
        pshm   r14,r14
        lr     r14,r15

/*
 * Start timers A & B 
 */
	xorr   r0,r0
	xio    r0,ota          
	xio    r0,otb          

/*
 * Set interrupt mask then enable interrupts
 */
	lim    r0,0b0000000101000000   ! only timers a b
	xio    r0,smk
	xio    r0,enbl

/* 
 * call main (0, argv), where *argv == NULL 
 */
        xorr   r0,r0
        lim    r1,argv
        lsjs   r15,_main

/*
 * when main exits, call any global destructors
 */
        .global __exit
__exit:
        sisp   r15,3
        pshm   r14,r14
        lr     r14,r15
        l      r3,__DTOR_LIST__+2
        st     r3,1,r14
        lisp   r0,1
        c      r0,1,r14
        jgt    L83
        lim    r2,__DTOR_LIST__+6
L85:
        l      r1,0,r2
        st     r0,2,r14
        stb    r14,3
        sjs    r15,0,r1
        lb     r14,3
        aisp   r2,2
        l      r0,2,r14
        aisp   r0,1
        c      r0,1,r14
        jle    L85
L83:
	bpt
	j      start


/*
 * Function to call any global constructors (C++ only)
 */
        .text
.globl ___main
___main:
        sisp   r15,3
        pshm   r14,r14
        lr     r14,r15
        l      r3,__CTOR_LIST__+2
        st     r3,1,r14
        lisp   r0,1
        c      r0,1,r14
        jgt    L93
        lim    r2,__CTOR_LIST__+6
L95:
        l      r1,0,r2
        st     r0,2,r14
        stb    r14,3
        sjs    r15,0,r1
        lb     r14,3
        aisp   r2,2
        l      r0,2,r14
        aisp   r0,1
        c      r0,1,r14
        jle    L95
L93:
        lr     r15,r14
        popm   r14,r14
        aisp   r15,3
        lurs   r15

/*
 * This is the C signal handler table. There is one entry for
 * each signal declared in <signal.h>. The entry is -1, meaning
 * error, 0 meaning take the default action, 1 meaning ignore
 * the signal, and any other value meaning call the function
 * at that address.
 */
	.set   SIGHUP,         1       /* Hangup (POSIX).  */
	.set   SIGINT,         2       /* Interrupt (ANSI).  */
	.set   SIGQUIT,        3       /* Quit (POSIX).  */
	.set   SIGILL,         4       /* Illegal instruction (ANSI).  */
	.set   SIGABRT,        SIGIOT  /* Abort (ANSI).  */
	.set   SIGTRAP,        5       /* Trace trap (POSIX).  */
	.set   SIGIOT,         6       /* IOT trap (4.2 BSD).  */
	.set   SIGEMT,         7       /* EMT trap (4.2 BSD).  */
	.set   SIGFPE,         8       /* Floating-point exception (ANSI).  */
	.set   SIGKILL,        9       /* Kill, unblockable (POSIX).  */
	.set   SIGBUS,         10      /* Bus error (4.2 BSD).  */
	.set   SIGSEGV,        11      /* Segmentation violation (ANSI).  */
	.set   SIGSYS,         12      /* Bad argument to system call (4.2 BSD)*/
	.set   SIGPIPE,        13      /* Broken pipe (POSIX).  */
	.set   SIGALRM,        14      /* Alarm clock (POSIX).  */
	.set   SIGTERM,        15      /* Termination (ANSI).  */
	.set   SIGUSR1,        16      /* User-defined signal 1 (POSIX).  */
	.set   SIGUSR2,        17      /* User-defined signal 2 (POSIX).  */
	.set   SIGCHLD,        18      /* Child status has changed (POSIX).  */
	.set   SIGCLD,         SIGCHLD /* Same as SIGCHLD (System V).  */
	.set   SIGPWR,         19      /* Power failure restart (System V).  */

	.set   SIGPOWER_DOWN,           20
	.set   SIGFIXED_OVERFLOW,       21
	.set   SIGTIMER_A,              22
	.set   SIGTIMER_B,              23
	.set   SIGLEVEL1,               24
	.set   SIGLEVEL2,               25

	.set   SIGSPARE1,               26
	.set   SIGSPARE2,               27
	.set   SIGSPARE3,               28
	.set   SIGSPARE4,               29
	.set   SIGSPARE5,               30
	.set   SIGSPARE6,               31

	.bss
	.global __sig_func
__sig_func:
	.space 36

/*
 * This function is the same as ANSI C raise
 */
	.text
	.globl  __raise
__raise:
        lr     r1,r0
        l      r1,__sig_func,r1
        lr     r2,r1
        xorm   r2,-32768
        cim    r2,-32767
        jgt    L3
        lisp   r0,1
        j      L4
L3:
        sjs    r15,0,r1
        xorr   r0,r0
L4:
        urs    r15


/*
 * These are the handlers for the 16 interrupt numbers, with
 * the 16 handlers for the BEX instruction. Add you own code
 * to call your own interrupt handlers.
 */
	.text
power_down_handler:
	pshm   R0,R13
        lim    r0,SIGPOWER_DOWN
        sjs    r15,_raise
        popm   R0,R13
	xio    r0,enbl
	lst    power_down_old

machine_error_handler:
	pshm   R0,R13
        lim    r0,SIGSEGV
        sjs    r15,_raise
        popm   R0,R13
	xio    r0,enbl
	lst    machine_error_old

spare1_handler:
	xio    r0,enbl
	lst    spare1_old

floating_overflow_handler:
	pshm   R0,R13
        lim    r0,SIGFPE
        sjs    r15,_raise
        popm   R0,R13
	xio    r0,enbl
	lst    floating_overflow_old

fixed_overflow_handler:
	pshm   R0,R13
        lim    r0,SIGFIXED_OVERFLOW
        sjs    r15,_raise
        popm   R0,R13
	xio    r0,enbl
	lst    fixed_overflow_old

/*
 * BEX0. This is the long call handler. The destination address
 * (which is a 32-bit byte address) is passed in registers R11,R12
 */
	.bss
temp:
	.space 2

	.text
bex_handler0:
	st     r0,temp
	l      r0,bex_old+4    ! old ic
	pshm   r0,r0
	l      r0,bex_old+2    ! old sw
	pshm   r0,r0
	l      r0,bex_old+0    ! old im
	pshm   r0,r0
	l      r0,temp
	dsrl   r11,1           ! convert to word address
	st     r11,bex_old+2
	st     r12,bex_old+4
	xio    r0,enbl
	lst    bex_old

/* 
 * BEX1 
 * This bex supports the longjmp mechanism and is called from _setjmp. It
 * saves the called context (IM, CS, IP, R14 and R15) in the jmpbuf for
 * use by longjmp. Register r0 is set to zero on exit to indicate
 * the return is from setjmp rather than longjmp. 
 */
bex_handler1:
        lr     r4,r0           ! get ptr to jmpbuf
	l      r0,bex_old+0    ! old im
        st     r0,0,r4
	l      r0,bex_old+2    ! old sw
        st     r0,1,r4
.ifdef MMU
	popm   r0,r2           ! get callers IC
        st     r2,2,r4
        dst    r14,3,r4        ! callers r14 and r15
        pshm   r0,r2
.else
	popm   r0,r0           ! get callers IC
        st     r0,2,r4
        dst    r14,3,r4        ! callers r14 and r15
        pshm   r0,r0
.endif
        xorr   r0,r0 
	xio    r0,enbl
	lst    bex_old

/* 
 * BEX2 
 * We have defined BEX 2 to be 'get time', which returns a 32-bit
 * value where the LS bit is worth 100 microseconds and a range of
 * about 4 days. (This BEX may be customized)
 */
bex_handler2:
	xio    r1,ita            ! this instruction and the next run
	l      r0,top_timer_a    ! with interrupts inhibited
	dsll   r0,1              ! adjust for our board which runs at half speed
	xio    r11,enbl
	lst    bex_old

bex_handler3:
	xio    r0,enbl
	lst    bex_old

bex_handler4:
	xio    r0,enbl
	lst    bex_old

bex_handler5:
	xio    r0,enbl
	lst    bex_old

bex_handler6:
	xio    r0,enbl
	lst    bex_old

bex_handler7:
	xio    r0,enbl
	lst    bex_old

bex_handler8:
	xio    r0,enbl
	lst    bex_old

bex_handler9:
	xio    r0,enbl
	lst    bex_old

bex_handler10:
	xio    r0,enbl
	lst    bex_old

bex_handler11:
	xio    r0,enbl
	lst    bex_old

bex_handler12:
	xio    r0,enbl
	lst    bex_old

bex_handler13:
	xio    r0,enbl
	lst    bex_old

bex_handler14:
	xio    r0,enbl
	lst    bex_old

bex_handler15:
	xio    r0,enbl
	lst    bex_old

floating_underflow_handler:
	xio    r0,enbl
	lst    floating_underflow_old

spare2_handler:
	xio    r0,enbl
	lst    spare2_old

	.bss
top_timer_a:
	.word  0    ! counts timer A interrupts
top_timer_b:
	.word  0    ! counts timer B interrupts

	.text
timer_a_handler:
	incm   1,top_timer_a
	xio    r0,enbl
	lst    timer_a_old

spare3_handler:
	xio    r0,enbl
	lst    spare3_old

timer_b_handler:
	pshm   R0,R13
        lim    r0,SIGTIMER_B
        sjs    r15,_raise
        popm   R0,R13
	incm   1,top_timer_b
	xio    r0,enbl
	lst    timer_b_old

spare4_handler:
	xio    r0,enbl
	lst    spare4_old

spare5_handler:
	xio    r0,enbl
	lst    spare5_old

level1_handler:
	pshm   R0,R13
        lim    r0,SIGLEVEL1
        sjs    r15,_raise
        popm   R0,R13
	xio    r0,enbl
	lst    level1_old

spare6_handler:
	xio    r0,enbl
	lst    spare6_old

level2_handler:
	pshm   R0,R13
        lim    r0,SIGLEVEL2
        sjs    r15,_raise
        popm   R0,R13
	xio    r0,enbl
	lst    level2_old

	.end


