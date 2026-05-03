#include "Projectile.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f velocity, float damage, bool firedbyenemy)
{
    this->position = position;
    this->velocity = velocity;
    this->damage = damage;
    this->firedbyenemy = firedbyenemy;

    visible = true;
    hitBox = sf::FloatRect(position.x, position.y, 0.f, 0.f);
}

bool Projectile::isVisible() const
{
    return visible;
}

float Projectile::getDamage() const
{
    return damage;
}

sf::FloatRect Projectile::getBounds() const
{
    return hitBox;
}

void Projectile::setInvisible()
{
    visible = false;
}