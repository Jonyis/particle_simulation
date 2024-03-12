#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "ParticleManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Rectangle.h"
#include "Circle.h"
#include <sstream>
#include <iomanip>
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

    sf::Font font;
    if (!font.loadFromFile("resources/fonts/arial.ttf"))
    {
        return -1;
    }
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);

    sf::Clock clock;

    std::unique_ptr<IShape> boundingShape = std::make_unique<Circle>(500, sf::Vector2f{300, 300});
    ParticleManager particleManager(n, boundingShape);
    
    SimulationStatistics simulationStatistics(particleManager, clock);

    bool isPaused = false;


    while (window.isOpen())
    {
        handleWindowEvents(window, particleManager, isPaused);

        if (!isPaused)
            particleManager.update(1.f / 120.f);

        simulationStatistics.calculateFPS();

        window.clear();
        particleManager.drawParticles(window);
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
    }
}