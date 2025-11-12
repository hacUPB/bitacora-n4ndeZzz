# [Reto 1](<../Códigos/Reto 1.asm>)  

**¿Cómo están implementadas las variables `i` y `sum`?**  
Como etiquetas simbólicas que el ensamblador traduce automáticamente a direcciones de memoria RAM.  
Por defecto, las primeras variables definidas se colocan desde la posición 16 en adelante.  

**¿En qué direcciones de memoria están estas variables?**  
Cuando no se usan registros predefinidos (como R0, R1, etc.), las primeras variables se asignan así:  

i → dirección 16  
sum → dirección 17  

**¿Cómo está implementado el ciclo `while`?**  
Con la etiqueta END. Si i >= 101, saltar a END (salir del bucle), en caso de que no, salta a la etiqueta LOOP que repite todo el proceso  

**¿Cómo se implementa la variable `i`?**  
inicialmente se declara esa variable y luego con:  
@i  
M=M+1     se suma 1 cada que se repite el bucle  


**¿En qué parte de la memoria se almacena la variable `i`?**  
En la 16 debido a que es la primera variable simbolica asignada  

**Después de todo lo que has hecho, ¿Qué es entonces una variable?**  
Es un nombre simbólico que se asigna a una dirección de memoria. Sirve para guardar datos que pueden cambiar durante la ejecución del programa (como contadores, resultados, etc.)  

**¿Qué es la dirección de una variable?**  
Es la ubicación de esta en la RAM  

**¿Qué es el contenido de una variable?**
Es el valor que hay almacenado en la ubicación de una variable  

# [Reto 2,3](<../Códigos/Reto 2-3.asm>)

**Conclusiones:**
Este codigo simbolicamente es muy similar a el del while, por lo que al menos para este ejercicio puedo concluir que es mas facil con el ciclo while, esto porque puede ser mas corto debido a que el for necesita un cuerpo y un lugar para la condicion como LOOP.  

# Reto 4  

**1. ¿Cómo se declara un puntero en C++?**  
```cpp
int *punt;
```
`punt` es una variable que almacenará la dirección de una variable de tipo `int`. El `*` en la declaración indica que es un puntero.

---

**2. ¿Cómo se define un puntero en C++?**  
```cpp
punt = &var;
```
Definir el puntero es asignarle la dirección de una variable. En este caso `punt` contendrá la dirección de `var`.

---

**3. ¿Cómo se almacena en C++ la dirección de memoria de una variable?**  
Con el operador `&`:
```cpp
punt = &var;
```
`&var` devuelve la dirección de memoria de `var`.

---

**4. ¿Cómo se escribe el contenido de la variable a la que apunta un puntero?**  
Con el operador de desreferencia `*`:
```cpp
*punt = 20;
```
Aquí `*punt` representa la variable a la que `punt` apunta. Si `punt` apunta a `var`, entonces `*punt = 20;` cambia el valor de `var` a 20.

---

**5. Conclusión:**  
- `punt` → contiene una dirección de memoria.  
- `*punt` → accede al valor almacenado en esa dirección.  
- `&variable` → obtiene la dirección de esa variable.  


# [Reto 5](<../Códigos/Reto 5.asm>)  

- Usamos RAM[16] como var.  
- Usamos RAM[17] como punt.  
- La instrucción @value carga un número en el registro A.  
- M significa la memoria en la dirección que está en A.  
- Para acceder a *punt, primero cargamos el valor de punt en A (A=M), y luego escribimos ahí.  

# [Reto 6,7](<../Códigos/Reto 6-7.asm>)

**Cómo funciona la parte clave (bis = *p_var;)**
- @18 → Cargamos en A la dirección de p_var.
- A=M → Ahora A pasa a ser el valor guardado en p_var, que es la dirección de var.
- D=M → Guardamos en D el contenido de esa dirección (el valor de var).
- @17 y M=D → Escribimos ese valor en bis.

# Reto 8  

**1. `int *pvar;`**    
- Declara una **variable puntero** llamada `pvar` que puede almacenar la **dirección de memoria** de un entero (`int`).  
- No apunta a nada todavía (contiene basura si no se inicializa).  
- Ejemplo mental: es como tener un papel donde anotar la dirección de una casa, pero aún no escribiste ninguna.  

**2. `pvar = var;`**  
- Intenta asignar a `pvar` el **valor de `var`**, no su dirección.  
- Esto **normalmente es un error de compilación** si `var` es un `int` y no un puntero, porque `pvar` espera recibir una dirección, no un valor entero.  
- Si `var` fuera un puntero, entonces se copiaría esa dirección.  

**3. `var2 = *pvar;`**   
- Lee el **contenido** de la dirección que guarda `pvar` y lo asigna a `var2`.  
- `*pvar` significa “el valor al que apunta `pvar`”.  
- Ejemplo: si `pvar` guarda la dirección de `var`, esto sería equivalente a `var2 = var;`.  

**4. `pvar = &var3;`**  
- Guarda en `pvar` la **dirección de memoria** de `var3`.  
- Ahora `pvar` “apunta” a `var3`.  

![alt text](<../../Imagenes/Resultado final reto 5-8.png>)

__________________________  


# [Código reto 9](<../Códigos/Reto 9.asm>)
# [Análisis reto 9](<Reto 9_notas.md>)