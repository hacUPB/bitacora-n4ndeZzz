# Punteros en C++

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
