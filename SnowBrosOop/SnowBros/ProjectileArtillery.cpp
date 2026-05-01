#include "ProjectileArtillery.h"

ProjectileArtillery::ProjectileArtillery(sf::Vector2f pos, sf::Vector2f vel)
    : Projectile(pos, vel, 20.f, true),
    exploded(false),
    explosionTimer(0.f)
{
    body.setSize(sf::Vector2f(30.f, 30.f));
    body.setFillColor(sf::Color(255, 120, 0));
    body.setPosition(pos);
}

void ProjectileArtillery::update(float dt)
{
    if (!visible && !exploded) return;

    if (!exploded)
    {
        position += velocity * dt;
        body.setPosition(position);
        hitBox = body.getGlobalBounds();

        if (position.x < -30.f || position.x > 830.f ||
            position.y < -30.f || position.y > 630.f)
        {
            ProjectileHit();
        }
    }
    else
    {
        explosionTimer += dt;

        // explosion lasts briefly (visual + future AoE hook)
        if (explosionTimer > 0.2f)
            visible = false;
    }
}

void ProjectileArtillery::draw(sf::RenderWindow& window)
{
    if (visible)
        window.draw(body);
}

void ProjectileArtillery::ProjectileHit()
{
    exploded = true;
    visible = false;
    explosionTimer = 0.f;
}


#include <cmath>

ArtilleryEmitter::ArtilleryEmitter(sf::Vector2f pos, float rate)
{
    position = pos;
    fireRate = rate;
    timer = 0.f;
}

void ArtilleryEmitter::update(float dt, sf::Vector2f target,
    ProjectileArtillery** out, int& outCount)
{
    timer += dt;

    if (timer < fireRate)
        return;

    timer = 0.f;

    sf::Vector2f dir = target - position;

    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0) dir /= len;

    out[outCount++] = new ProjectileArtillery(position, dir * 250.f);
}

void ArtilleryEmitter::draw(sf::RenderWindow& window)
{
    sf::CircleShape c(8.f);
    c.setPosition(position);
    c.setFillColor(sf::Color::Yellow);
    window.draw(c);
}