#include "ofApp.h"

//--------------------------------------------------------------
// SUBJECT METHODS
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
// PARTICLE METHODS
Particle::Particle() {
	position = ofVec2f(ofRandomWidth(), ofRandomHeight());
	velocity = ofVec2f(ofRandom(-0.5f, 0.5f), ofRandom(-0.5f, 0.5f));
	size = ofRandom(2, 5);
	color = ofColor(255);
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

//--------------------------------------------------------------
// 🔹 Modificación del comportamiento
void Particle::update() {
	if (state != nullptr) {
		state->update(this);
	}

	// Movimiento oscilante (más orgánico)
	float t = ofGetElapsedTimef();
	position.x += cos(t * 0.5 + ofRandom(0.1, 1.0)) * velocity.x;
	position.y += sin(t * 0.5 + ofRandom(0.1, 1.0)) * velocity.y;

	// Cambio de color progresivo
	color.setHueAngle(fmod(ofGetElapsedTimef() * 10, 360));

	// Rebote en bordes
	if (position.x < 0 || position.x > ofGetWidth()) velocity.x *= -1;
	if (position.y < 0 || position.y > ofGetHeight()) velocity.y *= -1;
}

//--------------------------------------------------------------
void Particle::draw() {
	// Efecto de pulso
	float pulse = ofMap(sin(ofGetElapsedTimef() * 2), -1, 1, 0.8, 1.2);
	ofSetColor(color);
	ofDrawCircle(position, size * pulse);
}

//--------------------------------------------------------------
void Particle::onNotify(const std::string & event) {
	if (event == "attract") {
		setState(new AttractState());
	} else if (event == "repel") {
		setState(new RepelState());
	} else if (event == "stop") {
		setState(new StopState());
	} else if (event == "normal") {
		setState(new NormalState());
	}
}

//--------------------------------------------------------------
// STATES IMPLEMENTATION
void NormalState::update(Particle * particle) {
	// Movimiento base: mantenemos la velocidad con suavidad
	particle->position += particle->velocity * 0.5;
}

void NormalState::onEnter(Particle * particle) {
	particle->velocity = ofVec2f(ofRandom(-0.5f, 0.5f), ofRandom(-0.5f, 0.5f));
}

void AttractState::update(Particle * particle) {
	ofVec2f mousePosition(((ofApp *)ofGetAppPtr())->mouseX, ((ofApp *)ofGetAppPtr())->mouseY);
	ofVec2f direction = mousePosition - particle->position;
	direction.normalize();
	particle->velocity += direction * 0.05;
	particle->position += particle->velocity * 0.3;
}

void RepelState::update(Particle * particle) {
	ofVec2f mousePosition(((ofApp *)ofGetAppPtr())->mouseX, ((ofApp *)ofGetAppPtr())->mouseY);
	ofVec2f direction = particle->position - mousePosition;
	direction.normalize();
	particle->velocity += direction * 0.05;
	particle->position += particle->velocity * 0.3;
}

void StopState::update(Particle * particle) {
	particle->velocity.set(0, 0);
}

//--------------------------------------------------------------
// FACTORY IMPLEMENTATION
Particle * ParticleFactory::createParticle(const std::string & type) {
	Particle * particle = new Particle();

	if (type == "star") {
		particle->size = ofRandom(2, 4);
		particle->color = ofColor(255, 255, 0);
	} else if (type == "shooting_star") {
		particle->size = ofRandom(3, 6);
		particle->color = ofColor(0, 255, 255);
		particle->velocity *= 3;
	} else if (type == "planet") {
		particle->size = ofRandom(5, 8);
		particle->color = ofColor(0, 0, 255);
	} else if (type == "comet") {
		particle->size = ofRandom(6, 10);
		particle->color = ofColor(255, 165, 0);
		particle->velocity *= 5;
	}

	return particle;
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

	for (int i = 0; i < 5; ++i) {
		Particle * p = ParticleFactory::createParticle("shooting_star");
		particles.push_back(p);
		addObserver(p);
	}

	for (int i = 0; i < 10; ++i) {
		Particle * p = ParticleFactory::createParticle("planet");
		particles.push_back(p);
		addObserver(p);
	}

	for (int i = 0; i < 3; ++i) {
		Particle * p = ParticleFactory::createParticle("comet");
		particles.push_back(p);
		addObserver(p);
	}
}

void ofApp::update() {
	for (Particle * p : particles) {
		p->update();
	}
}

void ofApp::draw() {
	for (Particle * p : particles) {
		p->draw();
	}
}

void ofApp::keyPressed(int key) {
	if (key == 's') {
		notify("stop");
	} else if (key == 'a') {
		notify("attract");
	} else if (key == 'r') {
		notify("repel");
	} else if (key == 'n') {
		notify("normal");
	}
}
