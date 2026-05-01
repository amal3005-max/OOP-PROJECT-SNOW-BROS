#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Player
{
private:
    sf::RectangleShape body;

    int lives;

    float speed;
    float velocityY;
    float gravity;

    bool onGround;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key jumpKey;

public:
    bool isInvincible;
    float invincibleTimer;
    float invincibleDuration;

    int direction = 1;

    Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j);

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window, bool debugMode);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    void checkPlatformCollision(sf::RectangleShape& platform);

    int getLives() const;
    bool loseLife();
    void gainLife();
    bool isAlive() const;
};