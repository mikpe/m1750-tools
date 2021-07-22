#
# Makefile for libc/tests2
#
# $Log: Makefile,v $
# Revision 1.2  1997/08/04 14:20:02  nettleto
# Added test-abort
#
# Revision 1.1  1997/08/01 16:07:08  nettleto
# Initial revision
#
#

CFLAGS = -O2 -g 
CC = m1750-coff-gcc 
LDLIBS=

TESTS = \
  test-abort    \
  test-assert   \
  test-atexit   \
  test-calloc   \
  test-malloc   \
  test-setjmp   \
  test-strftime  \
  test-strtok   \
  test-strxfrm


all: $(TESTS)

run: $(TESTS)
	m1750-coff-run $(TESTS)

clean:
	rm -rf *.o a.out $(TESTS)

