#pragma once
#include "IShape.h"

class Rectangle : public IShape {
public:
    Rectangle(float width, float height, sf::Vector2f center);

    void bounceParticle(Particle& particle) override;

    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f getRandomPosition() const override;

    sf::Vector2f getSize() const override { return { width, height }; }

    sf::Vector2f getOffset() const override { return center - sf::Vector2f(width / 2, height / 2); }

private:
    float width;
    float height;
    sf::Vector2f center;
    sf::RectangleShape shape;

    void bounce(Particle& particle, const sf::Vector2f& newPos, const sf::Vector2f& newVel) const;
};
