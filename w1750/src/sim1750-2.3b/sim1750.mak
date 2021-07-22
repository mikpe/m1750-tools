#
# Borland C++ IDE generated makefile
# Generated 01/05/97 at 14:46:25 
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
LinkerLocalOptsAtC32_sim1750dexe =  -Tpe -ap -c
ResLocalOptsAtC32_sim1750dexe = 
BLocalOptsAtC32_sim1750dexe = 
CompInheritOptsAt_sim1750dexe = -IC:\BC\INCLUDE;.\SRC; -D_RTLDLL;_BIDSDLL;STRDUP;WIN32;MAS281
LinkerInheritOptsAt_sim1750dexe = -x
LinkerOptsAt_sim1750dexe = $(LinkerLocalOptsAtC32_sim1750dexe)
ResOptsAt_sim1750dexe = $(ResLocalOptsAtC32_sim1750dexe)
BOptsAt_sim1750dexe = $(BLocalOptsAtC32_sim1750dexe)

#
# Dependency List
#
Dep_sim1750 = \
   sim1750.exe

sim1750 : BccW32.cfg $(Dep_sim1750)
  echo MakeNode

Dep_sim1750dexe = \
   .\OBJ\arith.obj\
   .\OBJ\asyncio.obj\
   .\OBJ\utils.obj\
   .\OBJ\tldldm.obj\
   .\OBJ\tekops.obj\
   .\OBJ\tekhex.obj\
   .\OBJ\status.obj\
   .\OBJ\smemacc.obj\
   .\OBJ\sdisasm.obj\
   .\OBJ\phys_mem.obj\
   .\OBJ\peekpoke.obj\
   .\OBJ\main.obj\
   .\OBJ\loadfile.obj\
   .\OBJ\load_coff.obj\
   .\OBJ\lic.obj\
   .\OBJ\flt1750.obj\
   .\OBJ\exec.obj\
   .\OBJ\do_xio.obj\
   .\OBJ\dism1750.obj\
   .\OBJ\cpu.obj\
   .\OBJ\cmd.obj\
   .\OBJ\break.obj\
   .\OBJ\xiodef.obj

sim1750.exe : $(Dep_sim1750dexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_sim1750dexe) $(LinkerInheritOptsAt_sim1750dexe) +
C:\BC\LIB\c0x32.obj+
.\OBJ\arith.obj+
.\OBJ\asyncio.obj+
.\OBJ\utils.obj+
.\OBJ\tldldm.obj+
.\OBJ\tekops.obj+
.\OBJ\tekhex.obj+
.\OBJ\status.obj+
.\OBJ\smemacc.obj+
.\OBJ\sdisasm.obj+
.\OBJ\phys_mem.obj+
.\OBJ\peekpoke.obj+
.\OBJ\main.obj+
.\OBJ\loadfile.obj+
.\OBJ\load_coff.obj+
.\OBJ\lic.obj+
.\OBJ\flt1750.obj+
.\OBJ\exec.obj+
.\OBJ\do_xio.obj+
.\OBJ\dism1750.obj+
.\OBJ\cpu.obj+
.\OBJ\cmd.obj+
.\OBJ\break.obj+
.\OBJ\xiodef.obj
$<,$*
C:\BC\LIB\bidsfi.lib+
C:\BC\LIB\import32.lib+
C:\BC\LIB\cw32i.lib

|

.\OBJ\arith.obj :  src\arith.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\arith.c
|

.\OBJ\asyncio.obj :  src\asyncio.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\asyncio.c
|

.\OBJ\utils.obj :  src\utils.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\utils.c
|

.\OBJ\tldldm.obj :  src\tldldm.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\tldldm.c
|

.\OBJ\tekops.obj :  src\tekops.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\tekops.c
|

.\OBJ\tekhex.obj :  src\tekhex.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\tekhex.c
|

.\OBJ\status.obj :  src\status.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\status.c
|

.\OBJ\smemacc.obj :  src\smemacc.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\smemacc.c
|

.\OBJ\sdisasm.obj :  src\sdisasm.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\sdisasm.c
|

.\OBJ\phys_mem.obj :  src\phys_mem.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\phys_mem.c
|

.\OBJ\peekpoke.obj :  src\peekpoke.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\peekpoke.c
|

.\OBJ\main.obj :  src\main.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\main.c
|

.\OBJ\loadfile.obj :  src\loadfile.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\loadfile.c
|

.\OBJ\load_coff.obj :  src\load_coff.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\load_coff.c
|

.\OBJ\lic.obj :  src\lic.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\lic.c
|

.\OBJ\flt1750.obj :  src\flt1750.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\flt1750.c
|

.\OBJ\exec.obj :  src\exec.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\exec.c
|

.\OBJ\do_xio.obj :  src\do_xio.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\do_xio.c
|

.\OBJ\dism1750.obj :  src\dism1750.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\dism1750.c
|

.\OBJ\cpu.obj :  src\cpu.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\cpu.c
|

.\OBJ\cmd.obj :  src\cmd.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\cmd.c
|

.\OBJ\break.obj :  src\break.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\break.c
|

.\OBJ\xiodef.obj :  src\xiodef.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_sim1750dexe) $(CompInheritOptsAt_sim1750dexe) -o$@ src\xiodef.c
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=sim1750.csm
-WC
-g0
-j0
| $@


