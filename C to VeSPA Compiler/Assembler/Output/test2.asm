INIT:
    LD R0, #100
    LDI R1, #0
    LDI R2, #0
    LDI R3, #10
    ADD R2, R0, R1

LOOP:
    MOV R1, R0
    MOV R0, R2
    ADD R2, R0, R1
    SUB R3, R3, #1
    CMP R3, #1
    BGT LOOP