# Makfile for GCC-1750 libc
#
# Note: this file should be customized for non-BSD hosts.
# On Solaris, change prefix to /opt/gnu/, and change
# INSTALL to cp.
#


libc_version = 1.0
libc = libc

target=m1750-coff
version=2.7.2

# Common prefix for installation directories.
# NOTE: This directory must exist when you start installation.
prefix = /usr/local

# Directory in which to put host dependent programs and libraries
exec_prefix = $(prefix)

# Directory in which to put the directories used by the compiler.
libdir = $(exec_prefix)/lib

# Directory in which the compiler finds executables, libraries, etc.
libsubdir = $(libdir)/gcc-lib/$(target)/$(version)

# Directory in which to put man pages.
mandir = $(prefix)/man/man1

# Directory in which to find other cross-compilation tools and headers.
tooldir = $(exec_prefix)/$(target)

# The name of the compiler is target-gcc, for example m1750-coff-gcc
# Tools are located in the tool directory, which is also target dependent
#
program_transform_cross_name = -e s,^,$(target)-,

TARGET_TOOLPREFIX = $(tooldir)/bin/
AR_FOR_TARGET = $(TARGET_TOOLPREFIX)ar
INSTALL=install

CC = $(target)-gcc 

AR = $(AR_FOR_TARGET)

CFLAGS = -O2 -g 

PROJ_DIR=.

LIBC_OBJS = \
  libc.a(assert/_assert.o) \
  libc.a(intrrpt/handler.o) \
  libc.a(intrrpt/ivt.o) \
  libc.a(intrrpt/set_mk.o) \
  libc.a(ctype/ctype.o)  \
  libc.a(report/_dtoa.o)  \
  libc.a(report/printf.o)  \
  libc.a(report/sprintf.o)  \
  libc.a(report/test.o)  \
  libc.a(report/vprintf.o)  \
  libc.a(report/vsprintf.o)  \
  libc.a(setjmp/_setjmp.o)  \
  libc.a(setjmp/longjmp.o)  \
  libc.a(signal/raise.o)  \
  libc.a(signal/signal.o)  \
  libc.a(stdlib/abort.o)  \
  libc.a(stdlib/abs.o)  \
  libc.a(stdlib/atexit.o)  \
  libc.a(stdlib/atof.o)  \
  libc.a(stdlib/atoi.o)  \
  libc.a(stdlib/atol.o)  \
  libc.a(stdlib/bsearch.o)  \
  libc.a(stdlib/calloc.o) \
  libc.a(stdlib/div.o)  \
  libc.a(stdlib/exit.o)  \
  libc.a(stdlib/getenv.o)  \
  libc.a(stdlib/free.o) \
  libc.a(stdlib/labs.o)  \
  libc.a(stdlib/ldiv.o)  \
  libc.a(stdlib/malloc.o) \
  libc.a(stdlib/mblen.o)  \
  libc.a(stdlib/mbstowcs.o)  \
  libc.a(stdlib/mbtowc.o)  \
  libc.a(stdlib/rand.o)  \
  libc.a(stdlib/realloc.o)  \
  libc.a(stdlib/srand.o)  \
  libc.a(stdlib/strtod.o)  \
  libc.a(stdlib/strtol.o)  \
  libc.a(stdlib/strtoul.o)  \
  libc.a(stdlib/system.o)  \
  libc.a(stdlib/wcstombs.o)  \
  libc.a(stdlib/wctomb.o)  \
  libc.a(string/memchr.o)  \
  libc.a(string/memcmp.o)  \
  libc.a(string/memcpy.o)  \
  libc.a(string/memmove.o)  \
  libc.a(string/memset.o)  \
  libc.a(string/strcat.o)  \
  libc.a(string/strchr.o)  \
  libc.a(string/strcmp.o)  \
  libc.a(string/strcoll.o)  \
  libc.a(string/strcpy.o)  \
  libc.a(string/strcspn.o)  \
  libc.a(string/strerror.o)  \
  libc.a(string/strlen.o)  \
  libc.a(string/strncat.o)  \
  libc.a(string/strncmp.o)  \
  libc.a(string/strncpy.o)  \
  libc.a(string/strpbrk.o)  \
  libc.a(string/strrchr.o)  \
  libc.a(string/strspn.o)  \
  libc.a(string/strstr.o)  \
  libc.a(string/strtok.o)  \
  libc.a(string/strxfrm.o)  \
  libc.a(sys/close.o)  \
  libc.a(sys/errno.o)  \
  libc.a(sys/getpid.o)  \
  libc.a(sys/gettime.o)  \
  libc.a(sys/isatty.o)  \
  libc.a(sys/kill.o)  \
  libc.a(sys/lseek.o)  \
  libc.a(sys/open.o)  \
  libc.a(sys/read.o)  \
  libc.a(sys/sbrk.o)  \
  libc.a(sys/settime.o)  \
  libc.a(sys/times.o)  \
  libc.a(sys/unlink.o)  \
  libc.a(sys/write.o)  \
  libc.a(time/asctime.o)  \
  libc.a(time/clock.o)  \
  libc.a(time/ctime.o)  \
  libc.a(time/difftime.o)  \
  libc.a(time/gmtime.o)  \
  libc.a(time/localtime.o)  \
  libc.a(time/mktime.o)  \
  libc.a(time/strftime.o)  \
  libc.a(time/time.o)

LIBC_XOBJS = \
  libcx.a(assert/_assert.o) \
  libcx.a(intrrpt/handler.o) \
  libcx.a(intrrpt/set_mk.o) \
  libcx.a(ctype/ctype.o)  \
  libcx.a(report/_dtoa.o)  \
  libcx.a(report/printf.o)  \
  libcx.a(report/sprintf.o)  \
  libcx.a(report/test.o)  \
  libcx.a(report/vprintf.o)  \
  libcx.a(report/vsprintf.o)  \
  libcx.a(setjmp/_setjmp.o)  \
  libcx.a(setjmp/longjmp.o)  \
  libcx.a(signal/raise.o)  \
  libcx.a(signal/signal.o)  \
  libcx.a(stdlib/abort.o)  \
  libcx.a(stdlib/abs.o)  \
  libcx.a(stdlib/atexit.o)  \
  libcx.a(stdlib/atof.o)  \
  libcx.a(stdlib/atoi.o)  \
  libcx.a(stdlib/atol.o)  \
  libcx.a(stdlib/bsearch.o)  \
  libcx.a(stdlib/calloc.o) \
  libcx.a(stdlib/div.o)  \
  libcx.a(stdlib/exit.o)  \
  libcx.a(stdlib/getenv.o)  \
  libcx.a(stdlib/free.o) \
  libcx.a(stdlib/labs.o)  \
  libcx.a(stdlib/ldiv.o)  \
  libcx.a(stdlib/malloc.o) \
  libcx.a(stdlib/mblen.o)  \
  libcx.a(stdlib/mbstowcs.o)  \
  libcx.a(stdlib/mbtowc.o)  \
  libcx.a(stdlib/rand.o)  \
  libcx.a(stdlib/realloc.o)  \
  libcx.a(stdlib/srand.o)  \
  libcx.a(stdlib/strtod.o)  \
  libcx.a(stdlib/strtol.o)  \
  libcx.a(stdlib/strtoul.o)  \
  libcx.a(stdlib/system.o)  \
  libcx.a(stdlib/wcstombs.o)  \
  libcx.a(stdlib/wctomb.o)  \
  libcx.a(string/memchr.o)  \
  libcx.a(string/memcmp.o)  \
  libcx.a(string/memcpy.o)  \
  libcx.a(string/memmove.o)  \
  libcx.a(string/memset.o)  \
  libcx.a(string/strcat.o)  \
  libcx.a(string/strchr.o)  \
  libcx.a(string/strcmp.o)  \
  libcx.a(string/strcoll.o)  \
  libcx.a(string/strcpy.o)  \
  libcx.a(string/strcspn.o)  \
  libcx.a(string/strerror.o)  \
  libcx.a(string/strlen.o)  \
  libcx.a(string/strncat.o)  \
  libcx.a(string/strncmp.o)  \
  libcx.a(string/strncpy.o)  \
  libcx.a(string/strpbrk.o)  \
  libcx.a(string/strrchr.o)  \
  libcx.a(string/strspn.o)  \
  libcx.a(string/strstr.o)  \
  libcx.a(string/strtok.o)  \
  libcx.a(string/strxfrm.o)  \
  libcx.a(sys/close.o)  \
  libcx.a(sys/errno.o)  \
  libcx.a(sys/getpid.o)  \
  libcx.a(sys/gettime.o)  \
  libcx.a(sys/isatty.o)  \
  libcx.a(sys/kill.o)  \
  libcx.a(sys/lseek.o)  \
  libcx.a(sys/open.o)  \
  libcx.a(sys/read.o)  \
  libcx.a(sys/sbrk.o)  \
  libcx.a(sys/settime.o)  \
  libcx.a(sys/times.o)  \
  libcx.a(sys/unlink.o)  \
  libcx.a(sys/write.o)  \
  libcx.a(time/asctime.o)  \
  libcx.a(time/clock.o)  \
  libcx.a(time/ctime.o)  \
  libcx.a(time/difftime.o)  \
  libcx.a(time/gmtime.o)  \
  libcx.a(time/localtime.o)  \
  libcx.a(time/mktime.o)  \
  libcx.a(time/strftime.o)  \
  libcx.a(time/time.o)

all: crt0.o crt0x.o
	$(MAKE) "CFLAGS=$(CFLAGS) -I ./include/" "AR=$(AR)" "CC=$(CC)" libc.a
	$(MAKE) "CFLAGS=$(CFLAGS) -I ./include/ -DMMU -mmmu" "AR=$(AR)" "CC=$(CC)" libcx.a

# Make crt0 and crt0x

crt0.o: crt0.c
	m1750-coff-gcc crt0.c $(CFLAGS) -I ./include/ -c -o crt0.o

# Note: crt0x is NOT compiled with -mmmu
crt0x.o: crt0x.c
	m1750-coff-gcc crt0x.c $(CFLAGS) -I ./include/ -c -o crt0x.o

libc.a: $(LIBC_OBJS)
	echo "$@ is now up-to-date"

libcx.a: $(LIBC_XOBJS)
	echo "$@ is now up-to-date"

# target install, probably needs super user
install: 
	for f in include/*.h; do $(INSTALL) $$f $(tooldir)/include/; done
	for f in include/sys/*.h; do $(INSTALL) $$f $(tooldir)/include/sys/; done
	$(INSTALL) crt0.o $(libsubdir)/
	$(INSTALL) crt0x.o $(libsubdir)/mmmu/crt0.o
	$(INSTALL) libc.a $(libsubdir)/
	$(INSTALL) libcx.a $(libsubdir)/mmmu/libc.a
	$(INSTALL) libc.a $(libsubdir)/libg.a
	$(INSTALL) libcx.a $(libsubdir)/mmmu/libg.a
	for f in include/*.h; do $(INSTALL) $$f $(tooldir)/include/; done

# Remove all object files and the libraries
#
clean:
	rm -rf *.a *.o *~
	rm -rf */*.o

# Entry point 'dist'
# Make a source distribution
dist:
	rm -rf $(libc)
	mkdir $(libc)
	mkdir $(libc)/include
	mkdir $(libc)/include/sys
	mkdir $(libc)/assert
	mkdir $(libc)/ctype
	mkdir $(libc)/intrrpt
	mkdir $(libc)/report
	mkdir $(libc)/setjmp
	mkdir $(libc)/signal
	mkdir $(libc)/stdlib
	mkdir $(libc)/string
	mkdir $(libc)/sys
	mkdir $(libc)/time
	mkdir $(libc)/tests1
	mkdir $(libc)/tests2
	mkdir $(libc)/tests3
	mkdir $(libc)/doc
	cp Makefile $(libc)
	cp README $(libc)
	cp ChangeLog $(libc)
	cp crt0.c $(libc)
	cp crt0x.c $(libc)
	for f in include/*.h; do cp -P $$f $(libc); done
	for f in include/*,v; do cp -P $$f $(libc); done
	for f in include/sys/*.h; do cp -P $$f $(libc); done
	for f in include/sys/*,v; do cp -P $$f $(libc); done
	for f in assert/*.c; do cp -P $$f $(libc); done
	for f in assert/*,v; do cp -P $$f $(libc); done
	for f in ctype/*.c; do cp -P $$f $(libc); done
	for f in ctype/*,v; do cp -P $$f $(libc); done
	for f in intrrpt/*.c; do cp -P $$f $(libc); done
	for f in intrrpt/*,v; do cp -P $$f $(libc); done
	for f in report/*.c; do cp -P $$f $(libc); done
	for f in report/*,v; do cp -P $$f $(libc); done
	for f in setjmp/*.c; do cp -P $$f $(libc); done
	for f in setjmp/*,v; do cp -P $$f $(libc); done
	for f in signal/*.c; do cp -P $$f $(libc); done
	for f in signal/*,v; do cp -P $$f $(libc); done
	for f in stdlib/*.c; do cp -P $$f $(libc); done
	for f in stdlib/*,v; do cp -P $$f $(libc); done
	for f in string/*.c; do cp -P $$f $(libc); done
	for f in string/*,v; do cp -P $$f $(libc); done
	for f in sys/*.c; do cp -P $$f $(libc); done
	for f in sys/*,v; do cp -P $$f $(libc); done
	for f in time/*.c; do cp -P $$f $(libc); done
	for f in time/*,v; do cp -P $$f $(libc); done
	-for f in doc/*; do cp -P $$f $(libc); done
	cp tests1/Makefile $(libc)/tests1
	cp tests2/Makefile $(libc)/tests2
	cp tests3/Makefile $(libc)/tests3
	for f in tests1/*.c; do cp -P $$f $(libc); done
	for f in tests2/*.c; do cp -P $$f $(libc); done
	for f in tests3/*.c; do cp -P $$f $(libc); done
	tar zcf gcc-1750-$(libc_version)-libc.tar.gz $(libc)
	rm -rf $(libc)

