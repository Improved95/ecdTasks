swap:
        movl    (%rdi), %eax
        movl    (%rsi), %edx
        movl    %edx, (%rdi)
        movl    %eax, (%rsi)
        ret
.LC0:
        .string "%d "
main:
        pushq   %r12
        movl    $10, %edx
        pushq   %rbp
        pushq   %rbx
        movq    8(%rsi), %rdi
        xorl    %esi, %esi
        call    strtol
        movslq  %eax, %r12
        movq    %rax, %rbx
        leaq    0(,%r12,4), %rdi
        call    malloc
        movq    %rax, %rbp
        testq   %r12, %r12
        je      .L13
        movl    %ebx, %eax
        xorl    %edx, %edx
.L5:
        movl    %eax, %ecx
        movq    %rdx, %r8
        subl    %edx, %ecx
        movl    %ecx, 0(%rbp,%rdx,4)
        addq    $1, %rdx
        cmpq    %rdx, %r12
        jne     .L5
        testq   %r8, %r8
        je      .L21
.L4:
        xorl    %edi, %edi
        leaq    0(%rbp,%r8,4), %rsi
.L7:
        movq    %rbp, %rax
.L9:
        movq    (%rax), %xmm0
        pshufd  $0xe5, %xmm0, %xmm1
        movd    %xmm0, %edx
        movd    %xmm1, %ecx
        cmpl    %edx, %ecx
        jge     .L8
        pshufd  $225, %xmm0, %xmm0
        movq    %xmm0, (%rax)
.L8:
        addq    $4, %rax
        cmpq    %rsi, %rax
        jne     .L9
        addq    $1, %rdi
        cmpq    %r8, %rdi
        jb      .L7
        xorl    %ebx, %ebx
        testq   %r12, %r12
        je      .L19
.L11:
        movl    0(%rbp,%rbx,4), %esi
        movl    $.LC0, %edi
        xorl    %eax, %eax
        addq    $1, %rbx
        call    printf
        cmpq    %r12, %rbx
        jb      .L11
.L19:
        popq    %rbx
        xorl    %eax, %eax
        popq    %rbp
        popq    %r12
        ret
.L13:
        orq     $-1, %r8
        jmp     .L4
.L21:
        movl    0(%rbp), %esi
        movl    $.LC0, %edi
        xorl    %eax, %eax
        call    printf
        jmp     .L19