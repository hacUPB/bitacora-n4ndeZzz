#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    baseColor = ofColor::fromHsb(ofRandom(255), 200, 255);

    // Crear gotas iniciales
    for (int i = 0; i < 20; i++) {
        drops.push_back(std::make_unique<LineDrop>(ofRandomWidth(), baseColor));
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // Crear nuevas gotas en la pila
    if (ofRandom(1) < 0.1) {
        dropStack.push(std::make_unique<LineDrop>(ofRandomWidth(), baseColor));
    }

    // Mover gotas de la pila al arreglo
    while (!dropStack.empty()) {
        drops.push_back(std::move(dropStack.top()));
        dropStack.pop();
    }

    // Actualizar gotas
    for (int i = drops.size() - 1; i >= 0; i--) {
        drops[i]->update();
        if (drops[i]->isOffScreen()) {
            // Convertir en partículas al llegar abajo
            for (int j = 0; j < 5; j++) {
                particles.push_back(std::make_unique<Particle>(drops[i]->x, ofGetHeight(), baseColor));
            }
            drops.erase(drops.begin() + i);
        }
    }

    // Actualizar partículas
    for (int i = particles.size() - 1; i >= 0; i--) {
        particles[i]->update();
        if (particles[i]->isDead()) {
            particles.erase(particles.begin() + i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (auto &drop : drops) {
        drop->draw();
    }
    for (auto &p : particles) {
        p->draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'c') {
        // Cambiar color base único
        baseColor = ofColor::fromHsb(ofRandom(255), 200, 255);

        // Aplicar el color nuevo a todas las gotas
        for (auto &drop : drops) {
            drop->color = baseColor;
        }

        // Aplicar el color nuevo a todas las partículas
        for (auto &p : particles) {
            p->color = baseColor;
        }
    }

    if (key == 'm') {
        // Agregar manualmente más gotas
        for (int i = 0; i < 5; i++) {
            drops.push_back(std::make_unique<LineDrop>(ofRandomWidth(), baseColor));
        }
    }
}
