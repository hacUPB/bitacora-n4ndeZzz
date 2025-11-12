// Si hay tecla presionada → enciende la fila superior de la pantalla

@KBD        // Dirección del teclado (24576)
D=M         // D = valor leído (código de tecla)
@NO_KEY
D;JEQ       // Si D == 0, no hay tecla → salta a NO_KEY

// --- Tecla presionada → dibujar fila superior ---
@SCREEN     // Dirección de inicio de pantalla (16384)
M=-1        // -1 = 1111111111111111 → enciende los 16 píxeles de la primera palabra
@END
0;JMP       // Salta al final

(NO_KEY)
// --- Ninguna tecla → apagar fila superior ---
@SCREEN
M=0         // Apagar píxeles
(END)
@END
0;JMP       // Bucle infinito
