/* This file is part of GNU Radius.
   Copyright (C) 2000,2001,2002,2003 Free Software Foundation, Inc.

   Written by Sergey Poznyakoff
  
   GNU Radius is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  
   GNU Radius is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with GNU Radius; if not, write to the Free Software Foundation, 
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if defined(HAVE_SYS_ERRLIST)

#if !HAVE_DECL_SYS_ERRLIST
extern char *sys_errlist[];
#endif
#if !HAVE_DECL_SYS_NERR
extern int sys_nerr;
#endif

char *
strerror (int err)
{
  static char buf[80];

  if (err > sys_nerr)
    {
      sprintf(buf, _("error %d"), err);
      return buf;
    }
  return sys_errlist[err];
}

#else

char *
strerror (int err)
{
        static char buf[80];

        sprintf(buf, _("error %d"), err);
        return buf;
}

#endif /* HAVE_SYS_ERRLIST */


