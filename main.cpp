#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <iostream>
#include <vector>
#include <cstdlib>


void updateParticles(const std::vector<Particle*>& particles) {
    for (auto particle : particles)
        particle->update();
}

std::vector<Particle*> createParticles(int n) {
    std::vector<Particle*> particles;
    particles.reserve(n);
    for (int i = 0; i < n; i++) {
        particles.emplace_back(new Particle(50.f, 50.f, 0.03f * 75, 0.04f * 75, 50.f-((float)i/n)*50));
    }
    return particles;
}

void drawParticles(sf::RenderWindow& window, const std::vector<Particle*>& particles) {
    for (auto particle : particles)
        window.draw(particle->getShape());
}

void drawFrame(sf::RenderWindow& window, const std::vector<Particle*>& particles) {
    window.clear();
    drawParticles(window, particles);
    window.display();
}

void handleWindowEvents(sf::RenderWindow& window, const std::vector<Particle*>& particles, bool& isPaused);

int main()  
{
    int n = 20;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    std::vector<Particle*> particles = createParticles(n);
    bool isPaused = false;

    while (window.isOpen())
    {
        handleWindowEvents(window, particles, isPaused);

        if (!isPaused)
            updateParticles(particles);

        drawFrame(window, particles);
    }

    return 0;
}

void handleWindowEvents(sf::RenderWindow& window, const std::vector<Particle*>& particles, bool &isPaused) {
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::P)
                isPaused = !isPaused;
            if (isPaused && event.key.code == sf::Keyboard::S)
                updateParticles(particles);
        }
        if (event.type == sf::Event::KeyPressed)
            if (isPaused && event.key.code == sf::Keyboard::Right)
                updateParticles(particles);
    }
}