#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& _window) : window(_window) {
	if (!this->particleTexture.loadFromFile("resources/images/circle2.png")) {
		throw std::runtime_error("Failed to load texture");
	}
	if (!colorImage.loadFromFile("resources/images/texture_tst2.jpg")) {
		throw std::runtime_error("Failed to load image");
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
	drawParticles(boundingShape, particles);
	drawBoundingShape(boundingShape);
}

void Renderer::drawParticles(const IShape& boundingShape, const std::vector<std::unique_ptr<Particle>>& particles) {
	const auto particleCount = particles.size();

	static const sf::Vector2f textureUpperLeft(0, 0);
	static const sf::Vector2f textureUpperRight(particleTextureSize.x, 0);
	static const sf::Vector2f textureLowerRight(particleTextureSize.x, particleTextureSize.y);
	static const sf::Vector2f textureLowerLeft(0, particleTextureSize.y);

	for (std::size_t i = 0, index = 0; i < particleCount; i++, index += 4) {
		const auto& particle = particles[i];
		const sf::Vector2f pos = particle->getPosition();
		const float size = particle->getRadius();
		sf::Color color = getColor(pos, boundingShape.getSize(), boundingShape.getOffset());

		particleVertices[index] = sf::Vertex({ pos.x - size, pos.y - size }, color, textureUpperLeft);
		particleVertices[index + 1] = sf::Vertex({ pos.x + size, pos.y - size }, color, textureUpperRight);
		particleVertices[index + 2] = sf::Vertex({ pos.x + size, pos.y + size }, color, textureLowerRight);
		particleVertices[index + 3] = sf::Vertex({ pos.x - size, pos.y + size }, color, textureLowerLeft);
	}
	window.draw(particleVertices, &particleTexture);
}

void Renderer::drawBoundingShape(const IShape& boundingShape) const {
	boundingShape.draw(window);
}

sf::Color Renderer::getColor(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f offset) const {
	if (!useColorImage) {
		return sf::Color::White;
	}
	const auto x = (int)((pos.x - offset.x) / size.x * colorImage.getSize().x);
	const auto y = (int)((pos.y - offset.y) / size.y * colorImage.getSize().y);
	return colorImage.getPixel(x, y);
}
