## Actividad 4:  

### **¿Qué hace el código del ejemplo?**

El ejemplo **“Adding some interactivity”** utiliza *shaders* (programas que corren en la GPU) para deformar un plano de vértices y cambiar su color en función de la posición del mouse.
Cuando el usuario mueve el cursor por la pantalla, las coordenadas del mouse se envían como variables (*uniforms*) al *vertex shader*, que desplaza los vértices cercanos al puntero, generando una sensación de “repulsión” o deformación dinámica.
Al mismo tiempo, el *fragment shader* utiliza esas mismas coordenadas para cambiar el color del plano, haciendo una transición gradual entre magenta y azul según la posición del mouse.

En resumen, el código crea una interacción visual entre el movimiento del usuario y la geometría renderizada en pantalla, mostrando cómo los *uniforms* permiten comunicar datos desde la CPU hacia la GPU en tiempo real.

---

### **¿Cómo funciona el código de aplicación, los shaders y cómo se comunican estos?**

El flujo de trabajo se divide en tres partes:

1. **Código de aplicación (ofApp.cpp)**

   * Crea un plano con una malla de vértices (`plane`).
   * Carga el shader (`shader.load(...)`).
   * En el método `draw()`, calcula la posición del mouse y define varias variables (*uniforms*):

     * `mouseRange` → determina el radio de influencia del mouse.
     * `mousePos` → almacena la posición del mouse (x, y).
     * `mouseColor` → define un color interpolado entre magenta y azul según la posición horizontal.
   * Estas variables se envían al shader mediante `shader.setUniform...()`.

2. **Vertex Shader (`shader.vert`)**

   * Recibe las coordenadas del mouse (`mousePos`) y calcula la distancia de cada vértice a esa posición.
   * Si el vértice está dentro del rango definido (`mouseRange`), modifica su posición desplazándolo ligeramente, lo que produce una deformación local de la malla.
   * Finalmente, transforma la posición con `modelViewProjectionMatrix`.

3. **Fragment Shader (`shader.frag`)**

   * Usa el color pasado desde la aplicación (`mouseColor`) y lo asigna a cada píxel con `outputColor`.
   * Así, el color de la figura cambia dinámicamente según el movimiento del cursor.

En conjunto, el *ofApp* (CPU) envía datos a los *shaders* (GPU) mediante *uniforms*.
Los *shaders* los procesan y devuelven el resultado gráfico renderizado en pantalla.

---

### **Modificaciones a `ofApp.cpp` y al vertex shader para conseguir otros comportamientos**

#### Ejemplo 1 — Olas verticales con tiempo:

**ofApp.cpp**

```cpp
shader.setUniform1f("time", ofGetElapsedTimef());
```

**shader.vert**

```glsl
#version 150
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
uniform float time;

void main() {
    vec4 pos = position;
    pos.y += sin(time + pos.x * 0.05) * 50.0;
    gl_Position = modelViewProjectionMatrix * pos;
}
```

### **Modificaciones al fragment shader para conseguir otros comportamientos**

#### Ejemplo 1 — Gradiente dinámico con el tiempo:

```glsl
#version 150
out vec4 outputColor;
uniform vec4 mouseColor;
uniform float time;

void main() {
    float pulse = abs(sin(time * 2.0));
    outputColor = mix(mouseColor, vec4(1.0, 1.0, 1.0, 1.0), pulse);
}
```

Aquí el color oscila suavemente entre el color del mouse y blanco, creando un efecto de brillo.

---

#### Ejemplo 2 — Color por distancia al centro:

```glsl
#version 150
out vec4 outputColor;
uniform vec2 mousePos;

void main() {
    vec2 uv = gl_FragCoord.xy / vec2(1024.0, 768.0); // Normaliza coordenadas
    float dist = distance(uv, vec2(0.5, 0.5));
    outputColor = vec4(dist, 1.0 - dist, abs(sin(dist * 10.0)), 1.0);
}
```

Esto genera un degradado de colores radiales que cambian según la distancia al centro de la pantalla.

