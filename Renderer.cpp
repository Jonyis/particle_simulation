#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& _window) : window(_window) {
	if (!this->particleTexture.loadFromFile("resources/images/circle.png")) {
		throw std::runtime_error("Failed to load texture");
	}
	particleVertices.setPrimitiveType(sf::Quads);
	particleTexture.setSmooth(true);
	particleTextureSize = {(float)particleTexture.getSize().x, (float)particleTexture.getSize().y };
}

void Renderer::clear() {
	particleVertices.clear();
}

void Renderer::drawAll(const IShape& boundingShape, const std::vector<std::unique_ptr<Particle>>& particles) {
	if (particleVertices.getVertexCount() != particles.size() * 4) {
		particleVertices.resize(particles.size() * 4);
	}
	drawParticles(particles);
	drawBoundingShape(boundingShape);
}

void Renderer::drawParticles(const std::vector<std::unique_ptr<Particle>>& particles) {
	const auto particleCount = particles.size();

	sf::Vector2f textureUpperLeft(0, 0);
	sf::Vector2f textureUpperRight(particleTextureSize.x, 0);
	sf::Vector2f textureLowerRight(particleTextureSize.x, particleTextureSize.y);
	sf::Vector2f textureLowerLeft(0, particleTextureSize.y);

	for (std::size_t i = 0; i < particleCount; i++) {
		const auto& particle = particles[i];
		const auto& pos = particle->getPosition();
		const auto& size = particle->getRadius();

		const auto index = i * 4;
		particleVertices[index] = sf::Vertex(sf::Vector2f(pos.x - size, pos.y - size), textureUpperLeft);
		particleVertices[index + 1] = sf::Vertex(sf::Vector2f(pos.x + size, pos.y - size), textureUpperRight);
		particleVertices[index + 2] = sf::Vertex(sf::Vector2f(pos.x + size, pos.y + size), textureLowerRight);
		particleVertices[index + 3] = sf::Vertex(sf::Vector2f(pos.x - size, pos.y + size), textureLowerLeft);
	}
	window.draw(particleVertices, &particleTexture);
}

void Renderer::drawBoundingShape(const IShape& boundingShape) const {
	boundingShape.draw(window);
}
