# m1750-tools

This contains a copy of [cpp1750.zip](https://downloads.cleanscape.net/1750a/resources/cpp1750.zip),
which, as far as I know, are the only publicly available sources for the `m1750-coff` GNU toolchain
for the MIL-STD-1750A processor. (The alternative `1750a` toolchain is not considered here.)
With a little effort this toolchain can be built on a contemporary Linux/x86-64 host.

Due to the age of these sources you need an old compiler to build them.
gcc-2.95.3 is known to work, gcc-3.x/4.x and newer do _not_ work.
You need kernel and libc support for 32-bit executables.
This compiler is assumed to be installed in `/opt/gcc-2.95.3`. (See below for how to build it.)

Your local copy of this repository is assumed to be in `/path/to/m1750-tools`.

## Build m1750-coff binutils

Create a separate build directory, `cd` to it, and execute:

```
> PATH=/opt/gcc-2.95.3/bin:$PATH /path/to/m1750-tools/w1750/src/binutils-2.7/configure --target=m1750-coff --host=i386-linux --prefix=/opt/cross-m1750 --with-sysroot=/opt/cross-m1750 --disable-nls
> PATH=/opt/gcc-2.95.3/bin:$PATH make MAKEINFO=/bin/true
> PATH=/opt/gcc-2.95.3/bin:$PATH make MAKEINFO=/bin/true install
```

## Install m1750-coff libc and libm header files

```
> tar -C /path/to/m1750-tools/w1750/src/libc/ -cf - include | tar -C /opt/cross-m1750/m1750-coff/ -xv
> tar -C /path/to/m1750-tools/w1750/src/libm/ -cf - include | tar -C /opt/cross-m1750/m1750-coff/ -xv
```

## Build m1750-coff gcc

Create a separate build directory, `cd` to it, and execute:

```
> PATH=/opt/gcc-2.95.3/bin:$PATH /path/to/m1750-tools/w1750/src/gcc-2.7.2/configure --target=m1750-coff --host=i386-linux --prefix=/opt/cross-m1750 --with-sysroot=/opt/cross-m1750 --disable-nls --disable-shared
> PATH=/opt/gcc-2.95.3/bin:$PATH make CC=gcc CFLAGS="-O2 -g" MAKEINFO=/bin/true LANGUAGES=c
> PATH=/opt/gcc-2.95.3/bin:$PATH make CC=gcc CFLAGS="-O2 -g" MAKEINFO=/bin/true LANGUAGES=c install
```

## Build m1750-coff libc

This needs to run from within the sources:

```
> cd /path/to/m1750-tools/w1750/src/libc
> PATH=/opt/cross-m1750/bin:$PATH make prefix=/opt/cross-m1750
> PATH=/opt/cross-m1750/bin:$PATH make prefix=/opt/cross-m1750 install
```

## Build m1750-coff libm

This needs to run from within the sources:

```
> cd /path/to/m1750-tools/w1750/src/libm
> PATH=/opt/cross-m1750/bin:$PATH make prefix=/opt/cross-m1750
> PATH=/opt/cross-m1750/bin:$PATH make prefix=/opt/cross-m1750 install
```

## Build m1750-coff libpthread

This needs to run from within the sources:

```
> cd /path/to/m1750-tools/w1750/src/libpthread
> PATH=/opt/cross-m1750/bin:$PATH make prefix=/opt/cross-m1750
> PATH=/opt/cross-m1750/bin:$PATH make prefix=/opt/cross-m1750 install
```

## Build sim1750

This requires that 32-bit `termcap` and `readline` system libraries are installed.

This needs to run from within the sources:

```
> cd /path/to/m1750-tools/w1750/src/sim1750-2.3b
> mkdir -p obj
> PATH=/opt/gcc-2.95.3/bin:$PATH make CFLAGS="-DSTRDUP -DSTRNDUP -DSTRNCASECMP -DLONGLONG -DMAS281 -DUNIX -DGNU_READLINE"
> mv sim1750 /opt/cross-m1750/bin/
```

(See also [milstd1750tools](https://github.com/okellogg/milstd1750tools) for a newer version of `sim1750`.)

## Build m1750-coff gdb

This requires that 32-bit `termcap` system libraries are installed.

Create a separate build directory, `cd` to it, and execute:

```
> PATH=/opt/gcc-2.95.3/bin:$PATH /path/to/m1750-toolst/w1750/src/gdb-4.16/configure --target=m1750-coff --host=i386-linux --prefix=/opt/cross-m1750
> PATH=/opt/gcc-2.95.3/bin:$PATH make
# The above ends with a "*** No rule to make target '../sim/m1750/libsim.a', needed by 'gdb'." error. This is expected.
> mkdir sim/m1750
> cd sim/m1750
> PATH=/opt/gcc-2.95.3/bin:$PATH /path/to/m1750-tools/w1750/src/gdb-4.16/sim/m1750/configure --host=i386-linux
> PATH=/opt/gcc-2.95.3/bin:$PATH make
> cd ../..
> PATH=/opt/gcc-2.95.3/bin:$PATH make
> PATH=/opt/gcc-2.95.3/bin:$PATH make install
```

## Try it out

```
> cat > test.c
#include <stdio.h>
int main(void) { printf("hello\n"); return 0; }
^D
> /opt/cross-m1750/bin/m1750-coff-gcc -O2 test.c
> /opt/cross-m1750/bin/sim1750

MIL-STD-1750 software simulator v. 2.3b configured for MAS281
sim1750 is free software and you are welcome to distribute copies of it
 under certain conditions; type "cond" to see the conditions.
There is absolutely no warranty for sim1750; type "warr" for details.
Copyright 1994-97 Daimler-Benz Aerospace AG
command > lcf a.out
Entry point = 0x00008000
00008000 00A60 (2656) .text
poke: dynamically allocating page 08
00008A60 00006 (6) .data
00008A66 0021C (540) .rodata
00008C82 00001 (1) .bss
command > go
poke: dynamically allocating page 0F
hello
        BPT at 8042
command > q
> /opt/cross-m1750/bin/m1750-coff-gdb a.out
GDB is free software and you are welcome to distribute copies of it
 under certain conditions; type "show copying" to see the conditions.
There is absolutely no warranty for GDB; type "show warranty" for details.
GDB 4.16 (i386-unknown-linux --target m1750-coff), Copyright 1996 Free Software Foundation, Inc...
(gdb) run
Starting program: a.out
Loading section .text, size 0x14c0 vma 0x10000
Loading section .data, size 0xc vma 0x114c0
Loading section .rodata, size 0x438 vma 0x114cc
hello

Program received signal SIGTRAP, Trace/breakpoint trap.
_exit (code=0 '\000') at crt0.c:113
crt0.c:113: No such file or directory.
(gdb) q
The program is running.  Quit anyway (and kill it)? (y or n) y
```

## Build a 32-bit gcc-2.95.3 compiler on x86-64

gcc-2.95.3 predates x86-64 support in gcc, so it must be built for 32-bit x86.
It also needs a private copy of binutils that defaults to 32-bit x86.

Please see [build-gcc295](https://github.com/mikpe/build-gcc295) for build instructions.

## Copyright

For the copyright of w1750, see `COPYING` and `README` in the `w1750` directory.

This README and subsequent changes to w1750 are

    Copyright (C) 2021-2022  Mikael Pettersson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
