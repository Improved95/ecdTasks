swap:
        pushl   %ebx
        movl    8(%esp), %edx
        movl    12(%esp), %eax
        movl    (%edx), %ecx
        movl    (%eax), %ebx
        movl    %ebx, (%edx)
        movl    %ecx, (%eax)
        popl    %ebx
        ret
.LC3:
        .string "%d "
main:
        leal    4(%esp), %ecx
        andl    $-16, %esp
        pushl   -4(%ecx)
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %edi
        pushl   %esi
        pushl   %ebx
        pushl   %ecx
        subl    $36, %esp
        pushl   $400
        call    malloc
        addl    $16, %esp
        movdqa  .LC0, %xmm0
        movdqa  .LC1, %xmm4
        movdqa  .LC2, %xmm3
        movl    %eax, %ecx
        movl    %eax, %esi
        leal    400(%eax), %edi
.L5:
        movdqa  %xmm0, %xmm2
        movdqa  %xmm3, %xmm1
        paddd   %xmm4, %xmm0
        addl    $16, %eax
        psubd   %xmm2, %xmm1
        movups  %xmm1, -16(%eax)
        cmpl    %edi, %eax
        jne     .L5
        movl    $99, %edx
        movl    %esi, -32(%ebp)
        leal    396(%ecx), %ebx
        movl    %edx, -28(%ebp)
.L6:
        movl    %ecx, %eax
.L8:
        movl    (%eax), %esi
        movl    4(%eax), %edx
        cmpl    %edx, %esi
        jle     .L7
        movd    %edx, %xmm0
        movd    %esi, %xmm5
        punpckldq       %xmm5, %xmm0
        movq    %xmm0, (%eax)
.L7:
        addl    $4, %eax
        cmpl    %ebx, %eax
        jne     .L8
        subl    $1, -28(%ebp)
        jne     .L6
        movl    -32(%ebp), %esi
.L9:
        subl    $8, %esp
        pushl   (%esi)
        addl    $4, %esi
        pushl   $.LC3
        call    printf
        addl    $16, %esp
        cmpl    %edi, %esi
        jne     .L9
        leal    -16(%ebp), %esp
        xorl    %eax, %eax
        popl    %ecx
        popl    %ebx
        popl    %esi
        popl    %edi
        popl    %ebp
        leal    -4(%ecx), %esp
        ret
.LC0:
        .long   0
        .long   1
        .long   2
        .long   3
.LC1:
        .long   4
        .long   4
        .long   4
        .long   4
.LC2:
        .long   100
        .long   100
        .long   100
        .long   100