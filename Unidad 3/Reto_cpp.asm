#include "ofApp.h"

// ---------------- Raindrop ----------------
Raindrop::Raindrop(float startX, float startY) {
    x = startX;
    y = startY;
    velocity = ofRandom(2, 6);
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Raindrop::update() {
    y += velocity;
}

void Raindrop::draw() const {
    ofSetColor(color);
    ofDrawLine(x, y, x, y + 15);
}

bool Raindrop::isOffScreen() const {
    return y > ofGetHeight();
}

// ---------------- Particle ----------------
Particle::Particle(float startX, float startY) {
    x = startX;
    y = startY;
    velocityY = ofRandom(1, 4);
    lifetime = 60; // frames
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Particle::update() {
    y += velocityY;
    lifetime--;
}

void Particle::draw() const {
    ofSetColor(color);
    ofDrawCircle(x, y, 2);
}

bool Particle::isDead() const {
    return lifetime <= 0;
}

// ---------------- ofApp ----------------
void ofApp::setup() {
    ofBackground(0);
    uniformColor = false;
}

void ofApp::update() {
    // Crear nuevas gotas desde la cola
    if (ofRandom(1.0) < 0.2) {
        spawnQueue.push(new Raindrop(ofRandomWidth(), 0));
    }
    if (!spawnQueue.empty()) {
        raindrops.push_back(spawnQueue.front());
        spawnQueue.pop();
    }

    // Actualizar gotas
    for (int i = raindrops.size() - 1; i >= 0; i--) {
        raindrops[i]->update();
        if (raindrops[i]->isOffScreen()) {
            // Crear partículas al caer
            for (int j = 0; j < 5; j++) {
                particles.push_back(new Particle(raindrops[i]->x, ofGetHeight()));
            }
            delete raindrops[i];
            raindrops.erase(raindrops.begin() + i);
        }
    }

    // Actualizar partículas
    for (int i = particles.size() - 1; i >= 0; i--) {
        particles[i]->update();
        if (particles[i]->isDead()) {
            delete particles[i];
            particles.erase(particles.begin() + i);
        }
    }
}

void ofApp::draw() {
    // Dibujar gotas
    for (auto& drop : raindrops) {
        if (uniformColor) drop->color = globalColor;
        drop->draw();
    }

    // Dibujar partículas
    for (auto& part : particles) {
        if (uniformColor) part->color = globalColor;
        part->draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == 'c') {
        uniformColor = true;
        globalColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }
    if (key == 'r') {
        uniformColor = false;
    }
}
