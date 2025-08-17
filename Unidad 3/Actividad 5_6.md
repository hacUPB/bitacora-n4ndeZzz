# 5)   

## 1. ¿Cuál es la definición de un puntero?
Un puntero es una variable que no guarda directamente un valor, sino que guarda **la dirección de memoria de otra variable u objeto**.  
En palabras más simples: es como una “flecha” que apunta hacia dónde está guardada la información en la memoria del computador.

---

## 2. ¿Dónde está el puntero?
En el código tenemos punteros dentro de la clase `ofApp`:

```cpp
vector<Sphere*> spheres;
Sphere* selectedSphere;
```

- `spheres` es un vector de punteros, donde cada posición guarda la dirección de una esfera.
- `selectedSphere` es un puntero que se usará para recordar cuál esfera está seleccionada.

---

## 3. ¿Cómo se inicializa el puntero?
El puntero se inicializa de dos formas:

1. **Cuando se crean las esferas:**
   ```cpp
   spheres.push_back(new Sphere(x, y, radius));
   ```
   Aquí `new` crea una esfera en memoria y devuelve su dirección. Esa dirección se guarda en el vector de punteros.

2. **Al inicio en `setup`:**
   ```cpp
   selectedSphere = nullptr;
   ```
   Esto significa que, al principio, no hay ninguna esfera seleccionada.

---

## 4. ¿Para qué se está usando el puntero?
- Los punteros se usan para **guardar y manejar las esferas** que se crean en memoria.
- Con `selectedSphere` se puede **saber cuál esfera fue seleccionada con el mouse** y moverla.
- En lugar de copiar esferas, solo se guarda su dirección, lo cual es más eficiente.

---

## 5. ¿Qué es exactamente lo que está almacenado en el puntero?
El puntero no guarda la esfera en sí, sino **la dirección en memoria donde está guardada la esfera**.  
Gracias a eso, cuando escribimos:

```cpp
selectedSphere->update(ofGetMouseX(), ofGetMouseY());
```

El programa va a buscar en memoria la esfera seleccionada y actualiza sus coordenadas para que se mueva con el mouse.

---
# 6)  
 
# Problema en el código de selección y movimiento de esferas

## Error identificado
En el código actual, cuando se selecciona una esfera con click izquierdo, esta queda **permanentemente pegada al puntero del mouse**.  
Esto sucede porque en la función `update()` siempre se actualiza la posición de la esfera seleccionada (`selectedSphere`) con las coordenadas del mouse.  
Además, nunca se "suelta" la esfera porque no existe un evento `mouseReleased` que la deseleccione.

## Consecuencias
- Una vez que se hace click sobre una esfera, seguirá moviéndose aunque ya no mantengas presionado el mouse.  
- Si haces click fuera de cualquier esfera, la selección previa no se desactiva.  
- (Opcional) También hay una fuga de memoria, ya que las esferas se crean con `new` y nunca se liberan.

## Solución propuesta
1. **Mover solo cuando se arrastra el mouse:**  
   Usar `mouseDragged` para actualizar la posición de la esfera seleccionada.
   
2. **Liberar la esfera al soltar el mouse:**  
   Implementar `mouseReleased` para poner `selectedSphere = nullptr`.

3. **Opcional (buena práctica):**  
   - Descartar la selección si no se hace click sobre ninguna esfera.  
   - Liberar la memoria en el destructor o usar vectores de objetos en lugar de punteros.

## Código modificado (fragmentos relevantes)

```cpp
void ofApp::mousePressed(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT) {
        selectedSphere = nullptr; 
        for (int i = (int)spheres.size()-1; i >= 0; --i) {
            float distance = ofDist(x, y, spheres[i]->getX(), spheres[i]->getY());
            if (distance < spheres[i]->getRadius()) {
                selectedSphere = spheres[i];
                break;
            }
        }
    }
}

void ofApp::mouseDragged(int x, int y, int button) {
    if (selectedSphere != nullptr && button == OF_MOUSE_BUTTON_LEFT) {
        selectedSphere->update(x, y);
    }
}

void ofApp::mouseReleased(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT) {
        selectedSphere = nullptr;
    }
}
