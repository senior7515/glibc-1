/* Copyright (C) 2005-2017 Free Software Foundation, Inc.
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
#ifndef __ASSEMBLER__
# include <nptl/pthreadP.h>
#endif

#if IS_IN (libc) || IS_IN (libpthread) || IS_IN (librt)

# if IS_IN (libpthread)
#  define __local_multiple_threads __pthread_multiple_threads
# elif IS_IN (libc)
#  define __local_multiple_threads __libc_multiple_threads
# elif IS_IN (librt)
#  define __local_multiple_threads __librt_multiple_threads
# else
#  error Unsupported library
# endif

# define SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)

#else

/* This code should never be used but we define it anyhow.  */
# define SINGLE_THREAD_P (1)
# define NO_CANCELLATION 1

#endif
/* IS_IN (libc) || IS_IN (libpthread) || IS_IN (librt) */

#define RTLD_SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)
