### 3. ¿Qué es una lista enlazada y en qué se diferencia de un arreglo en cuanto a la forma en que los elementos están almacenados en la memoria?
Una lista enlazada es una estructura de datos donde cada nodo contiene la información y un puntero al siguiente nodo.  
La diferencia principal con un arreglo es que en los arreglos los elementos están en posiciones continuas de memoria y en el stack, mientras que en una lista enlazada cada nodo puede estar en cualquier parte de la memoria (heap), y lo que los conecta son los punteros.

---

### 4. Al observar el código de una lista enlazada en C++, ¿Cómo crees que se vinculan los nodos entre sí? ¿Qué estructura se utiliza para lograr esta conexión?
Los nodos se vinculan por medio de punteros.  
Cada nodo tiene un campo que apunta al siguiente nodo en la lista. Por ejemplo:

```cpp
struct Node {
    int data;
    Node* next; // puntero al siguiente nodo
};
```

---

### 5. ¿Cómo se gestiona la memoria en una lista enlazada?
- **Creación:** cuando se agrega un nodo nuevo, se utiliza `new` para reservar memoria en el heap.
  ```cpp
  Node* nuevo = new Node();
  ```
- **Destrucción:** cuando ya no se necesita, se libera con `delete`.
  ```cpp
  delete nodo;
  ```
---

### 6. ¿Qué ventajas ofrece una lista enlazada frente a un arreglo para insertar o eliminar elementos en posiciones intermedias?
En una lista enlazada no es necesario mover todos los elementos después de una inserción/eliminación. Solo se ajustan los punteros.  
En un arreglo, insertar en medio requiere desplazar varios elementos, lo cual es más costoso.

---

### **7. Explica cómo cambia la estructura en memoria de una lista enlazada al agregar un nuevo nodo al final de la lista.**

Cuando se agrega un nodo al final, se crea un nuevo nodo en el heap y se
ajusta el puntero del último nodo existente para que apunte a este nuevo
nodo. Esto no requiere mover los demás elementos, solo actualizar el
último puntero.

---

### 8. ¿Qué sucede en la memoria cuando se invoca el método `clear()` en una lista enlazada?
1. Se empieza desde el primer nodo.  
2. Se guarda una referencia temporal al siguiente nodo.  
3. Se elimina el nodo actual con `delete`.  
4. Se avanza al siguiente nodo.  
5. Se repite hasta que no quede ninguno.  

Al final, todos los nodos son liberados y la lista queda vacía (apunta a null).

---

### 9. Explica cómo cambia la estructura en memoria de una lista enlazada al agregar un nuevo nodo al final.
- Se crea un nodo en el heap con `new`.  
- El puntero `next` del último nodo pasa a apuntar al nuevo nodo.  
- En memoria, los nodos no están continuos, pero lógicamente quedan conectados.  

En cuanto a rendimiento, agregar al final implica recorrer toda la lista (O(n)), a menos que se guarde un puntero directo al último nodo.

---

### **10. Analiza una situación en la que utilizar una lista enlazada sería más ventajoso que utilizar un arreglo.**

La lista enlazada es más ventajosa cuando hay que insertar o eliminar
elementos en posiciones intermedias.
En un arreglo esas operaciones son costosas porque hay que mover
elementos, pero en la lista solo se actualizan punteros.

------------------------------------------------------------------------

### **11. Después de estudiar el manejo de memoria en listas enlazadas, ¿cómo aplicarías este conocimiento para diseñar una estructura de datos personalizada para una aplicación creativa?**

Si diseñara mi propia estructura, tendría en cuenta:
- Usar punteros controlados y liberar memoria siempre.
- Implementar destructores que limpien todo.
- Mantener la eficiencia de creación y destrucción.

Por ejemplo, para un proyecto de arte generativo con partículas, usaría
listas para manejar dinámicamente la vida de cada partícula.

------------------------------------------------------------------------

### **12. Reflexiona sobre las diferencias en la gestión de memoria entre C++ y un lenguaje con recolección de basura automática como C#.**

En C++ el programador controla todo con `new` y `delete`. Eso da más
control y rendimiento, pero también más riesgo de errores.
En C# la memoria se gestiona automáticamente con garbage collector, lo
que evita fugas, pero se pierde el control exacto sobre cuándo se libera
la memoria.

------------------------------------------------------------------------

### **13. Imagina que estás optimizando una pieza de arte generativo que usa listas enlazadas para representar elementos en movimiento.**

Tendría en cuenta:
- Liberar la memoria de los nodos al eliminar elementos.
- Usar destructores o `clear()` para limpiar al reiniciar.
- Revisar el rendimiento porque demasiados nodos pueden ser lentos.
- Manejar punteros con cuidado para evitar fugas de memoria.

------------------------------------------------------------------------

### **14. Pruebas: pregunta a ChatGPT cómo podrías probar las partes del programa y el programa completo. Luego realiza las pruebas y verifica si los resultados coinciden con tus expectativas.  
---

## Prueba 1: Constructor `LinkedList`
- **Acción realizada:** Inicialicé una lista con `LinkedList list;` y revisé `head`, `tail` y `size`.
- **Expectativa:** Que `head` y `tail` apunten al mismo nodo y que `size = 1`.
- **Resultado obtenido:**  
  ```
  Head: (512, 384)
  Tail: (512, 384)
  Size: 1
  ```
  ![alt text](<Imagenes/Prueba 1.png>)

- **Conclusión:** El constructor funcionó correctamente y creó el primer nodo en el centro de la pantalla. 

---

## Prueba 2: `addNode(float x, float y)`
- **Acción realizada:** Agregué dos nodos con coordenadas (100,100) y (200,200). Revisé el tamaño y la posición de `tail`.
- **Expectativa:** Que `size = 3` y `tail = (200,200)`.
- **Resultado obtenido:**  
  ```
  Size: 3
  Tail position: (200, 200)
  ```
  ![alt text](<Imagenes/Prueba 2.png>)  

- **Conclusión:** Los nodos se agregaron y enlazaron correctamente. El puntero `tail` se actualizó. 

---

## Prueba 3: `update(float x, float y)`
- **Acción realizada:** Llamé a `list.update(400,300)` y recorrí la lista para imprimir posiciones.
- **Expectativa:** Que el primer nodo tomara la nueva posición y que los demás heredaran las anteriores.
- **Resultado obtenido:**  
  ```
  Node 1: (400, 300)
  Node 2: (512, 384)
  Node 3: (100, 100)
  ```
  ![alt text](<Imagenes/Prueba 3.png>)

- **Conclusión:** El método funciona bien. Los nodos siguen la lógica de "serpiente". 

---

## Prueba 4: `clear()`
- **Acción realizada:** Llamé a `list.clear()` y revisé `head`, `tail` y `size`.
- **Expectativa:** Que la lista quedara vacía (`head = nullptr`, `tail = nullptr`, `size = 0`).
- **Resultado obtenido:**  
  ```
  Head after clear: 0x0
  Tail after clear: 0x0
  Size after clear: 0
  ```
![alt text](<Imagenes/Prueba 4 A.png>)
![alt text](<Imagenes/Prueba 4 B.png>)

- **Conclusión:** La memoria fue liberada correctamente y no quedaron nodos huérfanos. 

---