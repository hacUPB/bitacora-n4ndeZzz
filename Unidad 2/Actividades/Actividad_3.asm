// (ASCII 68) = 'D' → dibujar
// (ninguna tecla o cualquier otra) = borrar

(LOOP)
@KBD
D=M          // Leer teclado
@68
D=D-A
@DRAW
D;JEQ        // Si tecla == 'D', dibuja

// Si no es 'D' o si no hay tecla → borrar
@ERASE
0;JMP        

// -------------------
// Dibuja línea (fila 128)
(DRAW)
@20480
D=A
@addr
M=D

@32
D=A
@count
M=D

(DRAW_LOOP)
@addr
A=M
M=-1
@addr
M=M+1
@count
M=M-1
@count
D=M
@DRAW_LOOP
D;JGT

@LOOP
0;JMP

// -------------------
// Borra la línea (fila 128)
(ERASE)
@20480
D=A
@addr
M=D

@32
D=A
@count
M=D

(ERASE_LOOP)
@addr
A=M
M=0
@addr
M=M+1
@count
M=M-1
@count
D=M
@ERASE_LOOP
D;JGT

@LOOP
0;JMP
