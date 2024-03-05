#include "ParticleManager.h"

ParticleManager::ParticleManager(int n) {
	particles.reserve(n);
	addParticles(n);
}

void ParticleManager::addParticles(int n) {
	for (int i = 0; i < n; i++) {
		addParticle(std::make_unique<Particle>(50.f+100*i, 50.f+100*i, 0.03f * 75, 0.04f * 75, 50.f - ((float)i / n) * 50, 1 + 10*(1-i)));
	}
}

void ParticleManager::addParticle(std::unique_ptr<Particle> particle) {
	particles.push_back(std::move(particle));
}

void ParticleManager::removeParticle(int index) {
	if (index < 0 || index >= particles.size())
		throw std::out_of_range("Index out of range");
	particles.erase(particles.begin() + index);
}

Particle* ParticleManager::getParticle(int index) {
	if (index < 0 || index >= particles.size())
		throw std::out_of_range("Index out of range");
	return particles[index].get();
}

void ParticleManager::clearParticles() {
	particles.clear();
}

int ParticleManager::countParticles() const {
	return particles.size();
}

void ParticleManager::updateParticles() {
	for (auto const& particle : particles)
		particle->update();

	checkCollisions();
}

void ParticleManager::checkCollisions() {
	for (size_t i = 0; i < particles.size(); ++i) {
		for (size_t j = i + 1; j < particles.size(); ++j) {
			if (particles[i]->collidesWith(*particles[j])) {
				// Handle collision...
				//printf("Collision detected between particles %d and %d\n", i, j);
				bounceOff(i, j);
			}
		}
	}
}

void ParticleManager::bounceOff(int i, int j) {
	// Calculate new velocities based on masses
	float m1 = particles[i]->getMass();
	float m2 = particles[j]->getMass();
	sf::Vector2f v1 = particles[i]->getVelocity();
	sf::Vector2f v2 = particles[j]->getVelocity();

	sf::Vector2f newV1 = v1 * (m1 - m2) / (m1 + m2) + v2 * 2.f * m2 / (m1 + m2);
	sf::Vector2f newV2 = v1 * 2.f * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);

	particles[i]->setVelocity(newV1);
	particles[j]->setVelocity(newV2);
}

void ParticleManager::drawParticles(sf::RenderWindow& window) const {
	for (auto const& particle : particles)
		window.draw(particle->getShape());
}