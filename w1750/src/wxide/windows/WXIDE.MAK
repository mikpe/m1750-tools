#
# Borland C++ IDE generated makefile
# Generated 1-05-97 at 16:43:26 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCC32   = Bcc32 +BccW32.cfg 
TLINK32 = TLink32
TLIB    = TLib
BRC32   = Brc32
TASM32  = Tasm32
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGS32 =  -LC:\BC\LIB
IDE_ResFLAGS32 = 
LinkerLocalOptsAtW32_wxIDEdexe =  -Tpe -aa
ResLocalOptsAtW32_wxIDEdexe = 
BLocalOptsAtW32_wxIDEdexe = 
CompInheritOptsAt_wxIDEdexe = -IC:\BC\INCLUDE;C:\WXWIN\INCLUDE\MSW;C:\WXWIN\INCLUDE\BASE;C:\F2C\INCLUDE; -Dwx_msw;
LinkerInheritOptsAt_wxIDEdexe = -x
LinkerOptsAt_wxIDEdexe = $(LinkerLocalOptsAtW32_wxIDEdexe)
ResOptsAt_wxIDEdexe = $(ResLocalOptsAtW32_wxIDEdexe)
BOptsAt_wxIDEdexe = $(BLocalOptsAtW32_wxIDEdexe)

#
# Dependency List
#
Dep_wxIDE = \
   wxIDE.exe

wxIDE : BccW32.cfg $(Dep_wxIDE)
  echo MakeNode

Dep_wxIDEdexe = \
   wxidefct.obj\
   wxidetoo.obj\
   wxidesea.obj\
   wxiderun.obj\
   wxideopt.obj\
   wxidemak.obj\
   wxidelis.obj\
   wxidehlp.obj\
   wxidefil.obj\
   wxidevie.obj\
   wxIDE.obj\
   wxidedb.obj\
   ..\wxwin\lib\ctl3d32.lib\
   ..\..\wxwin\lib\wx32.lib\
   ..\..\wxwin\lib\rcparser.lib\
   ..\..\wxwin\lib\gauge.lib\
   ..\..\wxwin\lib\itsy.lib\
   ..\..\wxwin\lib\prologio.lib\
   ..\..\wxwin\lib\fafa.lib\
   ..\..\wxwin\lib\dib.lib\
   wxIDE.def\
   wxIDE.res

wxIDE.exe : $(Dep_wxIDEdexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_wxIDEdexe) $(LinkerInheritOptsAt_wxIDEdexe) +
C:\BC\LIB\c0w32.obj+
wxidefct.obj+
wxidetoo.obj+
wxidesea.obj+
wxiderun.obj+
wxideopt.obj+
wxidemak.obj+
wxidelis.obj+
wxidehlp.obj+
wxidefil.obj+
wxidevie.obj+
wxIDE.obj+
wxidedb.obj
$<,$*
..\wxwin\lib\ctl3d32.lib+
..\..\wxwin\lib\wx32.lib+
..\..\wxwin\lib\rcparser.lib+
..\..\wxwin\lib\gauge.lib+
..\..\wxwin\lib\itsy.lib+
..\..\wxwin\lib\prologio.lib+
..\..\wxwin\lib\fafa.lib+
..\..\wxwin\lib\dib.lib+
C:\BC\LIB\owlwfi.lib+
C:\BC\LIB\bidsfi.lib+
C:\BC\LIB\import32.lib+
C:\BC\LIB\cw32i.lib
wxIDE.def
|
   $(BRC32) wxIDE.res $<

wxidefct.obj :  wxidefct.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidefct.cpp
|

wxidetoo.obj :  wxidetoo.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidetoo.cpp
|

wxidesea.obj :  wxidesea.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidesea.cpp
|

wxiderun.obj :  wxiderun.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxiderun.cpp
|

wxideopt.obj :  wxideopt.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxideopt.cpp
|

wxidemak.obj :  wxidemak.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidemak.cpp
|

wxidelis.obj :  wxidelis.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidelis.cpp
|

wxidehlp.obj :  wxidehlp.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidehlp.cpp
|

wxidefil.obj :  wxidefil.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidefil.cpp
|

wxidevie.obj :  wxidevie.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidevie.cpp
|

wxIDE.obj :  wxIDE.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxIDE.cpp
|

wxidedb.obj :  wxidedb.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe) -o$@ wxidedb.cpp
|

wxIDE.res :  wxIDE.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe)  -FO$@ wxIDE.rc
|
wx.res :  ..\wxwin\include\msw\wx.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_wxIDEdexe) $(CompInheritOptsAt_wxIDEdexe)  -FO$@ ..\wxwin\include\msw\wx.rc
|
# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=mcd32.csm
-W
-H"owl\owlpch.h"
-v-
-R-
-whid
-Od
-d
-y-
-H=WXIDE.CSM
| $@


