
someLabel47: prn #48
 .entry LABEL
 .extern LABEL
.extern J
jmp %J
jmp %data
;operand addressing errors
mov %ohno, #1
mov %ohno, %ohyes
mov %ohno, someLabel47
mov %ohno, r3
mov #-1, #5
mov #-1, %ohyes
cmp %ohno, %ohyes
add %ohno, #1
add %ohno, %ohyes
add %ohno, someLabel47
add %ohno, r3
add #-1, #5
add #-1, %ohyes
sub %ohno, #1
sub %ohno, %ohyes
sub %ohno, someLabel47
sub %ohno, r3
sub #-1, #5
sub #-1, %ohyes
lea #-1, #8
lea #-1, someLabel47
lea #-1, %ohno
lea #-1, r4
lea %ohno, #-1
lea %ohno, %ohyes
lea %ohno, someLabel47
lea %ohno, r0
lea r1, #-1
lea r1, %ohno
lea r1, someLabel47
lea r1, r0
lea someLabel47, #-1
lea someLabel47, %ohno
clr #-1
clr %ohno
not #-1
not %ohno
inc #-1
inc %ohno
dec #-1
dec %ohno
jmp #-1
jmp r1
bne #-1
bne r1
jsr #-1
jsr r1
red #-1
red %ohno
prn %ohno
