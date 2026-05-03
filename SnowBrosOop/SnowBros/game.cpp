#include <SFML/Graphics.hpp>
#include "game.h"
#include "statemanager.h"
#include "inputmanager.h"
#include "Player.h"
#include "MenuState.h"
#include "SoundManager.h"
#include <iostream>
using namespace std;

class LogoState : public State
{
private:
    Game& game;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;

    sf::Font font;
    sf::Text pressStart;
    sf::Text copyright1;
    sf::Text copyright2;

    sf::Clock timer;
    sf::Clock blinkClock;
public:
    LogoState(StateManager& manager) : State(manager), game(game)
    {
        logoTexture.loadFromFile("logo2.png");
        font.loadFromFile("ARCADE.otf");
        logoSprite.setTexture(logoTexture);

        // center logo
        float logoX = (1060 - logoSprite.getGlobalBounds().width) / 2;
        logoSprite.setScale(0.7f, 0.7f);
        logoSprite.setPosition(logoX, 0);

        // PRESS START BUTTON text
        pressStart.setFont(font);
        pressStart.setString("PRESS START BUTTON");
        pressStart.setCharacterSize(28);
        pressStart.setFillColor(sf::Color::Yellow);

        float startX = (800 - pressStart.getGlobalBounds().width) / 2;
        pressStart.setPosition(startX, 420);

        // copyright line 1
        copyright1.setFont(font);
        copyright1.setString("© 2026 Snow Bros Game");
        copyright1.setCharacterSize(18);
        copyright1.setFillColor(sf::Color::White);

        float copy1X = (800 - copyright1.getGlobalBounds().width) / 2;
        copyright1.setPosition(copy1X, 500);
        // copyright line 2
        copyright2.setFont(font);
        copyright2.setString("Developed By [Amal Asif] & [Fatima Anees]");
        copyright2.setCharacterSize(18);
        copyright2.setFillColor(sf::Color::White);

        float copy2X = (800 - copyright2.getGlobalBounds().width) / 2;
        copyright2.setPosition(copy2X, 530);

        gSound().play("SnowBrosAssets/Sounds/snow_bros_theme_01.ogg");
    }

    void handleInput(sf::Event& event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                gSound().play("SnowBrosAssets/Sounds/snow_bros_theme_02.ogg");
                manager.changeState(new MenuState(manager));
            }
        }
    }
    void update(float deltaTime) override
    {
        // blink PRESS START BUTTON every 0.5 sec
        if (blinkClock.getElapsedTime().asSeconds() > 0.5f)
        {
            if (pressStart.getFillColor() == sf::Color::Yellow)
            {
                pressStart.setFillColor(sf::Color::Transparent);
            }
            else
            {
                pressStart.setFillColor(sf::Color::Yellow);
            }
            blinkClock.restart();
        }
    }

    void render(sf::RenderWindow& window) override
    {
        window.clear(sf::Color::Black);

        window.draw(logoSprite);
        window.draw(pressStart);
        window.draw(copyright1);
        window.draw(copyright2);

    }

};


Game::Game() : window(sf::VideoMode(800, 600), "Snow Bros Game")
{
    stateManager.changeState(new LogoState(stateManager));
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            inputManager.update(event);
            stateManager.handleInput(event);

        }
        stateManager.update(deltaTime);
        stateManager.render(window);

        window.display();
    }
}

