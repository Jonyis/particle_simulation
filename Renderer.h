#pragma once

#include <vector>
#include "Particle.h"
#include "IShape.h"

class Renderer {
public:

	explicit Renderer(sf::RenderWindow& window);
	
	void clear();

	void drawAll(const IShape& boundingShape, const std::vector<std::unique_ptr<Particle>>& particles);

private:
	sf::RenderWindow& window;
	sf::Texture particleTexture;
	sf::VertexArray particleVertices;
	sf::Vector2f particleTextureSize;
	sf::Image colorImage;
	bool useColorImage = true;

	void drawParticles(const IShape& boundingShape, const std::vector<std::unique_ptr<Particle>>& particles);

	void drawBoundingShape(const IShape& boundingShape) const;

	sf::Color getColor(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f offset) const;
};

