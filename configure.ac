dnl Process this file with autoconf to produce a configure script.
dnl This file is part of GNU cpio
dnl Copyright (C) 2003, 2004 Free Software Foundation, Inc.
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
dnl You should have received a copy of the GNU General Public License along
dnl with this program; if not, write to the Free Software Foundation, Inc.,
dnl 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  

AC_INIT([GNU cpio], [2.5.90], [bug-cpio@gnu.org], [cpio])
AC_CONFIG_SRCDIR(src/cpio.h)
AC_CONFIG_AUX_DIR([scripts])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

AC_PREREQ(2.54)

dnl Check for programs
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
AC_PROG_INSTALL

AC_AIX
AC_MINIX
AC_ISC_POSIX

AC_SYS_LARGEFILE

AC_TYPE_SIGNAL
AC_HEADER_MAJOR
AC_C_CONST
AC_TYPE_UID_T
AC_CHECK_TYPE(gid_t, int)
AC_HEADER_STDC
AC_HEADER_DIRENT

AC_SUBST(CPIO_MT_PROG)
AC_SUBST(CPIO_RMT_PROG)

AC_CHECKING(for remote tape and socket header files)
AC_CHECK_HEADER(sys/mtio.h,
[AC_DEFINE(HAVE_SYS_MTIO_H,1,[Define if you have working sys/mtio.h])
 CPIO_MT_PROG="mt"
 AC_TRY_CPP([
#include <sgtty.h>
#include <sys/socket.h>],
             CPIO_RMT_PROG="rmt")])

AC_CHECKING(for remote shell)
if test -f /usr/ucb/rsh || test -f /usr/bin/remsh || test -f /usr/bin/rsh ||
  test -f /usr/bsd/rsh || test -f /usr/bin/nsh; then
  AC_LIBOBJ(rtapelib)
else
  AC_CHECK_HEADER(netdb.h,
                 [AC_DEFINE(HAVE_NETDB_H,1,[Define if you have netbd.h])
                  AC_LIBOBJ(rtapelib)],
                 AC_DEFINE(NO_REMOTE,1,[Define if rmt is not needed]))
fi

AC_CHECK_HEADERS(unistd.h stdlib.h string.h fcntl.h sys/io/trioctl.h utmp.h getopt.h locale.h libintl.h)
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
dnl Some versions of Soalris have a fnmatch() function, but it doesn't work!
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
AC_CHECK_LIB(nsl, gethostname, [LIBS="$LIBS -lnsl"])
AC_CHECK_LIB(socket, setsockopt, [LIBS="$LIBS -lsocket"])

AC_TRY_RUN([
#include <unistd.h>
#ifdef HAVE_GETOPT_H
# include <getopt.h>
#endif

struct option longopt[] = {
	"help",    no_argument,       0, 'h',
        (char*)0
};

main(argc, argv)
int argc; char **argv;
{
	getopt_long_only(argc, argv, "h", longopt, (int*)0);
	return 0;
}],
   cpio_cv_have_gnu_getopt=yes,
   cpio_cv_have_gnu_getopt=no,
   cpio_cv_have_gnu_getopt=no)

if test x"$cpio_cv_have_gnu_getopt" != xyes ; then
   AC_CONFIG_LINKS(src/getopt.h:headers/getopt.h)
   AC_LIBOBJ(getopt)
   AC_LIBOBJ(getopt1)
fi

USE_INCLUDED_ARGP=
AC_ARG_WITH([included-argp],
            AC_HELP_STRING([--with-included-argp],
                           [Use included argp library]),
            [USE_INCLUDED_ARGP=${withval}],
            [AC_CHECK_HEADER(argp.h,
                             [AC_CHECK_FUNCS(argp_parse, :,
                                             [USE_INCLUDED_ARGP=yes])],
                             [USE_INCLUDED_ARGP=yes])])

if test "$USE_INCLUDED_ARGP" = yes; then
       AC_LIBOBJ(argp-ba)
       AC_LIBOBJ(argp-eexst)
       AC_LIBOBJ(argp-fmtstream)
       AC_LIBOBJ(argp-fs-xinl)
       AC_LIBOBJ(argp-help)
       AC_LIBOBJ(argp-parse)
       AC_LIBOBJ(argp-pv)
       AC_LIBOBJ(argp-pvh)
       AC_LIBOBJ(argp-xinl)
       AC_LIBOBJ(pin)
       AC_CONFIG_LINKS(src/argp.h:headers/argp.h)
fi

save_CPPFLAGS=$CPPFLAGS
CPPFLAGS="$CPPFLAGS -Isrc"
AC_MSG_CHECKING(whether extern program_invocation_name is present)
AC_TRY_COMPILE([#include <argp.h>
#include <errno.h>],
[ program_invocation_name = "test"; ],
[AC_DEFINE(PROGRAM_INVOCATION_NAME_DECLARED,1,
           [Define if program_invocation_name is declared in argp.h])
 AC_MSG_RESULT(yes)],
[AC_MSG_RESULT(no)])

AH_BOTTOM([
#ifndef PROGRAM_INVOCATION_NAME_DECLARED
extern char *program_invocation_short_name;
extern char *program_invocation_name;
#endif])

AC_MSG_CHECKING(whether program_invocation_name is declared)
AC_TRY_COMPILE([#include <argp.h>
#include <errno.h>],
[
#ifndef PROGRAM_INVOCATION_NAME_DECLARED
	extern char *program_invocation_name;
#endif
	program_invocation_name = "test";
],
[AC_DEFINE(HAVE_PROGRAM_INVOCATION_NAME,1,
           [Define if the variable program_invocation_name exists])
 AC_MSG_RESULT(yes)],
[AC_MSG_RESULT(no)])
CPPFLAGS=$save_CPPFLAGS

# Gettext.
AM_GNU_GETTEXT([external], [need-ngettext])
AM_GNU_GETTEXT_VERSION(0.13)

AH_BOTTOM([
#include "gettext.h"
#define _(s) gettext(s)
#define N_(s) gettext_noop(s)
])

AC_CONFIG_FILES([Makefile
 doc/Makefile
 headers/Makefile
 src/Makefile
 po/Makefile.in])
AC_OUTPUT
