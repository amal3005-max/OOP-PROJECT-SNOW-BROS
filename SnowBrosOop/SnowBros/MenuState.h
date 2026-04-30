#pragma once

#include <SFML/Graphics.hpp>
#include "game.h"
#include "statemanager.h"
#include "inputmanager.h"
#include "Player.h"


class MenuState : public State
{
public:
    MenuState(StateManager& manager) : State(manager) {}

    void handleInput(sf::Event& event) override;
    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) override
    {
        window.clear(sf::Color::Blue);
    }
};
