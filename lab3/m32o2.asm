swap:
        push    ebx
        mov     edx, DWORD PTR [esp+8]
        mov     eax, DWORD PTR [esp+12]
        mov     ecx, DWORD PTR [edx]
        mov     ebx, DWORD PTR [eax]
        mov     DWORD PTR [edx], ebx
        mov     DWORD PTR [eax], ecx
        pop     ebx
        ret
.LC0:
        .string "%d "
main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    edi
        push    esi
        push    ebx
        push    ecx
        sub     esp, 28
        mov     eax, DWORD PTR [ecx+4]
        push    10
        push    0
        push    DWORD PTR [eax+4]
        call    strtol
        mov     esi, eax
        sal     eax, 2
        mov     DWORD PTR [esp], eax
        call    malloc
        add     esp, 16
        mov     edi, eax
        test    esi, esi
        je      .L14
        xor     eax, eax
.L6:
        mov     edx, esi
        mov     ecx, eax
        sub     edx, eax
        mov     DWORD PTR [edi+eax*4], edx
        add     eax, 1
        cmp     esi, eax
        jne     .L6
        test    ecx, ecx
        je      .L22
.L5:
        mov     DWORD PTR [ebp-28], ecx
        xor     edx, edx
        lea     ebx, [edi+ecx*4]
        mov     DWORD PTR [ebp-32], esi
.L8:
        mov     eax, edi
.L10:
        mov     esi, DWORD PTR [eax]
        mov     ecx, DWORD PTR [eax+4]
        cmp     esi, ecx
        jle     .L9
        movd    xmm0, ecx
        movd    xmm1, esi
        punpckldq       xmm0, xmm1
        movq    QWORD PTR [eax], xmm0
.L9:
        add     eax, 4
        cmp     eax, ebx
        jne     .L10
        mov     eax, DWORD PTR [ebp-28]
        add     edx, 1
        cmp     edx, eax
        jb      .L8
        mov     esi, DWORD PTR [ebp-32]
        xor     ebx, ebx
        test    esi, esi
        je      .L20
.L12:
        sub     esp, 8
        push    DWORD PTR [edi+ebx*4]
        add     ebx, 1
        push    OFFSET FLAT:.LC0
        call    printf
        add     esp, 16
        cmp     ebx, esi
        jb      .L12
.L20:
        lea     esp, [ebp-16]
        xor     eax, eax
        pop     ecx
        pop     ebx
        pop     esi
        pop     edi
        pop     ebp
        lea     esp, [ecx-4]
        ret
.L14:
        or      ecx, -1
        jmp     .L5
.L22:
        push    eax
        push    eax
        push    DWORD PTR [edi]
        push    OFFSET FLAT:.LC0
        call    printf
        add     esp, 16
        jmp     .L20