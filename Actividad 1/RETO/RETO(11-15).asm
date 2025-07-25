
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

14)
@R1     
A=M 
D=M    
@R4      
M=D    

15)
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


