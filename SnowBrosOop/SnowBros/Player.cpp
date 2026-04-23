#include "Player.h"

const float WINDOW_WIDTH = 600.f;
const float WINDOW_HEIGHT = 600.f;

Player::Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j)
{
    body.setSize(sf::Vector2f(40, 40));
    body.setFillColor(sf::Color::Red);
    body.setPosition(200, 200);

    

    speed = 200.f;
    velocityY = 0.f;
    gravity = 800.f;
    onGround = false;

    leftKey = l;
    rightKey = r;
    jumpKey = j;
}

void Player::handleInput()
{
    
    if (sf::Keyboard::isKeyPressed(jumpKey) && onGround)
    {
        velocityY = -400.f;
        onGround = false;
    }
}

void Player::update(float dt)
{
    onGround = false;
    // horizontal movement
    if (sf::Keyboard::isKeyPressed(leftKey))
    {
        body.move(-speed * dt, 0);
    }
    if (sf::Keyboard::isKeyPressed(rightKey))
    {
        body.move(speed * dt, 0);
    }

    // gravity
    velocityY += gravity * dt;
    body.move(0, velocityY * dt);

    // ground collision
    if (body.getPosition().y >= 500)
    {
        body.setPosition(body.getPosition().x, 500);
        velocityY = 0;
        onGround = true;
    }

    // bounds
    sf::Vector2f pos = body.getPosition();
    sf::Vector2f size = body.getSize();

    float x = body.getPosition().x;
    float y = body.getPosition().y;
    float width = body.getSize().x;

    if (x + width < 0)        // fully left
    {
        body.setPosition(600, y);
    }
    else if (x > 600)         // fully right
    {
        body.setPosition(-width, y);
    }

    if (!sf::Keyboard::isKeyPressed(jumpKey) && velocityY < 0)
    {
        velocityY *= 0.95f; // cuts jump height
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(body);
    //window.draw(platform);
}
void Player::checkPlatformCollision(sf::RectangleShape& platform)
{
    sf::FloatRect playerBounds = body.getGlobalBounds();
    sf::FloatRect platBounds = platform.getGlobalBounds();

    float playerBottom = playerBounds.top + playerBounds.height;

    // ONLY LAND IF FALLING AND TOUCHING TOP SURFACE
    if (velocityY > 0 &&
        playerBottom >= platBounds.top &&
        playerBottom <= platBounds.top + 10.f &&  // small tolerance
        playerBounds.left + playerBounds.width > platBounds.left &&
        playerBounds.left < platBounds.left + platBounds.width)
    {
        body.setPosition(
            body.getPosition().x,
            platBounds.top - playerBounds.height
        );

        velocityY = 0;
        onGround = true;
    }
}