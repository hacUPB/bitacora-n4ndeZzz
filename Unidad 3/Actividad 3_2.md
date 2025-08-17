```py  

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(1);
	particleColor = ofColor::white;
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto & pos : particles) {
		ofSetColor(particleColor);
		ofDrawCircle(pos.x, pos.y, 10);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	particles.push_back(ofVec2f(x, y));
	if (particles.size() > 10) {
		particles.erase(particles.begin());
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	particleColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

```  

__En este código lo que hice fue cambiar el color del background, el tamaño de las partículas, y también el de la esfera__  
