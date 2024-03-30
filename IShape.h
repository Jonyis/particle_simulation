#pragma once
#include "Particle.h"

class IShape {
public:
    virtual void bounceParticle(Particle& particle) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual sf::Vector2f getRandomPosition() const = 0;
};