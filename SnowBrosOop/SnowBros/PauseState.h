#pragma once

#include <SFML/Graphics.hpp>
#include "game.h"
#include "statemanager.h"
#include "inputmanager.h"
#include "Player.h"


class PauseState : public State
{
private:
    sf::Font font;
    sf::Text title;
    sf::Text resumeText;
    sf::Text menuText;
    sf::Text exitText;

public:
    PauseState(StateManager& manager);

    void handleInput(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};