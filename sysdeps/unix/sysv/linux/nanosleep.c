/* Copyright (C) 2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

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

#include <time.h>
#include <sysdep-cancel.h>

/* Pause execution for a number of nanoseconds.  */
int
__nanosleep (const struct timespec *requested_time,
	     struct timespec *remaining)
{
  return SYSCALL_CANCEL (nanosleep, requested_time, remaining);
}
libc_hidden_def (__nanosleep)
weak_alias (__nanosleep, nanosleep)