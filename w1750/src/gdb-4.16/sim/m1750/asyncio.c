/***************************************************************************/
/*                                                                         */
/* Project   :        sim1750 -- Mil-Std-1750 Software Simulator           */
/*                                                                         */
/* Component :         asyncio.c -- async I/O for MAS281                   */
/*                                                                         */
/* Copyright :         (C) ESA/ESTEC, 1997                                 */
/*                                                                         */
/* Author    :      Maurizio Martignano - ESA/ESTEC/WME                    */
/*                  Keplerlaan 1, 2200 AG Noordwijk, The Netherlands       */
/* Contact   :      maurizio@wm.estec.esa.nl                               */
/*                                                                         */
/* Disclaimer:                                                             */
/*                                                                         */
/*  This program is free software; you can redistribute it and/or modify   */
/*  it under the terms of the GNU General Public License as published by   */
/*  the Free Software Foundation; either version 2 of the License, or      */
/*  (at your option) any later version.                                    */
/*                                                                         */
/*  This program is distributed in the hope that it will be useful,        */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/*  GNU General Public License for more details.                           */
/*                                                                         */
/*  You should have received a copy of the GNU General Public License      */
/*  along with this program; if not, write to the Free Software            */
/*  Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.   */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
#ifdef UNIX
#include <fcntl.h>
#endif
#ifdef WIN32
#include <windows.h>
#endif

#ifdef WIN32
#define STK_SIZE 8192
HANDLE _io_rt;
int _io_ischar = 0;
void _io_reader(void);
#endif

int set_input(void);
void reset_input(int);
int nodelay_getchar(void);

// Set the standar input,
// when needed
int set_input(void)
{
#ifdef UNIX
  int stat;
  stat = fcntl(0, F_GETFL);
  fcntl(0, F_SETFL, O_NDELAY);
  return stat;
#endif
#ifdef WIN32
  DWORD rtid;

  _io_rt = CreateThread(0, STK_SIZE, (LPTHREAD_START_ROUTINE) _io_reader, NULL, 0, &rtid);
  if (_io_rt == NULL) {
    fprintf(stderr, "CreateThread failed.\n");
    exit(-1);
  }
  SuspendThread(_io_rt);
  SetThreadPriority(_io_rt, THREAD_PRIORITY_HIGHEST);
  ResumeThread(_io_rt);
  return 0;
#else
  return 0;
#endif
}

#ifdef WIN32
//
// Read a char from STDIN and suspend
//
void _io_reader(void)
{
  char ch;

  while (1) {
   if (_io_ischar == 0) {
     ch = getchar();
     ungetc(ch, stdin);
     _io_ischar = 1;
     SuspendThread(_io_rt);
     }
   }
}
#endif


// Reset the standard input,
// when needed
void reset_input(int stat)
{
#ifdef UNIX
  fcntl(0, F_SETFL, stat);
#endif

#ifdef WIN32
  SuspendThread(_io_rt);
  CloseHandle(_io_rt);
#endif
}

// Get a character from the standar input,
// without suspending
int nodelay_getchar(void)
{
  int res;
  char ch;


#ifdef UNIX
  res = read(0, &ch, 1);
  if (res > 0) {
    return (int) ch;
  } else {
    return 0;
  }
#endif

#ifdef WIN32
  if (_io_ischar == 1) {
    ch = getchar();
    _io_ischar = 0;
    ResumeThread(_io_rt);
    return (int) ch;
  } else {
    return 0;
  }
#endif
}

