#pragma once

#include <SFML/Graphics.hpp>
#include "statemanager.h"
#include "inputmanager.h"
#include "SoundManager.h"

class Player;

class Game
{
private:
    sf::RenderWindow window;
    StateManager stateManager;
    InputManager inputManager;

public:
    Game();
    void run();
};