
@SCREEN
D=A
@screenBase
M=D     

@KBD
D=A
@kbd
M=D          // kbd = 24576

(LOOP)
    // Leer teclado
    @kbd
    A=M
    D=M
    @100
    D=D-A
    @DRAW
    D;JEQ     // Si D == 0 (tecla 'd'), salta a DRAW

    // Si no, borrar
    @screenBase
    D=M
    @addr
    M=D

    @7
    D=A
    @i
    M=D

(CLEAR_LOOP)
    @addr
    A=M
    M=0

    @addr
    M=M+1
    @i
    M=M-1
    D=M
    @CLEAR_LOOP
    D;JGT

    @LOOP
    0;JMP

(DRAW)
    @screenBase
    D=M
    @addr
    M=D

    // Línea 1
    @49152
    D=A
    @addr
    A=M
    M=D
    @addr
    M=M+1

    // Línea 2
    @49152
    D=A
    @addr
    A=M
    M=D
    @addr
    M=M+1

    // Línea 3
    @0
    D=A
    @addr
    A=M
    M=D
    @addr
    M=M+1

    // Línea 4
    @12288
    D=A
    @addr
    A=M
    M=D
    @addr
    M=M+1

    // Línea 5
    @0
    D=A
    @addr
    A=M
    M=D
    @addr
    M=M+1

    // Línea 6
    @33024
    D=A
    @addr
    A=M
    M=D
    @addr
    M=M+1

    // Línea 7
    @32256
    D=A
    @addr
    A=M
    M=D

    @LOOP
    0;JMP
