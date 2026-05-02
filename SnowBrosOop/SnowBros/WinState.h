#pragma once
#include <SFML/Graphics.hpp>
#include "statemanager.h"

class WinState : public State
{
private:
    sf::Font font;

    sf::Text congratsText;
    sf::Text subtitleText;
    sf::Text storyText;
    sf::Text statsText;
    sf::Text promptText;
    sf::Text menuText;

    // Stats passed in from PlayState
    int finalScore;
    int enemiesDefeated;
    int levelsCleared;

    // Blinking
    sf::Clock blinkClock;
    bool promptVisible;

    // Snowflakes
    struct Snowflake
    {
        sf::CircleShape shape;
        float speed;
    };

    static const int NUM_FLAKES = 40;
    Snowflake snowflakes[NUM_FLAKES];

    // Title color cycle
    sf::Clock colorClock;

public:
    WinState(StateManager& manager,
        int score = 0,
        int enemies = 0,
        int levels = 10);

    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};