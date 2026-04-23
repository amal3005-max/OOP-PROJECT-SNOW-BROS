#include "inputmanager.h"

InputManager::InputManager()
{
    for (int i = 0; i < 256; i++)
    {
        keys[i] = false;
    }
}

void InputManager::update(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        keys[event.key.code] = true;
    }

    if (event.type == sf::Event::KeyReleased)
    {
        keys[event.key.code] = false;
    }
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
    return keys[key];
}