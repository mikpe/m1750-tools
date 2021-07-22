/*
 * ANSI Standard C: 7.11.6.2
 * 
 * #include <string.h>
 * char *strerror (int errnum);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
 * European Space Agency contract 11935/96/NL/JG. Permission to use 
 * copy, modify, and distribute this software for any purpose without 
 * fee is hereby granted, provided that this entire notice is included 
 * in all copies of any software which is or includes a copy or 
 * modification of this software and in all copies of the supporting 
 * documentation for such software. This software is provided "as is", 
 * without any express or implied warranty. In particular, neither the 
 * author nor the European Space Agency makes any representation or 
 * warranty of any kind concerning the merchantability of this software 
 * or its fitness for any particular purpose. 
 *
 * $Log: strerror.c,v $
 * Revision 1.1  1997/05/09 16:59:19  nettleto
 * Initial revision
 *
 */

#include <string.h>

#include <errno.h>

char *
strerror (int errnum)
{
  char *error;

  switch (errnum)
    {
    case EPERM:
      error = "Not owner";
      break;
    case ENOENT:
      error = "No such file or directory";
      break;
    case ESRCH:
      error = "No such process";
      break;
    case EINTR:
      error = "Interrupted system call";
      break;
    case EIO:
      error = "I/O error";
      break;
    case ENXIO:
      error = "No such device or address";
      break;
    case E2BIG:
      error = "Arg list too long";
      break;
    case ENOEXEC:
      error = "Exec format error";
      break;
    case EBADF:
      error = "Bad file number";
      break;
    case ECHILD:
      error = "No children";
      break;
    case EAGAIN:
      error = "No more processes";
      break;
    case ENOMEM:
      error = "Not enough space";
      break;
    case EACCES:
      error = "Permission denied";
      break;
    case EFAULT:
      error = "Bad address";
      break;
    case ENOTBLK:
      error = "Block device required";
      break;
    case EBUSY:
      error = "Device or resource busy";
      break;
    case EEXIST:
      error = "File exists";
      break;
    case EXDEV:
      error = "Cross-device link";
      break;
    case ENODEV:
      error = "No such device";
      break;
    case ENOTDIR:
      error = "Not a directory";
      break;
    case EISDIR:
      error = "Is a directory";
      break;
    case EINVAL:
      error = "Invalid argument";
      break;
    case ENFILE:
      error = "Too many open files in system";
      break;
    case EMFILE:
      error = "Too many open files";
      break;
    case ENOTTY:
      error = "Not a character device";
      break;
    case ETXTBSY:
      error = "Text file busy";
      break;
    case EFBIG:
      error = "File too large";
      break;
    case ENOSPC:
      error = "No space left on device";
      break;
    case ESPIPE:
      error = "Illegal seek";
      break;
    case EROFS:
      error = "Read-only file system";
      break;
    case EMLINK:
      error = "Too many links";
      break;
    case EPIPE:
      error = "Broken pipe";
      break;
    case EDOM:
      error = "Math argument";
      break;
    case ERANGE:
      error = "Result too large";
      break;
    case ENOMSG:
      error = "No message of desired type";
      break;
    case EIDRM:
      error = "Identifier removed";
      break;
    case EDEADLK:
      error = "Deadlock";
      break;
    case ENOLCK:
      error = "No lock";
      break;
    case ENOSTR:
      error = "Not a stream";
      break;
    case ETIME:
      error = "Stream ioctl timeout";
      break;
    case ENOSR:
      error = "No stream resources";
      break;
    case ENONET:
      error = "Machine is not on the network";
      break;
    case ENOPKG:
      error = "No package";
      break;
    case EREMOTE:
      error = "Resource is remote";
      break;
    case ENOLINK:
      error = "Virtual circuit is gone";
      break;
    case EADV:
      error = "Advertise error";
      break;
    case ESRMNT:
      error = "Srmount error";
      break;
    case ECOMM:
      error = "Communication error";
      break;
    case EPROTO:
      error = "Protocol error";
      break;
    case EMULTIHOP:
      error = "Multihop attempted";
      break;
    case EBADMSG:
      error = "Bad message";
      break;
    case ELIBACC:
      error = "Cannot access a needed shared library";
      break;
    case ELIBBAD:
      error = "Accessing a corrupted shared library";
      break;
    case ELIBSCN:
      error = ".lib section in a.out corrupted";
      break;
    case ELIBMAX:
      error = "Attempting to link in more shared libraries than system limit";
      break;
    case ELIBEXEC:
      error = "Cannot exec a shared library directly";
      break;
    case ENOSYS:
      error = "Function not implemented";
      break;
    case ENMFILE:
      error = "No more files";
      break;
    case ENOTEMPTY:
      error = "Directory not empty";
      break;
    case ENAMETOOLONG:
      error = "File or path name too long";
      break;
    default:
      error = "";
      break;
    }

  return error;
}

