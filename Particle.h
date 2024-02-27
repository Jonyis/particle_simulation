#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle(float xPos, float yPos, float xVel, float yVel, float radius);

	void update();

	void draw() const;

	sf::CircleShape getShape() const;

private:
	float xPos;
	float yPos;
	float xVel;
	float yVel;
	float radius;
	sf::CircleShape shape;

	void checkCollisions();
};

