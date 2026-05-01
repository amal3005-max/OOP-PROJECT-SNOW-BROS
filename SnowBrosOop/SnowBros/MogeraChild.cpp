//#include "MogeraChild.h"
//MogeraChild::MogeraChild( sf::Vector2f MogeraPosition,sf::Vector2f playerPosition):Enemy (EnemyType::MogeraChild ,200.f,MogeraPosition)
//{
//	sf::Vector2f dir = playerPosition- MogeraPosition ;
//	
//	
//	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
//	direction = dir / length;
//}
//void MogeraChild::update(float dt)
//{
//	position += speed * dt * direction ; 
//}
//void MogeraChild::draw(sf::RenderWindow& window)
//{
//	sf::RectangleShape rect(sf::Vector2f(40, 40));
//	rect.setPosition(position);
//	rect.setFillColor(sf::Color::Yellow);
//	window.draw(rect); 
//}
//#include "MogeraChild.h"
//#include <cmath>
//
//MogeraChild::MogeraChild(sf::Vector2f mogeraPos, sf::Vector2f playerPos)
//    : SimpleEnemy(EnemyType::MogeraChild, 200.f, mogeraPos)
//{
//    sf::Vector2f dir = playerPos - mogeraPos;
//
//    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//    if (length != 0)
//        direction = dir / length;
//    else
//        direction = sf::Vector2f(1.f, 0.f);
//}
//
//void MogeraChild::update(float dt)
//{
//    position += direction * speed * dt;
//}
//
//void MogeraChild::draw(sf::RenderWindow& window)
//{
//    sf::RectangleShape rect(sf::Vector2f(30, 30));
//    rect.setPosition(position);
//    rect.setFillColor(sf::Color::Yellow);
//    window.draw(rect);
//}

#include "MogeraChild.h"

//MogeraChild::MogeraChild(sf::Vector2f mogeraPos, sf::Vector2f playerPos)
//    : SimpleEnemy(EnemyType::MogeraChild, 150.f, mogeraPos)
//{
//    // Decide horizontal direction toward player at spawn time
//    moveSpeedX = (playerPos.x >= mogeraPos.x) ? speed : -speed;
//    direction = (moveSpeedX > 0.f) ? 1 : -1;
//
//    body.setSize(sf::Vector2f(30.f, 30.f));
//    body.setFillColor(sf::Color::Yellow);
//    body.setPosition(mogeraPos);
//    position = mogeraPos;
//
//    pushable = false;
//    health = 1;     // one snowball kill
//}
//
//void MogeraChild::update(float dt)
//{
//    // ── Gravity (same logic SimpleEnemy::update uses internally) ──
//    if (!onGround)
//        velocityY += gravity * dt;
//
//    // ── Move body ──
//    body.move(moveSpeedX * dt, velocityY * dt);
//    position = body.getPosition();
//
//    // ── Ground clamp (floor at y=560 — adjust to match your level) ──
//    // Platform collisions are handled by PlayState calling
//    // checkPlatformCollision() on every enemy each frame, which sets
//    // onGround and corrects position — so we only need a hard floor here.
//    const float FLOOR_Y = 560.f;
//    if (body.getPosition().y + body.getSize().y >= FLOOR_Y)
//    {
//        body.setPosition(body.getPosition().x,
//            FLOOR_Y - body.getSize().y);
//        velocityY = 0.f;
//        onGround = true;
//    }
//    else
//    {
//        onGround = false;
//    }
//
//    position = body.getPosition();
//
//    // ── Kill when off-screen horizontally ──
//    float x = body.getPosition().x;
//    if (x < -60.f || x > 860.f)
//        alive = false;
//}
//
//void MogeraChild::draw(sf::RenderWindow& window, bool debugMode)
//{
//    // Snow-coat colour: yellow → blue as snowCoat increases toward 3
//    sf::Color col = sf::Color::Yellow;
//    if (snowCoat > 0.f)
//    {
//        float t = snowCoat / 3.f;
//        if (t > 1.f) t = 1.f;
//        col = sf::Color(
//            static_cast<sf::Uint8>(255 * (1.f - t)),
//            static_cast<sf::Uint8>(255 * (1.f - t)),
//            255
//        );
//    }
//    body.setFillColor(col);
//    window.draw(body);
//
//    if (debugMode)
//    {
//        sf::FloatRect b = body.getGlobalBounds();
//        sf::RectangleShape box(sf::Vector2f(b.width, b.height));
//        box.setPosition(b.left, b.top);
//        box.setFillColor(sf::Color::Transparent);
//        box.setOutlineColor(sf::Color::Red);
//        box.setOutlineThickness(1.f);
//        window.draw(box);
//    }
//}

#include "MogeraChild.h"

//MogeraChild::MogeraChild(sf::Vector2f mogeraPos, sf::Vector2f playerPos)
/*    : Botom(mogeraPos)
{
    // Visual distinction from Botom
    body.setSize(sf::Vector2f(30.f, 30.f));
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(mogeraPos);
    position = mogeraPos;

    health = 3;      // one snowball kill
    speed = 150.f;  // slightly faster than Botom (80)

    // Set initial direction toward the player
    movingLeft = (playerPos.x < mogeraPos.x);
}*/

//MogeraChild::MogeraChild(sf::Vector2f mogeraPos, sf::Vector2f playerPos)
//    : Botom(mogeraPos)
//{
//    body.setSize(sf::Vector2f(30.f, 30.f));
//
//    sf::Vector2f centeredPos(
//        mogeraPos.x - body.getSize().x / 2.f,
//        mogeraPos.y - body.getSize().y / 2.f
//    );
//
//    body.setPosition(centeredPos);
//    position = centeredPos;
//
//    health = 3;
//    speed = 150.f;
//
//    movingLeft = (playerPos.x < mogeraPos.x);
//}
#include "MogeraChild.h"
MogeraChild::MogeraChild(sf::Vector2f mogeraPos,
    sf::Vector2f playerPos,
    ChildType t)
    : Botom(mogeraPos), type(t)
{
    body.setSize(sf::Vector2f(30.f, 30.f));

    // center properly
    sf::Vector2f centeredPos(
        mogeraPos.x - 15.f,
        mogeraPos.y - 15.f
    );

    body.setPosition(centeredPos);
    position = centeredPos;

    health = 3;

    // base speed
    speed = 150.f;

    //  DIFFERENT BEHAVIOR BASED ON TYPE
    if (type == ChildType::TOP)
    {
        speed = 220.f;          // faster
        jumpStrength = -500.f;  // higher jumps → longer range
    }
    else if (type == ChildType::CENTER)
    {
        speed = 150.f;
    }
    else // BOTTOM
    {
        speed = 120.f;          // slower
    }

    movingLeft = (playerPos.x < mogeraPos.x);
}
// ─────────────────────────────────────────────────────────────────────────────
// GamakichiChild
// ─────────────────────────────────────────────────────────────────────────────
GamakichiChild::GamakichiChild(sf::Vector2f pos, sf::Vector2f launchVel)
    : Botom(pos)
{
    // Visual
    body.setSize(sf::Vector2f(28.f, 28.f));
    body.setFillColor(sf::Color(255, 200, 80));   // warm yellow-orange
    body.setPosition(pos);
    position = pos;

    // --- KEY: override the velocity Botom starts with ---
    // Botom initialises velocity to (0,0).  We overwrite it with the
    // cannon launch vector so the child arcs through the air first.
    velocity = launchVel;

    // The child should NOT immediately start the Botom walk logic while it is
    // still airborne.  We mark it as not-on-ground so gravity takes over.
    onGround = false;

    health = 3;
    speed = 100.f;   // walking speed once landed
}

void GamakichiChild::update(float dt)
{
    // While airborne let gravity + current velocity move the body directly,
    // bypassing Botom's horizontal walk decision (which would overwrite velocity.x).
    if (!onGround)
    {
        velocity.y += gravity * dt;        // gravity is inherited from Botom (800 f/s²)
        body.move(velocity * dt);
        position = body.getPosition();

        // Hard floor — same floor Botom uses
        if (body.getPosition().y >= 500.f)
        {
            body.setPosition(body.getPosition().x, 500.f);
            velocity.y = 0.f;
            velocity.x = 0.f;   // stop horizontal launch momentum
            onGround = true;   // from here Botom::update() takes full control
        }

        // Screen edges while flying
        float x = body.getPosition().x;
        float w = body.getSize().x;
        if (x <= 0.f) { body.setPosition(0.f, body.getPosition().y); velocity.x = std::abs(velocity.x); }
        else if (x + w >= 800.f) { body.setPosition(800.f - w, body.getPosition().y); velocity.x = -std::abs(velocity.x); }

        hitBox = body.getGlobalBounds();

        // Also update snow-coat colour while airborne (reuse SimpleEnemy logic)
        if (isFullyEncased())
            body.setFillColor(sf::Color::Cyan);
        else if (snowCoat > 0.f)
            body.setFillColor(sf::Color(200, 150, 50));
        else
            body.setFillColor(sf::Color(255, 200, 80));

        return;   // skip Botom::update() entirely while in the air
    }

    // Landed — hand full control back to Botom (walk, jump, coat colour, etc.)
    // Restore normal Botom colour scheme so SimpleEnemy::update can tint it.
    body.setFillColor(sf::Color(255, 200, 80));
    Botom::update(dt);

    // Keep our distinct colour after Botom recolours to green
    if (!isFullyEncased() && snowCoat == 0.f)
        body.setFillColor(sf::Color(255, 200, 80));
}