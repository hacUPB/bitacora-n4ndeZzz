// var = 10
@10
D=A
@16
M=D

// punt = &var
@16
D=A
@17
M=D

// *punt = 20
@20
D=A
@17
A=M
M=D

(END)
@END
0;JMP


// Explicación:

//Usamos RAM[16] como var.

//Usamos RAM[17] como punt.

//La instrucción @value carga un número en el registro A.

//M significa la memoria en la dirección que está en A.

//Para acceder a *punt, primero cargamos el valor de punt en A (A=M), y luego escribimos ahí.