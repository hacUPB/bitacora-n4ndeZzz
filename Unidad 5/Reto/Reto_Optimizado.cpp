#include "ofApp.h"
#include <algorithm>

// Particle
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
bool Particle::isDead() const { return lifespan <= 0.0f; }

// Seeker
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

// Wanderer
WandererParticle::WandererParticle(const ofVec2f & startPos)
	: Particle(startPos) { radius = 6.0f; }
void WandererParticle::update() {
	ofVec2f randomForce(ofRandom(-0.2f, 0.2f), ofRandom(-0.2f, 0.2f));
	acceleration += randomForce;
	Particle::update();
}

// ofApp
void ofApp::setup() {
	ofSetBackgroundColor(0);
	ofSetVerticalSync(false);
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
	if (useVbo) {
		// ✅ Dibujo optimizado con VBO
		ofVboMesh mesh;
		mesh.setMode(OF_PRIMITIVE_POINTS);

		for (auto & p : particles) {
			ofVec2f pos2D = p->getPosition();
			mesh.addVertex(glm::vec3(pos2D.x, pos2D.y, 0)); // conversión a 3D
			mesh.addColor(p->getColor());
		}

		mesh.draw();
		ofDrawBitmapStringHighlight("Modo: VBO (ofVboMesh)", 20, 20, ofColor::black, ofColor::white);
	} else {
		// Dibujo clásico
		for (auto & p : particles) {
			p->draw();
		}
		ofDrawBitmapStringHighlight("Modo: Clásico (ofDrawCircle)", 20, 20, ofColor::black, ofColor::white);
	}

	// FPS y partículas activas
	ofSetColor(255);
	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate(), 2), 20, 40, ofColor::black, ofColor::white);
	ofDrawBitmapStringHighlight("Particulas activas: " + ofToString(particles.size()), 20, 60, ofColor::black, ofColor::white);
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
	if (key == 'a') {
		for (int i = 0; i < 100000; i++) {
			particles.emplace_back(new WandererParticle(ofVec2f(ofRandomWidth(), ofRandomHeight())));
		}
	}
	if (key == 'v') perfTest = !perfTest;
	if (key == 'b') useVbo = !useVbo;
}