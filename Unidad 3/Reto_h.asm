#pragma once
#include "ofMain.h"
#include <queue>

// Clase que representa una gota de lluvia
class Raindrop {
public:
    Raindrop(float startX, float startY);

    void update();
    void draw() const;

    bool isOffScreen() const;

    float x, y;
    float velocity;
    ofColor color;
};

// Clase que representa una partícula pequeña cuando la gota se rompe
class Particle {
public:
    Particle(float startX, float startY);

    void update();
    void draw() const;

    bool isDead() const;

    float x, y;
    float velocityY;
    int lifetime;
    ofColor color;
};

// Clase principal de la aplicación
class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

private:
    std::vector<Raindrop*> raindrops;   // gotas activas
    std::vector<Particle*> particles;   // partículas generadas
    std::queue<Raindrop*> spawnQueue;   // gotas pendientes de aparecer
    ofColor globalColor;
    bool uniformColor;
};
