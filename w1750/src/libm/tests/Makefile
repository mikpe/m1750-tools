CFLAGS = -O2 -g 
CC = m1750-coff-gcc 
LDLIBS=-lm

LIBM_TESTS = \
  test-acos  \
  test-asin  \
  test-atan  \
  test-atan2  \
  test-ceil  \
  test-cos  \
  test-cosh  \
  test-exp  \
  test-fabs  \
  test-floor  \
  test-fmod  \
  test-frexp  \
  test-ldexp  \
  test-log  \
  test-log10  \
  test-modf  \
  test-pow  \
  test-sin  \
  test-sinh  \
  test-sqrt  \
  test-tan  \
  test-tanh  \
  test-machar

all: $(LIBM_TESTS)

run: $(LIBM_TESTS)
	m1750-coff-run $(LIBM_TESTS)

testmath: testmath.c
	$(CC) $(CFLAGS) testmath.c -lm -o testmath 

clean:
	rm -rf *.o a.out testmath $(LIBM_TESTS)



