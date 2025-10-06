# Actividad 1

---

## Análisis de funcionalidad del código:

En ejecución, el código lo que hace es generar aleatoriamente partículas 3 tipos diferentes, las cuales inician en un estado de órbita aleatoria, cada tipo tiene un color y tamaño distinto. En el programa al presionar un tecla, genera una respuesta diferente, la tecla "n", es el estado inicial y se visualiza como se describió anteriormente; la tecla "r" por su parte lo que hace es repeler estas partículas, al contrario de lo que haría la tecla "a" que se encarga de atraerlas; por último la letra "s" lo que hace es detenerlas.

En las imágenes no se visializa el mouse, pero se identifican las 3 pruebas principales, ya que el "s" se ve completamente estático.

![A](<../Imágenes/Estado a.png>)![N](<../Imágenes/Estado n.png>)![R](<../Imágenes/Estado r.png>)

## Análisis de los patrones de diseño:

* **Observer**: las partículas son observadores (`Particle` implementa `Observer`) y reciben notificaciones de la clase `Subject` (que en este caso hereda `ofApp`).
* **State**: cada partícula cambia su comportamiento dinámicamente según el estado (`NormalState`, `AttractState`, `RepelState`, `StopState`).
Todas las partículas arrancan en `NormalState`, pero podrías hacer que la fábrica defina su estado inicial según el tipo de partícula.
* **Factory**: `ParticleFactory` crea distintos tipos de partículas (`star`, `shooting_star`, `planet`).

## Análisis de cosas claves del código:

* **Encapsulamiento**:

   * Las partículas ocultan su estado interno (`state`) y solo cambian de comportamiento a través de `setState`.
   * `Subject` maneja la lista de observadores sin exponer la implementación.

* **Herencia y polimorfismo**:

   * `Particle` hereda de `Observer` y redefine `onNotify`.
   * `State` es una interfaz abstracta y las subclases (`NormalState`, `AttractState`, etc.) redefinen `update()` → esto es polimorfismo puro.

* **Uso de patrones de diseño**:

   * El patrón **Observer** permite que al presionar una tecla (`s`, `a`, `r`, `n`), todas las partículas cambien su comportamiento al mismo tiempo.
   * El patrón **State** encapsula comportamientos distintos y los intercambia dinámicamente.
   * El patrón **Factory** centraliza la creación de partículas de diferentes tipos.



