/* mt -- control magnetic tape drive operation
   Copyright (C) 1991, 1992, 1995, 2001 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
   */


/* If -f is not given, the environment variable TAPE is used;
   if that is not set, a default device defined in sys/mtio.h is used.
   The device must be either a character special file or a remote
   tape drive with the form "[user@]system:path".
   The default count is 1.  Some operations ignore it.

   Exit status:
   0	success
   1	invalid operation or device name
   2	operation failed

   Operations (unique abbreviations are accepted):
   eof, weof	Write COUNT EOF marks at current position on tape.
   fsf		Forward space COUNT files.
		Tape is positioned on the first block of the file.
   bsf		Backward space COUNT files.
		Tape is positioned on the first block of the file.
   fsr		Forward space COUNT records.
   bsr		Backward space COUNT records.
   bsfm		Backward space COUNT file marks.
		Tape is positioned on the beginning-of-the-tape side of
		the file mark.
   asf		Absolute space to file number COUNT.
		Equivalent to rewind followed by fsf COUNT.
   eom		Space to the end of the recorded media on the tape
		(for appending files onto tapes).
   rewind	Rewind the tape.
   offline, rewoffl
		Rewind the tape and, if applicable, unload the tape.
   status	Print status information about the tape unit.
   retension	Rewind the tape, then wind it to the end of the reel,
		then rewind it again.
   erase	Erase the tape.

   David MacKenzie <djm@gnu.ai.mit.edu> */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#ifdef HAVE_SYS_MTIO_H
#ifdef HAVE_SYS_IO_TRIOCTL_H
#include <sys/io/trioctl.h>
#endif
#include <sys/mtio.h>
#endif
#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif
#include "rmt.h"

#if defined(HAVE_STRING_H) || defined(STDC_HEADERS)
#include <string.h>
#else
#include <strings.h>
#endif

#if defined(STDC_HEADERS)
#include <stdlib.h>
#else
extern int errno;
char *getenv ();
int atoi ();
void exit ();
#endif

int fstat ();

int argmatch ();
void check_type ();
void error ();
void invalid_arg ();
void perform_operation ();
void print_status ();
void usage ();

char *opnames[] =
{
  "eof", "weof", "fsf", "bsf", "fsr", "bsr",
  "rewind", "offline", "rewoffl", "eject", "status",
#ifdef MTBSFM
  "bsfm",
#endif
#ifdef MTEOM
  "eom",
#endif
#ifdef MTRETEN
  "retension",
#endif
#ifdef MTERASE
  "erase",
#endif
  "asf",
#ifdef MTFSFM
  "fsfm",
#endif
#ifdef MTSEEK
  "seek",
#endif
  NULL
};

#define MTASF 600		/* Random unused number.  */
short operations[] =
{
  MTWEOF, MTWEOF, MTFSF, MTBSF, MTFSR, MTBSR,
  MTREW, MTOFFL, MTOFFL, MTOFFL, MTNOP,
#ifdef MTBSFM
  MTBSFM,
#endif
#ifdef MTEOM
  MTEOM,
#endif
#ifdef MTRETEN
  MTRETEN,
#endif
#ifdef MTERASE
  MTERASE,
#endif
  MTASF,
#ifdef MTFSFM
  MTFSFM,
#endif
#ifdef MTSEEK
  MTSEEK,
#endif
  0
};

/* If nonzero, don't consider file names that contain a `:' to be
   on remote hosts; all files are local.  Always zero for mt;
   since when do local device names contain colons?  */
int f_force_local = 0;

struct option longopts[] =
{
  {"file", 1, NULL, 'f'},
  {"rsh-command", 1, NULL, 1},
  {"version", 0, NULL, 'V'},
  {"help", 0, NULL, 'H'},
  {NULL, 0, NULL, 0}
};

/* The name this program was run with.  */
char *program_name;

int
main (argc, argv)
     int argc;
     char **argv;
{
  extern char *version_string;
  short operation;
  int count;
  char *tapedev;
  int tapedesc;
  int i;
  char *rsh_command_option = NULL;

  program_name = argv[0];
  tapedev = NULL;
  count = 1;

  /* Debian hack: Fixed a bug in the -V flag.  This bug has been
     reported to "bug-gnu-utils@prep.ai.mit.edu".  -BEM */
  while ((i = getopt_long (argc, argv, "f:t:VH", longopts, (int *) 0)) != -1)
    {
      switch (i)
	{
	case 'f':
	case 't':
	  tapedev = optarg;
	  break;

	case 1:
	  rsh_command_option = optarg;
	  break;

	case 'V':
	  printf ("GNU mt %s", version_string);
	  exit (0);
	  break;

	case 'H':
	default:
	  usage (stdout, 0);
	}
    }

  if (optind == argc)
    usage (stderr, 1);

  i = argmatch (argv[optind], opnames);
  if (i < 0)
    {
      invalid_arg ("tape operation", argv[optind], i);
      exit (1);
    }
  operation = operations[i];

  if (++optind < argc)
    /* Debian hack: Replaced the atoi function call with strtol so
       that hexidecimal values can be used for the count parameter.
       This bug has been reported to "bug-gnu-utils@prep.ai.mit.edu".
       (97/12/5) -BEM */
#if defined(STDC_HEADERS)
    count = (int) strtol (argv[optind], NULL, 0);
#else
    count = atoi (argv[optind]);
#endif
  if (++optind < argc)
    usage (stderr, 1);

  if (tapedev == NULL)
    {
      tapedev = getenv ("TAPE");
      if (tapedev == NULL)
#ifdef DEFTAPE			/* From sys/mtio.h.  */
        tapedev = DEFTAPE;
#else
	error (1, 0, "no tape device specified");
#endif
    }

  if ( (operation == MTWEOF)
#ifdef MTERASE
       || (operation == MTERASE)
#endif
	)
    tapedesc = rmtopen (tapedev, O_WRONLY, 0, rsh_command_option);
  else
    tapedesc = rmtopen (tapedev, O_RDONLY, 0, rsh_command_option);
  if (tapedesc == -1)
    error (1, errno, "%s", tapedev);
  check_type (tapedev, tapedesc);

  if (operation == MTASF)
    {
      perform_operation (tapedev, tapedesc, MTREW, 1);
      operation = MTFSF;
    }
  perform_operation (tapedev, tapedesc, operation, count);
  if (operation == MTNOP)
    print_status (tapedev, tapedesc);

  if (rmtclose (tapedesc) == -1)
    error (2, errno, "%s", tapedev);

  exit (0);
}

void
check_type (dev, desc)
     char *dev;
     int desc;
{
  struct stat stats;

  if (_isrmt (desc))
    return;
  if (fstat (desc, &stats) == -1)
    error (1, errno, "%s", dev);
  if ((stats.st_mode & S_IFMT) != S_IFCHR)
    error (1, 0, "%s is not a character special file", dev);
}

void
perform_operation (dev, desc, op, count)
     char *dev;
     int desc;
     short op;
     int count;
{
  struct mtop control;

  control.mt_op = op;
  control.mt_count = count;
  /* Debian hack: The rmtioctl function returns -1 in case of an
     error, not 0.  This bug has been reported to
     "bug-gnu-utils@prep.ai.mit.edu".  (96/7/10) -BEM */
  if (rmtioctl (desc, MTIOCTOP, &control) == -1)
    error (2, errno, "%s", dev);
}

void
print_status (dev, desc)
     char *dev;
     int desc;
{
  struct mtget status;

  if (rmtioctl (desc, MTIOCGET, &status) == -1)
    error (2, errno, "%s", dev);

  printf ("drive type = %d\n", (int) status.mt_type);
#if defined(hpux) || defined(__hpux)
  printf ("drive status (high) = %d\n", (int) status.mt_dsreg1);
  printf ("drive status (low) = %d\n", (int) status.mt_dsreg2);
#else
  printf ("drive status = %d\n", (int) status.mt_dsreg);
#endif
  printf ("sense key error = %d\n", (int) status.mt_erreg);
  printf ("residue count = %d\n", (int) status.mt_resid);
#if !defined(ultrix) && !defined(__ultrix__) && !defined(hpux) && !defined(__hpux) && !defined(__osf__)
  printf ("file number = %d\n", (int) status.mt_fileno);
  printf ("block number = %d\n", (int) status.mt_blkno);
#endif
}

void
usage (fp, status)
  FILE *fp;
  int status;
{
  fprintf (fp, "\
Usage: %s [-V] [-f device] [--file=device] [--rsh-command=command]\n\
\t[--help] [--version] operation [count]\n",
	   program_name);
  exit (status);
}
