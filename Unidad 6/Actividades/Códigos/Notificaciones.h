#pragma once

#include "ofMain.h"
#include <string>
#include <vector>

//-------------------------------------------
// OBSERVER PATTERN
class Observer {
public:
	virtual void onNotify(const std::string & event) = 0;
};

class Subject {
public:
	void addObserver(Observer * observer);
	void removeObserver(Observer * observer);

protected:
	void notify(const std::string & event);

private:
	std::vector<Observer *> observers;
};

//-------------------------------------------
// STATE PATTERN
class Particle;

class State {
public:
	virtual void update(Particle * particle) = 0;
	virtual void onEnter(Particle * particle) { }
	virtual void onExit(Particle * particle) { }
	virtual ~State() = default;
};

class NormalState : public State {
public:
	void update(Particle * particle) override;
	void onEnter(Particle * particle) override;
};

class AttractState : public State {
public:
	void update(Particle * particle) override;
};

class RepelState : public State {
public:
	void update(Particle * particle) override;
};

class StopState : public State {
public:
	void update(Particle * particle) override;
};

// 🔹 NUEVOS ESTADOS
class ExplodeState : public State {
public:
	void onEnter(Particle * particle) override;
	void update(Particle * particle) override;
};

class GatherState : public State {
public:
	void onEnter(Particle * particle) override;
	void update(Particle * particle) override;
};

//-------------------------------------------
// PARTICLE CLASS
class Particle : public Observer {
public:
	Particle();
	~Particle();

	void update();
	void draw();
	void onNotify(const std::string & event) override;
	void setState(State * newState);

	ofVec2f position;
	ofVec2f velocity;
	float size;
	ofColor color;

private:
	State * state;
};

//-------------------------------------------
// FACTORY
class ParticleFactory {
public:
	static Particle * createParticle(const std::string & type);
};

//-------------------------------------------
// APP
class ofApp : public ofBaseApp, public Subject {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

private:
	std::vector<Particle *> particles;
};
