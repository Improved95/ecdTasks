.LC0:
        .string "stoull"
swap(int&, int&):
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
.LC1:
        .string " "
main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ebx
        push    ecx
        sub     esp, 64
        mov     ebx, ecx
        sub     esp, 12
        push    20
        call    srand
        add     esp, 16
        lea     eax, [ebp-37]
        mov     DWORD PTR [ebp-36], eax
        nop
        nop
        mov     eax, DWORD PTR [ebx+4]
        add     eax, 4
        mov     eax, DWORD PTR [eax]
        sub     esp, 4
        lea     edx, [ebp-37]
        push    edx
        push    eax
        lea     eax, [ebp-64]
        push    eax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string<std::allocator<char> >(char const*, std::allocator<char> const&)
        add     esp, 16
        sub     esp, 4
        push    10
        push    0
        lea     eax, [ebp-64]
        push    eax
        call    std::__cxx11::stoull(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned int*, int)
        add     esp, 16
        mov     DWORD PTR [ebp-28], eax
        sub     esp, 12
        lea     eax, [ebp-64]
        push    eax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        add     esp, 16
        sub     esp, 12
        lea     eax, [ebp-37]
        push    eax
        call    std::__new_allocator<char>::~__new_allocator() [base object destructor]
        add     esp, 16
        nop
        mov     eax, DWORD PTR [ebp-28]
        cmp     eax, 536870911
        ja      .L10
        sal     eax, 2
        sub     esp, 12
        push    eax
        call    operator new[](unsigned int)
        add     esp, 16
        mov     DWORD PTR [ebp-32], eax
        mov     DWORD PTR [ebp-12], 0
        jmp     .L12
.L10:
        call    __cxa_throw_bad_array_new_length
.L13:
        mov     eax, DWORD PTR [ebp-12]
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        lea     ebx, [edx+eax]
        call    rand
        mov     DWORD PTR [ebx], eax
        add     DWORD PTR [ebp-12], 1
.L12:
        mov     eax, DWORD PTR [ebp-12]
        cmp     eax, DWORD PTR [ebp-28]
        jb      .L13
        mov     DWORD PTR [ebp-16], 0
        jmp     .L14
.L18:
        mov     DWORD PTR [ebp-20], 0
        jmp     .L15
.L17:
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
        jle     .L16
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
        call    swap(int&, int&)
        add     esp, 16
.L16:
        add     DWORD PTR [ebp-20], 1
.L15:
        mov     eax, DWORD PTR [ebp-28]
        sub     eax, 1
        cmp     DWORD PTR [ebp-20], eax
        jb      .L17
        add     DWORD PTR [ebp-16], 1
.L14:
        mov     eax, DWORD PTR [ebp-28]
        sub     eax, 1
        cmp     DWORD PTR [ebp-16], eax
        jb      .L18
        mov     DWORD PTR [ebp-24], 0
        jmp     .L19
.L20:
        mov     eax, DWORD PTR [ebp-24]
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebp-32]
        add     eax, edx
        mov     eax, DWORD PTR [eax]
        sub     esp, 8
        push    eax
        push    OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(int)
        add     esp, 16
        sub     esp, 8
        push    OFFSET FLAT:.LC1
        push    eax
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
        add     esp, 16
        add     DWORD PTR [ebp-24], 1
.L19:
        mov     eax, DWORD PTR [ebp-24]
        cmp     eax, DWORD PTR [ebp-28]
        jb      .L20
        mov     eax, 0
        jmp     .L26
        mov     ebx, eax
        sub     esp, 12
        lea     eax, [ebp-64]
        push    eax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        add     esp, 16
        jmp     .L23
        mov     ebx, eax
.L23:
        sub     esp, 12
        lea     eax, [ebp-37]
        push    eax
        call    std::__new_allocator<char>::~__new_allocator() [base object destructor]
        add     esp, 16
        nop
        mov     eax, ebx
        sub     esp, 12
        push    eax
        call    _Unwind_Resume
.L26:
        lea     esp, [ebp-8]
        pop     ecx
        pop     ebx
        pop     ebp
        lea     esp, [ecx-4]
        ret
.LC2:
        .string "basic_string: construction from null is not valid"