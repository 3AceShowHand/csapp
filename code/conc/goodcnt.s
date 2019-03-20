	.file	"goodcnt.c"
	.text
	.globl	thread
	.type	thread, @function
thread:
.LFB92:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	(%rdi), %ebp
	testl	%ebp, %ebp
	jle	.L2
	movl	$0, %ebx
.L3:
	movl	$mutex, %edi
	call	P
	movq	cnt(%rip), %rax
	addq	$1, %rax
	movq	%rax, cnt(%rip)
	movl	$mutex, %edi
	call	V
	addl	$1, %ebx
	cmpl	%ebx, %ebp
	jne	.L3
.L2:
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
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
	je	.L7
	movq	(%rsi), %rdx
	movl	$.LC0, %esi
	movl	$1, %edi
	call	__printf_chk
	movl	$0, %edi
	call	exit
.L7:
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movl	%eax, 4(%rsp)
	movl	$1, %edx
	movl	$0, %esi
	movl	$mutex, %edi
	call	Sem_init
	leaq	4(%rsp), %rcx
	movl	$thread, %edx
	movl	$0, %esi
	leaq	8(%rsp), %rdi
	call	Pthread_create
	leaq	4(%rsp), %rcx
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
	movl	4(%rsp), %eax
	addl	%eax, %eax
	cltq
	cmpq	%rdx, %rax
	je	.L8
	movq	cnt(%rip), %rdx
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	jmp	.L9
.L8:
	movq	cnt(%rip), %rdx
	movl	$.LC2, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
.L9:
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE91:
	.size	main, .-main
	.comm	mutex,32,32
	.globl	cnt
	.bss
	.align 8
	.type	cnt, @object
	.size	cnt, 8
cnt:
	.zero	8
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
