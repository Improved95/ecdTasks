swap:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD PTR [ebp+8]
        mov     eax, DWORD PTR [eax]
        mov     DWORD PTR [ebp-4], eax
        mov     eax, DWORD PTR [ebp+12]
        mov     edx, DWORD PTR [eax]
        mov     eax, DWORD PTR [ebp+8]
        mov     DWORD PTR [eax], edx
        mov     eax, DWORD PTR [ebp+12]
        mov     edx, DWORD PTR [ebp-4]
        mov     DWORD PTR [eax], edx
        nop
        leave
        ret
.LC0:
        .string "%d "
main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ecx
        sub     esp, 36
        mov     eax, ecx
        mov     eax, DWORD PTR [eax+4]
        add     eax, 4
        mov     eax, DWORD PTR [eax]
        sub     esp, 12
        push    eax
        call    atoi
        add     esp, 16
        mov     DWORD PTR [ebp-28], eax
        mov     eax, DWORD PTR [ebp-28]
        sal     eax, 2
        sub     esp, 12
        push    eax
        call    malloc
        add     esp, 16
        mov     DWORD PTR [ebp-32], eax
        mov     DWORD PTR [ebp-12], 0
        jmp     .L3
.L4:
        mov     eax, DWORD PTR [ebp-28]
        sub     eax, DWORD PTR [ebp-12]
        mov     ecx, eax
        mov     eax, DWORD PTR [ebp-12]
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     eax, edx
        mov     edx, ecx
        mov     DWORD PTR [eax], edx
        add     DWORD PTR [ebp-12], 1
.L3:
        mov     eax, DWORD PTR [ebp-12]
        cmp     eax, DWORD PTR [ebp-28]
        jb      .L4
        mov     DWORD PTR [ebp-16], 0
        jmp     .L5
.L9:
        mov     DWORD PTR [ebp-20], 0
        jmp     .L6
.L8:
        mov     eax, DWORD PTR [ebp-20]
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     eax, edx
        mov     edx, DWORD PTR [eax]
        mov     eax, DWORD PTR [ebp-20]
        add     eax, 1
        lea     ecx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     eax, ecx
        mov     eax, DWORD PTR [eax]
        cmp     edx, eax
        jle     .L7
        mov     eax, DWORD PTR [ebp-20]
        add     eax, 1
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     edx, eax
        mov     eax, DWORD PTR [ebp-20]
        lea     ecx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     eax, ecx
        sub     esp, 8
        push    edx
        push    eax
        call    swap
        add     esp, 16
.L7:
        add     DWORD PTR [ebp-20], 1
.L6:
        mov     eax, DWORD PTR [ebp-28]
        sub     eax, 1
        cmp     DWORD PTR [ebp-20], eax
        jb      .L8
        add     DWORD PTR [ebp-16], 1
.L5:
        mov     eax, DWORD PTR [ebp-28]
        sub     eax, 1
        cmp     DWORD PTR [ebp-16], eax
        jb      .L9
        mov     DWORD PTR [ebp-24], 0
        jmp     .L10
.L11:
        mov     eax, DWORD PTR [ebp-24]
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     eax, edx
        mov     eax, DWORD PTR [eax]
        sub     esp, 8
        push    eax
        push    OFFSET FLAT:.LC0
        call    printf
        add     esp, 16
        add     DWORD PTR [ebp-24], 1
.L10:
        mov     eax, DWORD PTR [ebp-24]
        cmp     eax, DWORD PTR [ebp-28]
        jb      .L11
        mov     eax, 0
        mov     ecx, DWORD PTR [ebp-4]
        leave
        lea     esp, [ecx-4]
        ret