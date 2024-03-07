#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "ParticleManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>


void handleWindowEvents(sf::RenderWindow& window, ParticleManager& particleManager, bool& isPaused);

int main()
{
    std::srand(std::time(nullptr));

    int n = 1;
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    ParticleManager particleManager(n);
    bool isPaused = false;

    while (window.isOpen())
    {
        handleWindowEvents(window, particleManager, isPaused);

        if (!isPaused)
            particleManager.update(1.f / 120.f);

        window.clear();
        particleManager.drawParticles(window);
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
        if (event.type == sf::Event::KeyPressed)
            if (isPaused && event.key.code == sf::Keyboard::Right)
                particleManager.update(1.f / 120.f);
    }
}