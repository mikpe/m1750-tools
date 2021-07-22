# Makfile for GCC-1750 libm
#
# Note: this file should be customized for non-BSD hosts.
# On Solaris, change prefix to /opt/gnu/, and change
# INSTALL to cp.
#

libm_version = 1.0
libm = libm

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

CC = $(target)-gcc 

AR = $(AR_FOR_TARGET)

CFLAGS = -O2 -Wall -g

PROJ_DIR=.


# target all
# All
all: src/libm.a src/libmx.a 

src/libm.a:
	(cd ./src; $(MAKE) -I ../include/ "CFLAGS=$(CFLAGS)" "AR=$(AR)" "CC=$(CC)" libm.a)

src/libmx.a:
	(cd ./src; $(MAKE) -I ../include/ "CFLAGS=$(CFLAGS) -mmmu" "AR=$(AR)" "CC=$(CC)" libmx.a)

# target install, probably needs super user
install: 
	$(INSTALL) src/libm.a $(libsubdir)
	$(INSTALL) src/libmx.a $(libsubdir)/mmmu/libm.a
	for f in include/*.h; do $(INSTALL) $$f $(tooldir)/include/; done

# Remove all object files and the libraries
#
clean:
	(cd src; make clean)
	(cd tests; make clean)
	(cd graphs; make clean)

# Entry point 'dist'
# Make a source distribution
dist:
	rm -rf $(libm)
	mkdir $(libm)
	mkdir $(libm)/include
	mkdir $(libm)/src
	mkdir $(libm)/tests
	mkdir $(libm)/graphs
	cp Makefile $(libm)
	cp README $(libm)
	cp ChangeLog $(libm)
	cp src/Makefile $(libm)/src
	for f in include/*.h; do cp -P $$f $(libm); done
	for f in src/*.c; do cp -P $$f $(libm); done
	for f in src/*,v; do cp -P $$f $(libm); done
	for f in tests/*; do cp -P $$f $(libm); done
	for f in graphs/*; do cp -P $$f $(libm); done
	tar zcf gcc-1750-$(libm_version)-libm.tar.gz $(libm)
	rm -rf $(libm)

# Entry point to make the tests.
test:
	(cd tests; make compile)

