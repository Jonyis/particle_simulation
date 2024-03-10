#include "Circle.h"

Circle::Circle(float radius, sf::Vector2f center) : radius(radius), center(center) {}

void Circle::bounceParticle(Particle& particle) {
    // Calculate the distance from the particle to the center of the circle
    sf::Vector2f relPos = particle.getPosition() - center;

    float distance_sqrd = (relPos.x * relPos.x + relPos.y * relPos.y);

    // If the particle is at the boundary of the circle
    if (distance_sqrd >= radius_sqrd) {
        float length = std::sqrt(distance_sqrd);
        sf::Vector2f direction = relPos / length;

        // Reverse the direction of the particle
        particle.setVelocity(-direction);
    }
}

void Circle::draw(sf::RenderWindow& window) {
	// Implement the logic to draw the circle
    return; 
}