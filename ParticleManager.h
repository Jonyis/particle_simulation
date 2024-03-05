#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>

class ParticleManager {
public:
    explicit ParticleManager(int n);

    void addParticles(int n);

    void addParticle(std::unique_ptr<Particle> particle);

    void removeParticle(int index);

    Particle* getParticle(int index);

    void clearParticles();
    
    int countParticles() const;

    void updateParticles() const;

    void checkCollisions() const;

    void drawParticles(sf::RenderWindow& window) const;

private:
    std::vector<std::unique_ptr<Particle>> particles;
};
