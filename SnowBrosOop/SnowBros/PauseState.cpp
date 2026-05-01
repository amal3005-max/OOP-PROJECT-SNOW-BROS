#include "PauseState.h"
#include "MenuState.h"
#include "PlayState.h"

PauseState::PauseState(StateManager& manager)
    : State(manager)
{
    font.loadFromFile("arcade.otf");

    title.setFont(font);
    title.setString("PAUSED");
    title.setCharacterSize(50);
    title.setPosition(250, 150);

    resumeText.setFont(font);
    resumeText.setString("Press R to Resume");
    resumeText.setPosition(200, 300);

    menuText.setFont(font);
    menuText.setString("Press M for Main Menu");
    menuText.setPosition(200, 350);

    //exitText.setFont(font);
    //exitText.setString("Press ESC to Quit");
    //exitText.setPosition(300, 400);
}

void PauseState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
        {
            manager.resumeState();
        }
        else if (event.key.code == sf::Keyboard::M)
        {
            manager.changeState(new MenuState(manager));
        }
        //else if (event.key.code == sf::Keyboard::Escape)
        //{
        //    manager.quit();
        //}
    }
}

void PauseState::update(float) {}

void PauseState::render(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(resumeText);
    window.draw(menuText);
    //window.draw(exitText);
}