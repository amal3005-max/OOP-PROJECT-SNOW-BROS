// WinState.cpp
#include "WinState.h"
#include "MenuState.h"
#include "PlayState.h"
#include <cstdlib>
#include <sstream>

WinState::WinState(StateManager& manager,
    int score, int enemies, int levels)
    : State(manager),
    finalScore(score),
    enemiesDefeated(enemies),
    levelsCleared(levels),
    promptVisible(true)
{
    font.loadFromFile("ARCADE.otf");

    // ── CONGRATS title ──
    congratsText.setFont(font);
    congratsText.setString("CONGRATULATIONS!");
    congratsText.setCharacterSize(42);
    congratsText.setFillColor(sf::Color::Yellow);
    float cx = (800.f - congratsText.getGlobalBounds().width) / 2.f;
    congratsText.setPosition(cx, 40.f);

    // ── Subtitle ──
    subtitleText.setFont(font);
    subtitleText.setString("YOU SAVED THE KINGDOM!");
    subtitleText.setCharacterSize(24);
    subtitleText.setFillColor(sf::Color::Cyan);
    float sx = (800.f - subtitleText.getGlobalBounds().width) / 2.f;
    subtitleText.setPosition(sx, 100.f);

    // ── Story ──
    storyText.setFont(font);
    storyText.setString(
        "Nick and Tom defeated all enemies\n"
        "and freed the princes from the curse.\n"
        "Peace returns to the Snow Kingdom!");
    storyText.setCharacterSize(16);
    storyText.setFillColor(sf::Color::White);
    float stx = (800.f - storyText.getGlobalBounds().width) / 2.f;
    storyText.setPosition(stx, 160.f);

    // ── Stats ──
    std::ostringstream ss;
    ss << "LEVELS CLEARED :  " << levelsCleared << "\n"
        << "ENEMIES DEFEATED: " << enemiesDefeated << "\n"
        << "FINAL SCORE    :  " << finalScore;

    statsText.setFont(font);
    statsText.setString(ss.str());
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::Green);
    float stsx = (800.f - statsText.getGlobalBounds().width) / 2.f;
    statsText.setPosition(stsx, 280.f);

    // ── Blink prompt ──
    promptText.setFont(font);
    promptText.setString("PRESS ENTER TO PLAY AGAIN");
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color::Yellow);
    float px = (800.f - promptText.getGlobalBounds().width) / 2.f;
    promptText.setPosition(px, 430.f);

    // ── Menu prompt ──
    menuText.setFont(font);
    menuText.setString("PRESS M FOR MAIN MENU");
    menuText.setCharacterSize(18);
    menuText.setFillColor(sf::Color::Red);
    float mx = (800.f - menuText.getGlobalBounds().width) / 2.f;
    menuText.setPosition(mx, 470.f);

    // ── Snowflakes ──
    for (int i = 0; i < NUM_FLAKES; i++)
    {
        snowflakes[i].shape.setRadius(3.f + (rand() % 4));
        snowflakes[i].shape.setFillColor(sf::Color(200, 230, 255));
        snowflakes[i].shape.setPosition(
            static_cast<float>(rand() % 800),
            static_cast<float>(rand() % 600));
        snowflakes[i].speed = 30.f + (rand() % 60);
    }
}

void WinState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter)
            manager.changeState(new PlayState(manager));

        if (event.key.code == sf::Keyboard::M)
            manager.changeState(new MenuState(manager));

        if (event.key.code == sf::Keyboard::Escape)
        {
            // close window — get window ref via manager if you have it,
            // or just go to menu as fallback
            manager.changeState(new MenuState(manager));
        }
    }
}

void WinState::update(float dt)
{
    // ── Blink prompt ──
    if (blinkClock.getElapsedTime().asSeconds() > 0.5f)
    {
        promptVisible = !promptVisible;
        blinkClock.restart();
    }

    // ── Cycle title color ──
    float t = colorClock.getElapsedTime().asSeconds();
    int r = static_cast<int>(128 + 127 * std::sin(t * 2.0f));
    int g = static_cast<int>(128 + 127 * std::sin(t * 2.0f + 2.094f));
    int b = static_cast<int>(128 + 127 * std::sin(t * 2.0f + 4.189f));
    congratsText.setFillColor(sf::Color(r, g, b));

    // ── Move snowflakes ──
    for (int i = 0; i < NUM_FLAKES; i++)
    {
        snowflakes[i].shape.move(0.f, snowflakes[i].speed * dt);

        // wrap back to top
        if (snowflakes[i].shape.getPosition().y > 610.f)
        {
            snowflakes[i].shape.setPosition(
                static_cast<float>(rand() % 800), -10.f);
        }
    }
}

void WinState::render(sf::RenderWindow& window)
{
    // Dark night-sky background
    window.clear(sf::Color(10, 10, 60));

    // Snowflakes behind everything
    for (int i = 0; i < NUM_FLAKES; i++)
        window.draw(snowflakes[i].shape);

    window.draw(congratsText);
    window.draw(subtitleText);
    window.draw(storyText);
    window.draw(statsText);

    if (promptVisible)
        window.draw(promptText);

    window.draw(menuText);
}