#pragma once
#include "Projectile.h"

class Knife : public Projectile
{
private:
    sf::RectangleShape body;

public:
    Knife(sf::Vector2f position, sf::Vector2f direction);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void ProjectileHit() override;
};