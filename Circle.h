#pragma once
#include "IShape.h"

class Circle : public IShape {
private:
    float radius;
    sf::Vector2f center = { 0.f, 0.f };
    sf::CircleShape shape;
public:
    explicit Circle(float radius, sf::Vector2f);

    void bounceParticle(Particle& particle) override;

    void draw(sf::RenderWindow& window) const override;
};
