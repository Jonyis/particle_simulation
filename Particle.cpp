#include "Particle.h"

Particle::Particle(float xPos, float yPos, float xVel, float yVel, float radius) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->xVel = xVel;
	this->yVel = yVel;
	this->radius = radius;

	this->shape = sf::CircleShape(radius);
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineThickness(-2);
	shape.setOutlineColor(sf::Color::Red);
}

void Particle::update() {
	this->xPos += this->xVel;
	this->yPos += this->yVel;
	this->shape.setPosition(this->xPos - this->radius, this->yPos - this->radius);
	checkCollisions();
}

void Particle::checkCollisions() {
	if (this->xPos + this->radius > 500 || this->xPos - this->radius < 0)
		this->xVel *= -1;

	if (this->yPos + this->radius > 500 || this->yPos - this->radius < 0)
		this->yVel *= -1;
}

void Particle::draw() const {
	// draw stuff here (put in render class to centralize in case of changing renderer?)
}


sf::CircleShape Particle::getShape() const {
	return this->shape;
}