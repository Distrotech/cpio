# This file is part of GNU cpio
# Copyright (C) 2003 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  

AUTOMAKE_OPTIONS = gnits 1.7.1 dist-bzip2 std-options

bin_PROGRAMS=cpio @CPIO_MT_PROG@
libexec_PROGRAMS=@CPIO_RMT_PROG@
EXTRA_PROGRAMS=mt rmt

cpio_SOURCES = \
 copyin.c\
 copyout.c\
 copypass.c\
 defer.c\
 dstring.c\
 global.c\
 main.c\
 tar.c\
 util.c\
 error.c\
 filemode.c\
 dirname.c\
 idcache.c\
 makepath.c\
 xmalloc.c\
 stripslash.c\
 userspec.c\
 xstrdup.c

noinst_HEADERS =\
 cpio.h\
 cpiohdr.h\
 tar.h\
 tarhdr.h\
 defer.h\
 dstring.h\
 extern.h\
 filetypes.h\
 system.h\
 rmt.h\
 safe-stat.h\
 fnmatch.h\
 getopt.h

cpio_LDADD = @LIBOBJS@

mt_SOURCES = \
 mt.c argmatch.c
mt_LDADD = @LIBOBJS@

rmt_SOURCES = rmt.c
rmt_LDADD = @LIBOBJS@

EXTRA_DIST=\
 getopt.c\
 getopt1.c\
 bcopy.c\
 fnmatch.c\
 mkdir.c\
 strdup.c
