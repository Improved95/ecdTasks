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
.LC0:
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
        subl    $28, %esp
        movl    4(%ecx), %eax
        pushl   $10
        pushl   $0
        pushl   4(%eax)
        call    strtol
        movl    %eax, %esi
        sall    $2, %eax
        movl    %eax, (%esp)
        call    malloc
        addl    $16, %esp
        movl    %eax, %edi
        testl   %esi, %esi
        je      .L14
        xorl    %eax, %eax
.L6:
        movl    %esi, %edx
        movl    %eax, %ecx
        subl    %eax, %edx
        movl    %edx, (%edi,%eax,4)
        addl    $1, %eax
        cmpl    %eax, %esi
        jne     .L6
        testl   %ecx, %ecx
        je      .L22
.L5:
        movl    %ecx, -28(%ebp)
        xorl    %edx, %edx
        leal    (%edi,%ecx,4), %ebx
        movl    %esi, -32(%ebp)
.L8:
        movl    %edi, %eax
.L10:
        movl    (%eax), %esi
        movl    4(%eax), %ecx
        cmpl    %ecx, %esi
        jle     .L9
        movd    %ecx, %xmm0
        movd    %esi, %xmm1
        punpckldq       %xmm1, %xmm0
        movq    %xmm0, (%eax)
.L9:
        addl    $4, %eax
        cmpl    %ebx, %eax
        jne     .L10
        movl    -28(%ebp), %eax
        addl    $1, %edx
        cmpl    %eax, %edx
        jb      .L8
        movl    -32(%ebp), %esi
        xorl    %ebx, %ebx
        testl   %esi, %esi
        je      .L20
.L12:
        subl    $8, %esp
        pushl   (%edi,%ebx,4)
        addl    $1, %ebx
        pushl   $.LC0
        call    printf
        addl    $16, %esp
        cmpl    %esi, %ebx
        jb      .L12
.L20:
        leal    -16(%ebp), %esp
        xorl    %eax, %eax
        popl    %ecx
        popl    %ebx
        popl    %esi
        popl    %edi
        popl    %ebp
        leal    -4(%ecx), %esp
        ret
.L14:
        orl     $-1, %ecx
        jmp     .L5
.L22:
        pushl   %eax
        pushl   %eax
        pushl   (%edi)
        pushl   $.LC0
        call    printf
        addl    $16, %esp
        jmp     .L20