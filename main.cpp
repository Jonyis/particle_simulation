#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "ParticleManager.h"
#include <iostream>
#include "Rectangle.h"
#include "Circle.h"
#include "SimulationStatistics.h"

void handleWindowEvents(sf::RenderWindow& window, ParticleManager& particleManager, bool& isPaused);

int main()
{
    std::srand(std::time(nullptr));

    int n = 1;
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500*2, 2*500), "", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    sf::Clock clock;

    std::unique_ptr<IShape> boundingShapeCirc = std::make_unique<Circle>(150, sf::Vector2f{ 400, 400 });
    std::unique_ptr<IShape> boundingShapeRect = std::make_unique<Rectangle>(500, 500, sf::Vector2f(400, 400));
    Renderer renderer(window);    
    ParticleManager particleManager(n, boundingShapeCirc, renderer);
    
    SimulationStatistics simulationStatistics(particleManager, clock);

    bool isPaused = false;

    
    while (window.isOpen())
    {
        handleWindowEvents(window, particleManager, isPaused);

        if (!isPaused)
            particleManager.update(1.f / 120.f);

        simulationStatistics.calculateFPS();

        window.clear();
        particleManager.drawParticles();
        simulationStatistics.draw(window);
        window.display();
    }

    return 0;
}


void handleWindowEvents(sf::RenderWindow& window, ParticleManager& particleManager, bool &isPaused) {
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::P)
                isPaused = !isPaused;
            if (isPaused && event.key.code == sf::Keyboard::S)
                particleManager.update(1.f / 120.f);
            if (event.key.code == sf::Keyboard::R)
				particleManager.clearParticles();
            if (event.key.code == sf::Keyboard::C)
				particleManager.addParticles(20);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (isPaused && event.key.code == sf::Keyboard::Right)
                particleManager.update(1.f / 120.f);
            if (event.key.code == sf::Keyboard::A)
                particleManager.addParticles(20);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
				particleManager.addParticle({ (float)event.mouseButton.x, (float)event.mouseButton.y });
			}
            if (event.mouseButton.button == sf::Mouse::Right) {
                particleManager.addParticles(100);

            }
		}
    }
}