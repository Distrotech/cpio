dnl Process this file with autoconf to produce a configure script.
dnl This file is part of GNU cpio
dnl Copyright (C) 2003, 2004, 2005 Free Software Foundation, Inc.
dnl
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2, or (at your option)
dnl any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

AC_INIT([GNU cpio], [2.7], [bug-cpio@gnu.org], [cpio])
AC_CONFIG_SRCDIR(src/cpio.h)
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

AC_PREREQ([2.59])

dnl Check for programs
gl_USE_SYSTEM_EXTENSIONS
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_C_PROTOTYPES

AC_SYS_LARGEFILE

AC_TYPE_SIGNAL
AC_HEADER_MAJOR
AC_C_CONST
AC_TYPE_UID_T
AC_CHECK_TYPE(gid_t, int)
AC_HEADER_STDC
AC_HEADER_DIRENT

cpio_GNULIB
cpio_PAXUTILS

AC_SUBST(CPIO_MT_PROG)

AC_ARG_ENABLE(mt,
 AC_HELP_STRING([--enable-mt], [Enable building of mt program]),
 [case $enableval in
  yes) CPIO_MT_PROG='mt$(EXEEXT)';;
  no)  ;;
  esac])

AC_CHECK_HEADERS(unistd.h stdlib.h string.h fcntl.h sys/io/trioctl.h utmp.h getopt.h locale.h libintl.h sys/wait.h utime.h locale.h)
AC_REPLACE_FUNCS(bcopy mkdir strdup strerror)

AC_MSG_CHECKING(for sys_errlist and sys_nerr)
AC_TRY_RUN(
extern char *sys_errlist[[]];
extern int sys_nerr;
main() { char *s = sys_errlist[[0]]; return 0; },
        AC_DEFINE(HAVE_SYS_ERRLIST,1,
                  [Define if your system has sys_errlist global variable])
        AC_MSG_RESULT(yes),
        AC_MSG_RESULT(no),
        AC_MSG_RESULT(don't know))

AC_CHECK_DECLS([errno, sys_nerr, sys_errlist, getpwnam, getgrnam, getgrgid, strdup, strerror, getenv, atoi, exit], , , [
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <pwd.h>
#include <grp.h>])

dnl Checks for fnmatch
have_fnmatch=no
AC_MSG_CHECKING(for working fnmatch)
dnl Some versions of Solaris have a fnmatch() function, but it doesn't work!
dnl So we run a test program.  If we're cross-compiling, do it the old way.
AC_TRY_RUN([
main() {
if (fnmatch ("a*", "abc", 0) == 0) return 0;
else return 1; }],
have_fnmatch=yes, have_fnmatch=no, have_fnmatch=no)
if test $have_fnmatch = yes ; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_LIBOBJ(fnmatch)
  AC_CONFIG_LINKS(src/fnmatch.h:headers/fnmatch.h)
fi

AC_CHECK_FUNCS(lchown endpwent endgrent)
AC_FUNC_VPRINTF
AC_FUNC_ALLOCA

# Gettext.
AM_GNU_GETTEXT([external], [need-formatstring-macros])
AM_GNU_GETTEXT_VERSION(0.15)

# Initialize the test suite.
AC_CONFIG_TESTDIR(tests)
AC_CONFIG_FILES([tests/Makefile tests/atlocal]) # FIXME: tests/preset?
AM_MISSING_PROG([AUTOM4TE], [autom4te])

AC_CONFIG_FILES([Makefile
 doc/Makefile
 headers/Makefile
 lib/Makefile
 rmt/Makefile
 src/Makefile
 po/Makefile.in])
AC_OUTPUT
