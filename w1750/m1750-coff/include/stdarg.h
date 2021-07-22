/*
 * m1750-coff/include/stdarg.h
 *
 * ANSI Standard C: 7.8 Variable arguments
 *
 * Copyright (c) 1996, Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose,
 * provided that existing copyright notices are retained in all copies
 * and that this notice is included verbatim in any distributions. No
 * written agreement, license, or royalty fee is required for any of the
 * authorized uses. Modifications to this software may be copyrighted by
 * their authors and need not follow the licensing terms described here,
 * provided that the new terms are clearly indicated on the first page
 * of each file where they apply.
 *
 * $Log: stdarg.h,v $
 * Revision 1.2  1997/05/09 17:37:46  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:45  nettleto
 * Initial revision
 *
 */

#ifndef _STDARG_H_
#define _STDARG_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef struct
{
  int  __va_arg;    /* argument number */
  int *__va_stk;    /* start of args passed on stack */
  int *__va_reg;    /* start of args passed in regs */
} *va_list;

/* 7.8.1.1 */
#define va_start(AP,LASTARG) \
    ((AP) = __builtin_saveregs(0), \
     (AP)->__va_stk = __builtin_next_arg(LASTARG), \
     (AP)->__va_arg = __builtin_args_info(0))

/* 7.8.1.2 */
#define __va_reg_p(TYPE) \
  (__builtin_classify_type(*(TYPE *)0) < 12 \
   && sizeof(TYPE) <= 4)

#define __va_size(TYPE) (sizeof(TYPE))

#define va_arg(AP,TYPE)    \
(    \
  (AP)->__va_arg < 11    \
  ?    \
  (AP)->__va_arg = (AP)->__va_arg + __va_size(TYPE)    \
  ,    \
  (    \
    (AP)->__va_arg <= 11    \
    ?    \
    *(TYPE*)((AP)->__va_reg + (AP)->__va_arg - __va_size(TYPE))    \
    :    \
    (    \
      (AP)->__va_arg = 11 + __va_size(TYPE)    \
      ,    \
      *(TYPE*)((AP)->__va_stk + (AP)->__va_arg - __va_size(TYPE) - 11)    \
    )    \
  )    \
  :    \
  (    \
    (AP)->__va_arg = (AP)->__va_arg + __va_size(TYPE)    \
    ,    \
    *(TYPE*)((AP)->__va_stk + (AP)->__va_arg - __va_size(TYPE) - 11)    \
  )    \
)

#define va_arg2(AP,TYPE)    \
(    \
  (AP)->__va_arg < 11 && (AP)->__va_arg + __va_size(TYPE) < 11?    \
  ((AP)->__va_arg = (AP)->__va_arg + __va_size(TYPE),    \
   *(TYPE*)(AP)->__va_reg + (AP)->__va_arg - __va_size(TYPE)) :    \
  (     \
    \
    (AP)->__va_arg < 11 && (AP)->__va_arg + __va_size(TYPE) >= 11?    \
    (AP)->__va_arg = 11 +  __va_size(TYPE),    \
   *(TYPE*)((AP)->__va_reg + (AP)->__va_arg - __va_size(TYPE)) :    \
   (((AP)->__va_arg = (AP)->__va_arg + __va_size(TYPE),    \
   *(TYPE*)((AP)->__va_stk + (AP)->__va_arg - __va_size(TYPE) - 11)    \
       ))

/* 7.8.1.3 */
#define va_end(AP) ((void)0)

__END_DECLS

#endif /* not _STDARG_H_ */

