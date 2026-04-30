#include "Player.h"

const float WINDOW_WIDTH = 800.f;
const float WINDOW_HEIGHT = 600.f;

Player::Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j)
{
    body.setSize(sf::Vector2f(40, 40));
    body.setFillColor(sf::Color::Red);
    body.setPosition(200, 200);

    //body.setOrigin(20.f, 20.f);
    speed = 200.f;
    velocityY = 0.f;
    gravity = 800.f;
    onGround = false;

    leftKey = l;
    rightKey = r;
    jumpKey = j;

	direction = 1;
    //initTexture();
}

sf::FloatRect Player::getBounds() const
{
    return body.getGlobalBounds();
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

    if (x + width < 0)        
    {
        body.setPosition(800, y);
    }
    else if (x > 800)        
    {
        body.setPosition(-width, y);
    }

    if (!sf::Keyboard::isKeyPressed(jumpKey) && velocityY < 0)
    {
        velocityY *= 0.95f; 
    }

    if (sf::Keyboard::isKeyPressed(leftKey))
        direction = -1;

    if (sf::Keyboard::isKeyPressed(rightKey))
        direction = 1;
}

void Player::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(body);
    //window.draw(sprite);


    if (debugMode)
    {
        sf::FloatRect bounds = body.getGlobalBounds();

        sf::RectangleShape hitbox;
        hitbox.setPosition(bounds.left, bounds.top);
        hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Green);
        hitbox.setOutlineThickness(1);

        window.draw(hitbox);
        //window.draw(body);
    }
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
