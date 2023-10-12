swap:
        mov     eax, DWORD PTR [rdi]
        mov     edx, DWORD PTR [rsi]
        mov     DWORD PTR [rdi], edx
        mov     DWORD PTR [rsi], eax
        ret
.LC0:
        .string "%d "
main:
        push    r12
        mov     edx, 10
        push    rbp
        push    rbx
        mov     rdi, QWORD PTR [rsi+8]
        xor     esi, esi
        call    strtol
        movsx   r12, eax
        mov     rbx, rax
        lea     rdi, [0+r12*4]
        call    malloc
        mov     rbp, rax
        test    r12, r12
        je      .L13
        mov     eax, ebx
        xor     edx, edx
.L5:
        mov     ecx, eax
        mov     r8, rdx
        sub     ecx, edx
        mov     DWORD PTR [rbp+0+rdx*4], ecx
        add     rdx, 1
        cmp     r12, rdx
        jne     .L5
        test    r8, r8
        je      .L21
.L4:
        xor     edi, edi
        lea     rsi, [rbp+0+r8*4]
.L7:
        mov     rax, rbp
.L9:
        movq    xmm0, QWORD PTR [rax]
        pshufd  xmm1, xmm0, 0xe5
        movd    edx, xmm0
        movd    ecx, xmm1
        cmp     ecx, edx
        jge     .L8
        pshufd  xmm0, xmm0, 225
        movq    QWORD PTR [rax], xmm0
.L8:
        add     rax, 4
        cmp     rax, rsi
        jne     .L9
        add     rdi, 1
        cmp     rdi, r8
        jb      .L7
        xor     ebx, ebx
        test    r12, r12
        je      .L19
.L11:
        mov     esi, DWORD PTR [rbp+0+rbx*4]
        mov     edi, OFFSET FLAT:.LC0
        xor     eax, eax
        add     rbx, 1
        call    printf
        cmp     rbx, r12
        jb      .L11
.L19:
        pop     rbx
        xor     eax, eax
        pop     rbp
        pop     r12
        ret
.L13:
        or      r8, -1
        jmp     .L4
.L21:
        mov     esi, DWORD PTR [rbp+0]
        mov     edi, OFFSET FLAT:.LC0
        xor     eax, eax
        call    printf
        jmp     .L19