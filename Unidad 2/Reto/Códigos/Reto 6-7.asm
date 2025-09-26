// var = 10
@10
D=A
@16     // RAM[16] = var
M=D

// bis = 5
@5
D=A
@17     // RAM[17] = bis
M=D

// p_var = &var
@16
D=A
@18     // RAM[18] = p_var
M=D

// bis = *p_var
@18
A=M     // A = RAM[18] → dirección de var
D=M     // D = RAM[var]
@17
M=D     // bis = D

(END)
@END
0;JMP


//Cómo funciona la parte clave (bis = *p_var;)

//@18 → Cargamos en A la dirección de p_var.

//A=M → Ahora A pasa a ser el valor guardado en p_var, que es la dirección de var.

//D=M → Guardamos en D el contenido de esa dirección (el valor de var).

//@17 y M=D → Escribimos ese valor en bis.