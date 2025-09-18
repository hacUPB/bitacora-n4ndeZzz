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

<video controls src="Video (2).mp4" title="Title"></video>