#pragma once
#include "ofMain.h"
#include <memory>
#include <vector>

// ---------------------------
// Clase base Particle
// ---------------------------
class Particle {
public:
	Particle(const ofVec2f & startPos);
	virtual ~Particle() = default;

	virtual void update();
	virtual void draw();
	bool isDead() const;

	ofVec2f getPosition() const { return position; }
	ofColor getColor() const { return color; }

protected:
	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;
	float radius;
	float lifespan;
	ofColor color;
};

// ---------------------------
// SeekerParticle: persigue el mouse
// ---------------------------
class SeekerParticle : public Particle {
public:
	SeekerParticle(const ofVec2f & startPos);
	void update() override;
};

// ---------------------------
// WandererParticle: se mueve aleatoriamente
// ---------------------------
class WandererParticle : public Particle {
public:
	WandererParticle(const ofVec2f & startPos);
	void update() override;
};

// ---------------------------
// Clase principal ofApp
// ---------------------------
class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	std::vector<std::unique_ptr<Particle>> particles;

	// test rendimiento
	bool perfTest = false; // toggle con tecla 'v'
	uint64_t drawTime = 0; // duración draw en microsegundos
};
