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
	const auto requiredVertexCount = particles.size() * 4;
	if (particleVertices.getVertexCount() != requiredVertexCount) {
		particleVertices.resize(requiredVertexCount);
	}
	drawParticles(particles);
	drawBoundingShape(boundingShape);
}

void Renderer::drawParticles(const std::vector<std::unique_ptr<Particle>>& particles) {
	const auto particleCount = particles.size();

	static const sf::Vector2f textureUpperLeft(0, 0);
	static const sf::Vector2f textureUpperRight(particleTextureSize.x, 0);
	static const sf::Vector2f textureLowerRight(particleTextureSize.x, particleTextureSize.y);
	static const sf::Vector2f textureLowerLeft(0, particleTextureSize.y);

	for (std::size_t i = 0, index = 0; i < particleCount; i++, index += 4) {
		const auto& particle = particles[i];
		const sf::Vector2f pos = particle->getPosition();
		const float size = particle->getRadius();

		particleVertices[index] = sf::Vertex({ pos.x - size, pos.y - size }, textureUpperLeft);
		particleVertices[index + 1] = sf::Vertex({ pos.x + size, pos.y - size }, textureUpperRight);
		particleVertices[index + 2] = sf::Vertex({ pos.x + size, pos.y + size }, textureLowerRight);
		particleVertices[index + 3] = sf::Vertex({ pos.x - size, pos.y + size }, textureLowerLeft);
	}
	window.draw(particleVertices, &particleTexture);
}

void Renderer::drawBoundingShape(const IShape& boundingShape) const {
	boundingShape.draw(window);
}
