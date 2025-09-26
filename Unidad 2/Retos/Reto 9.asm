// Programa: Simulación de
// c = suma(6, 9)
// y mostrar el resultado en RAM[0] como si fuera la salida.

// Definimos:
// RAM[0] = resultado final (simula cout)
// RAM[1] = a
// RAM[2] = b
// RAM[3] = variable temporal 'var' en suma
// RAM[4] = variable 'c' en main

// ----- MAIN -----
@6
D=A
@1
M=D        // a = 6

@9
D=A
@2
M=D        // b = 9

// Simular llamada a suma(a, b)
@Suma
0;JMP      // Saltar a la "función" suma

(ReturnFromSuma) // Punto al que "regresa" la función
@3
D=M        // D = valor retornado (var)
@4
M=D        // c = var

// Simular std::cout << c
@4
D=M
@0
M=D        // Mostrar resultado en RAM[0]

// Fin del programa
(END)
@END
0;JMP

// ----- FUNCION SUMA -----
(Suma)
@1
D=M        // D = a
@2
D=D+M      // D = a + b
@3
M=D        // var = a + b

@ReturnFromSuma
0;JMP      // Volver a main
