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

### 7. En el código presentado, ¿Cómo se asegura que no haya fugas de memoria? ¿Qué papel juega el destructor en la clase `LinkedList`?

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
