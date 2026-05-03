#include "Tornado.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Tornado::Tornado(sf::Vector2f p) : FlyingFooga(p)
{
    knifeTimer = 0.f;
    knifeCooldown = 3.0f;

    teleportTimer = 0.f;
    teleportCooldown = 2.0f;

    body.setFillColor(sf::Color::Yellow);
}
void Tornado::update(float dt)
{
    FlyingFooga::update(dt);

    if (isrolling())
        return;

    if (isFlying)
    {
        //TELEPORT / JUMP MOVEMENT
        teleportTimer += dt;

        if (teleportTimer >= teleportCooldown)
        {
            teleportTimer = 0.f;

            float x = static_cast<float>(rand() % 760);
            float y = static_cast<float>(rand() % 400);

            body.setPosition(x, y);
        }

        //  RANDOM SPEED (unpredictable flight)
        float randomSpeed = 50.f + (rand() % 200);
        body.move(flightDir * randomSpeed * dt);

        // bounce off edges
        if (body.getPosition().x <= 0 || body.getPosition().x >= 760)
            flightDir.x *= -1;

        if (body.getPosition().y <= 0 || body.getPosition().y >= 500)
            flightDir.y *= -1;

        // KNIFE ATTACK TIMER
        knifeTimer += dt;

        if (knifeTimer >= knifeCooldown)
        {
            knifeTimer = 0.f;

            cout << "Tornado throws knife!\n";
        }
    }

    hitBox = body.getGlobalBounds();
}

void Tornado::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(body);

    if (debugMode)
    {
        sf::RectangleShape box;
        box.setPosition(hitBox.left, hitBox.top);
        box.setSize({ hitBox.width, hitBox.height });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Red);
        box.setOutlineThickness(1.f);

        window.draw(box);
    }
}