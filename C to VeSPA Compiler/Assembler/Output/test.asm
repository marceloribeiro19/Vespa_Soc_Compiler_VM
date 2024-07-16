.org 0x10
.equ VAR1, 100

INIT :      ;Init variables
LDI R0, #VAR1
ADD R2, R0, R1
LDI R0, :LOOP

.org 0x2FF

LOOP :      //Computing Loop 
MOV R1, R0
BNE LOOP
