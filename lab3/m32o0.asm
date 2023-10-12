swap:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $16, %esp
        movl    8(%ebp), %eax
        movl    (%eax), %eax
        movl    %eax, -4(%ebp)
        movl    12(%ebp), %eax
        movl    (%eax), %edx
        movl    8(%ebp), %eax
        movl    %edx, (%eax)
        movl    12(%ebp), %eax
        movl    -4(%ebp), %edx
        movl    %edx, (%eax)
        nop
        leave
        ret
.LC0:
        .string "%d "
main:
        leal    4(%esp), %ecx
        andl    $-16, %esp
        pushl   -4(%ecx)
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ecx
        subl    $36, %esp
        movl    %ecx, %eax
        movl    4(%eax), %eax
        addl    $4, %eax
        movl    (%eax), %eax
        subl    $12, %esp
        pushl   %eax
        call    atoi
        addl    $16, %esp
        movl    %eax, -28(%ebp)
        movl    -28(%ebp), %eax
        sall    $2, %eax
        subl    $12, %esp
        pushl   %eax
        call    malloc
        addl    $16, %esp
        movl    %eax, -32(%ebp)
        movl    $0, -12(%ebp)
        jmp     .L3
.L4:
        movl    -28(%ebp), %eax
        subl    -12(%ebp), %eax
        movl    %eax, %ecx
        movl    -12(%ebp), %eax
        leal    0(,%eax,4), %edx
        movl    -32(%ebp), %eax
        addl    %edx, %eax
        movl    %ecx, %edx
        movl    %edx, (%eax)
        addl    $1, -12(%ebp)
.L3:
        movl    -12(%ebp), %eax
        cmpl    -28(%ebp), %eax
        jb      .L4
        movl    $0, -16(%ebp)
        jmp     .L5
.L9:
        movl    $0, -20(%ebp)
        jmp     .L6
.L8:
        movl    -20(%ebp), %eax
        leal    0(,%eax,4), %edx
        movl    -32(%ebp), %eax
        addl    %edx, %eax
        movl    (%eax), %edx
        movl    -20(%ebp), %eax
        addl    $1, %eax
        leal    0(,%eax,4), %ecx
        movl    -32(%ebp), %eax
        addl    %ecx, %eax
        movl    (%eax), %eax
        cmpl    %eax, %edx
        jle     .L7
        movl    -20(%ebp), %eax
        addl    $1, %eax
        leal    0(,%eax,4), %edx
        movl    -32(%ebp), %eax
        addl    %eax, %edx
        movl    -20(%ebp), %eax
        leal    0(,%eax,4), %ecx
        movl    -32(%ebp), %eax
        addl    %ecx, %eax
        subl    $8, %esp
        pushl   %edx
        pushl   %eax
        call    swap
        addl    $16, %esp
.L7:
        addl    $1, -20(%ebp)
.L6:
        movl    -28(%ebp), %eax
        subl    $1, %eax
        cmpl    %eax, -20(%ebp)
        jb      .L8
        addl    $1, -16(%ebp)
.L5:
        movl    -28(%ebp), %eax
        subl    $1, %eax
        cmpl    %eax, -16(%ebp)
        jb      .L9
        movl    $0, -24(%ebp)
        jmp     .L10
.L11:
        movl    -24(%ebp), %eax
        leal    0(,%eax,4), %edx
        movl    -32(%ebp), %eax
        addl    %edx, %eax
        movl    (%eax), %eax
        subl    $8, %esp
        pushl   %eax
        pushl   $.LC0
        call    printf
        addl    $16, %esp
        addl    $1, -24(%ebp)
.L10:
        movl    -24(%ebp), %eax
        cmpl    -28(%ebp), %eax
        jb      .L11
        movl    $0, %eax
        movl    -4(%ebp), %ecx
        leave
        leal    -4(%ecx), %esp
        ret