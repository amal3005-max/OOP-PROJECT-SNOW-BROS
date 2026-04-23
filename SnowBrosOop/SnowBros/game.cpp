#include <SFML/Graphics.hpp>
#include "game.h"
#include "statemanager.h"
#include "inputmanager.h"
#include "Player.h"


// The concrete State implementations have been moved to separate files.

// Forward declaration kept for older code that might reference it.
class PlayState;


// Local fallback MenuState definition removed; use MenuState class from header

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

class LogoState : public State
{
private:
    sf::Texture logoTexture;
    sf::Sprite logoSprite;

    sf::Font font;
    sf::Text pressStart;
    sf::Text copyright1;
    sf::Text copyright2;

    sf::Clock timer;
    sf::Clock blinkClock;
public:
    LogoState(StateManager& manager) : State(manager)
    {
        // load image and font
        logoTexture.loadFromFile("logo2.png");
        font.loadFromFile("ARCADE.otf");

        logoSprite.setTexture(logoTexture);

        // center logo
        float logoX = (850 - logoSprite.getGlobalBounds().width) / 2;
        logoSprite.setScale(0.7f, 0.7f);
        logoSprite.setPosition(logoX, 0);

        // PRESS START BUTTON text
        pressStart.setFont(font);
        pressStart.setString("PRESS START BUTTON");
        pressStart.setCharacterSize(28);
        pressStart.setFillColor(sf::Color::Yellow);

        float startX = (600 - pressStart.getGlobalBounds().width) / 2;
        pressStart.setPosition(startX, 420);

        // copyright line 1
        copyright1.setFont(font);
        copyright1.setString("© 2026 Snow Bros Game");
        copyright1.setCharacterSize(18);
        copyright1.setFillColor(sf::Color::White);

        float copy1X = (600 - copyright1.getGlobalBounds().width) / 2;
        copyright1.setPosition(copy1X, 500);
        // copyright line 2
        copyright2.setFont(font);
        copyright2.setString("Developed By [Amal Asif] & [Fatima Anees]");
        copyright2.setCharacterSize(18);
        copyright2.setFillColor(sf::Color::White);

        float copy2X = (600 - copyright2.getGlobalBounds().width) / 2;
        copyright2.setPosition(copy2X, 530);
    }

    void handleInput(sf::Event& event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
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


class PlayState : public State
{
private:

    Player player1;
    Player* player2;

    sf::RectangleShape platform;
public:
    PlayState(StateManager& manager)
        : State(manager),
        player1(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W),
        player2(nullptr)
    {
        if (manager.getMode() == GameMode::TwoPlayer)
        {
            player2 = new Player(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up);
        }

        platform.setSize(sf::Vector2f(200, 15));
        platform.setPosition(200, 450);
        platform.setFillColor(sf::Color::White);
    }

    void handleInput(sf::Event& event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                manager.changeState(new MenuState(manager));
            }
        }
    }

    void update(float deltaTime) override 
    {
        player1.handleInput();
        player1.update(deltaTime);

        if (player2 != nullptr)
        {
            player2->handleInput();
            player2->update(deltaTime);
        }

        player1.checkPlatformCollision(platform);

        if (player2 != nullptr)
        {
            player2->checkPlatformCollision(platform);
        }
    }

    void render(sf::RenderWindow& window) override
    {
        window.clear(sf::Color::Black);
        player1.draw(window);

        if (player2 != nullptr)
        {
            player2->draw(window);
        }
        window.draw(platform);
    }
    ~PlayState()
    {
        delete player2;
    }
};

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

Game::Game() : window(sf::VideoMode(600, 600), "Snow Bros Game")
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

