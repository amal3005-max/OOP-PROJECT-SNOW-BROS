
#include "FlyingFooga.h"
#include <cstdlib>

FlyingFooga::FlyingFooga(sf::Vector2f p)
	: Botom(p)
{
	isFlying = false;

	flightTimer = 0.f;
	groundTimer = 0.f;

	flightSpeedMultiplier = 1.5f;

	flightDir = sf::Vector2f(0.f, -1.f);
}
void FlyingFooga::update(float dt)
{
    if (!isFlying)
    {
        Botom::update(dt);

        groundTimer += dt;

        // enter flight mode
        if (groundTimer >= 3.0f)
        {
            isFlying = true;
            groundTimer = 0.f;

            // pick valid 8-direction movement
            int rx = (rand() % 3) - 1;
            int ry = (rand() % 3) - 1;

            // prevent zero vector
            if (rx == 0 && ry == 0)
                rx = 1;

            flightDir = sf::Vector2f((float)rx, (float)ry);

            // normalize direction 
            float len = sqrt(flightDir.x * flightDir.x + flightDir.y * flightDir.y);
            flightDir.x /= len;
            flightDir.y /= len;
        }
    }
    else
    {
        // FLIGHT MODE
        velocity = flightDir * speed * flightSpeedMultiplier;

        body.move(velocity * dt);
        position = body.getPosition();

        flightTimer += dt;

        // return to ground mode
        if (flightTimer >= 3.0f)
        {
            isFlying = false;
            flightTimer = 0.f;

            velocity = sf::Vector2f(0.f, 0.f);
        }

        // screen bounds 
        sf::Vector2f pos = body.getPosition();

        if (pos.x < 0) pos.x = 0;
        if (pos.x > 800 - body.getSize().x) pos.x = 800 - body.getSize().x;
        if (pos.y < 0) pos.y = 0;
        if (pos.y > 600 - body.getSize().y) pos.y = 600 - body.getSize().y;

        body.setPosition(pos);
    }

    hitBox = body.getGlobalBounds();
}

void FlyingFooga::draw(sf::RenderWindow& window, bool debugMode)
{
    body.setFillColor(isFlying ? sf::Color::Cyan : sf::Color::Blue);

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

