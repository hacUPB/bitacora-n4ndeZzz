#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);

	// Cargar los shaders desde la carpeta bin/data/shadersGL3/
	shader.load("shadersGL3/shader");

	// Crear un plano centrado en pantalla
	float planeScale = 0.75;
	int planeWidth = ofGetWidth() * planeScale;
	int planeHeight = ofGetHeight() * planeScale;
	int planeGridSize = 20;
	int planeColumns = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;

	plane.set(planeWidth, planeHeight, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
}

void ofApp::update() {
	// No hay animaciones en la lógica por ahora
}

void ofApp::draw() {
	// Calcular un color base dependiendo del mouse
	float percentX = mouseX / (float)ofGetWidth();
	percentX = ofClamp(percentX, 0, 1);

	ofColor colorLeft = ofColor::magenta;
	ofColor colorRight = ofColor::cyan;
	ofColor colorMix = colorLeft.getLerped(colorRight, percentX);
	ofSetColor(colorMix);

	// Activar el shader
	shader.begin();

	// Enviar variables uniformes
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	shader.setUniform4f("globalColor", colorMix.r / 255.0, colorMix.g / 255.0, colorMix.b / 255.0, 1.0);

	// Posicionar y rotar el plano
	float tx = ofGetWidth() / 2;
	float ty = ofGetHeight() / 2;
	ofTranslate(tx, ty);

	float percentY = mouseY / (float)ofGetHeight();
	float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
	ofRotate(rotation, 1, 0, 0);

	// Dibujar el plano
	plane.draw();

	shader.end();
}
