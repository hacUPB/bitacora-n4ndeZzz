## Actividad 1

### **¿Qué son los vértices?**

Los vértices son **los puntos base de toda figura en 3D**, representados normalmente por coordenadas *(x, y, z)*.
A partir de ellos se construyen las formas más complejas: líneas, triángulos y superficies.
En mi caso, los vértices son esenciales para definir la posición y el movimiento de cada partícula o figura dentro del espacio visual de *openFrameworks*.

---

### **¿Con qué figura geométrica se dibuja en 3D?**

En gráficos 3D todo se construye a partir de **triángulos**.
Estos son la unidad geométrica más simple que puede definir una superficie en el espacio.
Los motores gráficos y librerías (como OpenGL o el propio openFrameworks) dividen todos los modelos en triángulos, ya que son estables matemáticamente y garantizan que cualquier superficie pueda representarse correctamente.

---

### **¿Qué es un shader?**

Un **shader** es un programa pequeño que se ejecuta directamente en la **GPU** para controlar cómo se dibujan los objetos.
Permite modificar desde el color y la iluminación hasta efectos visuales complejos como reflejos, sombras o distorsiones.
En proyectos de arte generativo, los shaders son herramientas poderosas para lograr efectos visuales expresivos y dinámicos en tiempo real.

---

### **¿Cómo se le llaman a los grupos de píxeles de un mismo triángulo?**

A los grupos de píxeles que pertenecen a un mismo triángulo se les llama **fragmentos**.
Cada fragmento representa un píxel potencial en pantalla y será evaluado por el **fragment shader** antes de determinar su color final.

---

### **¿Qué es un fragment shader?**

El **fragment shader** es el programa que determina el color final de cada píxel (fragmento) que forma una figura.
Aquí se aplican efectos de **textura, iluminación, transparencias o sombras**.
En mi caso, sería como el proceso que define el color final de cada partícula, dependiendo de su estado o tipo.

---

### **¿Qué es un vertex shader?**

El **vertex shader** procesa cada vértice individual de una figura.
Su función es aplicar transformaciones como **traslación, rotación o escalado**, y pasar la información al siguiente paso del pipeline.
En otras palabras, determina **dónde estará ubicado cada punto del modelo en la pantalla**.

---

### **¿Al proceso de determinar qué píxeles del display va a cubrir cada triángulo de una mesh se le llama...?**

Ese proceso se llama **rasterización**.
Durante la rasterización, el sistema convierte los triángulos definidos por vértices en fragmentos (píxeles) que luego serán procesados por el *fragment shader*.

---

### **¿Qué es el render pipeline?**

El **render pipeline** es la cadena completa de pasos que sigue una escena 3D desde que se definen los vértices hasta que se dibujan los píxeles en la pantalla.
Incluye etapas como:

1. Procesamiento de vértices (vertex shader).
2. Ensamblaje de primitivas (triángulos).
3. Rasterización.
4. Procesamiento de fragmentos (fragment shader).
5. Escritura en el framebuffer.

Es el corazón del renderizado en tiempo real y permite que los proyectos visuales como los míos cobren vida en la pantalla.

---

### **¿Hay alguna diferencia entre aplicar un color a una superficie de una mesh o aplicar una textura?**

Sí.

* Aplicar un **color** significa asignar un tono uniforme o calculado a toda la superficie.
* Aplicar una **textura** implica **mapear una imagen** sobre la geometría, de manera que cada píxel del modelo corresponda a un píxel de la textura.
  En mis experimentos con partículas, uso colores programáticos, pero una textura permitiría darles apariencia más realista (como pétalos, hojas o fuego).

---

### **¿Cuál es la diferencia entre una textura y un material?**

Una **textura** es una imagen que se aplica sobre una superficie.
Un **material** combina múltiples propiedades (color, textura, brillo, reflexión, rugosidad, etc.) para definir **cómo responde esa superficie a la luz**.
Mientras la textura es visual, el material es físico: define la interacción con la iluminación y el entorno.

---

### **¿Qué transformaciones se requieren para mover un vértice del 3D world al View Screen?**

Para convertir un vértice del **mundo 3D al espacio 2D de la pantalla**, el vértice pasa por tres transformaciones principales:

1. **Model Matrix:** coloca el objeto en su posición dentro del mundo 3D.
2. **View Matrix:** transforma las coordenadas desde el mundo hacia la cámara (punto de vista).
3. **Projection Matrix:** convierte las coordenadas 3D en 2D para mostrarlas en la pantalla.

Este proceso es esencial para que los objetos del mundo virtual se representen correctamente en el espacio visible.

---

### **¿Al proceso de convertir los triángulos en fragmentos se le llama...?**

Ese proceso también se llama **rasterización**.
Durante esta etapa, los triángulos que conforman una malla se convierten en fragmentos que representan posibles píxeles visibles en la pantalla.

---

### **¿Qué es el framebuffer?**

El **framebuffer** es un espacio de memoria donde se almacenan temporalmente los píxeles renderizados antes de ser enviados a la pantalla.
Contiene la información de color, profundidad y otros datos por cada píxel.
Es como el “lienzo digital” donde se dibuja la imagen final que se mostrará.

---

### **¿Para qué se usa el Z-buffer o depth buffer en el render pipeline?**

El **Z-buffer** (o **depth buffer**) almacena la **profundidad de cada píxel**.
Su función es evitar que los objetos del fondo se dibujen encima de los que están adelante.
Gracias a él, el sistema sabe qué fragmentos deben ser visibles y cuáles deben descartarse según su distancia a la cámara.

