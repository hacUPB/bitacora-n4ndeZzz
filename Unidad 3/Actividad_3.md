
Este programa dibuja partículas (círculos) que siguen el movimiento del mouse y cambian de color al hacer clic.

## Funciones y su funcionamiento

### 1. `void ofApp::setup()`
```cpp
ofBackground(0);
particleColor = ofColor::white;
```
- Establece el fondo en negro (`ofBackground(0)`).
- Inicializa el color de las partículas como blanco.

---

### 2. `void ofApp::update()`
- En este caso está vacío.
- Se ejecuta cada frame antes de `draw()` para actualizar la lógica, pero no se utiliza.

---

### 3. `void ofApp::draw()`
```cpp
for(auto &pos: particles){
    ofSetColor(particleColor);
    ofDrawCircle(pos.x, pos.y, 50);
}
```
- Recorre todas las posiciones almacenadas en `particles`.
- Establece el color actual (`particleColor`).
- Dibuja un círculo en cada posición con radio de 50 píxeles.

---

### 4. `void ofApp::mouseMoved(int x, int y)`
```cpp
particles.push_back(ofVec2f(x, y));
if (particles.size() > 100) {
    particles.erase(particles.begin());
}
```
- Guarda la posición del mouse en `particles`.
- Si hay más de 100 elementos, elimina el más antiguo para mantener un máximo de 100.

---

### 5. `void ofApp::mousePressed(int x, int y, int button)`
```cpp
particleColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
```
- Cambia el color de todas las partículas a un color aleatorio cuando se hace clic.

---