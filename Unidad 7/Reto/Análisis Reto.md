# **Bitácora – Pruebas y funcionamiento de la aplicación con shaders**

## **Funcionamiento general de la aplicación**

La aplicación se compone de tres partes esenciales:

1. **ofApp.cpp:**
   Es la parte que corre en la **CPU**. Aquí se define la ventana, se carga el shader (`shader.load()`), se crea una **malla (plane)** y se envían datos al shader mediante **uniformes**, como el tiempo, la posición del ratón y colores.

2. **Vertex Shader (`shader.vert`):**
   Corre en la **GPU** y controla la posición de cada vértice antes de ser dibujado.
   En mis pruebas, lo usé para generar **movimiento ondulante** y **deformaciones** dependientes del tiempo o la posición del ratón.

3. **Fragment Shader (`shader.frag`):**
   También corre en la **GPU**, pero afecta el color de cada píxel en la superficie.
   En las pruebas modifiqué el color dinámicamente en función del tiempo y de la posición del mouse.

---

## **Cuadro general de las pruebas realizadas**

|  Nº | Tipo de prueba                 | Archivos modificados        | Cambios realizados                                                        | Resultado / Verificación                                                                       |
| :-: | :----------------------------- | :-------------------------- | :------------------------------------------------------------------------ | :--------------------------------------------------------------------------------------------- |
| 1 | **Vertex Shader**              | `shader.vert` + `ofApp.cpp` | Se añadió animación sinusoidal en Y según el tiempo (`sin(time + pos.x)`) | El plano ondula constantemente → confirma que el *vertex shader* modifica la geometría.        |
| 2 | **Fragment Shader**            | `shader.frag` + `ofApp.cpp` | Se añadió animación de color RGB según `sin(time)`                        | El color del plano cambia continuamente → confirma que el *fragment shader* controla el color. |
| 3 | **ofApp.cpp (Interactividad)** | `ofApp.cpp`                 | Se interpolan colores según la posición del mouse (de rojo a verde)       | El color cambia al mover el mouse → confirma la comunicación CPU → GPU mediante uniformes.     |

---

## **1️ Prueba del Vertex Shader**

### Cambios realizados

**`shader.vert`**

```glsl
#version 150
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
uniform float time;

void main() {
    vec4 pos = position;
    pos.y += sin(pos.x * 0.05 + time) * 50.0;
    gl_Position = modelViewProjectionMatrix * pos;
}
```

**`ofApp.cpp` (dentro de draw):**

```cpp
shader.setUniform1f("time", ofGetElapsedTimef());
plane.drawWireframe();
```

### Explicación técnica

En esta prueba, cada vértice del plano se desplaza en el eje **Y** según una función seno dependiente del tiempo.
Esto crea un efecto de **onda dinámica**, confirmando que el vertex shader puede **alterar las posiciones de los vértices** en tiempo real antes de ser enviados al rasterizador.
El uso del `uniform float time` demuestra cómo **la CPU (ofApp.cpp)** puede **pasar valores a la GPU** en cada cuadro.

### Resultado

El plano se mueve como si fuera una bandera o superficie líquida, lo cual confirma el funcionamiento correcto del **vertex shader**.

---

## **2️ Prueba del Fragment Shader**

### Cambios realizados

**`shader.frag`**

```glsl
#version 150
out vec4 outputColor;
uniform float time;

void main() {
    float r = abs(sin(time));
    float g = abs(sin(time + 2.0));
    float b = abs(sin(time + 4.0));
    outputColor = vec4(r, g, b, 1.0);
}
```

**`ofApp.cpp`**

```cpp
shader.setUniform1f("time", ofGetElapsedTimef());
```

### Explicación técnica

En esta segunda prueba, se manipula el color de cada píxel del plano directamente desde el **fragment shader**, variando los valores RGB con funciones seno basadas en el tiempo.
Esto demuestra que cada píxel puede calcular su propio color en la GPU sin necesidad de volver a la CPU, mostrando el poder del procesamiento paralelo.

### Resultado

El color del plano varía continuamente entre tonos magenta, azul y verde, confirmando el control total del **fragment shader** sobre la etapa final del pipeline.

---

## **3️ Prueba del ofApp.cpp (Interactividad)**

### Cambios realizados

**`ofApp.cpp` (sección draw):**

```cpp
float percentX = mouseX / (float)ofGetWidth();
percentX = ofClamp(percentX, 0, 1);

ofFloatColor colorLeft = ofColor::red;
ofFloatColor colorRight = ofColor::green;
ofFloatColor colorMix = colorLeft.getLerped(colorRight, percentX);

ofSetColor(colorMix);
plane.drawWireframe();
```

### Explicación técnica

En esta tercera prueba, se verifica la comunicación desde la CPU hacia la GPU mediante **uniformes dependientes del ratón**.
La aplicación calcula un color entre rojo y verde según la posición horizontal del mouse (`mouseX`) y lo pasa como **color global** al shader.
De esta forma, la interacción con el usuario modifica el resultado en pantalla sin reiniciar el programa.

### Resultado

El plano cambia su color gradualmente de rojo a verde al mover el mouse de izquierda a derecha, demostrando la correcta comunicación CPU→GPU y el uso dinámico de uniformes.

---

## **Conclusión general**

Con estas pruebas pude comprender el flujo de datos entre la CPU y la GPU en **openFrameworks**, y cómo se divide el trabajo entre ambos:

* La **CPU** prepara la escena, envía uniformes y controla la lógica interactiva.
* La **GPU**, mediante los **shaders**, se encarga del cálculo paralelo de posiciones y colores.

Logré comprobar que:

* El **vertex shader** puede manipular la forma y movimiento de los vértices.
* El **fragment shader** define el color final de los píxeles.
* Desde **ofApp.cpp** se pueden enviar variables que alteren los shaders en tiempo real.

Gracias a esto, comprendí la base del **renderizado programable**, que es fundamental para crear efectos visuales avanzados, simulaciones físicas, visualizadores musicales y experiencias interactivas complejas.

[Video con pruebas y muestra del funcionamiento de la aplicación](https://youtu.be/gxmC6OvNenk)