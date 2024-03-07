#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle(float xPos, float yPos, float xVel, float yVel, float radius, float mass);

	void update(float timeStep);

	bool collidesWith(const Particle& other) const;

	void draw() const;

	sf::CircleShape getShape() const;

	sf::Vector2f getVelocity() const;

	void setVelocity(sf::Vector2f velocity);

	float getMass() const;

	void accelerate(sf::Vector2f accel);


private:
	sf::Vector2f position;
	sf::Vector2f oldPosition = position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration = { 0.f, 0.f };
	float radius;
	float mass;
	sf::CircleShape shape;

	void checkCollisions();
};

