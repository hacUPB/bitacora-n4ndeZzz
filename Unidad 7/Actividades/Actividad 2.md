## Actividad 2:

### ¿Cómo funciona?  
El programa carga un *shader* (tanto vertex como fragment) y lo aplica sobre una figura dibujada en la pantalla. En este caso, se dibuja un rectángulo o un círculo que ocupa gran parte del área del display, y el shader es el encargado de modificar los colores de los píxeles según los parámetros definidos en el código GLSL.  
Cuando se usa `shader.begin()` y `shader.end()`, la GPU aplica las instrucciones del shader sobre cada vértice y fragmento de la figura que se dibuja entre esas llamadas. Si se comenta el shader, el dibujo se muestra solo con el color definido por `ofSetColor`, sin ningún tipo de efecto.  

### ¿Qué resultados obtuviste?  

![alt text](<../Imágenes/Actividad 2 ejemplo.png>)  
![alt text](<../Imágenes/Actividad 2 ejemplo 2.png>)  
![alt text](<../Imágenes/Actividad 2 ejemplo 3.png>)  

Cuando dejé activado el shader, el resultado fue un círculo con un degradado entre colores magenta y azul, con una transición suave que depende de las coordenadas de la pantalla (como se ve en las primeras imágenes).  
Cuando comenté el shader, el resultado fue una pantalla completamente blanca o un rectángulo blanco ocupando todo el área del *viewport* (como se ve en la última imagen). Esto demuestra que sin el shader activo, el color mostrado es el que se establece por defecto con `ofSetColor(255)`, sin ningún cálculo adicional.  

### ¿Estás usando un vertex shader?  
Sí. El *vertex shader* se está ejecutando cuando el shader está activo. Su función es procesar cada vértice de la figura (en este caso los vértices que forman el círculo o rectángulo) y definir sus posiciones finales en el espacio de pantalla. Además, puede enviar información (como coordenadas o normales) al *fragment shader*.  

### ¿Estás usando un fragment shader?  
Sí, también se usa un *fragment shader*. Este es el que realmente genera el color visible en pantalla, procesando cada píxel (fragmento) del área cubierta por los triángulos que forman la figura. En este caso, es el responsable del degradado de color que se observa en el círculo.  

### Analiza el código de los shaders. ¿Qué hace cada uno?  

* **Vertex Shader:** toma las coordenadas de los vértices y las transforma según la matriz del modelo y la vista, posicionando correctamente los puntos en el espacio de pantalla. Además, suele pasar información al *fragment shader* (como las coordenadas normalizadas o de textura).  
* **Fragment Shader:** calcula el color final de cada fragmento (píxel). En este ejemplo, parece usar las coordenadas del fragmento (`gl_FragCoord`) o valores interpolados para crear una mezcla de colores que genera el degradado magenta–azul. Básicamente, este shader define el color de salida de cada punto que se dibuja en la pantalla.
