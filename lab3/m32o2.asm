swap:
    pushl   %ebx              ; Сохранение регистра %ebx на стеке
    movl    8(%esp), %edx     ; Загрузка адреса первого аргумента (int *a) в регистр %edx
    movl    12(%esp), %eax    ; Загрузка адреса второго аргумента (int *b) в регистр %eax
    movl    (%edx), %ecx      ; Загрузка значения, на которое указывает %edx, в регистр %ecx (значение a)
    movl    (%eax), %ebx      ; Загрузка значения, на которое указывает %eax, в регистр %ebx (значение b)
    movl    %ebx, (%edx)      ; Сохранение значения b по адресу %edx (a = b)
    movl    %ecx, (%eax)      ; Сохранение значения a по адресу %eax (b = a)
    popl    %ebx              ; Восстановление регистра %ebx из стека
    ret                      ; Возврат из функции swap
.LC0:
        .string "%d "
main:
    leal    4(%esp), %ecx      ; Загрузка адреса аргументов (argc и argv) в %ecx
    andl    $-16, %esp         ; Выравнивание указателя стека %esp на границу 16 байт
    pushl   -4(%ecx)           ; Запись значения argc на стек
    pushl   %ebp               ; Сохранение указателя стека %ebp на стеке
    movl    %esp, %ebp         ; Установка указателя стека %ebp на текущее значение %esp
    pushl   %edi               ; Сохранение регистра %edi на стеке
    pushl   %esi               ; Сохранение регистра %esi на стеке
    pushl   %ebx               ; Сохранение регистра %ebx на стеке
    pushl   %ecx               ; Сохранение регистра %ecx на стеке
    subl    $28, %esp          ; Резервирование 28 байтов на стеке
    movl    4(%ecx), %eax      ; Загрузка указателя на первый аргумент (char *argv[]) в %eax
    pushl   $10                ; Помещение значения 10 на стек
    pushl   $0                 ; Помещение значения 0 на стек
    pushl   4(%eax)            ; Загрузка указателя на первый элемент argv (строка с числом)
    call    strtol             ; Вызов функции strtol для преобразования строки в число
    movl    %eax, %esi         ; Сохранение результата в %esi (n)
    sall    $2, %eax           ; Сдвиг значения %eax на 2 бита влево (умножение на 4)
    movl    %eax, (%esp)       ; Помещение %eax на вершину стека
    call    malloc             ; Вызов функции malloc для выделения памяти
    addl    $16, %esp          ; Очистка верхней части стека
    movl    %eax, %edi         ; Сохранение указателя на выделенную память в %edi (arr)
    testl   %esi, %esi         ; Проверка, равно ли %esi нулю (если n == 0)
    je      .L14               ; Если n == 0, переход к .L14
    xorl    %eax, %eax         ; Обнуление %eax (счетчик i)
.L6:
    movl    %esi, %edx         ; Загрузка значения %esi в %edx (n)
    movl    %eax, %ecx         ; Загрузка значения %eax в %ecx (i)
    subl    %eax, %edx         ; Вычисление (n - i)
    movl    %edx, (%edi,%eax,4) ; Сохранение значения (%edi + 4 * i) = n - i в массив arr
    addl    $1, %eax           ; Увеличение счетчика i на 1
    cmpl    %eax, %esi         ; Сравнение i с n
    jne     .L6                ; Если i != n, переход к .L6
    testl   %ecx, %ecx         ; Проверка, равно ли %ecx нулю (если i == 0)
    je      .L22               ; Если i == 0, переход к .L22
.L5:
    movl    %ecx, -28(%ebp)    ; Сохранение значения %ecx (i) в -28(%ebp)
    xorl    %edx, %edx         ; Обнуление %edx (счетчик j)
    leal    (%edi,%ecx,4), %ebx ; Вычисление адреса элемента arr[i] и сохранение в %ebx
    movl    %esi, -32(%ebp)    ; Сохранение значения %esi (n) в -32(%ebp)
.L8:
    movl    %edi, %eax         ; Загрузка указателя на начало массива arr в %eax
.L10:
    movl    (%eax), %esi       ; Загрузка значения по адресу %eax (arr[j]) в %esi
    movl    4(%eax), %ecx      ; Загрузка значения по адресу %eax+4 (arr[j+1]) в %ecx
    cmpl    %ecx, %esi         ; Сравнение arr[j] и arr[j+1]
    jle     .L9                ; Если arr[j] <= arr[j+1], переход к .L9
    movd    %ecx, %xmm0        ; Загрузка значения %ecx (arr[j+1]) в XMM регистр %xmm0
    movd    %esi, %xmm1        ; Загрузка значения %esi (arr[j]) в XMM регистр %xmm1
    punpckldq %xmm1, %xmm0     ; Объединение двух значений XMM в одно
    movq    %xmm0, (%eax)      ; Сохранение объединенного значения в arr[j]
.L9:
    addl    $4, %eax           ; Переход к следующей паре элементов arr
    cmpl    %ebx, %eax         ; Сравнение %eax с адресом arr[i]
    jne     .L10               ; Если %eax != адресу arr[i], переход к .L10
    movl    -28(%ebp), %eax    ; Загрузка значения -28(%ebp) (i) в %eax
    addl    $1, %edx           ; Увеличение счетчика j на 1
    cmpl    %eax, %edx         ; Сравнение j с i
    jb      .L8                ; Если j < i, переход к .L8
    movl    -32(%ebp), %esi    ; Загрузка значения -32(%ebp) (n) в %esi
    xorl    %ebx, %ebx         ; Обнуление %ebx (счетчик k)
    testl   %esi, %esi         ; Проверка, равно ли %esi нулю (если n == 0)
    je      .L20               ; Если n == 0, переход к .L20
.L12:
    subl    $8, %esp           ; Выделение места на стеке для аргументов функции printf
    pushl   (%edi,%ebx,4)      ; Помещение значения arr[k] на стек
    addl    $1, %ebx           ; Увеличение счетчика k на 1
    pushl   $.LC0              ; Помещение адреса строки формата на стек
    call    printf             ; Вызов функции printf
    addl    $16, %esp          ; Очистка верхней части стека
    cmpl    %esi, %ebx         ; Сравнение k с n
    jb      .L12               ; Если k < n, переход к .L12
.L20:
    leal    -16(%ebp), %esp    ; Восстановление указателя стека %esp
    xorl    %eax, %eax         ; Обнуление %eax (результат функции main)
     popl    %ecx               ; Восстановление регистра %ecx
    popl    %ebx               ; Восстановление регистра %ebx
    popl    %esi               ; Восстановление регистра %esi
    popl    %edi               ; Восстановление регистра %edi
    popl    %ebp              ; Восстановление указателя стека %ebp
    leal    -4(%ecx), %esp     ; Восстановление указателя стека %esp
    ret                       ; Возврат из функции main
.L14:
    orl     $-1, %ecx           ; Установка %ecx в -1 (0xFFFFFFFF)
    jmp     .L5                ; Переход к .L5
.L22:
    pushl   %eax               ; Помещение %eax на стек (результат функции strtol)
    pushl   %eax               ; Помещение %eax на стек (результат функции strtol)
    pushl   (%edi)             ; Помещение указателя на первый элемент arr на стек
    pushl   $.LC0              ; Помещение адреса строки формата на стек
    call    printf             ; Вызов функции printf
    addl    $16, %esp          ; Очистка верхней части стека
    jmp     .L20               ; Переход к .L20


; сохраняет значение регистров на стеке, освобождая их, потом восстанавливает их
; xor для зануления
; встраивание функций
; объединение значений punpckldq
; использует movsql это короче 32 битное значение перемещает куда то, делая его 64 битным