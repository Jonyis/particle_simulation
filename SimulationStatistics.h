#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleManager.h"


class SimulationStatistics
{
public:
    explicit SimulationStatistics(const ParticleManager& _particleManager, sf::Clock& clock);

    void calculateFPS();

    void draw(sf::RenderWindow& window);

private:
    const ParticleManager& particleManager;
    sf::Clock& clock;
    sf::Text fpsText;
    sf::Font font;
    float frameTimes = 0.0f;
    int frameCount = 0;
    float fps = 120.0f;
    float averageFPS = 120.0f;
    int frameRateCount = 0.0f;
};
