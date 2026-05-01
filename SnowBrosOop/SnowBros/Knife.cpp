#include "Knife.h"
#include <cmath>

Knife::Knife(sf::Vector2f pos, sf::Vector2f dir)
    : Projectile(pos, dir * 150.f, 1.0f, true)
{
    body.setSize(sf::Vector2f(30, 8));   // bigger
    body.setFillColor(sf::Color::Red);   // bright color
    body.setPosition(pos);

    // optional: rotate knife in direction of travel
    float angle = atan2(dir.y, dir.x) * 180.f / 3.14159f;
    body.setRotation(angle);
}

void Knife::update(float dt)
{
    position += velocity * dt;
    body.setPosition(position);

    hitBox = body.getGlobalBounds();

    // remove if outside screen
    if (position.x < 0 || position.x > 800 ||
        position.y < 0 || position.y > 600)
    {
        visible = false;
    }
}

void Knife::draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(body);
    }
}

void Knife::ProjectileHit()
{
    visible = false;
}