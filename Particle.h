#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle(float xPos, float yPos, float xVel, float yVel, float radius);

	void update();

	void draw();

	sf::CircleShape getShape();

private:
	float xPos;
	float yPos;
	float xVel;
	float yVel;
	float radius;
	sf::CircleShape shape;

	void checkCollisions();
};

