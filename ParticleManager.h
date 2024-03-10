#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "IShape.h"
#include <iostream>
#include <vector>
#include <memory>

class ParticleManager {
public:
    explicit ParticleManager(int n, std::unique_ptr<IShape>& _boundingShape);

    void addParticles(int n);

    void addParticle(std::unique_ptr<Particle> particle);

    void removeParticle(int index);

    Particle* getParticle(int index);

    void clearParticles();
    
    int countParticles() const;

    void update(float dt);

    void drawParticles(sf::RenderWindow& window) const;

private:
    std::unique_ptr<IShape> boundingShape;

    std::vector<std::unique_ptr<Particle>> particles;

    void updateParticles(float dt) const;

    void applyGravity(float dt) const;

    void applyAirResistance(float dt) const;

    void checkCollisions();

    void bounceOff(int i, int j);
};
