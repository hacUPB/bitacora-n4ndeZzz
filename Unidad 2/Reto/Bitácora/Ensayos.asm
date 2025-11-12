@SCREEN      // Dirección base de la pantalla (16384)
D=A
@screenBase  // Variable simbólica donde guardamos SCREEN
M=D

@KBD         // Dirección del teclado (24576)
D=A
@kbd         // Variable simbólica para teclado
M=D

(LOOP)
    // Leer teclado
    @kbd
    A=M         // Ir a dirección del teclado
    D=M         // Leer valor (si una tecla está presionada, D != 0)

    @100
    D=D-A       // Comparar con 100 (podrías usar @0 si solo quieres verificar si se presionó algo)

    @DRAW
    D;JEQ       // Si D == 0 (se presionó la tecla 100), ir a DRAW

    @screenBase
    D=M         // Dirección base de pantalla
    @addr
    M=D         // addr = dirección actual para borrar

    @7
    D=A
    @i
    M=D         // i = 7, se borrarán 7 palabras de pantalla (líneas)

(CLEAR_LOOP)
    @addr
    A=M
    M=0         // Borrar contenido en addr

    @addr
    M=M+1       // addr++
    @i
    M=M-1       // i--
    D=M
    @CLEAR_LOOP
    D;JGT       // Si i > 0, repetir


//En este intento lo deje incompleto debido a que el dibujo no lo logré, seguiré intentando porque quizá sea un error en pixeles.
// la siguiente actividad está documentada en el reto