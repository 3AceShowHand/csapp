	.file	"badcnt.c"
	.text
	.globl	thread
	.type	thread, @function
thread:
.LFB92:
	.cfi_startproc
	movq	(%rdi), %rcx
	testq	%rcx, %rcx
	jle	.L2
	movl	$0, %edx
.L3:
	movq	cnt(%rip), %rax
	addq	$1, %rax
	movq	%rax, cnt(%rip)
	addq	$1, %rdx
	cmpq	%rdx, %rcx
	jne	.L3
.L2:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE92:
	.size	thread, .-thread
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"usage: %s <niters>\n"
.LC1:
	.string	"BOOM! cnt=%ld\n"
.LC2:
	.string	"OK cnt=%ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB91:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpl	$2, %edi
	je	.L6
	movq	(%rsi), %rdx
	movl	$.LC0, %esi
	movl	$1, %edi
	call	__printf_chk
	movl	$0, %edi
	call	exit
.L6:
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	cltq
	movq	%rax, (%rsp)
	movq	%rsp, %rcx
	movl	$thread, %edx
	movl	$0, %esi
	leaq	8(%rsp), %rdi
	call	Pthread_create
	movq	%rsp, %rcx
	movl	$thread, %edx
	movl	$0, %esi
	leaq	16(%rsp), %rdi
	call	Pthread_create
	movl	$0, %esi
	movq	8(%rsp), %rdi
	call	Pthread_join
	movl	$0, %esi
	movq	16(%rsp), %rdi
	call	Pthread_join
	movq	cnt(%rip), %rdx
	movq	(%rsp), %rax
	addq	%rax, %rax
	cmpq	%rdx, %rax
	je	.L7
	movq	cnt(%rip), %rdx
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	jmp	.L8
.L7:
	movq	cnt(%rip), %rdx
	movl	$.LC2, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
.L8:
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE91:
	.size	main, .-main
	.globl	cnt
	.bss
	.align 8
	.type	cnt, @object
	.size	cnt, 8
cnt:
	.zero	8
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
