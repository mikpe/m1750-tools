CFLAGS = -O2 -g 
CC = m1750-coff-gcc
LDLIBS=

TESTS = \
  test-CHAR_BIT  \
  test-CHAR_MAX  \
  test-CHAR_MIN  \
  test-INT_MAX  \
  test-INT_MIN  \
  test-LONG_MAX  \
  test-LONG_MIN  \
  test-MB_LEN_MAX  \
  test-SCHAR_MAX  \
  test-SCHAR_MIN  \
  test-SHRT_MAX  \
  test-SHRT_MIN  \
  test-UCHAR_MAX  \
  test-UINT_MAX  \
  test-ULONG_MAX  \
  test-USHRT_MAX 

all: $(TESTS)

run: $(TESTS)
	m1750-coff-run $(TESTS)

clean:
	rm -rf *.o a.out $(TESTS)


