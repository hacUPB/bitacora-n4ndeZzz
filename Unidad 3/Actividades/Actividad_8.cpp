#include "ofApp.h"
#include <sstream>

// Definición del objeto global (vive toda la ejecución)
Ball globalBall(40, 40, 24, ofColor::fromHsb(150, 200, 255));

void ofApp::setup() {
    ofSetBackgroundColor(30);
    ofSetFrameRate(60);
    // inicializamos un par de balls en heap para empezar
    createHeapBall(200, 200);
    createHeapBall(300, 250);
}

void ofApp::update() {
    // ejemplo: hacemos que los objetos en heap se muevan ligeramente
    for (auto &bptr : heapBalls) {
        // movimiento muy suave, basado en ruido
        float t = ofGetElapsedTimef();
        bptr->pos.x += sin(t + bptr->pos.y * 0.01f) * 0.2f;
        bptr->pos.y += cos(t + bptr->pos.x * 0.01f) * 0.2f;
    }

    // El objeto global también puede animarse un poco para que se note
    float t = ofGetElapsedTimef();
    globalBall.pos.y = 40 + sin(t) * 8;
}

void ofApp::draw() {
    // Dibujo del objeto global (memoria global)
    globalBall.draw("GLOBAL");

    // Dibujo de objetos en heap (persisten)
    for (size_t i = 0; i < heapBalls.size(); ++i) {
        std::ostringstream label;
        label << "HEAP " << i;
        heapBalls[i]->draw(label.str());
    }

    // ---- Stack object demo ----
    // spawnStackBallOnce crea una Ball local en stack y la dibuja inmediatamente:
    // aparece SOLO este frame (ilustra vida en stack)
    // (Nota: spawnStackBallOnce solo dibuja la bola; no guarda puntero)
    // Lógica: si el usuario pulsó 's' la función spawnStackBallOnce fue llamada (lo implementamos vía variable temporal)
    // Para este sencillo experimento, llamamos spawnStackBallOnce si se presionó recientemente (por facilidad, la llamamos cada frame
    // si showInstructions false, pero se hace también al presionar S; aquí la mostramos como demo cada frame que pase después de pulsar S)
    // Para simplicidad, dibujamos la stackBall cuando (ofGetFrameNum() % 120) < 1 si se desea demostración automática; 
    // pero en este diseño, el spawn se hace desde keyPressed -> setear una variable / o se llama directamente.

    // (No guardamos punteros a objetos de stack — eso sería peligroso y provocaría punteros colgantes.)

    // Texto e instrucciones
    ofSetColor(230);
    int y = ofGetHeight() - 90;
    ofDrawBitmapString("Click left : create ball in HEAP (persists until 'c')", 10, y);
    ofDrawBitmapString("'s'         : create ball in STACK (only THIS frame)", 10, y + 14);
    ofDrawBitmapString("'g'         : change GLOBAL ball color/position", 10, y + 28);
    ofDrawBitmapString("'c'         : clear HEAP balls", 10, y + 42);
    ofDrawBitmapString("'i'         : toggle instructions", 10, y + 56);
    ofDrawBitmapString("Note: STACK balls are local temporaries and disappear when the function returns.", 10, y + 70);
}

void ofApp::keyPressed(int key) {
    if (key == 'c' || key == 'C') {
        // Liberar todas las balls del heap (unique_ptr se encarga del delete)
        heapBalls.clear();
        heapCounter = 0;
        ofLog() << "Cleared heap balls (memory freed automatically by unique_ptr).";
    } else if (key == 'g' || key == 'G') {
        // Modificar el objeto global (vive todo el programa)
        globalBall.color = ofColor::fromHsb(ofRandom(255), 200, 255);
        // Moverlo a una nueva posición para visualizar que es 'global'
        globalBall.pos.set(40 + ofRandom(-10, 10), 40 + ofRandom(-10, 10));
        ofLog() << "Changed global object color/position.";
    } else if (key == 's' || key == 'S') {
        // Crear una ball en stack: la dibujamos inmediatamente y se destruye al salir de la función.
        // Para que el dibujo ocurra, llamamos a spawnStackBallOnce() aquí — la función crea una variable local (stack) y la dibuja.
        spawnStackBallOnce(ofRandomWidth(), ofRandomHeight());
        ofLog() << "Spawned stack ball (lives only during this call/frame).";
    } else if (key == 'i' || key == 'I') {
        showInstructions = !showInstructions;
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT) {
        createHeapBall(x, y);
    }
}

// createHeapBall: crea un objeto en el heap (unique_ptr) y lo guarda en vector
void ofApp::createHeapBall(float x, float y) {
    auto b = std::make_unique<Ball>(x, y, 14, ofColor::fromHsb(ofRandom(255), 190, 255));
    heapBalls.emplace_back(std::move(b));
    heapCounter++;
    ofLog() << "Created HEAP ball #" << heapCounter << " at (" << x << "," << y << ")";
}

// spawnStackBallOnce: crea un objeto local (stack) y lo dibuja en el mismo momento
void ofApp::spawnStackBallOnce(float x, float y) {
    Ball stackBall(x, y, 12, ofColor::fromHsb(ofRandom(255), 200, 255));
    // dibujamos la ball local directamente
    stackBall.draw("STACK");
    // Nota: cuando esta función retorna, 'stackBall' se destruye automáticamente (su memoria estaba en el stack)
}
