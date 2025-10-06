#include "ofApp.h"
#include <algorithm> // remove_if

// ---------------------------
// Implementación Particle
// ---------------------------
Particle::Particle(const ofVec2f & startPos) {
	position = startPos;
	velocity.set(ofRandom(-2, 2), ofRandom(-2, 2));
	acceleration.set(0, 0);
	radius = 5.0f;
	color = ofColor::fromHsb(ofRandom(255), 200, 255);
	lifespan = 255.0f;
}

void Particle::update() {
	velocity += acceleration;
	position += velocity;
	acceleration *= 0;
	lifespan -= 1.0f;
}

void Particle::draw() {
	ofSetColor(color, ofClamp(lifespan, 0.0f, 255.0f));
	ofDrawCircle(position, radius);
}

bool Particle::isDead() const {
	return lifespan <= 0.0f;
}

// ---------------------------
// SeekerParticle
// ---------------------------
SeekerParticle::SeekerParticle(const ofVec2f & startPos)
	: Particle(startPos) { radius = 4.0f; }

void SeekerParticle::update() {
	ofVec2f mousePos(ofGetMouseX(), ofGetMouseY());
	ofVec2f desired = mousePos - position;
	if (desired.length() > 0.0001f) {
		desired.normalize();
		desired *= 0.5f;
	}
	ofVec2f steer = desired - velocity;
	if (steer.length() > 0.1f) {
		steer.normalize();
		steer *= 0.1f;
	}
	acceleration += steer;
	Particle::update();
}

// ---------------------------
// WandererParticle
// ---------------------------
WandererParticle::WandererParticle(const ofVec2f & startPos)
	: Particle(startPos) { radius = 6.0f; }

void WandererParticle::update() {
	ofVec2f randomForce(ofRandom(-0.2f, 0.2f), ofRandom(-0.2f, 0.2f));
	acceleration += randomForce;
	Particle::update();
}

// ---------------------------
// ofApp
// ---------------------------
void ofApp::setup() {
	ofSetBackgroundColor(0);
	ofSetVerticalSync(false); // sin límite
}

void ofApp::update() {
	for (auto & p : particles)
		p->update();
	particles.erase(
		std::remove_if(particles.begin(), particles.end(),
			[](const std::unique_ptr<Particle> & p) { return p->isDead(); }),
		particles.end());
}

void ofApp::draw() {
	uint64_t start = ofGetElapsedTimeMicros();

	for (auto & p : particles)
		p->draw();

	uint64_t end = ofGetElapsedTimeMicros();
	drawTime = end - start;

	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate()), 20, 20);
	if (perfTest) {
		ofDrawBitmapStringHighlight("Tiempo draw(): " + ofToString(drawTime) + " us", 20, 40);
		ofDrawBitmapStringHighlight("Particulas: " + ofToString(particles.size()), 20, 60);
	}
}

void ofApp::keyPressed(int key) {
	if (key == 's') {
		for (int i = 0; i < 1000; i++) {
			particles.emplace_back(new SeekerParticle(ofVec2f(ofRandomWidth(), ofRandomHeight())));
		}
	}
	if (key == 'w') {
		for (int i = 0; i < 1000; i++) {
			particles.emplace_back(new WandererParticle(ofVec2f(ofRandomWidth(), ofRandomHeight())));
		}
	}
	if (key == 'a') { // stress test masivo
		for (int i = 0; i < 100000; i++) {
			particles.emplace_back(new WandererParticle(ofVec2f(ofRandomWidth(), ofRandomHeight())));
		}
	}
	if (key == 'v') perfTest = !perfTest; // toggle
}
