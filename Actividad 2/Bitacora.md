//lectura D
(START)
@KBD
D=M
@68
D=D-A        
@DRAW
D;JEQ        

@START
0;JMP      

// codigo solo una linea

@20480 
D=A
@addr
M=D        

@32
D=A
@count
M=D      

(Loop)
@addr
A=M
M=-1        

@addr
M=M+1      

@count
M=M-1      
@count
D=M
@Loop
D;JGT       

(End)
@End
0;JMP       // Bucle infinito 


@R0
A=M
M=-1