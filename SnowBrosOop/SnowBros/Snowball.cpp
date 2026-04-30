#include "Snowball.h"

Snowball::Snowball(float x, float y, int dir)
{
    //snowball
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);


    direction = dir;
    speed = 200.f;

    lifeTime = 0.f;
    maxLifeTime = 1.5f;
    wrapped = false;
}

void Snowball::update(float dt)
{
    // Move snowball horizontally
    shape.move(speed * direction * dt, 0);

    float x = shape.getPosition().x;
    float y = shape.getPosition().y;
    float r = shape.getRadius();

    if (x + r < 0)
    {
        shape.setPosition(800, y);
		wrapped = true;
    }
    else if (x - r > 800)
    {
        shape.setPosition(0, y);
        wrapped = true;
    }
    lifeTime += dt;
}

void Snowball::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(shape);

    // hitbox for snowball
    if (debugMode)
    {
        sf::FloatRect bounds = shape.getGlobalBounds();

        sf::RectangleShape hitbox;
        hitbox.setPosition(bounds.left, bounds.top);
        hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(1);

        window.draw(hitbox);
    }
}

sf::FloatRect Snowball::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Snowball::isWrapped() const
{
    return wrapped;
}

float Snowball::getLifeTime() const
{
    return lifeTime;
}

float Snowball::getMaxLifeTime() const
{
    return maxLifeTime;
}
