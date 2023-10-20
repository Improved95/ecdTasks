swap:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -24(%rbp)
        movq    %rsi, -32(%rbp)
        movq    -24(%rbp), %rax
        movl    (%rax), %eax
        movl    %eax, -4(%rbp)
        movq    -32(%rbp), %rax
        movl    (%rax), %edx
        movq    -24(%rbp), %rax
        movl    %edx, (%rax)
        movq    -32(%rbp), %rax
        movl    -4(%rbp), %edx
        movl    %edx, (%rax)
        nop
        popq    %rbp
        ret
.LC0:
        .string "%d "
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $64, %rsp
        movl    %edi, -52(%rbp)
        movq    %rsi, -64(%rbp)
        movq    -64(%rbp), %rax
        addq    $8, %rax
        movq    (%rax), %rax
        movq    %rax, %rdi
        call    atoi
        cltq
        movq    %rax, -40(%rbp)
        movq    -40(%rbp), %rax
        salq    $2, %rax
        movq    %rax, %rdi
        call    malloc
        movq    %rax, -48(%rbp)
        movq    $0, -8(%rbp)
        jmp     .L3
.L4:
        movq    -40(%rbp), %rax
        movl    %eax, %edx
        movq    -8(%rbp), %rax
        movl    %edx, %ecx
        subl    %eax, %ecx
        movq    -8(%rbp), %rax
        leaq    0(,%rax,4), %rdx
        movq    -48(%rbp), %rax
        addq    %rdx, %rax
        movl    %ecx, %edx
        movl    %edx, (%rax)
        addq    $1, -8(%rbp)
.L3:
        movq    -8(%rbp), %rax
        cmpq    -40(%rbp), %rax
        jb      .L4
        movq    $0, -16(%rbp)
        jmp     .L5
.L9:
        movq    $0, -24(%rbp)
        jmp     .L6
.L8:
        movq    -24(%rbp), %rax
        leaq    0(,%rax,4), %rdx
        movq    -48(%rbp), %rax
        addq    %rdx, %rax
        movl    (%rax), %edx
        movq    -24(%rbp), %rax
        addq    $1, %rax
        leaq    0(,%rax,4), %rcx
        movq    -48(%rbp), %rax
        addq    %rcx, %rax
        movl    (%rax), %eax
        cmpl    %eax, %edx
        jle     .L7
        movq    -24(%rbp), %rax
        addq    $1, %rax
        leaq    0(,%rax,4), %rdx
        movq    -48(%rbp), %rax
        addq    %rax, %rdx
        movq    -24(%rbp), %rax
        leaq    0(,%rax,4), %rcx
        movq    -48(%rbp), %rax
        addq    %rcx, %rax
        movq    %rdx, %rsi
        movq    %rax, %rdi
        call    swap
.L7:
        addq    $1, -24(%rbp)
.L6:
        movq    -40(%rbp), %rax
        subq    $1, %rax
        cmpq    %rax, -24(%rbp)
        jb      .L8
        addq    $1, -16(%rbp)
.L5:
        movq    -40(%rbp), %rax
        subq    $1, %rax
        cmpq    %rax, -16(%rbp)
        jb      .L9
        movq    $0, -32(%rbp)
        jmp     .L10
.L11:
        movq    -32(%rbp), %rax
        leaq    0(,%rax,4), %rdx
        movq    -48(%rbp), %rax
        addq    %rdx, %rax
        movl    (%rax), %eax
        movl    %eax, %esi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf
        addq    $1, -32(%rbp)
.L10:
        movq    -32(%rbp), %rax
        cmpq    -40(%rbp), %rax
        jb      .L11
        movl    $0, %eax
        leave
        ret