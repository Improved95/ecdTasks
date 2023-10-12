swap:
        movl    (%rdi), %eax
        movl    (%rsi), %edx
        movl    %edx, (%rdi)
        movl    %eax, (%rsi)
        ret
.LC4:
        .string "%d "
main:
        pushq   %rbp
        movl    $400, %edi
        pushq   %rbx
        subq    $8, %rsp
        call    malloc
        movdqa  .LC0(%rip), %xmm1
        movdqa  .LC1(%rip), %xmm5
        movdqa  .LC2(%rip), %xmm4
        movq    %rax, %r8
        movq    %rax, %rbp
        leaq    400(%rax), %rbx
        movdqa  .LC3(%rip), %xmm3
.L4:
        movdqa  %xmm1, %xmm0
        addq    $16, %rax
        paddq   %xmm5, %xmm1
        movdqa  %xmm0, %xmm2
        paddq   %xmm4, %xmm2
        shufps  $136, %xmm2, %xmm0
        movdqa  %xmm3, %xmm2
        psubd   %xmm0, %xmm2
        movups  %xmm2, -16(%rax)
        cmpq    %rbx, %rax
        jne     .L4
        movl    $99, %edi
        leaq    396(%r8), %rsi
.L5:
        movq    %r8, %rax
.L7:
        movq    (%rax), %xmm0
        pshufd  $0xe5, %xmm0, %xmm6
        movd    %xmm0, %ecx
        movd    %xmm6, %edx
        cmpl    %edx, %ecx
        jle     .L6
        pshufd  $225, %xmm0, %xmm0
        movq    %xmm0, (%rax)
.L6:
        addq    $4, %rax
        cmpq    %rsi, %rax
        jne     .L7
        subq    $1, %rdi
        jne     .L5
.L8:
        movl    0(%rbp), %esi
        movl    $.LC4, %edi
        xorl    %eax, %eax
        addq    $4, %rbp
        call    printf
        cmpq    %rbx, %rbp
        jne     .L8
        addq    $8, %rsp
        xorl    %eax, %eax
        popq    %rbx
        popq    %rbp
        ret
.LC0:
        .quad   0
        .quad   1
.LC1:
        .quad   4
        .quad   4
.LC2:
        .quad   2
        .quad   2
.LC3:
        .long   100
        .long   100
        .long   100
        .long   100