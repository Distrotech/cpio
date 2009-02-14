# This file is part of GNU cpio
# Copyright (C) 2003, 2004, 2007, 2009 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301 USA.

ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = gnits 1.8 dist-bzip2 std-options

SUBDIRS = doc headers gnu paxlib rmt src po tests

gen_start_date = 2008-03-07

.PHONY: make-ChangeLog
make-ChangeLog: 
	if test -d .git; then                                           \
	  $(top_srcdir)/build-aux/gitlog-to-changelog                   \
	    --since=$(gen_start_date) |                                 \
            sed '/<unknown>$$/d' | fmt -s > $(distdir)/cl-t;            \
	  cat ChangeLog.cvs | sed '/^Local Variables:/,/^End:/d'	\
		>> $(distdir)/cl-t;					\
	  echo "Local Variables:" >> $(distdir)/cl-t;                   \
	  echo "mode: change-log" >> $(distdir)/cl-t;                   \
	  echo "version-control: never"  >> $(distdir)/cl-t;            \
	  echo "buffer-read-only: t" >> $(distdir)/cl-t;                \
	  echo "End:" >> $(distdir)/cl-t;                               \
	  rm -f $(distdir)/ChangeLog;                                   \
	  mv $(distdir)/cl-t $(distdir)/ChangeLog;                      \
	fi

dist-hook: make-ChangeLog

.PHONY: ChangeLog
ChangeLog: 
	if test -d .git; then                                           \
	  $(top_srcdir)/build-aux/gitlog-to-changelog                   \
	    --since=$(gen_start_date) |                                 \
            sed '/<unknown>$$/d' | fmt -s > ChangeLog;                  \
	  cat ChangeLog.cvs | sed '/^Local Variables:/,/^End:/d'	\
		>> ChangeLog;						\
	  echo "Local Variables:" >> ChangeLog;                         \
	  echo "mode: change-log" >> ChangeLog;                         \
	  echo "version-control: never"  >> ChangeLog;                  \
	  echo "buffer-read-only: t" >> ChangeLog;                      \
	  echo "End:" >> ChangeLog;                                     \
        fi
