#include "ParticleManager.h"

ParticleManager::ParticleManager(int n, std::unique_ptr<IShape>& _boundingShape, const Renderer& renderer) : renderer(renderer) {
	particles.reserve(n);
	boundingShape = std::move(_boundingShape);
	addParticles(n);
}

void ParticleManager::addParticles(int n) {
	for (int i = 0; i < n; i++) {
		sf::Vector2f pos = (*boundingShape).getRandomPosition();
		addParticle(
			std::make_unique<Particle>(
				pos.x, 
				pos.y,
				0.03f * 75, 
				0.04f * 75,
				20, 
				10,
				1.f));
	}
}

void ParticleManager::addParticle(std::unique_ptr<Particle> particle) {
	particles.push_back(std::move(particle));
}

void ParticleManager::addParticle(sf::Vector2f pos) {
	addParticle(
		std::make_unique<Particle>(
			pos.x,
			pos.y,
			0,
			0,
			20,
			10,
			1.f));
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
	renderer.clear();
}

int ParticleManager::countParticles() const {
	return particles.size();
}

void ParticleManager::update(float dt) {
	const int sub_steps = 1;

	for (int i = 0; i < sub_steps; i++) {
		// Update particles
		updateParticles(dt / sub_steps);

		// Apply gravity
		applyGravity(dt / sub_steps);

		// Apply air resistance
		//applyAirResistance(dt);

		// Check for collisions
		//checkCollisions();
	}
}

void ParticleManager::updateParticles(float dt) const{
	for (auto const& particle : particles) {
		particle->update(dt);
		boundingShape->bounceParticle(*particle);
	}
}

void ParticleManager::applyGravity(float dt) const {
	static const sf::Vector2f gravity(0.f, 9.8f*100);

	for (auto const& particle : particles) {
		particle->accelerate(gravity);
	}
}

void ParticleManager::applyAirResistance(float dt) const {
	static const float airResistance = 0.1f;  // Air resistance coefficient

	for (auto& particle : particles) {
		sf::Vector2f velocity = particle->getVelocity();
		velocity -= airResistance * velocity * dt;
		particle->setVelocity(velocity);
	}
}

void ParticleManager::checkCollisions() {
	for (size_t i = 0; i < particles.size(); ++i) {
		for (size_t j = i + 1; j < particles.size(); ++j) {
			bounceOff(i, j);
		}
	}
}

void ParticleManager::bounceOff(int i, int j) {
	sf::Vector2f pos1 = particles[i]->getPosition();
	sf::Vector2f pos2 = particles[j]->getPosition();
	sf::Vector2f distance = pos1 - pos2;
	float distance_sqrd = (distance.x * distance.x + distance.y * distance.y);
	float radius_sum = particles[i]->getRadius() + particles[j]->getRadius();

	if (distance_sqrd < radius_sum * radius_sum) {
		// Calculate new velocities based on masses
		float m1 = particles[i]->getMass();
		float m2 = particles[j]->getMass();
		sf::Vector2f v1 = particles[i]->getVelocity();
		sf::Vector2f v2 = particles[j]->getVelocity();

		float m1_m2 = m1 + m2;

		// Calculate collision normal
		float distance_magnitude = std::sqrt(distance_sqrd);
		sf::Vector2f n = distance / distance_magnitude;

		// Add a small displacement in the direction of the collision normal
		static const float response_coef = 0.75f;
		float displacement = 0.5f * response_coef * (distance_magnitude - radius_sum);
		particles[i]->setPosition(pos1 - n * (displacement * (m2 / m1_m2)));
		particles[j]->setPosition(pos2 + n * (displacement * (m1 / m1_m2)));

		float combined_elasticity = particles[i]->getElasticity() * particles[j]->getElasticity();
		if (combined_elasticity > 0) {
			sf::Vector2f newV1 = (v1 * (m1 - m2) + v2 * 2.f * m2) / m1_m2;
			sf::Vector2f newV2 = (v1 * 2.f * m1 + v2 * (m2 - m1)) / m1_m2;
			particles[i]->setVelocity(newV1 * combined_elasticity);
			particles[j]->setVelocity(newV2 * combined_elasticity);
		}
	}
}

void ParticleManager::drawParticles() {
	renderer.drawAll(*boundingShape, particles);
}