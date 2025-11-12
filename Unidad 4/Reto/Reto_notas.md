# Análisis hecho durante la creación del proyecto, requisitos y estructuras:

## Estructuras de datos usadas

-   **Arreglo dinámico (`vector`)**: almacena las gotas de lluvia
    activas.
-   **Pila (`stack`)**: acumula nuevas gotas antes de pasarlas al
    arreglo principal.
-   **Arreglo dinámico (`vector`)**: guarda las partículas que aparecen
    cuando una gota toca el fondo.

## Memoria

-   Cada gota y partícula se guarda en el **heap** usando
    `std::make_unique`.
-   Cuando se eliminan del `vector`, el `unique_ptr` libera
    automáticamente su memoria.
-   Esto evita fugas de memoria y mantiene el programa eficiente.

## Ciclo de vida de los objetos

-   **Gotas**: nacen arriba → caen → al llegar al fondo generan
    partículas → desaparecen.
-   **Partículas**: se crean al morir una gota → viven poco tiempo (se
    reduce `lifespan`) → se borran al llegar a 0.

## Interactividad

-   Tecla **`c`**: cambia el color de **todas** las gotas y partículas a
    un mismo color.
-   Tecla **`m`**: agrega más gotas de lluvia al sistema.


| **Requisito** | **Dónde se cumple en el código** | **Por qué se cumple** |
|---------------|----------------------------------|------------------------|
| **1. Combinación de estructuras de datos** | - `std::vector<std::unique_ptr<LineDrop>> drops` (gotas)<br>- `std::vector<std::unique_ptr<Particle>> particles` (partículas)<br>- `std::stack<std::unique_ptr<LineDrop>> dropStack` (pila de nuevas gotas) | Se usan en conjunto un **vector** para manejar elementos activos y una **pila** para gestionar las gotas temporales antes de agregarlas. Esto cumple el requisito de combinar estructuras de datos. |
| **2. Interactividad** | Método `keyPressed(int key)` | El usuario puede presionar:<br>- **`'c'`** para cambiar el color de todas las gotas y partículas.<br>- **`'m'`** para agregar manualmente más gotas. Esto modifica la visualización y el comportamiento de la obra en tiempo real. |
| **3. Gestión de memoria** | Uso de `std::unique_ptr` en `drops`, `particles` y `dropStack` | Los objetos dinámicos son gestionados automáticamente gracias a `unique_ptr`. Al eliminar elementos con `erase` o `pop`, la memoria se libera de forma segura, evitando fugas. Esto garantiza un uso eficiente de recursos. |

![alt text](../Imagenes/imagen.png)
![alt text](<../Imagenes/Imagen 2.png>)


# Pruebas del [programa de lluvia](https://youtu.be/LK57rLMu8TI)

| Nº | Nombre de la prueba                  | Acción realizada                                                                 | Expectativa                                                                                           | Resultado esperado                                                                 |
|----|---------------------------------------|----------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------|
| 1  | Creación y acumulación de gotas       | Ejecutar el programa y observar que se generan nuevas gotas de forma aleatoria.   | Las gotas aparecen desde la parte superior y aumentan en cantidad a medida que corre el programa.     | En pantalla se observa la lluvia constante de líneas que caen desde arriba.        |
| 2  | Interactividad con el teclado         | Presionar la tecla **c** para cambiar el color y la tecla **m** para añadir más.  | Con **c**, todas las gotas y partículas cambian a un nuevo color uniforme. Con **m**, se generan 5 más.| Los cambios se ven reflejados inmediatamente: cambio global de color o más gotas.  |
| 3  | Eliminación de partículas muertas     | Dejar que gotas lleguen al fondo y se conviertan en partículas. Observar su ciclo.| Las partículas se dispersan, se desvanecen progresivamente y luego desaparecen de la memoria.         | En la consola se registran mensajes de eliminación y en pantalla dejan de verse.   |

## Prueba 1
![alt text](<../Imagenes/Prueba1 reto4a.png>)
![alt text](<../Imagenes/Prueba1 reto4b.png>)

## Prueba 2
![alt text](<../Imagenes/Prueba2 reto4.png>)

## Prueba 3
![alt text](<../Imagenes/Prueba3 reto4.png>)