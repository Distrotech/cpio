# Makefile for GNU cpio library.

# Copyright (C) 2004, 2005 Free Software Foundation, Inc.

## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
## 02110-1301, USA.

include gnulib.mk

noinst_HEADERS += \
 paxlib.h\
 rmt.h\
 rmt-command.h\
 system-ioctl.h\
 system.h

libcpio_a_SOURCES += \
 fatal.c\
 paxerror.c\
 paxexit.c\
 paxlib.h\
 paxnames.c\
 rtapelib.c

DISTCLEANFILES += rmt-command.h
rmt-command.h: Makefile
	echo '#define LOCALEDIR "$(localedir)"' >$@
	echo "#ifndef DEFAULT_RMT_COMMAND" >> $@
	echo "# define DEFAULT_RMT_COMMAND \"$(DEFAULT_RMT_DIR)/`echo \"rmt\" | sed 's,^.*/,,;$(transform)'`$(EXEEXT)\"" >> $@
	echo "#endif" >> $@

BUILT_SOURCES += rmt-command.h
CLEANFILES += rmt-command.h

libcpio_a_LIBADD += $(LIBOBJS)
libcpio_a_DEPENDENCIES += $(LIBOBJS)
