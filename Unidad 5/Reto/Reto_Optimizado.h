#pragma once
#include "ofMain.h"
#include <memory>
#include <vector>

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

class SeekerParticle : public Particle {
public:
	SeekerParticle(const ofVec2f & startPos);
	void update() override;
};

class WandererParticle : public Particle {
public:
	WandererParticle(const ofVec2f & startPos);
	void update() override;
};

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	std::vector<std::unique_ptr<Particle>> particles;

	bool perfTest = false;
	bool useVbo = true; // toggle entre clásico y VBO
	uint64_t drawTime = 0;
};
