## 1. ¿Cómo se gestiona la memoria en una implementación manual de un stack en C++? Reflexiona sobre cómo el uso de new y delete en la creación y destrucción de nodos afecta el rendimiento y la seguridad de tu programa.
Cuando empecé a programar mi stack manual, me di cuenta de que me convertí en el "administrador" directo de la memoria de mi programa. Cada vez que presiono la tecla **'a'**, mi función `push` usa `new Node(...)`.  
Lo que realmente estoy haciendo ahí es pedirle al sistema un trocito de memoria del **heap** para guardar la posición de mi nuevo círculo.

Esto me da un control total, lo cual es genial, pero también es una gran responsabilidad. El rendimiento se ve afectado porque cada `new` y `delete` es una pequeña operación que consume tiempo.  
Pero lo más importante es la seguridad: si me olvido de llamar a `delete` en la función `pop`, ese pedazo de memoria queda "flotando", ocupado pero inaccesible.  
Es como dejar basura en la memoria, y si lo hago muchas veces, mi programa se volverá lento y pesado.

---

## 2. ¿Por qué es importante liberar la memoria cuando se desapila un nodo en un stack? Considera las consecuencias de no liberar memoria en términos de fugas de memoria y cómo esto puede impactar aplicaciones de largo tiempo de ejecución.
Al principio no le di mucha importancia a la línea `delete temp;` en la función `pop`. Pero luego entendí que es quizás la parte más crítica de todo el código.

No liberar esa memoria es lo que causa una **fuga de memoria (memory leak)**.  
Mi profesor lo explicó con una analogía que me ayudó mucho: es como alquilar casilleros (`new Node`) uno tras otro y nunca devolver las llaves.  
Los casilleros siguen a tu nombre, pero has perdido las llaves y ya no puedes usarlos. Nadie más puede usarlos tampoco.

Para una aplicación que corre por mucho tiempo, como una instalación interactiva en un museo, una pequeña fuga se convierte en un problema gigante.  
La aplicación consumiría más y más RAM con el paso de las horas hasta que, inevitablemente, el sistema operativo la cerraría.  
Así que, sí, liberar la memoria es básicamente hacer una buena limpieza para que el programa se mantenga saludable. 🧹

---

## 3. ¿Qué diferencias existen entre usar un stack de la STL (std::stack) y crear un stack manualmente? Explora cómo la abstracción que proporciona la STL puede simplificar la implementación, pero también cómo una implementación manual ofrece mayor control sobre la gestión de recursos.
Después de sudar un poco para que mi stack funcionara bien, me puse a investigar y vi que C++ ya tiene `std::stack` en su **Librería Estándar (STL)**.  
La diferencia es como construir tu propio carro desde cero versus comprar uno de fábrica.

- **Mi Stack Manual:** Me dio un control absoluto. Tuve que entender cómo funcionan los punteros y gestionar `new` y `delete` yo mismo. Fue una experiencia de aprendizaje increíble y me siento mucho más cómodo con la gestión de memoria ahora.  
- **`std::stack` de la STL:** Es la opción fácil y segura. Él se encarga de toda la gestión de memoria por debajo. No tengo que preocuparme por `new` o `delete`, lo que elimina casi por completo el riesgo de fugas de memoria. Es súper optimizado y, para ser honesto, para la mayoría de los proyectos, probablemente usaría este para ir más rápido y seguro.

**En resumen:** construir el mío fue una clase maestra sobre cómo funcionan las cosas, pero en la práctica, `std::stack` es mi mejor amigo para no cometer errores.

---

## 4. ¿Cómo afecta la estructura de un stack al orden de acceso y eliminación de elementos? Analiza cómo la naturaleza LIFO (Last In, First Out) del stack influye en los tipos de problemas que esta estructura de datos puede resolver eficientemente.
La estructura de una pila es súper estricta: **LIFO (Last-In, First-Out)**. El último que entra es el primero que sale.

Lo visualizo como una pila de platos sucios. Pones un plato encima (**push**) y cuando vas a lavar, coges el de más arriba (**pop**). No puedes sacar uno del medio sin romperlo todo.

Este comportamiento es sorprendentemente útil para resolver ciertos tipos de problemas.  
El ejemplo más claro para mí es la función **"Deshacer" (Undo)** de cualquier programa. Cada acción que haces (escribir, borrar, dibujar) se mete en una pila.  
Si quieres deshacer, el programa simplemente saca la última acción de la pila y la revierte.  
Funciona perfectamente porque necesitas deshacer las cosas en el orden inverso al que las hiciste.  
También sé que es la base de cómo el procesador gestiona las llamadas a funciones en el código. ¡Está en todas partes!

---

## 5. ¿Cómo podrías modificar el stack para almacenar tipos de datos más complejos (e.g., objetos con múltiples atributos) sin causar problemas de memoria? Reflexiona sobre cómo gestionar adecuadamente la memoria para objetos más complejos y cómo esto afectaría tu implementación actual.
Mi stack actual solo guarda un `ofVec2f`, que es simple. Pero, ¿y si quisiera guardar un objeto más complejo, como una **Particula** con posición, velocidad, color y tiempo de vida?

Si simplemente usara un puntero crudo (`Particula*`), estaría pidiendo a gritos tener problemas. Tendría que acordarme de hacer `delete` al objeto `Particula` antes de hacer `delete` al `Node`, lo que complica la lógica y aumenta el riesgo de errores.

La solución moderna que he estado viendo en clase son los **punteros inteligentes**.  
Modificaría mi `Node` para que en lugar de un `ofVec2f`, tuviera un `std::unique_ptr<Particula>`.

```cpp
#include <memory>

class Node {
public:
    std::unique_ptr<Particula> data;
    Node* next;
    // ...
};
```
Es una gestión de memoria automática y segura. De esta forma, puedo trabajar con objetos todo lo complejos que quiera sin tener que preocuparme por causar fugas de memoria. ¡Es un salvavidas! 🚀
