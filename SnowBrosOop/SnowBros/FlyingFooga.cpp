//#include "FlyingFooga.h"
//FlyingFooga::FlyingFooga(sf::Vector2f p): Botom(p)
//{
//	position = p;
//	isFlying = false;
//	flightTimer = 0;
//	groundTimer = 0;
//	// ground mode it behaves like Botom 
//	// flight mode it  moves freely in 8 directions 
//
//}
//void FlyingFooga::update(float dt)
//{
//	
//	if (!isFlying)
//	{
//		Botom::update(dt);
//		groundTimer += dt;
//		if (groundTimer > 3.0f)
//		{
//			isFlying = true;
//			groundTimer = 0; 
//			int rx = rand() % 3 - 1;
//			int ry = rand() % 3 - 1;
//			direction = sf::Vector2f(rx, ry);
//		}
//	}
//	else
//	{
//		position += direction * speed * dt;
//		flightTimer += dt;
//		if (flightTimer > 3.0f)
//		{
//			isFlying = false;
//			flightTimer = 0;
//
//		}
//	}
//}
//
//void FlyingFooga::draw(sf::RenderWindow& window)
//{
//	sf::RectangleShape rect(sf::Vector2f(40, 40));
//	rect.setPosition(position);
//	rect.setFillColor(sf::Color::Blue);
//	window.draw(rect);
//}
//


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
        // behave exactly like Botom
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

            // normalize direction (important)
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

        // screen bounds clamp (important)
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



//
//#include "FlyingFooga.h"
//#include <cmath>
//
//// Helper: pick a random 8-direction unit vector (dx/dy each in {-1, 0, 1})
//static sf::Vector2f randomFlightDir()
//{
//    sf::Vector2f d;
//    // Make sure we don't get (0,0)
//    do {
//        d.x = static_cast<float>(rand() % 3 - 1);   // -1, 0, 1
//        d.y = static_cast<float>(rand() % 3 - 1);
//    } while (d.x == 0.f && d.y == 0.f);
//
//    // Normalise so diagonal speed equals cardinal speed
//    float len = std::sqrt(d.x * d.x + d.y * d.y);
//    return d / len;
//}
//
//FlyingFooga::FlyingFooga(sf::Vector2f p)
//    : Botom(p),
//    isFlying(false),
//    flightTimer(0.f), groundTimer(0.f),
//    groundInterval(3.0f), flightInterval(3.0f),
//    flightSpeed(120.f)
//{
//    body.setFillColor(sf::Color::Blue);
//    flightDir = randomFlightDir();
//}
//
//void FlyingFooga::update(float dt)
//{
//    // --- Snow/encasing colour handled by SimpleEnemy, but we set it here
//    //     because flight changes the visual ---
//    if (isFullyEncased())
//        body.setFillColor(sf::Color::Cyan);
//    else if (snowCoat > 0)
//        body.setFillColor(sf::Color(0, 80, 200));
//    else
//        body.setFillColor(isFlying ? sf::Color(0, 100, 255)
//            : sf::Color::Blue);
//
//    // Rolling is handled by SimpleEnemy — delegate and return
//    if (isrolling())
//    {
//        SimpleEnemy::update(dt);
//        return;
//    }
//
//    if (isFullyEncased())
//    {
//        // Frozen in place — just update encasing logic
//        SimpleEnemy::update(dt);
//        return;
//    }
//
//    if (!isFlying)
//    {
//        // ---- GROUND PHASE: behave exactly like Botom ----
//        Botom::update(dt);
//
//        groundTimer += dt;
//        if (groundTimer >= groundInterval)
//        {
//            groundTimer = 0.f;
//            isFlying = true;
//            flightDir = randomFlightDir();
//        }
//    }
//    else
//    {
//        // ---- FLIGHT PHASE: free 8-dir movement ----
//        body.move(flightDir * flightSpeed * dt);
//        position = body.getPosition();
//
//        // Bounce off all four screen edges
//        float x = body.getPosition().x;
//        float y = body.getPosition().y;
//        float w = body.getSize().x;
//        float h = body.getSize().y;
//
//        if (x <= 0.f) { body.setPosition(0.f, y);           flightDir.x = std::abs(flightDir.x); }
//        if (x + w >= 800.f) { body.setPosition(800.f - w, y);     flightDir.x = -std::abs(flightDir.x); }
//        if (y <= 0.f) { body.setPosition(x, 0.f);           flightDir.y = std::abs(flightDir.y); }
//        if (y + h >= 600.f) { body.setPosition(x, 600.f - h);     flightDir.y = -std::abs(flightDir.y); }
//
//        position = body.getPosition();
//        hitBox = body.getGlobalBounds();
//
//        flightTimer += dt;
//        if (flightTimer >= flightInterval)
//        {
//            flightTimer = 0.f;
//            isFlying = false;
//            // Land: snap to floor or let gravity take over in next Botom::update
//            velocity.y = 0.f;
//        }
//    }
//
//    hitBox = body.getGlobalBounds();
//}
//
//void FlyingFooga::draw(sf::RenderWindow& w, bool debugMode)
//{
//    w.draw(body);
//
//    if (debugMode)
//    {
//        sf::RectangleShape box;
//        box.setPosition(hitBox.left, hitBox.top);
//        box.setSize({ hitBox.width, hitBox.height });
//        box.setFillColor(sf::Color::Transparent);
//        box.setOutlineColor(sf::Color::Red);
//        box.setOutlineThickness(1.f);
//        w.draw(box);
//    }
//}