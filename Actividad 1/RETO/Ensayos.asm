@0
D=M
@POS
D;JGE
@NEG
0;JMP

(POS)
@1
D=A
@1
M=D
@LOOP
0;JMP

(NEG)
@1
D=A
D=-D
@1
M=D

(LOOP)
@LOOP
0;JMP








