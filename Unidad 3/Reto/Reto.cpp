#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Grid de Esferas Animado + Raycasting");
	ofSetFrameRate(60);
	ofBackground(210);
	ofEnableDepthTest();

	cam.setDistance(600);
	cam.setNearClip(0.1f);
	cam.setFarClip(5000.f);

	buildGrid(); // Construye la malla inicial
}

//--------------------------------------------------------------
void ofApp::update() {
	updateScene(); // Actualiza la animación y colores en cada frame
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();

	// Dibuja todas las esferas usando los datos pre-calculados en updateScene()
	for (const auto & sphere : spheres) {
		ofSetColor(sphere.color);
		ofDrawSphere(sphere.position, params.sphereRadius);
	}

	// Resalta la esfera seleccionada, si existe
	if (selectedIndex.has_value()) {
		ofSetColor(0);
		ofNoFill();
		ofDrawSphere(spheres[*selectedIndex].position, params.sphereRadius * 1.8f);
		ofFill();
	}

	cam.end();

	// Dibuja la interfaz de usuario
	drawUI();
}

//--------------------------------------------------------------
void ofApp::updateScene() {
	float time = ofGetElapsedTimef();

	// Itera sobre cada esfera para actualizar su altura (z) y color
	for (auto & sphere : spheres) {
		float dist = ofDist(sphere.position.x, sphere.position.y, 0, 0);
		float z = cos(dist / params.distDiv + time * params.animationSpeed) * params.amplitude;
		sphere.position.z = z;

		// El color se calcula en base a la nueva altura
		float h = ofMap(z, -std::abs(params.amplitude), std::abs(params.amplitude), 0, 255, true);
		sphere.color = ofColor::fromHsb(static_cast<unsigned char>(h), 255, 255);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'w':
		params.amplitude += 10.f;
		break;
	case 's':
		params.amplitude -= 10.f;
		break;
	case 'd':
		params.distDiv += 5.f;
		break;
	case 'a':
		params.distDiv -= 5.f;
		break;
	case 'e':
		params.xStep += 2;
		params.yStep += 2;
		break;
	case 'q':
		params.xStep -= 2;
		params.yStep -= 2;
		break;
	case 'x':
		params.sphereRadius += 0.5f;
		break;
	case 'z':
		params.sphereRadius -= 0.5f;
		break;
	default:
		break;
	}

	// Aplicar límites
	params.xStep = std::max(2, params.xStep);
	params.yStep = std::max(2, params.yStep);
	params.distDiv = std::max(1.f, params.distDiv);
	params.amplitude = std::max(0.f, params.amplitude);
	params.sphereRadius = std::max(0.5f, params.sphereRadius);

	// Si el paso del grid cambia, hay que reconstruirlo
	if (key == 'q' || key == 'e') {
		buildGrid();
	}

	selectedIndex.reset(); // Anula la selección
}

//--------------------------------------------------------------
void ofApp::mousePressed(int mx, int my, int button) {
	glm::vec3 rayStart, rayEnd;
	convertMouseToRay(mx, my, rayStart, rayEnd);
	glm::vec3 dir = glm::normalize(rayEnd - rayStart);

	float bestT = std::numeric_limits<float>::max();
	int bestIdx = -1;

	for (int i = 0; i < spheres.size(); ++i) {
		glm::vec3 point;
		float t;
		if (rayIntersectsSphere(rayStart, dir, spheres[i].position, params.sphereRadius, t, point)) {
			if (t > 0.f && t < bestT) { // Encuentra la intersección más cercana
				bestT = t;
				bestIdx = i;
			}
		}
	}

	if (bestIdx != -1) {
		selectedIndex = bestIdx; // Asigna el índice si se encontró una esfera
	} else {
		selectedIndex.reset(); // Anula la selección si no
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	buildGrid(); // Recalcula el grid para que llene la nueva ventana
}

//--------------------------------------------------------------
void ofApp::buildGrid() {
	spheres.clear();
	spheres.reserve((ofGetWidth() / params.xStep + 2) * (ofGetHeight() / params.yStep + 2));

	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += params.xStep) {
		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += params.yStep) {
			// Crea una nueva esfera solo con su posición X y Y. Z se calculará en updateScene.
			spheres.emplace_back(Sphere { glm::vec3(x, y, 0) });
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawUI() {
	ofDisableDepthTest();
	ofSetColor(0);

	std::string info;
	info += "FPS: " + ofToString(ofGetFrameRate(), 2) + "\n";
	info += "Step (x,y): " + ofToString(params.xStep) + ", " + ofToString(params.yStep) + "\n";
	info += "distDiv: " + ofToString(params.distDiv, 2) + "\n";
	info += "amplitude: " + ofToString(params.amplitude, 2) + "\n";
	info += "radius: " + ofToString(params.sphereRadius, 2) + "\n";
	info += "Controles:\n";
	info += "  Q/E  - step -/+ (x,y)\n";
	info += "  A/D  - distDiv -/+\n";
	info += "  S/W  - amplitude -/+\n";
	info += "  Z/X  - radius -/+\n";
	info += "  Click para seleccionar una esfera\n";
	ofDrawBitmapStringHighlight(info, 18, 24);

	if (selectedIndex.has_value()) {
		const auto & sp = spheres[*selectedIndex].position;
		std::string selInfo = "Seleccion: idx=" + ofToString(*selectedIndex) + " pos=(" + ofToString(sp.x, 0) + ", " + ofToString(sp.y, 0) + ", " + ofToString(sp.z, 0) + ")";
		ofDrawBitmapStringHighlight(selInfo, 18, 180);
	}
	ofEnableDepthTest();
}

// ---- Las funciones de raycasting permanecen sin cambios lógicos ----
//--------------------------------------------------------------
void ofApp::convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd) {
	glm::mat4 modelview = cam.getModelViewMatrix();
	glm::mat4 projection = cam.getProjectionMatrix();
	ofRectangle viewport = ofGetCurrentViewport();
	float x = 2.f * (mouseX - viewport.x) / viewport.width - 1.f;
	float y = 1.f - 2.f * (mouseY - viewport.y) / viewport.height;
	glm::vec4 rayStartNDC(x, y, -1.f, 1.f);
	glm::vec4 rayEndNDC(x, y, 1.f, 1.f);
	glm::mat4 inv = glm::inverse(projection * modelview);
	glm::vec4 startWorld = inv * rayStartNDC;
	glm::vec4 endWorld = inv * rayEndNDC;
	startWorld /= startWorld.w;
	endWorld /= endWorld.w;
	rayStart = glm::vec3(startWorld);
	rayEnd = glm::vec3(endWorld);
}

//--------------------------------------------------------------
bool ofApp::rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
	const glm::vec3 & sphereCenter, float sphereRadius,
	float & outT, glm::vec3 & outPoint) {
	glm::vec3 oc = rayStart - sphereCenter;
	float a = glm::dot(rayDir, rayDir);
	float b = 2.f * glm::dot(oc, rayDir);
	float c = glm::dot(oc, oc) - sphereRadius * sphereRadius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0.f) return false;
	float sqrtDisc = sqrtf(discriminant);
	float t1 = (-b - sqrtDisc) / (2.f * a);
	float t2 = (-b + sqrtDisc) / (2.f * a);
	float t = std::numeric_limits<float>::max();
	if (t1 > 0.f) t = t1;
	if (t2 > 0.f && t2 < t) t = t2;
	if (t == std::numeric_limits<float>::max()) return false;
	outT = t;
	outPoint = rayStart + t * rayDir;
	return true;
}
