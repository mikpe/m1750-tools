# Makefile for POSIX Threads tests
#
# $Log: Makefile,v $
# Revision 1.1  1997/08/11 14:18:54  nettleto
# Initial revision
#
#

CC= m1750-coff-gcc
CFLAGS=-O2 -g 
LDLIBS=-lpthread -lm

TESTS = \
  test-dp \
  test_priority \
  test_pthread_create \
  test_pthread_join \
  test_pthread_mutex \
  t-latency  \
  t-intwait \
  t-mutex  \
  t-delay  \
  t-signal  \
  t-nanosleep  \
  t-self  \
  t-switch  

all : $(TESTS)

run : $(TESTS)
	m1750-coff-run $(TESTS)

clean:
	rm -rf *.o a.out *.log $(TESTS)

