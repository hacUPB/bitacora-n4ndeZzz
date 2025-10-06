#pragma once
#include "ofMain.h"
#include <memory>
#include <stack>
#include <vector>

// Clase para las gotas de lluvia
class LineDrop {
public:
    float x, y, speed;
    ofColor color;

    LineDrop(float startX, ofColor c) {
        x = startX;
        y = 0;
        speed = ofRandom(4, 10);
        color = c;
    }

    void update() {
        y += speed;
    }

    void draw() {
        ofSetColor(color);
        ofDrawLine(x, y, x, y + 10);
    }

    bool isOffScreen() {
        return y > ofGetHeight();
    }
};

// Clase para partículas
class Particle {
public:
    float x, y, vx, vy, lifespan;
    ofColor color;

    Particle(float startX, float startY, ofColor c) {
        x = startX;
        y = startY;
        vx = ofRandom(-2, 2);
        vy = ofRandom(-2, 2);
        lifespan = 255;
        color = c;
    }

    void update() {
        x += vx;
        y += vy;
        lifespan -= 3;
    }

    void draw() {
        ofSetColor(color, lifespan);
        ofDrawCircle(x, y, 3);
    }

    bool isDead() {
        return lifespan <= 0;
    }
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    std::vector<std::unique_ptr<LineDrop>> drops;   // Arreglo dinámico de gotas
    std::vector<std::unique_ptr<Particle>> particles; // Lista de partículas
    std::stack<std::unique_ptr<LineDrop>> dropStack;  // Pila de nuevas gotas

    ofColor baseColor; // Color base para todas las gotas/partículas
};
