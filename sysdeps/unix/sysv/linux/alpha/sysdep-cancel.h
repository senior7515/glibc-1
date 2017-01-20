/* Copyright (C) 2003-2017 Free Software Foundation, Inc.
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
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <sysdep.h>
#include <tls.h>
#include <nptl/pthreadP.h>

#if IS_IN (libc) || IS_IN (libpthread) || IS_IN (librt)

# if IS_IN (libpthread)
#  define __local_multiple_threads	__pthread_multiple_threads
# elif IS_IN (libc)
#  define __local_multiple_threads	__libc_multiple_threads
# endif

# if IS_IN (libpthread) || IS_IN (libc)
extern int __local_multiple_threads attribute_hidden;
#  define SINGLE_THREAD_P \
	__builtin_expect (__local_multiple_threads == 0, 1)
# else
#  define SINGLE_THREAD_P \
	__builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)
# endif

#else

# define SINGLE_THREAD_P (1)
# define NO_CANCELLATION 1

#endif

# define RTLD_SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)

static inline
uintptr_t __pthread_get_pc (const struct ucontext *uc)
{
  return uc->uc_mcontext.sc_pc;
}
