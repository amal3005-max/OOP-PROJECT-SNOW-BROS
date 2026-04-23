#pragma once
#include <SFML/Graphics.hpp>

class InputManager
{
private:
    bool keys[256];

public:
    InputManager();

    void update(sf::Event event);
    bool isKeyPressed(sf::Keyboard::Key key);
};