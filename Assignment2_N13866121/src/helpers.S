.syntax unified

.global asm_sub
.global asm_led
.global asm_error
.global asm_add_6


asm_sub:
    MOV r0, #2 ;r0 = 2
    MOV r1, #1 ;r1 = 1
    SUB r0, r0, r1 ; r0 = 2-1 = 1
    bx lr


asm_led:
    EOR r0, #1 ; XOR with 1, 1 XOR 1 = 0
    bx lr 
    
asm_error:
    ADDS r0, r0, r1 ; r0 = r0 + r1
    bvs ovf_l ;v flag = 1, so branches to ovf_l 
    bx lr
        ovf_l:
            mov r0, #1 ; r0 = 1
            bx lr

asm_add_6:

mov r3, r0  ; r0 is moved to r3
mov r0, #0  ; r0 is my result here, so initialised it as 0
        ldrb r1, [r3], #-4 ; loads data from r3 into r1
    adds r0, r0, r1        ; adds r0 with the value of r1. Status updated
        ldrb r1, [r3], #-4
    adds r0, r0, r1
        ldrb r1, [r3], #-4
    adds r0, r0, r1
        ldrb r1, [r3], #-4
    adds r0, r0, r1  
        ldrb r1, [r3], #-4
    adds r0, r0, r1
        ldrb r1, [r3], #-4
    adds r0, r0, r1

    bx lr


