#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "IShape.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Renderer.h"

class ParticleManager {
public:
    explicit ParticleManager(int n, std::unique_ptr<IShape>& _boundingShape, const Renderer& renderer);

    void addParticles(int n);

    void addParticle(std::unique_ptr<Particle> particle);

    void addParticle(sf::Vector2f pos);

    void removeParticle(int index);

    Particle* getParticle(int index);

    void clearParticles();
    
    int countParticles() const;

    void update(float dt);

    void drawParticles();

private:
    std::unique_ptr<IShape> boundingShape;

    std::vector<std::unique_ptr<Particle>> particles;

    Renderer renderer;

    void updateParticles(float dt) const;

    void applyGravity(float dt) const;

    void applyAirResistance(float dt) const;

    void checkCollisions();

    void bounceOff(int i, int j);
};
