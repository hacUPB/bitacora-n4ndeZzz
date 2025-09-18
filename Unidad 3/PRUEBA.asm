#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	distDiv = 50.0; // Ejemplo de valor inicial
	amplitud = 150.0; // Ejemplo de valor inicial
	xStep = 6.0; // Valor por defecto
	yStep = xStep; // Usar el mismo paso
	// Generar posiciones de esferas
	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += xStep) {
		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += yStep) {
			float z = cos(ofDist(x, y, 0, 0) / distDiv) * amplitud;
			spherePositions.push_back(glm::vec3(x, y, z));
		}
	}
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto & pos : spherePositions) {
		// Dibujar cada esfera en la posición pos
		ofDrawSphere(pos, 5.0); // 5.0 es el radio de la esfera
	}

	if (sphereSelected) {
		// Mostrar información de la esfera seleccionada
		ofDrawBitmapString("Selected Sphere: " + ofToString(selectedSphere), 20, 20);
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	// Convertir las coordenadas del mouse en un rayo 3D
	glm::vec3 rayStart, rayEnd;
	convertMouseToRay(x, y, rayStart, rayEnd);

	// Comprobar si el rayo intersecta alguna esfera
	sphereSelected = false;
	for (auto & pos : spherePositions) {
		glm::vec3 intersectionPoint;
		if (rayIntersectsSphere(rayStart, rayEnd - rayStart, pos, 5.0, intersectionPoint)) {
			// EN ESTA PARTE Debes adicionar la lógica para indicarle
			// a la aplicación la esfera seleccionada.
		}
	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



















#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		vector<glm::vec3> spherePositions; // Almacena las posiciones de las esferas
		float distDiv; // Variable para distDiv
		float amplitud; // Variable para amplitud
		float xStep; // Paso en el eje X
		float yStep; // Paso en el eje Y
		glm::vec3 selectedSphere; // Para almacenar la esfera seleccionada
		bool sphereSelected;
		bool rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir, const glm::vec3 & sphereCenter, float sphereRadius, glm::vec3 & intersectionPoint) {

		}
};
