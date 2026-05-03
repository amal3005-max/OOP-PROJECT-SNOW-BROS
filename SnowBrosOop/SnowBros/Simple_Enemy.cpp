#include "Enemy.h"

SimpleEnemy::SimpleEnemy(EnemyType t, float spd, sf::Vector2f pos) : Enemy(t, spd, pos)
{
    body.setSize(sf::Vector2f(40, 40));
    body.setFillColor(sf::Color::Green);
    body.setPosition(pos);

    pushable = false;
    hitBox = body.getGlobalBounds(); 
}

void SimpleEnemy::update(float dt)
{
    //colors
    if (isFullyEncased())
    {
        body.setFillColor(sf::Color::Cyan);   // frozen
    }
    else if (snowCoat > 0)
    {
        body.setFillColor(sf::Color::Blue);   // coated
    }
    else
    {
        body.setFillColor(sf::Color::Green);  // normal
    }
    //rolling
    if (isRolling)
    {
        body.move(currentspeed * direction * dt, 0.f);
        position = body.getPosition();
    }

    if (isFullyEncased() && !isRolling)
    {
        pushable = true;
    }

    // bounce off walls
    float x = body.getPosition().x;
    float width = body.getSize().x;
    const float leftBound = 0.f;
    const float rightBound = 800.f;

    if (isRolling)
    {
        if (x <= leftBound)
        {
            body.setPosition(leftBound, body.getPosition().y);
            direction = 1;
            incrementBounceCount();
        }
        else if (x + width >= rightBound)
        {
            body.setPosition(rightBound - width, body.getPosition().y);
            direction = -1;
            incrementBounceCount();
        }

        if (getBounceCount() >= 3)
        {
            kill();
        }
    }
    hitBox = body.getGlobalBounds();
    float xx = body.getPosition().x;
    float wwidth = body.getSize().x;

    bool atBottom = (body.getPosition().y >= 500.f);

    if (isrolling() && atBottom)
    {
        if (xx <= 0.f || xx + wwidth >= 800.f)
        {
            explode();
        }
    }
}
void Enemy::explode()
{
        alive = false;
}
void SimpleEnemy::push(float dx)
{
    body.move(dx, 0.f);
    hitBox = body.getGlobalBounds();
    position = body.getPosition();
}

void SimpleEnemy::draw(sf::RenderWindow& window, bool debugMode)
{    
    window.draw(body);
    if (debugMode)
    {
        sf::FloatRect b = body.getGlobalBounds();

        sf::RectangleShape box;
        box.setPosition(b.left, b.top);
        box.setSize({ b.width, b.height });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Red);
        box.setOutlineThickness(1.f);

        window.draw(box);
    }
}
