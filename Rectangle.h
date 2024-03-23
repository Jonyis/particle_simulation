#pragma once
#include "IShape.h"

class Rectangle : public IShape {
private:
    double width;
    double height;
    sf::RectangleShape shape;
public:
    Rectangle(double width, double height);

    void bounceParticle(Particle& particle) override;

    void draw(sf::RenderWindow& window) const override;
};
