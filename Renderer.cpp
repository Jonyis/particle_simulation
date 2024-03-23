#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& _window) : window(_window) {
	if (!this->particleTexture.loadFromFile("resources/images/circle.png")) {
		throw std::runtime_error("Failed to load texture");
	}
	particleVertices.setPrimitiveType(sf::Quads);
	particleTexture.setSmooth(true);
}

void Renderer::drawAll(const IShape& boundingShape, const std::vector<std::unique_ptr<Particle>>& particles) {
	particleVertices.resize(particles.size() * 4 + 4);
	drawParticles(particles);
	drawBoundingShape(boundingShape);
}

void Renderer::drawParticles(const std::vector<std::unique_ptr<Particle>>& particles) {
	for (int i = 0; i < particles.size(); i++) {
		const auto& particle = particles[i];
		const auto& pos = particle->getPosition();
		const auto& size = particle->getRadius();

		particleVertices[i * 4] = sf::Vertex(sf::Vector2f(pos.x - size, pos.y - size), sf::Vector2f(0, 0));
		particleVertices[i * 4 + 1] = sf::Vertex(sf::Vector2f(pos.x + size, pos.y - size), sf::Vector2f(256, 0));
		particleVertices[i * 4 + 2] = sf::Vertex(sf::Vector2f(pos.x + size, pos.y + size), sf::Vector2f(256, 256));
		particleVertices[i * 4 + 3] = sf::Vertex(sf::Vector2f(pos.x - size, pos.y + size), sf::Vector2f(0, 256));
	}
	window.draw(particleVertices, &particleTexture);
}

void Renderer::drawBoundingShape(const IShape& boundingShape) const {
	boundingShape.draw(window);
}
