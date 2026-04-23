#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape body;
    //sf::RectangleShape platform;

    float speed;
    float velocityY;
    float gravity;

    bool onGround;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key jumpKey;
public:
    Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j);
    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void checkPlatformCollision(sf::RectangleShape& platform);
};