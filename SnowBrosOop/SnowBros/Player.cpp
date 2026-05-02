#include "Player.h"
//
//const float WINDOW_WIDTH = 800.f;
//const float WINDOW_HEIGHT = 600.f;
//
//Player::Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j)
//{
//    body.setSize(sf::Vector2f(40, 40));
//    body.setFillColor(sf::Color::Red);
//    body.setPosition(200, 200);
//
//    //body.setOrigin(20.f, 20.f);
//    speed = 200.f;
//    velocityY = 0.f;
//    gravity = 800.f;
//    onGround = false;
//
//    leftKey = l;
//    rightKey = r;
//    jumpKey = j;
//
//	direction = 1;
//    lives = 2;   // or 5 depending on your design
//    isInvincible = false;
//    invincibleTimer = 0.f;
//    invincibleDuration = 2.0f; // 2 seconds cooldown (you can change)
//    //initTexture();
//}
//
//sf::FloatRect Player::getBounds() const
//{
//    return body.getGlobalBounds();
//}
//
//void Player::handleInput()
//{
//    
//    if (sf::Keyboard::isKeyPressed(jumpKey) && onGround)
//    {
//        velocityY = -400.f;
//        onGround = false;
//    }
//}
//
//void Player::update(float dt)
//{
//    onGround = false;
//    // horizontal movement
//    if (sf::Keyboard::isKeyPressed(leftKey))
//    {
//        body.move(-speed * dt, 0);
//    }
//    if (sf::Keyboard::isKeyPressed(rightKey))
//    {
//        body.move(speed * dt, 0);
//    }
//
//    // gravity
//    velocityY += gravity * dt;
//    body.move(0, velocityY * dt);
//
//    // ground collision
//    if (body.getPosition().y >= 500)
//    {
//        body.setPosition(body.getPosition().x, 500);
//        velocityY = 0;
//        onGround = true;
//    }
//
//    // bounds
//    sf::Vector2f pos = body.getPosition();
//    sf::Vector2f size = body.getSize();
//
//    float x = body.getPosition().x;
//    float y = body.getPosition().y;
//    float width = body.getSize().x;
//
//    if (x + width < 0)        
//    {
//        body.setPosition(800, y);
//    }
//    else if (x > 800)        
//    {
//        body.setPosition(-width, y);
//    }
//
//    if (!sf::Keyboard::isKeyPressed(jumpKey) && velocityY < 0)
//    {
//        velocityY *= 0.95f; 
//    }
//
//    if (sf::Keyboard::isKeyPressed(leftKey))
//        direction = -1;
//
//    if (sf::Keyboard::isKeyPressed(rightKey))
//        direction = 1;
//
//    if (invincibleTimer > 0.f)
//    {
//        invincibleTimer -= dt;
//        if (invincibleTimer <= 0.f)
//        {
//            isInvincible = false;
//        }
//    }
//}
//
//void Player::draw(sf::RenderWindow& window, bool debugMode)
//{
//    window.draw(body);
//    //window.draw(sprite);
//
//    if (isInvincible)
//    {
//        int blink = (invincibleTimer * 10);
//
//        if (blink % 2 == 0)
//            window.draw(body);
//    }
//    else
//    {
//        window.draw(body);
//    }
//
//    if (debugMode)
//    {
//        sf::FloatRect bounds = body.getGlobalBounds();
//
//        sf::RectangleShape hitbox;
//        hitbox.setPosition(bounds.left, bounds.top);
//        hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
//        hitbox.setFillColor(sf::Color::Transparent);
//        hitbox.setOutlineColor(sf::Color::Green);
//        hitbox.setOutlineThickness(1);
//
//        window.draw(hitbox);
//        //window.draw(body);
//    }
//}
//void Player::checkPlatformCollision(sf::RectangleShape& platform)
//{
//    sf::FloatRect playerBounds = body.getGlobalBounds();
//    sf::FloatRect platBounds = platform.getGlobalBounds();
//
//    float playerBottom = playerBounds.top + playerBounds.height;
//
//    // ONLY LAND IF FALLING AND TOUCHING TOP SURFACE
//    if (velocityY > 0 &&
//        playerBottom >= platBounds.top &&
//        playerBottom <= platBounds.top + 10.f &&  // small tolerance
//        playerBounds.left + playerBounds.width > platBounds.left &&
//        playerBounds.left < platBounds.left + platBounds.width)
//    {
//        body.setPosition(
//            body.getPosition().x,
//            platBounds.top - playerBounds.height
//        );
//
//        velocityY = 0;
//        onGround = true;
//    }
//}
//sf::Vector2f Player::getPosition() const
//{
//    return body.getPosition();   // or sprite.getPosition() if you use sprite
//}
//int Player::getLives() const
//{
//    return lives;
//}
//
//void Player::loseLife()
//{
//    if (isInvincible)
//        return;
//
//    lives--;
//
//    if (lives < 0)
//        lives = 0;
//
//    // activate invincibility after hit
//    isInvincible = true;
//    invincibleTimer = 0.f;
//}
//
//void Player::gainLife()
//{
//    lives++;
//}
//
//bool Player::isAlive() const
//{
//    return lives > 0;
//}

#include "Player.h"

const float WINDOW_WIDTH = 800.f;

Player::Player(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j)
{
    body.setSize(sf::Vector2f(40, 40));
    body.setFillColor(sf::Color::Red);
    //body.setPosition(200, 200);
    body.setPosition(sf::Vector2f(300.f, 480.f));

    speed = 200.f;
    velocityY = 0.f;
    gravity = 800.f;
    onGround = false;

    leftKey = l;
    rightKey = r;
    jumpKey = j;

    direction = 1;

    // -------- LIVES SYSTEM --------
    lives = 2;

    isInvincible = false;
    invincibleDuration = 1.5f;
    invincibleTimer = 0.f;
}

void Player::update(float dt)
{
    onGround = false;

    if (sf::Keyboard::isKeyPressed(leftKey))
        body.move(-speed * dt, 0);

    if (sf::Keyboard::isKeyPressed(rightKey))
        body.move(speed * dt, 0);

    velocityY += gravity * dt;
    body.move(0, velocityY * dt);

    if (body.getPosition().y >= 500)
    {
        body.setPosition(body.getPosition().x, 500);
        velocityY = 0;
        onGround = true;
    }

    float x = body.getPosition().x;
    float y = body.getPosition().y;
    float width = body.getSize().x;

    if (x + width < 0)
        body.setPosition(800, y);
    else if (x > 800)
        body.setPosition(-width, y);

    if (sf::Keyboard::isKeyPressed(leftKey))
        direction = -1;

    if (sf::Keyboard::isKeyPressed(rightKey))
        direction = 1;

    // -------- INVINCIBILITY TIMER --------
    if (isInvincible)
    {
        invincibleTimer -= dt;

        if (invincibleTimer <= 0.f)
        {
            isInvincible = false;
            invincibleTimer = 0.f;
        }
    }
}

bool Player::loseLife()
{
    if (isInvincible)
        return false;

    // if already at 0 → this hit kills player
    if (lives == 0)
        return true;

    lives--;

    //if (lives < 0)
    //{
    //    lives = 0;
    //    return true;
    //}

    // START cooldown correctly
    isInvincible = true;
    invincibleTimer = invincibleDuration;

    std::cout << "Player hit! Lives: " << lives << std::endl;
    return false;
}
//bool Player::loseLife()
//{
//    if (isInvincible)
//        return false;
//
//    // if already at 0 → this hit kills player
//    if (lives == 0)
//        return true;
//
//    // otherwise reduce life
//    lives--;
//
//    // activate cooldown
//    isInvincible = true;
//    invincibleTimer = invincibleDuration;
//
//    return false;
//}

void Player::draw(sf::RenderWindow& window, bool debugMode)
{
    if (isInvincible)
    {
        int blink = static_cast<int>(invincibleTimer * 10);

        if (blink % 2 == 0)
            window.draw(body);
    }
    else
    {
        window.draw(body);
    }

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
    }
}
sf::FloatRect Player::getBounds() const
{
    return body.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return body.getPosition();
}

int Player::getLives() const { return lives; }

void Player::gainLife() { lives++; }

bool Player::isAlive() const { return (lives > 0); }


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

void Player::handleInput()
{
    
    if (sf::Keyboard::isKeyPressed(jumpKey) && onGround)
    {
        velocityY = -400.f;
        onGround = false;
    }
}