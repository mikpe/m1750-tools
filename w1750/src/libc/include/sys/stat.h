/*
 * m1750-coff/include/sys/stat.h
 *
 * GCC-1750 system header file:  
 *
 * Copyright (c) 1996, Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose,
 * provided that existing copyright notices are retained in all copies
 * and that this notice is included verbatim in any distributions. No
 * written agreement, license, or royalty fee is required for any of the
 * authorized uses. Modifications to this software may be copyrighted by
 * their authors and need not follow the licensing terms described here,
 * provided that the new terms are clearly indicated on the first page
 * of each file where they apply.
 *
 * $log$
 */

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <time.h>
#include <sys/types.h>

struct  stat 
{
  dev_t  st_dev;
  ino_t  st_ino;
  mode_t st_mode;
  short  st_nlink;
  uid_t  st_uid;
  gid_t  st_gid;
  dev_t  st_rdev;
  off_t  st_size;
  time_t st_atime;
  int    st_spare1;
  time_t st_mtime;
  int    st_spare2;
  time_t st_ctime;
  int    st_spare3;
  long   st_blksize;
  long   st_blocks;
  long   st_spare4[2];
};

#define _IFMT   0170000  /* type of file */
#define _IFDIR  0040000  /* directory */
#define _IFCHR  0020000  /* character special */
#define _IFBLK  0060000  /* block special */
#define _IFREG  0100000  /* regular */
#define _IFLNK  0120000  /* symbolic link */
#define _IFSOCK 0140000  /* socket */
#define _IFIFO  0010000  /* fifo */

#define S_BLKSIZE 1024 /* size of a block */

#define S_ISUID  0004000  /* set user id on execution */
#define S_ISGID  0002000  /* set group id on execution */
#ifndef  _POSIX_SOURCE
#define S_ISVTX  0001000  /* save swapped text even after use */
#define S_IREAD  0000400  /* read permission, owner */
#define S_IWRITE 0000200  /* write permission, owner */
#define S_IEXEC  0000100  /* execute/search permission, owner */

#define S_ENFMT   0002000  /* enforcement-mode locking */

#define S_IFMT   _IFMT
#define S_IFDIR  _IFDIR
#define S_IFCHR  _IFCHR
#define S_IFBLK  _IFBLK
#define S_IFREG  _IFREG
#define S_IFLNK  _IFLNK
#define S_IFSOCK _IFSOCK
#define S_IFIFO  _IFIFO
#endif  /* !_POSIX_SOURCE */

#define S_IRWXU 0000700  /* rwx, owner */
#define S_IRUSR 0000400  /* read permission, owner */
#define S_IWUSR 0000200  /* write permission, owner */
#define S_IXUSR 0000100  /* execute/search permission, owner */
#define S_IRWXG 0000070  /* rwx, group */
#define S_IRGRP 0000040  /* read permission, group */
#define S_IWGRP 0000020  /* write permission, grougroup */
#define S_IXGRP 0000010  /* execute/search permission, group */
#define S_IRWXO 0000007  /* rwx, other */
#define S_IROTH 0000004  /* read permission, other */
#define S_IWOTH 0000002  /* write permission, other */
#define S_IXOTH 0000001  /* execute/search permission, other */

#define S_ISBLK(m)  (((m)&_IFMT) == _IFBLK)
#define S_ISCHR(m)  (((m)&_IFMT) == _IFCHR)
#define S_ISDIR(m)  (((m)&_IFMT) == _IFDIR)
#define S_ISFIFO(m) (((m)&_IFMT) == _IFIFO)
#define S_ISREG(m)  (((m)&_IFMT) == _IFREG)
#define S_ISLNK(m)  (((m)&_IFMT) == _IFLNK)
#define S_ISSOCK(m) (((m)&_IFMT) == _IFSOCK)

int chmod (const char *_path, mode_t _mode);
int fstat (int _fd, struct stat *_sbuf);
int mkdir (const char *_path, mode_t _mode);
int mkfifo (char *_path, mode_t _mode);
int stat (const char *_path, struct stat *_sbuf);
mode_t umask (mode_t _mask);


__END_DECLS

#endif /* not _SYS_STAT_H_ */

