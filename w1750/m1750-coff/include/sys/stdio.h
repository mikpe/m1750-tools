/*
 * m1750-coff/include/sys/stdio.h
 *
 * GCC-1750 system header file:  
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
 * $log:$
 */

#ifndef _SYS_STDIO_H_
#define _SYS_STDIO_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

/*
 * Stdio buffers.
 */

struct __sbuf {
	unsigned char *_base;
	int	_size;
};

/*
 * We need fpos_t for the following, but it doesn't have a leading "_",
 * so we use _fpos_t instead.
 */

typedef long _fpos_t;		/* XXX must match off_t in <sys/types.h> */
				/* (and must be `long' for now) */

/*
 * Stdio state variables.
 *
 * The following always hold:
 *
 *	if (_flags&(__SLBF|__SWR)) == (__SLBF|__SWR),
 *		_lbfsize is -_bf._size, else _lbfsize is 0
 *	if _flags&__SRD, _w is 0
 *	if _flags&__SWR, _r is 0
 *
 * This ensures that the getc and putc macros (or inline functions) never
 * try to write or read from a file that is in `read' or `write' mode.
 * (Moreover, they can, and do, automatically switch from read mode to
 * write mode, and back, on "r+" and "w+" files.)
 *
 * _lbfsize is used only to make the inline line-buffered output stream
 * code as compact as possible.
 *
 * _ub, _up, and _ur are used when ungetc() pushes back more characters
 * than fit in the current _bf, or when ungetc() pushes back a character
 * that does not match the previous one in _bf.  When this happens,
 * _ub._base becomes non-nil (i.e., a stream has ungetc() data iff
 * _ub._base!=NULL) and _up and _ur save the current values of _p and _r.
 */

struct __sFILE {
  unsigned char *_p;	/* current position in (some) buffer */
  int	_r;		/* read space left for getc() */
  int	_w;		/* write space left for putc() */
  short	_flags;		/* flags, below; this FILE is free if 0 */
  short	_file;		/* fileno, if Unix descriptor, else -1 */
  struct __sbuf _bf;	/* the buffer (at least 1 byte, if !NULL) */
  int	_lbfsize;	/* 0 or -_bf._size, for inline putc */

  /* operations */
  void *_cookie;	/* cookie passed to io functions */

  int	(*_read)(void * _cookie, char *_buf, int _n);
  int	(*_write)(void * _cookie, const char *_buf, int _n);
  _fpos_t (*_seek)(void * _cookie, _fpos_t _offset, int _whence);
  int	(*_close)(void * _cookie);

  /* separate buffer for long sequences of ungetc() */
  struct __sbuf _ub;	/* ungetc buffer */
  unsigned char *_up;	/* saved _p when _p is doing ungetc data */
  int	_ur;		/* saved _r when _r is counting ungetc data */

  /* tricks to meet minimum requirements even when malloc() fails */
  unsigned char _ubuf[3];	/* guarantee an ungetc() buffer */
  unsigned char _nbuf[1];	/* guarantee a getc() buffer */

  /* separate buffer for fgetline() when line crosses buffer boundary */
  struct __sbuf _lb;	/* buffer for fgetline() */

  /* Unix stdio files get aligned to block boundaries on fseek() */
  int	_blksize;	/* stat.st_blksize (may be != _bf._size) */
  int	_offset;	/* current lseek offset */

};


#define __SLBF  0x0001  /* line buffered */
#define __SNBF  0x0002  /* unbuffered */
#define __SRD   0x0004  /* OK to read */
#define __SWR   0x0008  /* OK to write */
#define __SRW   0x0010  /* open for reading & writing */
#define __SEOF  0x0020  /* found EOF */
#define __SERR  0x0040  /* found error */
#define __SMBF  0x0080  /* _buf is from malloc */
#define __SAPP  0x0100  /* fdopen()ed in append mode - so must  write to */
#define __SSTR  0x0200  /* this is an sprintf/snprintf string */
#define __SOPT  0x0400  /* do fseek() optimisation */
#define __SNPT  0x0800  /* do not do fseek() optimisation */
#define __SOFF  0x1000  /* set iff _offset is in fact correct */
#define __SMOD  0x2000  /* true => fgetline modified _p text */


/*
 * Routines internal to the implementation.
 */
int __srget (struct __sFILE *);
int __swbuf (int, struct __sFILE *);

/*
 * The __sfoo macros are here so that we can 
 * define function versions in the C library.
 */
#define __sgetc(p) (--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))

static __inline int __sputc(int _c, struct __sFILE *_p) {
  if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
    return (*_p->_p++ = _c);
  else
    return (__swbuf(_c, _p));
}

#define __sfeof(p)  (((p)->_flags & __SEOF) != 0)
#define __sferror(p)  (((p)->_flags & __SERR) != 0)
#define __sclearerr(p)  ((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define __sfileno(p)  ((p)->_file)

struct _glue 
{
  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};

struct _Bigint 
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  unsigned long _x[1];
};

/*
 * Global data
 */

extern struct _glue __sglue;
extern int __sdidinit;

extern void (*__cleanup)();
extern struct __sFILE __sf[3];               /* first three file descriptors */


__END_DECLS

#endif /* not _SYS_STDIO_H_ */

