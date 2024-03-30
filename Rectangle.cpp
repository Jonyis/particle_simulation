#include "Rectangle.h"

Rectangle::Rectangle(float width, float height, sf::Vector2f center) : width(width), height(height), center(center), shape({width, height}) {
	shape.setPosition(center.x - width / 2, center.y - height / 2);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Red);
}

void Rectangle::bounceParticle(Particle& particle) {
	sf::Vector2f pos = particle.getPosition();
	float radius = particle.getRadius();
	static const float leftBound = center.x - width / 2;
	static const float rightBound = center.x + width / 2;
	static const float topBound = center.y - height / 2;
	static const float bottomBound = center.y + height / 2;

	if (pos.x + radius > rightBound || pos.x - radius < leftBound) {
		sf::Vector2f vel = particle.getVelocity();
		sf::Vector2f oldPos = pos - vel;
		bounce(particle, { oldPos.x, pos.y }, { -vel.x, vel.y });
	}

	if (pos.y + radius > bottomBound || pos.y - radius < topBound) {
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

sf::Vector2f Rectangle::getRandomPosition() const {
	float padding = 50.f;
	float x = center.x - width / 2 + static_cast<float>(rand()) / RAND_MAX * (width - padding) + padding/2;
	float y = center.y - height / 2 + static_cast<float>(rand()) / RAND_MAX * (height - padding) + padding/2;
	return { x, y };
}
