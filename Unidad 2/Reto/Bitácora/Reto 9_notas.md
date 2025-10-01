## Conceptos rápidos sobre instrucciones Hack usados aquí
- `@X` — A-instr: carga el valor X en el registro `A` (si X es etiqueta, se carga la dirección asociada).  
- `D=A` / `D=M` / `D=D+M` — Operan sobre el registro `D` (otro registro temporal).  
- `M=D` — Escribe el contenido de `D` en la memoria cuya dirección está en `A`.  
- `0;JMP` — Salto incondicional a la dirección contenida en `A`. (El salto lleva la ejecución a la etiqueta que se haya cargado previamente con `@Etiqueta` o fijada con `A=`/`A=M`.)  
- `(...)` — Define una etiqueta (dirección de memoria del programa) a la que se puede saltar con `@Etiqueta` + `0;JMP`.

---

## Explicación paso a paso (bloque por bloque)

### 1) Inicializar `a` con 6
```asm
@6
D=A
@1
M=D        // a = 6
```
- `@6` coloca el número 6 en el registro `A`.  
- `D=A` copia 6 a `D`.  
- `@1` pone la dirección 1 en `A` (nos referimos a `RAM[1]`).  
- `M=D` escribe 6 en `RAM[1]`. => **RAM[1] = 6**.

---

### 2) Inicializar `b` con 9
```asm
@9
D=A
@2
M=D        // b = 9
```
- Análogo al caso anterior: deja **RAM[2] = 9**.

---

### 3) "Llamar" a la función `Suma`
```asm
@Suma
0;JMP      // Saltar a la "función" suma
```
- `@Suma` carga la dirección de la etiqueta `(Suma)` en `A`.  
- `0;JMP` salta incondicionalmente a esa dirección.  
- **Observación importante**: esto es un `goto` a la función, **no** un `call` con pila ni push automático de la dirección de retorno. Para poder regresar, el código usa una etiqueta fija `(ReturnFromSuma)` que la función conoce y a la que salta al terminar. Es una técnica simple válida sólo si la función y el punto de retorno están acordados de antemano y no hay anidamiento de llamadas.

---

### 4) Punto de retorno en `main` — leer el valor retornado y guardarlo en `c`
```asm
(ReturnFromSuma) // Punto al que "regresa" la función
@3
D=M        // D = valor retornado (var)
@4
M=D        // c = var
```
- `(ReturnFromSuma)` define la etiqueta a la que `Suma` saltará cuando termine.  
- `@3` y `D=M` cargan en `D` el contenido de `RAM[3]`, que la función `Suma` dejó como resultado (`var`).  
- `@4` y `M=D` guardan ese valor en `RAM[4]` (variable `c`).

---

### 5) "Imprimir" `c` (simulación)
```asm
@4
D=M
@0
M=D        // Mostrar resultado en RAM[0]
```
- Cargamos `c` desde `RAM[4]` a `D` y luego escribimos `D` en `RAM[0]`.  
- En este ejemplo `RAM[0]` actúa como la salida visible (equivalente a mostrar en pantalla).

---

### 6) Etiqueta de fin del programa
```asm
(END)
@END
0;JMP
```
- Paraliza la ejecución dejando el programa en un bucle infinito en la etiqueta `(END)`.

---

### 7) Cuerpo de la función `Suma`
```asm
(Suma)
@1
D=M        // D = a
@2
D=D+M      // D = a + b
@3
M=D        // var = a + b

@ReturnFromSuma
0;JMP      // Volver a main
```
- `(Suma)` define la entrada de la función.  
- `@1` / `D=M`: carga `a` (RAM[1]) en `D`.  
- `@2` / `D=D+M`: suma `b` (RAM[2]) al contenido de `D` → `D = a + b`.  
- `@3` / `M=D`: escribe la suma en `RAM[3]` (aquí usamos `var` como "valor de retorno").  
- Finalmente `@ReturnFromSuma` / `0;JMP` salta **de regreso** a la etiqueta `(ReturnFromSuma)` que está en `main`.

---
## Ejecución: valores de RAM (snapshot ejemplo)
Estado importante de la RAM **tras** la ejecución completa del programa (valores relevantes):

- RAM[0] = 15   ← valor "impreso" (salida simulada)  
- RAM[1] = 6    ← a  
- RAM[2] = 9    ← b  
- RAM[3] = 15   ← var (resultado dentro de suma)  
- RAM[4] = 15   ← c (variable en main)

Así, `c = 15` (6 + 9) y ese valor se copia a RAM[0] para "mostrarlo".

---
![alt text](<../../Imagenes/Resultado reto 9.png>)  


## Limitaciones y mejoras posibles

1. **No hay pila ni llamadas anidadas**: la técnica de `@Suma 0;JMP` + `@ReturnFromSuma 0;JMP` es una simulación simple. No permite llamadas anidadas o recursivas porque no se guarda una dirección de retorno única por llamada.  
2. **Mejor: simular call/return con pila**: puedes implementar una convención de pila usando una posición (por ejemplo `RAM[15]` como puntero `SP`) y luego **push** de la dirección de retorno antes de hacer `0;JMP Suma`, y en `Suma` **pop** de esa dirección y saltar a ella con `0;JMP` usando `A` cargado desde memoria. Eso requiere más instrucciones pero es la forma correcta de simular llamadas realistas.  
3. **Variables en memoria fija**: usar direcciones fijas (`RAM[1]`, `RAM[2]`, ...) está bien para ejemplos pequeños, pero para programas reales es mejor usar un marco de pila (stack frame) para variables locales y parámetros.  

---