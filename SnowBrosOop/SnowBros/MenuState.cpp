#include "MenuState.h"
#include "playstate.h"


void MenuState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            manager.setMode(GameMode::SinglePlayer);
            manager.changeState(new PlayState(manager));
        }
        else if (event.key.code == sf::Keyboard::L)
        {
            manager.setMode(GameMode::TwoPlayer);
            manager.changeState(new PlayState(manager));
        }

    }

}
