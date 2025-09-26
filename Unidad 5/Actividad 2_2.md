## Encapsulamiento y el "hack"

* **¿Qué es el encapsulamiento y cuál es su propósito en la programación orientada a objetos?**
    El **encapsulamiento** es el principio de agrupar datos y métodos en una sola unidad. Su propósito es proteger los datos de un objeto de accesos externos no controlados.

* **¿Por qué es importante proteger los datos de una clase y restringir el acceso desde fuera de la misma?**
    Es vital para mantener la **consistencia y la integridad** del estado del objeto, evitando que datos cruciales sean modificados de forma inesperada.

* **¿Qué significa `reinterpret_cast` y cómo afecta la seguridad del programa?**
    `reinterpret_cast` es un operador de casting que me permite tratar una dirección de memoria como si fuera de un tipo completamente diferente. Afecta la seguridad porque me permite eludir las restricciones de tipo, lo que puede llevar a comportamientos indefinidos y fallos graves.

* **¿Por qué crees que se pudo acceder a los miembros privados de `MyClass` en este experimento, a pesar de que el compilador normalmente lo impediría?**
    Se pudo porque el encapsulamiento es una **restricción a nivel de compilación**, no de ejecución. En tiempo de ejecución, todo se reduce a direcciones de memoria, y la aritmética de punteros me permite manipularlas directamente, saltándome las reglas del compilador.

* **¿Cuáles podrían ser las consecuencias de utilizar técnicas como las mostradas en este experimento en un programa real?**
    Las consecuencias serían desastrosas: corrupción de datos, fallos inesperados del programa ("crashes") y creación de vulnerabilidades de seguridad.

* **¿Qué implicaciones tiene este experimento sobre la confianza en las barreras de encapsulamiento que proporciona C++?**
    Me muestra que las barreras de C++ son una guía de buenas prácticas, no una protección absoluta. La seguridad final del código depende de mi disciplina como programador.

---

## Herencia y la relación en memoria

* **¿Cómo se organizan los atributos en memoria?**
    Los atributos de un objeto de clase derivada se organizan de forma secuencial: primero se almacenan los atributos de la **clase base**, seguidos inmediatamente por los de la **clase derivada**. 

* **¿Qué sucede si agregamos más niveles de herencia?**
    El patrón se repite. La memoria se organiza como una pila: la clase más base va primero, y cada clase derivada se añade a continuación en la memoria.

---

## Polimorfismo y Vtables en detalle

* **¿Cómo utiliza el programa las `vtables` para el polimorfismo?**
    Cada objeto con métodos virtuales tiene un puntero oculto (`vptr`) que apunta a una tabla de funciones (`vtable`). Esta tabla contiene las direcciones de los métodos virtuales de su clase. Cuando se llama a un método virtual, el programa usa el `vptr` para buscar la dirección correcta en la `vtable` y ejecutar la función apropiada para el tipo real del objeto. 

* **¿Cuál es el impacto en el rendimiento?**
    El impacto es mínimo. Las llamadas a métodos virtuales son ligeramente más lentas que las no virtuales debido al paso adicional de buscar la función en la `vtable`. Sin embargo, la flexibilidad que me ofrece el polimorfismo justifica este pequeño costo.