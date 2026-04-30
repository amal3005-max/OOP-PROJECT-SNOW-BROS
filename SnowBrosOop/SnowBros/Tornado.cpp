#include "Tornado.h"
#include <iostream>
using namespace std;
//Tornado::Tornado(sf::Vector2f p) : FlyingFooga (p)
//{
//    position = p;
//    knifeTimer = 0;
//}
//void Tornado ::update (float dt)
//{
//    FlyingFooga::update(dt);
//    if (isFlying)
//    {
//     
//        speed = 55.f + rand() % 250; // it randomized speed only during flying 
//        knifeTimer += dt;
//       
//        if (knifeTimer > 3.0f)
//        {
//            knifeTimer = 0;
//            
//        }
//   }
//    
//}
//void Tornado::draw(sf::RenderWindow& window)
//{
//    sf:: RectangleShape rect(sf::Vector2f(40, 40));
//    rect.setPosition(position);
//    rect.setFillColor(sf::Color::White);
//    window.draw (rect);
//
//}

#include "Tornado.h"
#include <cstdlib> // for rand()

Tornado::Tornado(sf::Vector2f p)
    : FlyingFooga(p)
{
    knifeTimer = 0.f;
    knifeCooldown = 3.0f;

    teleportTimer = 0.f;
    teleportCooldown = 2.0f;

    body.setFillColor(sf::Color::Yellow); // distinguish from others
}
void Tornado::update(float dt)
{
    // base behavior (ground + flying switching)
    FlyingFooga::update(dt);

    if (isrolling())
        return;

    // ONLY modify behavior during flight
    if (isFlying)
    {
        // --- 1. TELEPORT / JUMP MOVEMENT ---
        teleportTimer += dt;

        if (teleportTimer >= teleportCooldown)
        {
            teleportTimer = 0.f;

            // random position on screen
            float x = static_cast<float>(rand() % 760);
            float y = static_cast<float>(rand() % 400);

            body.setPosition(x, y);
        }

        // --- 2. RANDOM SPEED (unpredictable flight) ---
        float randomSpeed = 50.f + (rand() % 200);
        body.move(flightDir * randomSpeed * dt);

        // bounce off edges
        if (body.getPosition().x <= 0 || body.getPosition().x >= 760)
            flightDir.x *= -1;

        if (body.getPosition().y <= 0 || body.getPosition().y >= 500)
            flightDir.y *= -1;

        // --- 3. KNIFE ATTACK TIMER ---
        knifeTimer += dt;

        if (knifeTimer >= knifeCooldown)
        {
            knifeTimer = 0.f;

            // TODO: integrate with your projectile system
            // Example placeholder:
            // spawnKnifeTowardPlayer();

            // For now debug:
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