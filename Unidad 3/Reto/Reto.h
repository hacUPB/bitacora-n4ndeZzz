#pragma once
#include "ofMain.h"
#include <optional> // Necesario para std::optional

// Estructura para agrupar los datos de cada esfera
struct Sphere {
	glm::vec3 position;
	ofColor color;
};

// Estructura para agrupar todos los parámetros de control del grid
struct GridParams {
	int xStep = 20;
	int yStep = 20;
	float distDiv = 50.f;
	float amplitude = 150.f;
	float sphereRadius = 5.f;
	float animationSpeed = 0.5f; // Nuevo parámetro para la animación
};

class ofApp : public ofBaseApp {
public:
	// --- Ciclo de vida de OpenFrameworks
	void setup() override;
	void update() override;
	void draw() override;

	// --- Eventos de Interacción
	void keyPressed(int key) override;
	void mousePressed(int x, int y, int button) override;
	void windowResized(int w, int h) override;

private:
	// --- Funciones auxiliares (Helpers)
	void buildGrid(); // Construye la estructura inicial del grid (posiciones X, Y)
	void updateScene(); // Actualiza la posición Z (animación) y los colores
	void drawUI(); // Dibuja toda la información en pantalla

	// --- Funciones para el Raycasting
	void convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd);
	bool rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
		const glm::vec3 & sphereCenter, float sphereRadius,
		float & outT, glm::vec3 & outPoint);

	// --- Estado de la Escena
	ofEasyCam cam;
	std::vector<Sphere> spheres; // Usamos nuestro nuevo struct
	GridParams params; // Y nuestro struct de parámetros

	// --- Selección (usando una forma más moderna)
	std::optional<int> selectedIndex;
};
