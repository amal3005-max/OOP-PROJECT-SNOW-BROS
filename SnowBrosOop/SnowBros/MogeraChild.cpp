
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