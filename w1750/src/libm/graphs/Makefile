CFLAGS = -O2 -g
CC = m1750-coff-gcc
LDLIBS= -lm

TESTS = \
  graph-cos  \
  graph-cosh  \
  graph-exp  \
  graph-log  \
  graph-sin  \
  graph-sinh  \
  graph-sqrt  \
  graph-tan  

all: $(TESTS)

clean:
	rm -rf *.o a.out $(TESTS)

