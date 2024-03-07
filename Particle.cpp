#include "Particle.h"

Particle::Particle(float x, float y, float vx, float vy, float radius, float mass)
	: position(x, y), velocity(vx, vy), radius(radius), mass(mass) {
	if (radius <= 0) {
		throw std::invalid_argument("Radius must be positive");
	}
	if (mass <= 0) {
		throw std::invalid_argument("Mass must be positive");
	}
	this->radius = radius;
	this->mass = mass;

	this->shape = sf::CircleShape(radius);
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineThickness(-2);
	shape.setOutlineColor(sf::Color::Red);
}

void Particle::update(float timeStep) {

	sf::Vector2f _velocity = position - oldPosition;
	oldPosition = position;

	position = position + _velocity + acceleration * timeStep * timeStep;
	
	acceleration = { 0.f, 0.f };

	this->shape.setPosition(this->position.x - this->radius, this->position.y - this->radius);
	checkCollisions();
}

void Particle::accelerate(sf::Vector2f accel) {
	acceleration += accel;
}

bool Particle::collidesWith(const Particle& other) const {
	sf::Vector2f dPos = position - other.position;
	float distance_sqrd = (dPos.x * dPos.x + dPos.y * dPos.y);
	float radius_sum = radius + other.radius;
	return distance_sqrd < (radius_sum * radius_sum);
}

void Particle::checkCollisions() {
	if (this->position.x + this->radius > 500 || this->position.x - this->radius < 0) {
		sf::Vector2f tmp = position;

		this->position.x = std::max(this->position.x, this->radius);
		this->position.x = std::min(this->position.x, 500.f - this->radius);

		position.x = oldPosition.x;
		oldPosition.x = tmp.x;
		this->velocity.x *= -1;
	}

	if (this->position.y + this->radius > 500 || this->position.y - this->radius < 0) {
		sf::Vector2f tmp = position;

		this->position.y = std::max(this->position.y, this->radius);
		this->position.y = std::min(this->position.y, 500.f - this->radius);

		this->velocity.y *= -1;
		position.y = oldPosition.y;
		oldPosition.y = tmp.y;
	}
}

void Particle::draw() const {
	// draw stuff here (put in render class to centralize in case of changing renderer?)
}

sf::CircleShape Particle::getShape() const {
	return shape;
}

sf::Vector2f Particle::getVelocity() const {
	return position - oldPosition;
}

void Particle::setVelocity(sf::Vector2f newVelocity) {
	oldPosition = position - newVelocity;
}

float Particle::getMass() const {
	return mass;
}
