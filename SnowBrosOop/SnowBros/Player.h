#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Player
{
private:
    sf::RectangleShape body;
    sf::Sprite sprite;
    sf::Texture texture;

    //int frameWidth;
    //int frameHeight;

    //int currentFrame = 0;
    //float animationTimer = 0.f;
    //float animationSpeed = 0.1f;

    float speed;
    float velocityY;
    float gravity;

    bool onGround;
    bool showHitbox = false;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key jumpKey;

public:
    int direction = 1; 
    float x = 0, y = 0;


    Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j);
    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window, bool debugMode);
    sf::FloatRect getBounds() const;

    void checkPlatformCollision(sf::RectangleShape& platform);
};