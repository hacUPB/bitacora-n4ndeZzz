#pragma once
#include "ofMain.h"
#include <memory>
#include <vector>
#include <string>

// Simple struct para una bola (se puede almacenar en stack o heap)
struct Ball {
    Ball(float x = 0, float y = 0, float r = 10, ofColor col = ofColor::white)
        : pos(x, y), radius(r), color(col) {}
    ofVec2f pos;
    float radius;
    ofColor color;
    void draw(const std::string &label = "") const {
        ofSetColor(color);
        ofDrawCircle(pos.x, pos.y, radius);
        if (!label.empty()) {
            ofSetColor(255);
            ofDrawBitmapString(label, pos.x - radius, pos.y - radius - 4);
        }
    }
};

// Declaración del objeto global (definición en ofApp.cpp)
extern Ball globalBall;

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key) override;
    void mousePressed(int x, int y, int button) override;

private:
    // Contenedor de objetos creados en el heap (propietario: unique_ptr)
    std::vector<std::unique_ptr<Ball>> heapBalls;

    // Contador simple para poner etiquetas / IDs
    int heapCounter = 0;

    // Flag visual
    bool showInstructions = true;

    // Helper para crear ball en heap
    void createHeapBall(float x, float y);

    // Helper para spawnar una "stack ball" — solo vive dentro de draw() ese frame
    void spawnStackBallOnce(float x, float y);
};
