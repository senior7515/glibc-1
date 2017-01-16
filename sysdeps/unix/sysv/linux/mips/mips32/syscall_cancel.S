/* Cancellable syscall wrapper.  Linux/mips32 version.
   Copyright (C) 2017 Free Software Foundation, Inc.
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

#include <sysdep.h>
#include <sys/asm.h>

/* long int __syscall_cancel_arch (int *cancelhandling,
				   long int nr,
				   long int arg1,
				   long int arg2,
				   long int arg3,
				   long int arg4,
				   long int arg5,
				   long int arg6)  */

#define FRAME_SIZE 48

NESTED (__syscall_cancel_arch, FRAME_SIZE, fp)
	.mask	0xc0030000,-SZREG
	.fmask	0x00000000,0

	PTR_ADDIU sp, -FRAME_SIZE
	cfi_def_cfa_offset (FRAME_SIZE)

	sw	fp,40(sp)
	cfi_offset (30, -8)
	move	fp,sp
	cfi_def_cfa_register (30)
	sw	ra,44(sp)
	sw	s1,36(sp)
	sw	s0,32(sp)
#ifdef __PIC__
	.cprestore
#endif
	cfi_offset (31, -4)
	cfi_offset (17, -12)
	cfi_offset (16, -16)
	cfi_def_cfa_register (30)

	.globl __syscall_cancel_arch_start
__syscall_cancel_arch_start:

	lw	v0,0(a0)
	andi	v0,v0,0x4
	bne	v0,zero,2f

	addiu	sp,sp,-16
	addiu	v0,sp,16
	sw	v0,24(fp)

	move	s0,a1
	move	a0,a2
	move	a1,a3
	lw	a2,64(fp)
	lw	a3,68(fp)
	lw	v0,72(fp)
	lw	s1,76(fp)

	.set	noreorder
	subu	sp, 32
	sw	v0, 16(sp)
	sw	s1, 20(sp)
	move	v0, $16
	syscall

	.globl __syscall_cancel_arch_end
__syscall_cancel_arch_end:
	addiu	sp, 32
	.set	reorder

	beq	a3,zero,1f
	subu	v0,zero,v0
1:
	move	sp,fp
	cfi_remember_state
	cfi_def_cfa_register (29)
	lw	ra,44(fp)
	lw	fp,40(sp)
	lw	s1,36(sp)
	lw	s0,32(sp)
	.set	noreorder
	.set	nomacro
	jr	ra
	addiu	sp,sp,48

	.set	macro
	.set	reorder

	cfi_def_cfa_offset (0)
	cfi_restore (16)
	cfi_restore (17)
	cfi_restore (30)
	cfi_restore (31)

2:
	cfi_restore_state
#ifdef __PIC__
	PTR_LA	t9, __syscall_do_cancel
	jr	t9
#else
	j	__syscall_do_cancel
#endif

END (__syscall_cancel_arch)
libc_hidden_def (__syscall_cancel_arch)
