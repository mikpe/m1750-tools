# Makfile for GCC-1750 libpthread
#
# Note: this file should be customized for non-BSD hosts.
# On Solaris, change prefix to /opt/gnu/, and change
# INSTALL to cp.
#

libpthread_version = 1.0
libpthread = libpthread

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

INSTALL = install

TARGET_TOOLPREFIX = $(tooldir)/bin/
AR_FOR_TARGET = $(TARGET_TOOLPREFIX)ar
RANLIB = $(TARGET_TOOLPREFIX)ranlib

CC = $(target)-gcc
AR = $(AR_FOR_TARGET)

CFLAGS = -O2 -g

PROJ_DIR=.

# target all
# All
all:  
	(cd ./src; $(MAKE) "CFLAGS=$(CFLAGS) -I ../include/" "AR=$(AR)" "CC=$(CC)" libpthread.a)
	$(RANLIB) src/libpthread.a
	(cd ./src; $(MAKE) "CFLAGS=-mmmu -DMMU $(CFLAGS) -I ../include/" "AR=$(AR)" "CC=$(CC)" libpthreadx.a)
	$(RANLIB) src/libpthreadx.a


# target install, probably needs super user
install:
	$(INSTALL) src/libpthread.a $(libsubdir)
	$(INSTALL) src/libpthreadx.a $(libsubdir)/mmmu/libpthread.a
	for f in include/pthread.h; do $(INSTALL) $$f $(tooldir)/include/; done

# Remove all object files and the libraries
#
clean:
	(cd src; make clean)
	(cd tests; make clean)
	rm -rf *.a

# Entry point 'test'
test:
	(cd tests; make)

# Entry point 'dist'
# Make a source distribution
dist:
	rm -rf $(libpthread)
	mkdir $(libpthread)
	mkdir $(libpthread)/src
	mkdir $(libpthread)/include
	mkdir $(libpthread)/tests
	cp Makefile $(libpthread)
	cp README $(libpthread)
	cp ChangeLog $(libpthread)
	cp -P src/Makefile $(libpthread)
	for f in include/*; do cp -P $$f $(libpthread); done
	for f in src/*.{c,h}; do cp -P $$f $(libpthread); done
	for f in src/*,v; do cp -P $$f $(libpthread); done
	for f in tests/Makefile; do cp -P $$f $(libpthread); done
	for f in tests/*.c; do cp -P $$f $(libpthread); done
	tar zcf gcc-1750-$(libpthread_version)-libpthread.tar.gz $(libpthread)
	rm -rf $(libpthread)

