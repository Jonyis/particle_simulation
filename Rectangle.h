#pragma once
#include "IShape.h"

class Rectangle : public IShape {
public:
    Rectangle(float width, float height, sf::Vector2f center);

    void bounceParticle(Particle& particle) override;

    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f getRandomPosition() const override;

private:
    float width;
    float height;
    sf::Vector2f center;
    sf::RectangleShape shape;

    void bounce(Particle& particle, const sf::Vector2f& newPos, const sf::Vector2f& newVel) const;
};
