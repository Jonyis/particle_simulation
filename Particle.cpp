#include "Particle.h"

Particle::Particle(float x, float y, float vx, float vy, float radius, float mass, float elasticity)
	: position(x, y), radius(radius), mass(mass), elasticity(elasticity) {
	if (radius <= 0) {
		throw std::invalid_argument("Radius must be positive");
	}
	if (mass <= 0) {
		throw std::invalid_argument("Mass must be positive");
	}
	if (elasticity < 0) {
		throw std::invalid_argument("Elasticity must be positive");
	}

	oldPosition = position - sf::Vector2f(vx, vy);
}

void Particle::update(float timeStep) {

	sf::Vector2f _velocity = position - oldPosition;
	oldPosition = position;

	position = position + _velocity + acceleration * timeStep * timeStep;
	
	acceleration = { 0.f, 0.f };
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

float Particle::getElasticity() const {
	return elasticity;
}
