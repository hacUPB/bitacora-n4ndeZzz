@R0
D=M
@R2
M=D

(LOOP)
@R1
D=M
@END
D;JEQ

@R2
A=M
M=-1

@R2
M=M+1

@R1
M=M-1

@LOOP
0;JMP

(END)
@END
0;JMP






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








