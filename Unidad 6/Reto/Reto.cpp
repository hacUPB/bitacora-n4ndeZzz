#include "ofApp.h"

// ------------------------------------------------------------
// ?? Implementación de la clase Plant
Plant::Plant(float x, float y, float g, ofColor c, std::string t)
	: position(x, y)
	, growth(g)
	, color(c)
	, type(t)
	, currentState(new GrowingState()) { }

Plant::~Plant() {
	delete currentState;
}

void Plant::setState(IState * newState) {
	delete currentState;
	currentState = newState;
}

void Plant::update() {
	currentState->update(this);
}

void Plant::draw() {
	ofSetColor(color);
	ofDrawCircle(position, growth);
	ofDrawBitmapStringHighlight(type, position.x - 15, position.y + 25);
}

void Plant::onNotify(const std::string & event) {
	ofLogNotice("Observer") << "Planta tipo " << type << " recibió evento: " << event;

	if (event == "sun") {
		setState(new GrowingState());
	} else if (event == "rain") {
		setState(new BloomState());
	} else if (event == "night") {
		setState(new WitherState());
	}
}

// ------------------------------------------------------------
// ?? Estados (State Pattern)
void GrowingState::update(Plant * plant) {
	plant->growth += 0.3f;
	if (plant->growth > 40) plant->growth = 40;
	plant->color = ofColor::green;
}

void BloomState::update(Plant * plant) {
	plant->color = ofColor::fromHsb(ofRandom(255), 200, 255);
	plant->growth += sin(ofGetElapsedTimef() * 3) * 0.2f;
}

void WitherState::update(Plant * plant) {
	plant->growth -= 0.2f;
	if (plant->growth < 5) plant->growth = 5;
	plant->color.lerp(ofColor::brown, 0.02f);
}

// ------------------------------------------------------------
// ?? Factory Pattern
Plant * PlantFactory::createPlant(float x, float y, std::string type) {
	if (type == "flower") {
		return new Plant(x, y, 10, ofColor::pink, "Flor");
	} else if (type == "cactus") {
		return new Plant(x, y, 15, ofColor::green, "Cactus");
	} else if (type == "mushroom") {
		return new Plant(x, y, 8, ofColor::orange, "Hongo");
	} else {
		return new Plant(x, y, 12, ofColor::white, "Desconocida");
	}
}

// ------------------------------------------------------------
// ?? ofApp
void ofApp::setup() {
	ofBackground(0);
	ofSetFrameRate(60);

	// Crear distintas plantas desde el Factory
	plants.push_back(PlantFactory::createPlant(150, 400, "flower"));
	plants.push_back(PlantFactory::createPlant(300, 400, "cactus"));
	plants.push_back(PlantFactory::createPlant(450, 400, "mushroom"));
	plants.push_back(PlantFactory::createPlant(600, 400, "flower"));
	plants.push_back(PlantFactory::createPlant(750, 400, "cactus"));

	// Añadirlas como observadores
	for (auto & p : plants)
		addObserver(p);
}

// ------------------------------------------------------------
void ofApp::update() {
	for (auto & p : plants)
		p->update();
}

// ------------------------------------------------------------
void ofApp::draw() {
	for (auto & p : plants)
		p->draw();

	ofSetColor(255);
	ofDrawBitmapStringHighlight("?? [1] Sol  |  ?? [2] Lluvia  |  ?? [3] Noche", 20, 20);
	ofDrawBitmapStringHighlight("Patrones: Observer + State + Factory", 20, 50);
}

// ------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		currentEvent = "sun";
		notify("sun");
	} else if (key == '2') {
		currentEvent = "rain";
		notify("rain");
	} else if (key == '3') {
		currentEvent = "night";
		notify("night");
	}
}
