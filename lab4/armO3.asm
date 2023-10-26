fact:
        push    {r3, lr}
        cmp     r0, #0
        vpush.64        {d8, d9}
        blt     .L4
        bne     .L11
        vmov.f64        d8, #1.0e+0
.L1:
        vmov.f64        d0, d8
        vldm    sp!, {d8-d9}
        pop     {r3, pc}
.L11:
        vmov    s15, r0 @ int
        subs    r3, r0, #1
        vcvt.f64.s32    d8, s15
        beq     .L1
        vmov    s15, r3 @ int
        subs    r0, r0, #2
        vcvt.f64.s32    d9, s15
        bl      fact
        vmul.f64        d9, d9, d0
        vmul.f64        d8, d8, d9
        b       .L1
.L4:
        vldr.64 d8, .L12
        vmov.f64        d0, d8
        vldm    sp!, {d8-d9}
        pop     {r3, pc}
.L12:
        .word   0
        .word   0
.LC0:
        .ascii  "%Le \000"
main:
        push    {r3, r4, r5, r6, r7, lr}
        mvn     r7, #2
        mvn     r6, #1
        vpush.64        {d8, d9, d10, d11, d12, d13}
        mov     r5, #-1
        movs    r4, #0
        vldr.64 d9, .L53
.L27:
        vmov    s15, r4 @ int
        vmov.f64        d0, #2.0e+0
        vcvt.f64.s32    d8, s15
        vmov.f64        d1, d8
        bl      pow
        vmov.f64        d6, d0
        cbnz    r4, .L15
        vadd.f64        d9, d9, d0
        adds    r5, r5, #1
        adds    r6, r6, #1
        adds    r7, r7, #1
        movs    r4, #1
        b       .L27
.L15:
        cbnz    r5, .L44
.L17:
        vdiv.f64        d7, d6, d8
        adds    r4, r4, #1
        adds    r5, r5, #1
        adds    r6, r6, #1
        adds    r7, r7, #1
        cmp     r4, #101
        vadd.f64        d9, d9, d7
        bne     .L27
        vmov    r2, r3, d9
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0
        bl      printf
        movs    r0, #0
        vldm    sp!, {d8-d13}
        pop     {r3, r4, r5, r6, r7, pc}
.L44:
        vmov    s15, r5 @ int
        vcvt.f64.s32    d5, s15
        cbnz    r6, .L45
.L18:
        vmul.f64        d8, d8, d5
        b       .L17
.L45:
        vmov    s15, r6 @ int
        vcvt.f64.s32    d4, s15
        cbnz    r7, .L46
.L19:
        vmul.f64        d5, d5, d4
        b       .L18
.L46:
        vmov    s15, r7 @ int
        subs    r3, r4, #4
        vcvt.f64.s32    d3, s15
        bne     .L47
        vmov.f64        d13, #1.0e+0
.L20:
        vmul.f64        d3, d3, d13
        vmul.f64        d4, d4, d3
        b       .L19
.L47:
        vmov    s15, r3 @ int
        subs    r3, r4, #5
        vcvt.f64.s32    d13, s15
        bne     .L48
        vmov.f64        d12, #1.0e+0
.L21:
        vmul.f64        d13, d13, d12
        b       .L20
.L48:
        vmov    s15, r3 @ int
        subs    r3, r4, #6
        vmov    s4, r3  @ int
        vcvt.f64.s32    d12, s15
        bne     .L49
        vmov.f64        d2, #1.0e+0
.L22:
        vmul.f64        d12, d12, d2
        b       .L21
.L49:
        subs    r3, r4, #7
        vcvt.f64.s32    d2, s4
        vmov    s2, r3  @ int
        bne     .L50
        vmov.f64        d1, #1.0e+0
.L23:
        vmul.f64        d2, d2, d1
        b       .L22
.L50:
        subs    r3, r4, #8
        vcvt.f64.s32    d1, s2
        vmov    s20, r3 @ int
        bne     .L51
        vmov.f64        d10, #1.0e+0
.L24:
        vmul.f64        d1, d1, d10
        b       .L23
.L51:
        subs    r3, r4, #9
        vcvt.f64.s32    d10, s20
        vmov    s22, r3 @ int
        bne     .L52
        vmov.f64        d11, #1.0e+0
.L25:
        vmul.f64        d10, d10, d11
        b       .L24
.L52:
        vcvt.f64.s32    d11, s22
        sub     r0, r4, #10
        bl      fact
        vmul.f64        d11, d11, d0
        b       .L25
.L53:
        .word   0
        .word   0