CFLAGS = -O2 -g -mmmu
CC = m1750-coff-gcc
LDLIBS=

TESTS = \
  test-abs  \
  test-atof  \
  test-atoi  \
  test-atol  \
  test-div  \
  test-exit  \
  test-getenv  \
  test-isalnum  \
  test-isalpha  \
  test-iscntrl  \
  test-isdigit  \
  test-isgraph  \
  test-islower  \
  test-isprint  \
  test-ispunct  \
  test-isspace  \
  test-isupper  \
  test-isxdigit  \
  test-labs  \
  test-ldiv  \
  test-mblen  \
  test-mbstowcs  \
  test-mbtowc  \
  test-memchr  \
  test-memcmp  \
  test-memcpy  \
  test-memmove  \
  test-memset  \
  test-rand  \
  test-srand  \
  test-strcat  \
  test-strchr  \
  test-strcmp  \
  test-strcoll  \
  test-strcpy  \
  test-strcspn  \
  test-strerror  \
  test-strlen  \
  test-strncat  \
  test-strncmp  \
  test-strncpy  \
  test-strpbrk  \
  test-strrchr  \
  test-strspn  \
  test-strstr  \
  test-strtod  \
  test-strtol  \
  test-strtoul  \
  test-system  \
  test-tolower  \
  test-toupper  \
  test-wcstombs  \
  test-wctomb

all: $(TESTS)

run: $(TESTS)
	m1750-coff-run $(TESTS)

clean:
	rm -rf *.o a.out $(TESTS)


