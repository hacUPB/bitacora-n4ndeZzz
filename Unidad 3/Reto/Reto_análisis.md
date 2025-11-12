
## Gestión de Memoria (Stack vs. Heap) 

* **Heap (Memoria Principal):** La mayor parte de los datos, como el `std::vector` que contiene todas las esferas, se almacena en el **Heap**. Esta es una memoria grande y flexible que persiste mientras tu aplicación está en ejecución. Es ideal para almacenar colecciones de objetos o datos cuyo tamaño puede cambiar.

En este programa no estoy usando directamente `new` ni punteros inteligentes, pero el contenedor `std::vector<Sphere> spheres` internamente reserva memoria en el **heap**. Cuando hago `spheres.emplace_back(...)` en `buildGrid()`, el vector almacena dinámicamente los objetos `Sphere` en memoria heap. Esa memoria se gestiona automáticamente por el propio vector: si limpio con `spheres.clear()` o si el programa termina, se libera.

* **Stack (Memoria Rápida):** Las variables locales dentro de las funciones (por ejemplo, las que se usan para calcular la intersección del rayo) se crean en el **Stack**. Es una memoria muy rápida pero temporal; los datos que contiene se destruyen automáticamente cuando la función termina.

Las funciones de OpenFrameworks como `update()`, `draw()` o `keyPressed()` crean variables locales que existen **solo mientras dura la ejecución de cada función**. Por ejemplo, en `mousePressed()` cuando calculo vectores como `rayStart`, `rayEnd` o `dir`, estos se almacenan en el **stack**. Una vez que la función termina, la memoria de estas variables se libera automáticamente.

* **Objetos en **memoria global:**
Las instancias que forman parte de la clase `ofApp`, como `spheres`, `params` y `cam`, se almacenan en la memoria del **heap global del framework**, ya que OpenFrameworks gestiona el ciclo de vida de la aplicación. Estos objetos existen **durante toda la ejecución del programa**.

En resumen: los datos grandes y persistentes van al **Heap**; los datos pequeños y temporales van al **Stack**.

---

## Conceptos Básicos de Programación Gráfica aprendidos

1.  **El Ciclo de la Aplicación:** Comprensión del "corazón" de toda aplicación gráfica o de videojuego:
    * **`setup()`:** Se ejecuta **una vez** para inicializar todo.
    * **`update()`:** Se ejecuta en **cada fotograma** para actualizar la lógica (mover cosas, calcular animaciones).
    * **`draw()`:** Se ejecuta en **cada fotograma** (justo después de `update`) para dibujar el estado actual en la pantalla.

2.  **Organización de Datos:** Agrupar variables relacionadas en `structs` (como `Sphere` y `GridParams`) hace el código mucho más limpio y fácil de entender que tener muchas variables sueltas.

3.  **Transformación de Coordenadas:** La función de *raycasting* me enseñó un concepto clave: cómo traducir una acción en un espacio 2D (el clic del mouse en la pantalla) a un concepto en un espacio 3D (un rayo que viaja por el mundo virtual) para poder interactuar con los objetos.

https://youtu.be/c8TfET1w7Dc

## Conclusiones
Lo que aprendí es que:
- El **stack** sirve para datos temporales de funciones, como cálculos matemáticos.
- El **heap** se usa para estructuras dinámicas como `std::vector`, donde no sé de antemano cuántos objetos voy a tener.
- Los objetos miembro de la clase `ofApp` viven mientras la aplicación esté corriendo, actuando casi como memoria global controlada.

En resumen, este programa combina los tres modelos de memoria de manera natural: el stack para cálculos momentáneos, el heap para colecciones dinámicas de esferas, y la memoria global (a través de `ofApp`) para mantener el estado general de la escena.
