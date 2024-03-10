#pragma once
#include "Particle.h"

class IShape {
public:
    virtual void bounceParticle(Particle& particle) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};