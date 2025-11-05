
## Actividad 3:

### **¿Qué es un uniform?**

Un *uniform* es una variable global que se declara dentro del *shader* y que mantiene el mismo valor para todos los vértices o fragmentos procesados durante una llamada de dibujo.
A diferencia de las variables *in* o *out*, que cambian para cada vértice o píxel, las *uniforms* se usan para pasar información constante desde la aplicación de OpenFrameworks hacia los shaders.
Por ejemplo, puedo enviar el tiempo (`ofGetElapsedTimef()`), la posición del ratón o cualquier otro dato que quiero que el shader use para modificar el comportamiento del color, la posición o incluso efectos visuales.

En este caso, el *uniform* `time` controla el movimiento ondulante del plano, y el *uniform* `globalColor` permite pasar el color que se define desde la aplicación principal con `ofSetColor()`.

---

### **¿Cómo funciona el código de aplicación, los shaders y cómo se comunican estos?**

El flujo general de funcionamiento es así:

1. **Aplicación (ofApp.cpp)**

   * En el método `setup()` creo un plano con muchos vértices usando `ofPlanePrimitive`, que servirá como base para deformar con el shader.
   * En el `draw()`, uso la posición del ratón en X para mezclar colores (de magenta a cian), y esa mezcla la paso al shader mediante `ofSetColor()`.
   * Luego activo el shader con `shader.begin()`.
   * En este punto, envío el tiempo al shader con `shader.setUniform1f("time", ofGetElapsedTimef());`, lo que actualiza el valor del *uniform time* en cada frame.
   * Finalmente dibujo el plano con `plane.drawWireframe()` y cierro el shader con `shader.end()`.

2. **Vertex Shader (`shader.vert`)**

   * Aquí se ejecuta una vez por cada vértice del plano.
   * Recibe el valor del *uniform time* desde la app.
   * Calcula una onda senoidal sobre el eje Y de cada vértice usando la posición X y el tiempo.
   * Esto genera una animación tipo “ola” que se propaga a través del plano.

3. **Fragment Shader (`shader.frag`)**

   * Se ejecuta una vez por cada píxel de la superficie renderizada.
   * Recibe el color global `globalColor`, que fue establecido con `ofSetColor()` en el código de la app.
   * Asigna ese color a `outputColor`, determinando el color final de cada píxel en pantalla.

La comunicación entre la aplicación y los shaders se da por medio de estas *uniforms*, que se actualizan antes de cada dibujo. En cada frame, los valores se vuelven a pasar, permitiendo que la animación y los colores reaccionen en tiempo real.

---

### **Modificación del código: personalización del fragment shader**

1. **Shader de fragmentos (`shader.frag`):**
   Se añadieron las variables uniformes `u_resolution` (para conocer el tamaño de la ventana) y `time` (para animar los colores).
   Luego, se normalizaron las coordenadas de cada píxel usando `gl_FragCoord.xy / u_resolution`, lo que permite obtener valores entre 0 y 1 en los ejes **X** y **Y**.

   A partir de esas coordenadas, se aplicaron funciones trigonométricas (`sin` y `abs`) que generan variaciones suaves en los valores de color RGB. Al incluir el tiempo (`time`), estas variaciones se animan constantemente, creando un **efecto dinámico de degradado cambiante**.

   Finalmente, el color calculado se multiplica por el color global (`globalColor`) que depende de la posición del ratón, lo cual permite que el usuario siga influyendo en el resultado visual con el movimiento del mouse.

   ```glsl
   vec2 uv = gl_FragCoord.xy / u_resolution;
   float r = abs(sin(uv.x * 3.14 + time * 0.5));
   float g = abs(sin(uv.y * 3.14 + time * 0.7));
   float b = abs(sin((uv.x + uv.y) * 3.14 + time));
   vec3 finalColor = vec3(r, g, b) * globalColor.rgb;
   outputColor = vec4(finalColor, 1.0);
   ```
   [shader.frag](shader.frag)

2. **Shader de vértices (`shader.vert`):**
   Se mantuvo la lógica del desplazamiento de vértices con una onda sinusoidal.
   Esto hace que el plano tenga un movimiento fluido que se combina con el cambio de color de los píxeles, creando un efecto más dinámico y tridimensional.
   [shader.vert](shader.vert)

3. **Archivo `ofApp.cpp`:**
   Se enviaron las nuevas *uniforms* al shader (`u_resolution`, `time`, `globalColor`), permitiendo que este tenga toda la información necesaria para calcular los colores de forma independiente.  
   [ofApp.cpp](ofApp.cpp)  


[Video con cambios y ensayo del original](https://www.youtube.com/watch?v=d_HtT5g4D08)
