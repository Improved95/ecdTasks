fact:
        cmp     r0, #0
        blt     .L3
        cbnz    r0, .L9
        vmov.f64        d0, #1.0e+0
        bx      lr
.L9:
        push    {r3, lr}
        vpush.64        {d8}
        vmov    s15, r0 @ int
        vcvt.f64.s32    d8, s15
        subs    r0, r0, #1
        bl      fact
        vmul.f64        d0, d8, d0
        vldm    sp!, {d8}
        pop     {r3, pc}
.L3:
        vldr.64 d0, .L10
        bx      lr
.L10:
        .word   0
        .word   0
.LC0:
        .ascii  "%Le \000"
main:
        push    {r4, lr}
        vpush.64        {d8, d9, d10}
        movs    r4, #0
        vldr.64 d9, .L16
        vmov.f64        d10, #2.0e+0
.L13:
        vmov    s15, r4 @ int
        vcvt.f64.s32    d1, s15
        vmov.f64        d0, d10
        bl      pow
        vmov.f64        d8, d0
        mov     r0, r4
        bl      fact
        vdiv.f64        d7, d8, d0
        vadd.f64        d9, d9, d7
        adds    r4, r4, #1
        cmp     r4, #101
        bne     .L13
        vmov    r2, r3, d9
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0
        bl      printf
        movs    r0, #0
        vldm    sp!, {d8-d10}
        pop     {r4, pc}
.L16:
        .word   0
        .word   0