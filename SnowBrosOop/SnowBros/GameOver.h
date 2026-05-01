#pragma once

#include <SFML/Graphics.hpp>
#include "statemanager.h"

class GameOverState : public State
{
private:
    sf::Font font;
    sf::Text title;
    sf::Text retryText;
    sf::Text menuText;

public:
    GameOverState(StateManager& manager);

    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};