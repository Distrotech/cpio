/* System dependent functions for GNU cpio.

   Copyright (C) 2007, 2010, 2014 Free Software Foundation, Inc.

   GNU cpio is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GNU cpio is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GNU cpiio.  If not, see <http://www.gnu.org/licenses/>. */

ifelse(MODE,`C',`
#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <unistd.h>
#include <errno.h>
',MODE,`H',`
#ifdef HAVE_PROCESS_H
# include <process.h>
#endif

#ifndef HAVE_PWD_H
/* Borrowed from GNU libc */
/* The passwd structure.  */
struct passwd
{
  char *pw_name;		/* Username.  */
  char *pw_passwd;		/* Password.  */
  int pw_uid;			/* User ID.  */
  int pw_gid;			/* Group ID.  */
  char *pw_gecos;		/* Real name.  */
  char *pw_dir;			/* Home directory.  */
  char *pw_shell;		/* Shell program.  */
};
#endif
#ifndef HAVE_GRP_H
/* Borrowed from GNU libc */
/* The group structure.	 */
struct group
  {
    char *gr_name;		/* Group name.	*/
    char *gr_passwd;		/* Password.	*/
    int gr_gid;			/* Group ID.	*/
    char **gr_mem;		/* Member list.	*/
  };
#endif

#include <signal.h>
#ifndef SIGPIPE
# define SIGPIPE -1
#endif

')

BEGIN
MAKESTUB(struct passwd *, getpwuid, uid_t uid)
MAKESTUB(struct passwd *, getpwnam, const char *name)
MAKESTUB(struct group *, getgrgid, gid_t gid)
MAKESTUB(struct group *, getgrnam, const char *name)
MAKESTUB(int, pipe, int filedes[2])
MAKESTUB(int, fork)

define([INTRETVAL],0)
MAKESTUB(int, getuid)

define([INTRETVAL],0)
MAKESTUB(int, geteuid)

define([INTRETVAL],0)
MAKESTUB(int, getgid)

MAKESTUB(int, setuid, int newuid)
MAKESTUB(int, setgid, int newgid)
MAKESTUB(int, mknod, const char *filename, int mode, int dev)
MAKESTUB(int, symlink, const char *oldname, const char *newname)
MAKESTUB(int, link, const char *oldname, const char *newname)
MAKESTUB(int, chown, const char *filename, int owner, int group)
END
