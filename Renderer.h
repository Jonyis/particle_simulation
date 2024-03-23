#pragma once

#include <vector>
#include <memory>
#include "Particle.h"
#include "IShape.h"

class Renderer {
public:

	explicit Renderer(sf::RenderWindow& window);
	
	void clear();

	void drawAll(const IShape& boundingShape, const std::vector<std::unique_ptr<Particle>>& particles);

	void drawParticles(const std::vector<std::unique_ptr<Particle>>& particles);
	
	void drawBoundingShape(const IShape& boundingShape) const;

private:
	sf::RenderWindow& window;
	sf::Texture particleTexture;
	sf::VertexArray particleVertices;
};

