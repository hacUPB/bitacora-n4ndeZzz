#include "ofApp.h"
#include <algorithm>

//--------------------------------------------------------------
// SUBJECT IMPLEMENTATION
void Subject::addObserver(Observer * observer) {
	observers.push_back(observer);
}

void Subject::removeObserver(Observer * observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(const std::string & event) {
	for (Observer * observer : observers) {
		observer->onNotify(event);
	}
}

//--------------------------------------------------------------
// PARTICLE IMPLEMENTATION
Particle::Particle() {
	position = ofVec2f(ofRandomWidth(), ofRandomHeight());
	velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
	size = ofRandom(2, 6);
	color = ofColor::white;
	state = new NormalState();
}

Particle::~Particle() {
	delete state;
}

void Particle::setState(State * newState) {
	if (state != nullptr) {
		state->onExit(this);
		delete state;
	}
	state = newState;
	if (state != nullptr) {
		state->onEnter(this);
	}
}

void Particle::update() {
	if (state != nullptr)
		state->update(this);

	// Rebote en bordes
	if (position.x < 0 || position.x > ofGetWidth()) velocity.x *= -1;
	if (position.y < 0 || position.y > ofGetHeight()) velocity.y *= -1;
}

void Particle::draw() {
	ofSetColor(color);
	ofDrawCircle(position, size);
}

//--------------------------------------------------------------
// 🔹 NUEVOS EVENTOS AGREGADOS
void Particle::onNotify(const std::string & event) {
	if (event == "attract") {
		setState(new AttractState());
	} else if (event == "repel") {
		setState(new RepelState());
	} else if (event == "stop") {
		setState(new StopState());
	} else if (event == "normal") {
		setState(new NormalState());
	} else if (event == "explode") {
		setState(new ExplodeState());
	} else if (event == "gather") {
		setState(new GatherState());
	}
}

//--------------------------------------------------------------
// STATE IMPLEMENTATIONS
void NormalState::update(Particle * particle) {
	particle->position += particle->velocity;
}

void NormalState::onEnter(Particle * particle) {
	particle->velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
}

void AttractState::update(Particle * particle) {
	ofVec2f mouse(((ofApp *)ofGetAppPtr())->mouseX, ((ofApp *)ofGetAppPtr())->mouseY);
	ofVec2f dir = mouse - particle->position;
	dir.normalize();
	particle->velocity += dir * 0.05;
	particle->position += particle->velocity;
}

void RepelState::update(Particle * particle) {
	ofVec2f mouse(((ofApp *)ofGetAppPtr())->mouseX, ((ofApp *)ofGetAppPtr())->mouseY);
	ofVec2f dir = particle->position - mouse;
	dir.normalize();
	particle->velocity += dir * 0.05;
	particle->position += particle->velocity;
}

void StopState::update(Particle * particle) {
	particle->velocity.set(0, 0);
}

//--------------------------------------------------------------
// 🔹 NUEVO ESTADO: EXPLODE
void ExplodeState::onEnter(Particle * particle) {
	// Movimiento aleatorio fuerte
	particle->velocity = ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5));
	particle->color = ofColor::red;
}

void ExplodeState::update(Particle * particle) {
	particle->position += particle->velocity;
	particle->velocity *= 0.98; // se va frenando gradualmente
}

//--------------------------------------------------------------
// 🔹 NUEVO ESTADO: GATHER
void GatherState::onEnter(Particle * particle) {
	particle->color = ofColor(0, 200, 255);
}

void GatherState::update(Particle * particle) {
	ofVec2f center(ofGetWidth() / 2, ofGetHeight() / 2);
	ofVec2f dir = center - particle->position;
	dir.normalize();
	particle->velocity += dir * 0.1;
	particle->velocity.limit(3);
	particle->position += particle->velocity;
}

//--------------------------------------------------------------
// FACTORY IMPLEMENTATION
Particle * ParticleFactory::createParticle(const std::string & type) {
	Particle * p = new Particle();

	if (type == "star") {
		p->color = ofColor(255, 255, 150);
		p->size = ofRandom(2, 4);
	} else if (type == "planet") {
		p->color = ofColor(0, 0, 255);
		p->size = ofRandom(5, 8);
	} else if (type == "comet") {
		p->color = ofColor(255, 120, 0);
		p->size = ofRandom(4, 7);
		p->velocity *= 2;
	}

	return p;
}

//--------------------------------------------------------------
// APP IMPLEMENTATION
void ofApp::setup() {
	ofBackground(0);

	for (int i = 0; i < 100; ++i) {
		Particle * p = ParticleFactory::createParticle("star");
		particles.push_back(p);
		addObserver(p);
	}

	for (int i = 0; i < 10; ++i) {
		Particle * p = ParticleFactory::createParticle("planet");
		particles.push_back(p);
		addObserver(p);
	}
}

void ofApp::update() {
	for (Particle * p : particles)
		p->update();
}

void ofApp::draw() {
	for (Particle * p : particles)
		p->draw();

	ofSetColor(255);
	ofDrawBitmapString("Presiona:\nA - Attract\nR - Repel\nS - Stop\nN - Normal\nE - Explode\nG - Gather", 20, 20);
}

void ofApp::keyPressed(int key) {
	if (key == 's')
		notify("stop");
	else if (key == 'a')
		notify("attract");
	else if (key == 'r')
		notify("repel");
	else if (key == 'n')
		notify("normal");
	else if (key == 'e')
		notify("explode");
	else if (key == 'g')
		notify("gather");
}
