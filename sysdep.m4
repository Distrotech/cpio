divert(-1)
# System dependent functions for GNU cpio.
#
# Copyright (C) 2007, 2010, 2014 Free Software Foundation, Inc.
# GNU cpio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU cpio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU cpiio.  If not, see <http://www.gnu.org/licenses/>.

undef(`include')

ifelse(MODE,`AC',`

define(`FUNCLIST')

define(`BEGIN')
define(`END',`divert(0)dnl
# -*- buffer-read-only: t -*- vi: set ro:
# THIS FILE IS GENERATED AUTOMATICALLY.  PLEASE DO NOT EDIT.
AC_DEFUN([CPIO_SYSDEP],[AC_CHECK_FUNCS([FUNCLIST])])')

dnl MAKESTUB(type, name, args...)
define(`MAKESTUB',`define(`FUNCLIST',FUNCLIST` $2')')

',MODE,`H',`
changecom(/*,*/)
define(`ROHEADER',`/* -*- buffer-read-only: t -*- vi: set ro:
   THIS FILE IS GENERATED AUTOMATICALLY.  PLEASE DO NOT EDIT.
*/')

define(`BEGIN')
define(`END')

dnl MAKESTUB(type, name, args...)
define(`MAKESTUB',`
`#ifndef HAVE_'translit($2, `a-z-', `A-Z_')
$1 $2 (ifelse($#,2,`void',`shift(shift($@))'));
#endif
')

divert(0)dnl
ROHEADER
',MODE,`C',`
changecom(/*,*/)
define(`ROHEADER',`/* -*- buffer-read-only: t -*- vi: set ro:
   THIS FILE IS GENERATED AUTOMATICALLY.  PLEASE DO NOT EDIT.
*/')

define(`BEGIN')
define(`END')

define(`__make_unused_args',`dnl
 $1 __attribute__ ((unused))dnl
 ifelse($#,1,,`, __make_unused_args(shift($@))')')

define(`__makeargs',`ifelse($1,`',`void',`__make_unused_args($@)')')

define(`INTRETVAL',-1)

dnl MAKESTUB(type, name, args...)
define(`MAKESTUB',`
`#ifndef HAVE_'translit($2, `a-z-', `A-Z_')
# warning "Providing stub placeholder for $2 function"
$1
$2 (__makeargs(shift(shift($@))))
{
  errno = ENOSYS;
  return ifelse($1,`int',INTRETVAL,NULL);
}
#endif`'dnl
define(`INTRETVAL',-1)dnl
')

divert(0)dnl
ROHEADER
')

