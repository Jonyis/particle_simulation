#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle(float xPos, float yPos, float xVel, float yVel, float radius, float mass, float elasticity, const sf::Texture& texture);

	void update(float timeStep);

	bool collidesWith(const Particle& other) const;

	void draw(sf::RenderWindow& window) const;

	sf::Vector2f getPosition() const;

	void setPosition(sf::Vector2f position);

	sf::Vector2f getVelocity() const;

	void setVelocity(sf::Vector2f velocity);

	float getRadius() const;

	void setRadius(float radius);

	float getMass() const;

	float getElasticity() const;

	void accelerate(sf::Vector2f accel);


private:
	sf::Vector2f position;
	sf::Vector2f oldPosition = position;
	sf::Vector2f acceleration = { 0.f, 0.f };
	float radius;
	float mass;
	float elasticity = 1.f;
	sf::Sprite sprite;
};

