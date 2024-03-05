#include "Particle.h"

Particle::Particle(float xPos, float yPos, float xVel, float yVel, float radius, float mass) {
	this->position = sf::Vector2f(xPos, yPos);
	this->velocity = sf::Vector2f(xVel, yVel);
	this->radius = radius;
	this->mass = mass;

	this->shape = sf::CircleShape(radius);
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineThickness(-2);
	shape.setOutlineColor(sf::Color::Red);
}

void Particle::update() {
	this->position += this->velocity;
	this->shape.setPosition(this->position.x - this->radius, this->position.y - this->radius);
	checkCollisions();
}

bool Particle::collidesWith(const Particle& other) const {
	sf::Vector2f dPos = position - other.position;
	float distance_sqrd = (dPos.x * dPos.x + dPos.y * dPos.y);
	return distance_sqrd < std::pow(radius + other.radius, 2);
}

void Particle::checkCollisions() {
	if (this->position.x + this->radius > 500 || this->position.x - this->radius < 0)
		this->velocity.x *= -1;

	if (this->position.y + this->radius > 500 || this->position.y - this->radius < 0)
		this->velocity.y *= -1;
}

void Particle::draw() const {
	// draw stuff here (put in render class to centralize in case of changing renderer?)
}


sf::CircleShape Particle::getShape() const {
	return this->shape;
}

sf::Vector2f Particle::getVelocity() const {
	return this->velocity;
}

void Particle::setVelocity(sf::Vector2f newVelocity) {
	this->velocity = newVelocity;
}

float Particle::getMass() const {
	return this->mass;
}
