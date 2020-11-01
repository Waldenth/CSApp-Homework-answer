	.file	"store_iprod.c"
	.text
	.globl	store_iprod
	.def	store_iprod;	.scl	2;	.type	32;	.endef
	.seh_proc	store_iprod
store_iprod:
	.seh_endprologue
	movq	%rdx, %rax;rax存储x
	mulq	%r8		;rdx:rax存储r8*rax的结果
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx) ; 很显然rcx存储的是dest指针,由于小端法,高8字节(*dest+8开始)存储的是128位结果的高位
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
