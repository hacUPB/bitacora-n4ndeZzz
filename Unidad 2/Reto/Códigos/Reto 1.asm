// Inicializar i = 1
@1
D=A
@i
M=D

// Inicializar sum = 0
@sum
M=0

(LOOP)
    // Comparar si i <= 100
    @i
    D=M
    @101
    D=D-A         // D = i - 101
    @END
    D;JGE         // Si i >= 101, salir del bucle

    // sum = sum + i
    @i
    D=M
    @sum
    M=D+M

    // i++
    @i
    M=M+1

    // Repetir
    @LOOP
    0;JMP

(END)
    @END
    0;JMP         // Bucle infinito para terminar


