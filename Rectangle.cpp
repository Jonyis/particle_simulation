#include "Rectangle.h"

Rectangle::Rectangle(float width, float height) : width(width), height(height), shape({ width, height }) {
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Red);
}

void Rectangle::bounceParticle(Particle& particle) {
	sf::Vector2f pos = particle.getPosition();
	float radius = particle.getRadius();
	if (pos.x + radius > width || pos.x - radius < 0) {
		sf::Vector2f vel = particle.getVelocity();
		sf::Vector2f oldPos = pos - vel;
		bounce(particle, { oldPos.x, pos.y }, { -vel.x, vel.y });
	}

	if (pos.y + radius > height || pos.y - radius < 0) {
		sf::Vector2f vel = particle.getVelocity();
		sf::Vector2f oldPos = pos - vel;
		bounce(particle, { pos.x, oldPos.y }, { vel.x, -vel.y });
	}
}

void Rectangle::bounce(Particle& particle, const sf::Vector2f& newPos, const sf::Vector2f& newVel) const {
	particle.setPosition(newPos);
	float elasticity = particle.getElasticity();
	if (elasticity > 0)
		particle.setVelocity(newVel * elasticity);
}

void Rectangle::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}	
