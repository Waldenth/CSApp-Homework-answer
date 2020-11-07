	.file	"bufferoverflow.c"
	.text
	.globl	gets
	.def	gets;	.scl	2;	.type	32;	.endef
	.seh_proc	gets
gets:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rcx, %rsi
	movq	%rcx, %rbx
.L2:
	call	getchar
	cmpl	$10, %eax
	je	.L3
	cmpl	$-1, %eax
	je	.L3
	movb	%al, (%rbx)
	leaq	1(%rbx), %rbx
	jmp	.L2
.L3:
	cmpl	$-1, %eax
	sete	%dl
	cmpq	%rsi, %rbx
	sete	%al
	testb	%al, %dl
	jne	.L6
	movb	$0, (%rbx)
	movq	%rsi, %rax
.L1:
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	ret
.L6:
	movl	$0, %eax
	jmp	.L1
	.seh_endproc
	.globl	echo
	.def	echo;	.scl	2;	.type	32;	.endef
	.seh_proc	echo
echo:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	leaq	40(%rsp), %rbx
	movq	%rbx, %rcx
	call	gets
	movq	%rbx, %rcx
	call	puts
	nop
	addq	$48, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.globl	test
	.def	test;	.scl	2;	.type	32;	.endef
	.seh_proc	test
test:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movabsq	$2338328219631577172, %rax
	movq	%rax, 32(%rsp)
	movabsq	$7022364302207313268, %rax
	movq	%rax, 40(%rsp)
	movw	$27491, 48(%rsp)
	movb	$0, 50(%rsp)
	leaq	32(%rsp), %rbx
	movq	%rbx, %rcx
	call	puts
	call	echo
	movq	%rbx, %rcx
	call	puts
	nop
	addq	$64, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	call	test
	movl	$0, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	getchar;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
