#pragma once
#include "IShape.h"

class Circle : public IShape {
private:
    float radius;
    sf::Vector2f center = { 0.f, 0.f };
    sf::CircleShape shape;
    sf::Vector2f size = { radius * 2, radius * 2 };
    sf::Vector2f offset = { center.x - radius, center.y - radius };

public:
    explicit Circle(float radius, sf::Vector2f);

    void bounceParticle(Particle& particle) override;

    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f getRandomPosition() const override;

    sf::Vector2f getSize() const override {
		return size;
	}

    sf::Vector2f getOffset() const override {
		return offset;
	}

};
