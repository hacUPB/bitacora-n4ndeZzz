//(ASCII 68) = pintar negro
//(ASCII 69) = pintar blanco

(LOOP)
@KBD
D=M          // Lee la tecla presionada
@68
D=D-A
@DRAW
D;JEQ        // Si tecla == 'D' (68), dibujar

@KBD
D=M
@69
D=D-A
@ERASE
D;JEQ        // Si tecla == 'E' (69), ir a borrar

@LOOP
0;JMP        // Si no es 'D' ni 'E', seguir esperando

// -------------------
// Dibuja línea (fila 128)
(DRAW)
@20480       // Dirección base de la fila 128
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
M=-1         // Escribir 0xFFFF → encender 16 píxeles

@addr
M=M+1
@count
M=M-1
@count
D=M
@DRAW_LOOP
D;JGT        // Repetir 32 veces

@LOOP
0;JMP        // Volver a escuchar el teclado

// -------------------
// Borra la línea (fila 128)
(ERASE)
@20480       // Dirección base de la fila 128
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
M=0          // Escribir 0x0000 → apagar 16 píxeles

@addr
M=M+1
@count
M=M-1
@count
D=M
@ERASE_LOOP
D;JGT        // Repetir 32 veces

@LOOP
0;JMP        // Volver a escuchar el teclado
