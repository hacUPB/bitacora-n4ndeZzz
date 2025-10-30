# Experimentación

Tras la implementación del código y realizar los ajustes para hacerlo funcional, lo envíe a chatGPT para intentar mejorarlo o hacerle pruebas para identificar que este correcto o qué podría optimizarse más.
[Código original.cpp](Reto_Original.cpp)
[Código original.h](Reto_Original.h)

## Optimización de Reto 5

1. **Reserva de memoria anticipada**

   * Actualmente usas:

     ```cpp
     std::vector<std::unique_ptr<Particle>> particles;
     ```

     Si vas a crear muchas partículas en ráfagas (por ejemplo, 100 o 1000 al presionar teclas), lo ideal es **reservar memoria antes**:

     ```cpp
     particles.reserve(1000);  // ajusta según lo esperado
     ```

     Esto evita múltiples realocaciones dinámicas que pueden costar rendimiento.

---

2. **Uso eficiente de `erase-remove`**

   * Tu borrado de partículas muertas con `erase-remove` está correcto:

     ```cpp
     particles.erase(
         std::remove_if(...),
         particles.end()
     );
     ```
   * Para optimizar más, podrías **reutilizar partículas** en lugar de borrarlas (patrón *object pool*). Esto evita costosos `new` y `delete` en cada frame.

---

3. **Batch rendering**

   * Cada partícula actualmente hace su propio `ofDrawCircle()`.
   * Si aumentas el número de partículas a miles, esto **satura la GPU** con muchas llamadas de draw.
   * Puedes optimizarlo usando un **`ofVboMesh`** para dibujar muchas partículas en una sola llamada:

     ```cpp
     ofVboMesh mesh;
     mesh.setMode(OF_PRIMITIVE_POINTS);
     for (auto& p : particles) {
         mesh.addVertex(p->position);
         mesh.addColor(p->color);
     }
     mesh.draw();
     ```
   * Esto reduce drásticamente la sobrecarga de draw.

---

4. **Evitar cálculos innecesarios**

   * `ofRandom()` se usa en cada frame para Wanderer. Puedes precalcular vectores aleatorios y luego iterar sobre ellos.
   * Usa funciones *inline* para operaciones cortas (como clamp o normalización).

---

5. **Controlar el framerate**

   * Ya estableciste `ofSetFrameRate(60)`. Mantenerlo estable evita que el update/draw corra más veces de lo necesario.
   * Si quisieras más suavidad, podrías pasar a **time-based updates** usando `ofGetLastFrameTime()` en lugar de valores fijos.

---

## Impacto de los métodos virtuales

* Los métodos `virtual` (`update()`, `draw()`) permiten el polimorfismo, pero introducen una **ligera sobrecarga**:

  * Cada llamada a un método virtual implica una búsqueda en la **vtable** (tabla de funciones virtuales).
  * El impacto es mínimo (unos nanosegundos), pero puede acumularse si tienes **decenas de miles de partículas**.
* En tu caso (cientos o pocos miles de partículas), el costo es prácticamente despreciable comparado con el *rendering*.
* **Minimizar sobrecarga**:

  1. Evitar virtual en métodos que no necesiten ser polimórficos.
  2. Si una clase no será heredada, marcarla como `final`.
  3. Para escenarios masivos (ej. 100k partículas), separar las partículas por tipo y actualizar/dibujar en bloques, evitando llamadas virtuales dentro del loop:

     ```cpp
     for (auto& s : seekers) { s.update(); }
     for (auto& w : wanderers) { w.update(); }
     ```

     Así eliminas las llamadas virtuales en el loop principal.

---

# Reflexión y ajuste Final

[Reto Opntimizado.cpp](Reto_Optimizado.cpp)
[Reto Optimizado.h](Reto_Optimizado.h)

**1. Cambios entre ambos códigos y diferencias en optimización**
Al comparar el proyecto original y el optimizado, identifiqué que la principal diferencia radica en la forma de dibujar las partículas. En el código original, cada partícula se dibuja de manera individual mediante la llamada a `p->draw()`, lo cual implica múltiples llamadas de dibujo a la GPU. En cambio, en el código optimizado se utiliza un `ofVboMesh`, que permite agrupar todas las posiciones y colores de las partículas y enviarlas a la tarjeta gráfica en una sola operación. Este cambio hace que el código optimizado sea más eficiente, ya que reduce la sobrecarga de comunicación con la GPU. Aquí un comparación de cambios entre el **Reto 5 Original** y **Optimizado**.

### `ofApp.h`

1. **Original**

```cpp
class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    vector<unique_ptr<Particle>> particles;
    bool useVbo = false;   // Indicador de modo
};
```

2. **Optimizado**

```cpp
class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    vector<unique_ptr<Particle>> particles;
    bool useVbo = false;   // Indicador de modo
    ofVboMesh mesh;        // NUEVO: mesh para dibujar con VBO
};
```

**Cambio en línea nueva**: se añade `ofVboMesh mesh;`.

---

### `ofApp.cpp`

1. **En `setup()`**

   * **Original**

   ```cpp
   void ofApp::setup() {
       ofSetFrameRate(60);
       for (int i = 0; i < 1000; i++) {
           particles.push_back(make_unique<Particle>());
       }
   }
   ```

   * **Optimizado**

   ```cpp
   void ofApp::setup() {
       ofSetFrameRate(60);
       for (int i = 0; i < 1000; i++) {
           particles.push_back(make_unique<Particle>());
       }

       mesh.setMode(OF_PRIMITIVE_POINTS);  // 🔹 NUEVO
       mesh.enableColors();                // 🔹 NUEVO
   }
   ```

**Cambio en líneas nuevas**: inicialización del `mesh`.

---

2. **En `draw()`**

   * **Original**

   ```cpp
   void ofApp::draw() {
       for (auto &p : particles) {
           p->draw();   // Dibujo individual
       }

       ofDrawBitmapStringHighlight("Modo: Clásico (ofDrawCircle)", 20, 20, ofColor::black, ofColor::white);
   }
   ```

   * **Optimizado**

   ```cpp
   void ofApp::draw() {
       if (useVbo) {
           mesh.clear();   // 🔹 NUEVO
           for (auto &p : particles) {
               mesh.addVertex(p->getPosition()); // 🔹 NUEVO
               mesh.addColor(p->getColor());     // 🔹 NUEVO
           }
           mesh.draw(); // 🔹 NUEVO

           ofDrawBitmapStringHighlight("Modo: Optimizado (VBO)", 20, 20, ofColor::black, ofColor::white);
       } else {
           for (auto &p : particles) {
               p->draw();  // Clásico
           }
           ofDrawBitmapStringHighlight("Modo: Clásico (ofDrawCircle)", 20, 20, ofColor::black, ofColor::white);
       }
   }
   ```

**Cambios de líneas**:

* Se añade `if (useVbo)` para seleccionar el modo de dibujo.
* Se reemplaza el bucle clásico por la versión con `mesh.addVertex()` y `mesh.addColor()`.
* Se añade `mesh.clear()` antes de reconstruir el buffer.
* Cambia el texto mostrado en pantalla según el modo.

---

3. **En `keyPressed()`**

   * **Original**

   ```cpp
   void ofApp::keyPressed(int key) {
       // No hacía nada
   }
   ```

   * **Optimizado**

   ```cpp
   void ofApp::keyPressed(int key) {
       if (key == 'v') {
           useVbo = !useVbo;  // NUEVO: alternar entre clásico y optimizado
       }
   }
   ```

**Cambio en líneas**: se añade la interacción con el teclado para alternar entre modos.

---

## Resumen de cambios por archivos

* **ofApp.h**:

  * Añadido `ofVboMesh mesh`.

* **ofApp.cpp**:

  * `setup()`: inicialización del `mesh`.
  * `draw()`: se añade rama condicional para usar `mesh` en vez de `p->draw()`.
  * `keyPressed()`: ahora permite alternar con la tecla `'v'`.

---

**2. Buenas prácticas de OOP**
Considero que el proyecto sigue buenas prácticas de programación orientada a objetos. Se utilizan clases con encapsulamiento para definir partículas y sus propiedades, se aplica herencia para crear diferentes comportamientos (por ejemplo, partículas básicas o partículas con movimiento senoidal), y se aprovecha el polimorfismo para que, independientemente del tipo de partícula, todas puedan ser gestionadas dentro de una misma colección. Esto permitió que el sistema fuera más escalable y legible.

---

**3. Influencia del entendimiento de los mecanismos internos de OOP**
El entendimiento de conceptos como herencia, polimorfismo y encapsulamiento fue fundamental para estructurar el proyecto. Gracias a ellos pude organizar el sistema de partículas de manera modular, lo que me permitió añadir nuevos comportamientos sin modificar el código base. Asimismo, comprender cómo funcionan los métodos virtuales me ayudó a tomar decisiones sobre el balance entre claridad en el diseño y eficiencia en la ejecución.

---

**4. Desafíos enfrentados y cómo los superé**
Uno de los principales desafíos fue lograr que el proyecto no solo funcionara, sino que lo hiciera de forma eficiente. Inicialmente no notaba diferencias en los FPS entre ambas versiones, lo que me llevó a investigar cómo medir de manera más precisa el rendimiento (usando contadores de draw calls y tiempos de ejecución). Otro reto fue la conversión de tipos entre `ofVec2f` y los datos esperados por el `ofVboMesh`, que me obligó a revisar la documentación y realizar ajustes en el manejo de vectores. Estos problemas los superé con pruebas iterativas y consultando documentación oficial de openFrameworks.

---

**5. Aprendizaje sobre el equilibrio entre diseño y eficiencia**
De esta experiencia aprendí que un buen diseño orientado a objetos garantiza flexibilidad y escalabilidad, pero no siempre es la opción más eficiente en términos de rendimiento. El uso de polimorfismo, aunque útil, implica cierta sobrecarga, y cuando se manejan miles de objetos esa diferencia se hace evidente. Por eso entendí que, en proyectos de arte generativo y gráficos, es necesario combinar el diseño claro y modular de la OOP con técnicas de optimización como el uso de VBOs. El equilibrio entre ambos aspectos permite obtener un código que no solo es fácil de mantener y extender, sino también eficiente en tiempo de ejecución.

[Video comparativo de códigos](https://youtu.be/c8j0AnkVi9A)