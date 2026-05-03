#include "GameOver.h"
#include "PlayState.h"
#include "MenuState.h"

GameOverState::GameOverState(StateManager& manager)
    : State(manager)
{
    font.loadFromFile("arcade.otf");

    title.setFont(font);
    title.setString("GAME OVER");
    title.setCharacterSize(60);
    title.setPosition(200, 150);
	title.setFillColor(sf::Color::Green);

    retryText.setFont(font);
    retryText.setString("Press R to Retry");
    retryText.setPosition(200, 300);
	retryText.setFillColor(sf::Color::Red);

    menuText.setFont(font);
    menuText.setString("Press M for Main Menu");
    menuText.setPosition(200, 350);
	menuText.setFillColor(sf::Color::Red);
}

void GameOverState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
        {
            //manager.getSound()->play("SnowBrosAssets/Sounds/snow_bros_level.ogg");
            manager.changeState(new PlayState(manager));
        }
        else if (event.key.code == sf::Keyboard::M)
        {
            //manager.getSound()->play("SnowBrosAssets/Sounds/snow_bros_level.ogg");
            manager.changeState(new MenuState(manager));
        }
    }
}

void GameOverState::update(float) {}

void GameOverState::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(title);
    window.draw(retryText);
    window.draw(menuText);
}