## **Implementación de los patrones de diseño en el proyecto “Jardín Interactivo”**

[ofApp.cpp](Reto.cpp)
[ofApp.h](Reto.h)

---

### Descripción general del proyecto

En este proyecto desarrollé un **jardín generativo interactivo en tiempo real**, donde diferentes tipos de plantas responden a eventos globales (como sol, lluvia o noche) modificando su comportamiento visual.
Cada planta tiene un **estado dinámico** que cambia su tamaño, color y crecimiento según la situación ambiental.

El proyecto fue diseñado intencionalmente para **demostrar los patrones de diseño** **Observer**, **Factory** y **State** dentro de un mismo sistema visual y autónomo.

---

## **1. Patrón Observer**

### **¿Para qué lo implementé?**

El patrón **Observer** me permitió hacer que todas las plantas reaccionaran **sincronizadamente** ante un mismo evento global (por ejemplo, la llegada del sol o la lluvia).
Esto evita que tenga que recorrer manualmente todas las plantas para cambiar su comportamiento una por una.

### **¿Cómo lo implementé?**

* Creé una clase `Subject` que maneja una lista de observadores (`IObserver*`).
* Cada planta (`Plant`) hereda de `IObserver` y se suscribe como observador en `ofApp` durante el `setup()`.
* Cuando presiono una tecla (1, 2 o 3), el método `notify(event)` envía una señal a todas las plantas para que cambien su estado según el evento recibido.

```cpp
if (key == '1') notify("sun");
else if (key == '2') notify("rain");
else if (key == '3') notify("night");
```

De esta forma, todas las plantas responden simultáneamente, pero **cada una conserva su propia lógica interna** (definida por su estado actual).

---

## **2. Patrón Factory**

### **¿Para qué lo implementé?**

El patrón **Factory** me permitió generar distintos tipos de plantas con características únicas (color, tamaño inicial y tipo), sin tener que escribir múltiples clases o estructuras repetitivas.
De esta forma, puedo extender el proyecto fácilmente con nuevas especies sin modificar el código base.

### **¿Cómo lo implementé?**

* Creé la clase `PlantFactory` con un método estático `createPlant(x, y, type)`.
* Dependiendo del tipo de planta (`flower`, `cactus`, `mushroom`), se crean instancias con atributos diferentes.

```cpp
if (type == "flower") {
    return new Plant(x, y, 10, ofColor::pink, "Flor");
} else if (type == "cactus") {
    return new Plant(x, y, 15, ofColor::green, "Cactus");
}
```

Esto me permitió crear el jardín completo con apenas unas líneas dentro del `setup()`:

```cpp
plants.push_back(PlantFactory::createPlant(150, 400, "flower"));
plants.push_back(PlantFactory::createPlant(300, 400, "cactus"));
plants.push_back(PlantFactory::createPlant(450, 400, "mushroom"));
```

---

## **3. Patrón State**

### **¿Para qué lo implementé?**

El patrón **State** fue la base del comportamiento autónomo de cada planta.
Gracias a él, cada planta puede “vivir” en un estado diferente (creciendo, floreciendo o marchitándose) y cambiar de estado en tiempo real cuando recibe una notificación del **Observer**.

### **¿Cómo lo implementé?**

* Definí una interfaz `IState` con el método virtual `update(Plant* plant)`.
* Creé tres clases derivadas:

  * `GrowingState` → hace que la planta crezca gradualmente.
  * `BloomState` → la planta cambia de color y “florece”.
  * `WitherState` → la planta se marchita y su color se apaga.

Cada planta tiene un puntero a su estado actual (`currentState`) y lo reemplaza según el evento recibido:

```cpp
if (event == "sun") setState(new GrowingState());
else if (event == "rain") setState(new BloomState());
else if (event == "night") setState(new WitherState());
```

---

## **Cómo construí la aplicación**

Basé el diseño del proyecto en tres principios de la **programación orientada a objetos y patrones de diseño**:

1. **Abstracción:**
   Separé los conceptos principales (sujeto, observador, fábrica y estado) en componentes lógicos, permitiendo que el sistema crezca sin afectar las demás partes.

2. **Encapsulamiento:**
   Cada planta maneja internamente su comportamiento y estado.
   Los eventos globales no saben *cómo* la planta reacciona, solo que *debe hacerlo*.

3. **Polimorfismo:**
   Todos los estados (`GrowingState`, `BloomState`, `WitherState`) heredan de una misma interfaz, lo que permite cambiarlos dinámicamente en tiempo de ejecución sin alterar la lógica del resto del programa.

El resultado fue un sistema **flexible, escalable y visualmente dinámico**, con una clara separación de responsabilidades entre los patrones aplicados.

---

## **Pruebas realizadas**

| **Prueba**                     | **Descripción**                                                              | **Resultado esperado**                                                                   | **Resultado obtenido**                             |
| ------------------------------ | ---------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------- | -------------------------------------------------- |
| **Observer – Evento “Sol”**    | Presiono la tecla `1` para enviar el evento `"sun"` a todas las plantas.     | Todas las plantas cambian a estado “Growing”, aumentando su tamaño y volviéndose verdes. | Todas crecen y cambian de color simultáneamente. |
| **Observer – Evento “Lluvia”** | Presiono la tecla `2` para enviar `"rain"`.                                  | Las plantas florecen, cambiando de color aleatoriamente con movimiento suave.            | Se observan variaciones de color continuo.       |
| **Observer – Evento “Noche”**  | Presiono la tecla `3` para enviar `"night"`.                                 | Todas las plantas se marchitan, reduciendo su tamaño y adoptando tonos marrones.         | Efecto de marchitamiento visible y gradual.      |
| **Factory – Nuevas plantas**   | Cambié el tipo `"flower"` por `"mushroom"` en el `setup()`.                  | Se generan hongos con tamaño y color específicos sin tocar el resto del código.          | La nueva especie aparece correctamente.          |
| **State – Cambio interno**     | Modifiqué temporalmente la planta para que cambie de estado cada 2 segundos. | Cada planta alterna entre los tres estados mostrando diferentes dinámicas.               | Transiciones fluidas y sin errores.              |


---


### [Videos de aplicación y prueba de observer y state](https://youtu.be/dwpdNUp3YWU)

### Prueba factory:  
![alt text](<../Imágenes/Prueba factory.png>)