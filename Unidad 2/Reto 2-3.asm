// sum = 0
@sum
M=0

// i = 1
@1
D=A
@i
M=D

(FOR_COND)
    // if (i > 100) goto END
    @i
    D=M
    @101
    D=D-A
    @END
    D;JGE

    // sum += i
    @i
    D=M
    @sum
    M=D+M

    // i++
    @i
    M=M+1

    // Volver a condición
    @FOR_COND
    0;JMP

(END)
    @END
    0;JMP


//Este codigo simbolicamente es muy similar a el del while, por lo que al menos para este ejercicio puedo concluir que es mas facil con el ciclo while
//esto porque puede ser mas corto debido a que el for necesita un cuerpo y un lugar para la condicion como LOOP

// sum = 0
@sum
M=0

// i = 1 (Inicialización)
@1
D=A
@i
M=D

@CHECK      // Ir directamente a verificar la condición (como en un for)

(BODY)
    // sum = sum + i
    @i
    D=M
    @sum
    M=D+M

(INCREMENT)
    // i++
    @i
    M=M+1

(CHECK)
    // if i > 100 goto END
    @i
    D=M
    @101
    D=D-A
    @END
    D;JGE

    // si la condición sigue siendo verdadera, ejecutar el cuerpo
    @BODY
    0;JMP

(END)
    @END
    0;JMP
