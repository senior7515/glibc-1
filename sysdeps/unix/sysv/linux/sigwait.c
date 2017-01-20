/* Copyright (C) 1997-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <signal.h>
#define __need_NULL
#include <stddef.h>
#include <string.h>

#include <nptl/pthreadP.h>
#include <sysdep-cancel.h>
#include <sys/syscall.h>

#ifdef __NR_rt_sigtimedwait

/* Return any pending signal or wait for one for the given time.  */
int
__sigwait (const sigset_t *set, int *sig)
{
  siginfo_t si;
  if (__sigtimedwait (set, &si, NULL) < 0)
    return -1;
  *sig = si.si_signo;
  return 0;
}
libc_hidden_def (__sigwait)
weak_alias (__sigwait, sigwait)
#else
# include <sysdeps/posix/sigwait.c>
#endif
strong_alias (__sigwait, __libc_sigwait)
