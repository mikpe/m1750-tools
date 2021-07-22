# Makefile for libwx.a

CC = CC
LD = CC
# Replace this with your own path
GCCDIR =
GCCINC = 
WXDIR = /usr/local/wxwin
WXINC = -I$(WXDIR)/include/base -I$(WXDIR)/include/x
XWDIR = /export/dt
XWINC = -I$(XWDIR)/include 
OWDIR = /usr/openwin
OWINC = -I$(OWDIR)/include
GDB =

# Compiler flags.
DEBUG =
GUI = -Dwx_motif
COPT = -w
LOPT =

CPPFLAGS =  $(COPT) $(GCCINC) $(OWINC) $(XWINC) $(WXINC) $(GUI) $(DEBUG) $(OPT) $(GDB)
CFLAGS = $(GUI)
LDFLAGS =  $(LOPT) $(GDB) $(DEBUG) -L$(OWDIR)/lib -L$(XWDIR)/lib -L$(WXDIR)/lib
LIBS = -lwx_motif -lXm -lXmu -lX -lX11 -lXt -lsocket -lnsl -lm



wxide: wxide.o wxidefct.o wxidedb.o wxidefil.o wxidehlp.o wxideopt.o wxiderun.o wxidesea.o wxidetoo.o wxidevie.o wxidemak.o wxidelis.o
	$(LD) $(LDFLAGS) $(GDB) -o wxide wxide.o wxidefil.o wxidefct.o wxidedb.o wxidesea.o wxidehlp.o wxideopt.o wxiderun.o wxidetoo.o wxidevie.o wxidemak.o wxidelis.o $(LIBS)
#	strip wxide



wxide.o: wxide.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxide.cc

wxidelis.o: wxidelis.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidelis.cc

wxidefil.o: wxidefil.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidefil.cc

wxidefct.o: wxidefct.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidefct.cc

wxidedb.o: wxidedb.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidedb.cc

wxidehlp.o: wxidehlp.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidehlp.cc

wxideopt.o: wxideopt.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxideopt.cc

wxiderun.o: wxiderun.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxiderun.cc

wxidesea.o: wxidesea.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidesea.cc

wxidetoo.o: wxidetoo.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidetoo.cc

wxidevie.o: wxidevie.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidevie.cc

wxidemak.o: wxidemak.cc wxide.h
	$(CC) $(CPPFLAGS) -c wxidemak.cc

all: wxide

clean:
	rm -f *.o






