#include "Rectangle.h"

Rectangle::Rectangle(double width, double height) : width(width), height(height) {}

void Rectangle::bounceParticle(Particle& particle) {
	sf::Vector2f pos = particle.getPosition();
	float radius = particle.getRadius();
	if (pos.x + radius > width || pos.x - radius < 0) {
		sf::Vector2f vel = particle.getVelocity();
		sf::Vector2f oldPos = pos - vel;

		particle.setPosition({ oldPos.x, pos.y });
		sf::Vector2f newVel = { -vel.x, vel.y };
		particle.setVelocity(newVel * particle.getElasticity());
	}

	if (pos.y + radius > height || pos.y - radius < 0) {
		sf::Vector2f vel = particle.getVelocity();
		sf::Vector2f oldPos = pos - vel;

		particle.setPosition({ pos.x, oldPos.y });
		sf::Vector2f newVel = { vel.x, -vel.y };
		particle.setVelocity(newVel * particle.getElasticity());
	}
}

void Rectangle::draw(sf::RenderWindow& window) {
	// Implement the logic to draw the rectangle
	return;
}	
