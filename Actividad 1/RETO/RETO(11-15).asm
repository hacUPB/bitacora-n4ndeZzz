
11)
@1
D=M
@2
D=D+M
@69
D=D+A
@4
M=D

13)
@0
D=M
@POS
D;JGE
@NEG
0;JMP

(POS)
@1
M=1
@LOOP
0;JMP

(NEG)
@1
M=-1

(LOOP)
@LOOP
0;JMP



