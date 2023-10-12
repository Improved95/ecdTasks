swap:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-24], rdi
        mov     QWORD PTR [rbp-32], rsi
        mov     rax, QWORD PTR [rbp-24]
        mov     eax, DWORD PTR [rax]
        mov     DWORD PTR [rbp-4], eax
        mov     rax, QWORD PTR [rbp-32]
        mov     edx, DWORD PTR [rax]
        mov     rax, QWORD PTR [rbp-24]
        mov     DWORD PTR [rax], edx
        mov     rax, QWORD PTR [rbp-32]
        mov     edx, DWORD PTR [rbp-4]
        mov     DWORD PTR [rax], edx
        nop
        pop     rbp
        ret
.LC0:
        .string "%d "
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 64
        mov     DWORD PTR [rbp-52], edi
        mov     QWORD PTR [rbp-64], rsi
        mov     rax, QWORD PTR [rbp-64]
        add     rax, 8
        mov     rax, QWORD PTR [rax]
        mov     rdi, rax
        call    atoi
        cdqe
        mov     QWORD PTR [rbp-40], rax
        mov     rax, QWORD PTR [rbp-40]
        sal     rax, 2
        mov     rdi, rax
        call    malloc
        mov     QWORD PTR [rbp-48], rax
        mov     QWORD PTR [rbp-8], 0
        jmp     .L3
.L4:
        mov     rax, QWORD PTR [rbp-40]
        mov     edx, eax
        mov     rax, QWORD PTR [rbp-8]
        mov     ecx, edx
        sub     ecx, eax
        mov     rax, QWORD PTR [rbp-8]
        lea     rdx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-48]
        add     rax, rdx
        mov     edx, ecx
        mov     DWORD PTR [rax], edx
        add     QWORD PTR [rbp-8], 1
.L3:
        mov     rax, QWORD PTR [rbp-8]
        cmp     rax, QWORD PTR [rbp-40]
        jb      .L4
        mov     QWORD PTR [rbp-16], 0
        jmp     .L5
.L9:
        mov     QWORD PTR [rbp-24], 0
        jmp     .L6
.L8:
        mov     rax, QWORD PTR [rbp-24]
        lea     rdx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-48]
        add     rax, rdx
        mov     edx, DWORD PTR [rax]
        mov     rax, QWORD PTR [rbp-24]
        add     rax, 1
        lea     rcx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-48]
        add     rax, rcx
        mov     eax, DWORD PTR [rax]
        cmp     edx, eax
        jle     .L7
        mov     rax, QWORD PTR [rbp-24]
        add     rax, 1
        lea     rdx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-48]
        add     rdx, rax
        mov     rax, QWORD PTR [rbp-24]
        lea     rcx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-48]
        add     rax, rcx
        mov     rsi, rdx
        mov     rdi, rax
        call    swap
.L7:
        add     QWORD PTR [rbp-24], 1
.L6:
        mov     rax, QWORD PTR [rbp-40]
        sub     rax, 1
        cmp     QWORD PTR [rbp-24], rax
        jb      .L8
        add     QWORD PTR [rbp-16], 1
.L5:
        mov     rax, QWORD PTR [rbp-40]
        sub     rax, 1
        cmp     QWORD PTR [rbp-16], rax
        jb      .L9
        mov     QWORD PTR [rbp-32], 0
        jmp     .L10
.L11:
        mov     rax, QWORD PTR [rbp-32]
        lea     rdx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-48]
        add     rax, rdx
        mov     eax, DWORD PTR [rax]
        mov     esi, eax
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf
        add     QWORD PTR [rbp-32], 1
.L10:
        mov     rax, QWORD PTR [rbp-32]
        cmp     rax, QWORD PTR [rbp-40]
        jb      .L11
        mov     eax, 0
        leave
        ret