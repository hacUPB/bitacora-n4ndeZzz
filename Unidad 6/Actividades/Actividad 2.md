# Actividad 2:

## Adición de un nuevo tipo de partícula.

[PARTÍCULA.CPP](<Códigos/Añadir partículas.cpp>)
[PARTÍCULA.H](<Códigos/Añadir partículas.h>)
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
