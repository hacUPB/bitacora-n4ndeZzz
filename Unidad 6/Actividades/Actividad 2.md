# Actividad 2:

## Adición de un nuevo tipo de partícula.

[OFAPP.CPP](<Códigos/Añadir partículas.cpp>)
[OFAPP.H](<Códigos/Añadir partículas.h>)
![alt text](<../Imágenes/Cambio 1.png>)

### Cambios en el código:

1. **En `ParticleFactory::createParticle()` (en el .cpp)**

   * Añadí un nuevo bloque `else if (type == "comet")`.
   * Definí propiedades especiales para este nuevo tipo:

     ```cpp
     else if (type == "comet") {
         particle->size = ofRandom(6, 10);
         particle->color = ofColor(255, 165, 0); // naranja brillante
         particle->velocity *= 5; // mucho más rápido
     }
     ```
   * Esto significa que el **factory ahora puede producir cometas**, además de estrellas, planetas y estrellas fugaces.

2. **En `ofApp::setup()`**

   * Agregué un bucle para generar cometas:

     ```cpp
     for (int i = 0; i < 3; ++i) {
         Particle* p = ParticleFactory::createParticle("comet");
         particles.push_back(p);
         addObserver(p);
     }
     ```

---

### Qué hace cada patrón en este contexto

**Observer**

* *No fue modificado.*
* Su función sigue siendo que las partículas reaccionen a los **eventos globales** enviados por `ofApp` (como `"stop"`, `"attract"`, `"repel"`, `"normal"`).
* Todas las partículas (incluyendo los nuevos **comets**) están **suscritas como observadores** y responden a los mismos eventos.
* Ejemplo: si presionas `s`, **todas las partículas (incluyendo los comets) se detienen**.

Entonces, la adición del nuevo tipo **no cambia el Observer**, solo amplía el grupo de partículas que están suscritas.

---

**State**

* *Tampoco fue modificado.*
* Los estados (`NormalState`, `AttractState`, `RepelState`, `StopState`) siguen siendo los mismos.
* Los **comets también usan estos estados**, porque heredan el mismo comportamiento de `Particle`.
* Ejemplo: si un cometa está en estado `AttractState`, se moverá hacia el mouse igual que las demás partículas, pero **su velocidad base es mayor**, así que el efecto visual será distinto.

El **State aporta polimorfismo**: cada partícula puede estar en un estado distinto en un mismo instante, y el código no cambia.

---

**Factory**

* *Sí fue modificado.*
* El patrón Factory es el encargado de **decidir cómo inicializar un objeto Particle según el tipo** que le pases como string (`"star"`, `"planet"`, `"shooting_star"`, `"comet"`).
* Con el nuevo bloque `else if ("comet")`, ahora puede fabricar **otro tipo especializado de partícula**.
* Esto hace que sea muy fácil extender el sistema: **para agregar nuevas partículas solo modifico la fábrica y el setup, no todo el resto del programa**.

Aquí es donde realmente hice la diferencia. Añadí un nuevo "caso" en la fábrica.

---

## Adición de un nuevo evento

[Estado.h](<Códigos/Añadir estado.h>)
[Estado.cpp](<Códigos/Añadir estado.cpp>)

### Cambios en el código:

1. **En `ofApp::keyPressed()` (en el .cpp)**

   * Añadí un nuevo evento asociado a la tecla `'r'` para **activar el estado “random”**:

     ```cpp
     else if (key == 'r') {
         notify("random");
     }
     ```

   * Este evento notifica a todos los observadores (las partículas) que deben cambiar su comportamiento a un **estado aleatorio**, activando el nuevo estado `RandomState`.

---

2. **En `ParticleState` y derivados (en el .h y .cpp)**

   * Creé una nueva clase llamada `RandomState`, heredando de `ParticleState`.

   * Este estado hace que las partículas se muevan en direcciones completamente aleatorias y cambien ligeramente de color, generando un efecto caótico y visualmente atractivo.

     ```cpp
     class RandomState : public ParticleState {
     public:
         void update(Particle* p) override {
             p->position += ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5));
             p->color.setHueAngle(ofRandom(0, 360));
         }
     };
     ```

   * En `ofApp::notify()`, agregué una condición para activar este nuevo estado:

     ```cpp
     else if (event == "random") {
         currentState = new RandomState();
     }
     ```

---

### Qué hace cada patrón en este contexto

**Observer**

* Se mantiene igual, pero ahora incluye la **notificación del nuevo evento `"explode"`**.
* Todas las partículas están suscritas como observadores, por lo que **todas reciben la señal y cambian al nuevo estado simultáneamente**.
* Gracias a esto, no fue necesario modificar cada partícula individualmente; el cambio se maneja de forma centralizada desde `ofApp`.

---

**State**

* Aquí está el cambio más importante.
* Con la incorporación de `ExplodeState`, el sistema de estados se amplía sin alterar los existentes (`NormalState`, `AttractState`, `RepelState`, `StopState`).
* Esto demuestra el poder de la **herencia y el polimorfismo**, ya que `ExplodeState` hereda de la clase base y redefine solo el método `update()` para ofrecer un comportamiento distinto.
* El código principal **no necesita saber qué tipo de estado está activo**, simplemente llama a `state->update(p)` y el polimorfismo se encarga del resto.

---

**Factory**

* No fue necesario modificarlo.
* La creación de partículas sigue siendo la misma; lo que cambió fue **su comportamiento dinámico en tiempo de ejecución**, controlado por el nuevo estado.

---

## Modificación del comportamiento de las partículas

[Comportamiento.cpp](<Códigos/Modificar comportamiento.cpp>)
[Comportamiento.h](<Códigos/Modificar comportamiento.h>)
---

### Cambios en el código:

1. **En `Particle::update()` (en el .cpp)**

   * Modifiqué la forma en que cada partícula actualiza su movimiento.

   * Antes, las partículas se desplazaban de manera lineal según su velocidad:

     ```cpp
     position += velocity;
     ```

   * Ahora, añadí una lógica más dinámica que incorpora un movimiento **orgánico y oscilante**, basado en funciones de ruido y seno para generar trayectorias más naturales:

     ```cpp
     float t = ofGetElapsedTimef();
     position.x += cos(t * 0.5 + ofRandom(0.1, 1.0)) * velocity.x;
     position.y += sin(t * 0.5 + ofRandom(0.1, 1.0)) * velocity.y;
     ```

   * Este cambio hace que las partículas parezcan **flotar o vibrar** en el espacio, en lugar de moverse en líneas rectas.

---

2. **En `Particle::update()` (adicional)**

   * También añadí una pequeña variación de color progresiva, para dar una sensación de “vida” y evolución en el sistema:

     ```cpp
     color.setHueAngle(fmod(ofGetElapsedTimef() * 10, 360));
     ```
   * Esto hace que cada partícula **cambie su tonalidad con el tiempo**, generando una estética más rica visualmente.

---

3. **En `Particle::draw()` (en el .cpp)**

   * Modifiqué el tamaño visual de las partículas para que ahora **palpiten ligeramente**, dando un efecto más orgánico:

     ```cpp
     float pulse = ofMap(sin(ofGetElapsedTimef() * 2), -1, 1, 0.8, 1.2);
     ofDrawCircle(position, size * pulse);
     ```

---

### Qué hace cada patrón en este contexto

**Observer**

* No se modificó.
* Las partículas siguen recibiendo eventos globales (`"stop"`, `"attract"`, `"repel"`, `"random"`), pero ahora **responden de forma más rica visualmente** gracias a su nuevo comportamiento interno.

---

**State**

* Se mantiene igual, pero los efectos visuales ahora **se combinan con los estados dinámicos**.
  Por ejemplo:

  * En `AttractState`, las partículas se mueven hacia el mouse, pero con un patrón ondulante.
  * En `RepelState`, huyen con trayectorias más suaves, como si flotaran.
* Este cambio demuestra el principio de **polimorfismo dinámico**, donde el mismo método `update()` se comporta distinto según el estado y los nuevos cálculos agregados.

---

**Factory**

* No fue necesario modificarlo.
* La creación de partículas se mantiene igual, pero las instancias ahora poseen un **comportamiento más complejo en tiempo de ejecución**, definido por las funciones de actualización que acabamos de cambiar.

---

## Adición de nuevos eventos de notificación

[Notificaciones.h](Códigos/Notificaciones.h)
[Notificaciones.cpp](Códigos/Notificaciones.cpp)

### Cambios en el código:

1. **En `ofApp.h`**

   * Se declararon **dos nuevos métodos**:

     ```cpp
     void notifyExplosion();
     void notifyCollapse();
     ```

     Estos métodos sirven como nuevos *eventos globales* que serán enviados a todas las partículas observadoras.
   * Se añadió una breve descripción en los comentarios explicando su propósito.

2. **En `ofApp.cpp`**

   * Se implementaron los métodos `notifyExplosion()` y `notifyCollapse()`, los cuales utilizan `notify("explosion")` y `notify("collapse")` respectivamente para informar a todas las partículas.
   * Se actualizó `keyPressed()` para reconocer dos nuevas teclas:

     ```cpp
     else if (key == 'x') notifyExplosion();
     else if (key == 'c') notifyCollapse();
     ```

     * **`x`**: genera un evento de explosión (las partículas deberían dispersarse).
     * **`c`**: genera un evento de colapso (las partículas deberían atraerse al centro).
   * En la función `draw()`, se añadió una línea de texto informando al usuario las nuevas teclas disponibles:

     ```cpp
     ofDrawBitmapString("Presiona: 'x' (Explosión) | 'c' (Colapso)", 10, 40);
     ```

---

### Qué hace cada patrón en este contexto

**Observer**

* Fue el patrón **principalmente afectado** en esta modificación.
* Se amplió su alcance al agregar **nuevos eventos** que se notifican a todos los observadores (las partículas).
* Cada partícula, al implementar el método `onNotify(string event)`, puede decidir cómo reaccionar a `"explosion"` y `"collapse"`.
* Esto demuestra el **bajo acoplamiento** del sistema: no fue necesario cambiar el código de las partículas para enviarles nuevas señales.

---

**State**

* No se modificó directamente, pero sigue activo.
* Si una partícula está en estado `"Stop"`, por ejemplo, y recibe `"explosion"`, podría ignorarlo; mientras que si está en `"Normal"`, puede responder aumentando su velocidad.
* Esto refuerza la idea de que **el comportamiento depende del estado interno**, no solo del evento externo.

---

**Factory**

* No fue alterado en esta etapa.
* Su función sigue siendo la de instanciar partículas de distintos tipos, las cuales automáticamente quedan suscritas al sistema de notificación.

---

