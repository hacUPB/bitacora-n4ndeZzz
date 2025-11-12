#pragma once
#include "ofMain.h"
#include <string>
#include <vector>

// ------------------------------------------------------------
// ?? Patrón Observer
class IObserver {
public:
	virtual void onNotify(const std::string & event) = 0;
};

// ------------------------------------------------------------
// ?? Patrón Subject
class Subject {
protected:
	std::vector<IObserver *> observers;

public:
	void addObserver(IObserver * obs) { observers.push_back(obs); }

	void notify(const std::string & event) {
		for (auto & o : observers)
			o->onNotify(event);
	}
};

// ------------------------------------------------------------
// ?? Declaración previa
class Plant;

// ------------------------------------------------------------
// ?? Patrón State
class IState {
public:
	virtual void update(Plant * plant) = 0;
	virtual ~IState() = default;
};

class GrowingState : public IState {
public:
	void update(Plant * plant) override;
};

class BloomState : public IState {
public:
	void update(Plant * plant) override;
};

class WitherState : public IState {
public:
	void update(Plant * plant) override;
};

// ------------------------------------------------------------
// ?? Clase Plant (Observer + State)
class Plant : public IObserver {
public:
	glm::vec2 position;
	float growth;
	ofColor color;
	std::string type;
	IState * currentState;

	Plant(float x, float y, float g, ofColor c, std::string t);
	~Plant();

	void update();
	void draw();
	void setState(IState * newState);
	void onNotify(const std::string & event) override;
};

// ------------------------------------------------------------
// ?? Patrón Factory
class PlantFactory {
public:
	static Plant * createPlant(float x, float y, std::string type);
};

// ------------------------------------------------------------
// ?? Clase principal openFrameworks
class ofApp : public ofBaseApp, public Subject {
public:
	std::vector<Plant *> plants;
	std::string currentEvent;

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
};
