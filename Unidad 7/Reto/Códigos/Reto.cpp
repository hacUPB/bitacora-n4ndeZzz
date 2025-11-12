#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);


	shader.load("shadersGL3/shader");


	float planeScale = 0.75;
	int planeWidth = ofGetWidth() * planeScale;
	int planeHeight = ofGetHeight() * planeScale;
	int planeGridSize = 20;
	int planeColumns = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;

	plane.set(planeWidth, planeHeight, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
	plane.mapTexCoordsFromTexture(ofTexture()); 
}

void ofApp::update() {
}

void ofApp::draw() {
	ofBackground(0);

	shader.begin();

	float cx = ofGetWidth() / 2.0;
	float cy = ofGetHeight() / 2.0;
	float mx = mouseX - cx;
	float my = mouseY - cy;

	shader.setUniform1f("mouseRange", 150);
	shader.setUniform2f("mousePos", mx, my);


	float percentX = mouseX / (float)ofGetWidth();
	percentX = ofClamp(percentX, 0, 1);
	ofFloatColor colorLeft = ofColor::red;
	ofFloatColor colorRight = ofColor::green;
	ofFloatColor colorMix = colorLeft.getLerped(colorRight, percentX);

	float mouseColor[4] = { colorMix.r, colorMix.g, colorMix.b, colorMix.a };
	shader.setUniform4fv("mouseColor", &mouseColor[0]);

	ofTranslate(cx, cy);
	plane.drawWireframe();

	shader.end();
}
