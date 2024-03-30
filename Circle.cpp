#include "Circle.h"

Circle::Circle(float radius, sf::Vector2f center) : radius(radius), center(center), shape(radius) {
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
        float elasticity = particle.getElasticity();

        if (elasticity > 0)
            particle.setVelocity(-direction * vel_mag * elasticity);
    }
}

void Circle::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Circle::getRandomPosition() const {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f; // Random angle in [0, 2*pi]
    float r = radius * std::sqrt(static_cast<float>(rand()) / RAND_MAX); // Random radius in [0, radius]
    float x = center.x + r * std::cos(angle);
    float y = center.y + r * std::sin(angle);
    return { x, y };
}