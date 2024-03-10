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
	//checkCollisions();
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
		sf::Vector2f pos = getPosition();
		sf::Vector2f vel = getVelocity();
		sf::Vector2f oldPos = pos - vel;

		setPosition({ oldPos.x, pos.y });
		setVelocity({ -vel.x, vel.y });
	}

	if (this->position.y + this->radius > 500 || this->position.y - this->radius < 0) {
		sf::Vector2f pos = getPosition();
		sf::Vector2f vel = getVelocity();
		sf::Vector2f oldPos = pos - vel;

		setPosition({ pos.x, oldPos.y });
		setVelocity({ vel.x, -vel.y });
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

sf::Vector2f Particle::getPosition() const {
	return position;
}

void Particle::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
}

void Particle::setVelocity(sf::Vector2f newVelocity) {
	oldPosition = position - newVelocity;
}

float Particle::getMass() const {
	return mass;
}

float Particle::getRadius() const {
	return radius;
}

void Particle::setRadius(float newRadius) {
	radius = newRadius;
}
