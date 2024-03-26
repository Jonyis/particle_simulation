#include "Circle.h"

Circle::Circle(float radius, sf::Vector2f center) : radius(radius), center(center) {
    this->shape = sf::CircleShape(radius);
    shape.setPosition({center.x - radius, center.y - radius});
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Red);
    shape.setPointCount(100);
}

void Circle::bounceParticle(Particle& particle) {
    // Calculate the distance from the particle to the center of the circle
    sf::Vector2f relPos = particle.getPosition() - center;
    sf::Vector2f vel = particle.getVelocity();

    float distance_sqrd = (relPos.x * relPos.x + relPos.y * relPos.y);

    float radiusDiff = radius - particle.getRadius();
    float radius_sqrd = (radiusDiff * radiusDiff);

    // If the particle is at the boundary of the circle
    if (distance_sqrd >= radius_sqrd) {
        float length = std::sqrt(distance_sqrd);
        sf::Vector2f direction = relPos / length;

        // Move the particle to the boundary of the circle
        particle.setPosition(center + direction * radiusDiff);

        // Bounce particle off the circle's surface
        float vel_mag = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        particle.setVelocity(-direction * vel_mag * particle.getElasticity());

    }
}

void Circle::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}