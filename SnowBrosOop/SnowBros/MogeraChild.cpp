
#include "MogeraChild.h"
MogeraChild::MogeraChild(sf::Vector2f mogeraPos, sf::Vector2f playerPos, ChildType t)
    : Botom(mogeraPos), type(t)
{
    body.setSize(sf::Vector2f(30.f, 30.f));

    sf::Vector2f centeredPos(mogeraPos.x - 15.f, mogeraPos.y - 15.f);

    body.setPosition(centeredPos);
    position = centeredPos;

    health = 3;
    speed = 150.f;

    if (type == ChildType::TOP)
    {
        speed = 220.f; 
        jumpStrength = -500.f;
    }
    else if (type == ChildType::CENTER)
    {
        speed = 150.f;
    }
    else
    {
        speed = 120.f;
    }
    movingLeft = (playerPos.x < mogeraPos.x);
}

GamakichiChild::GamakichiChild(sf::Vector2f pos, sf::Vector2f launchVel)
    : Botom(pos)
{
    
    body.setSize(sf::Vector2f(28.f, 28.f));
    body.setFillColor(sf::Color(255, 200, 80));   // warm yellow-orange
    body.setPosition(pos);
    position = pos;

    velocity = launchVel;

    onGround = false;

    health = 3;
    speed = 100.f;
}

void GamakichiChild::update(float dt)
{
    if (!onGround)
    {
        velocity.y += gravity * dt;
        body.move(velocity * dt);
        position = body.getPosition();

        if (body.getPosition().y >= 500.f)
        {
            body.setPosition(body.getPosition().x, 500.f);
            velocity.y = 0.f;
            velocity.x = 0.f;  
            onGround = true;
        }

        float x = body.getPosition().x;
        float w = body.getSize().x;
        if (x <= 0.f) { body.setPosition(0.f, body.getPosition().y); velocity.x = std::abs(velocity.x); }
        else if (x + w >= 800.f) { body.setPosition(800.f - w, body.getPosition().y); velocity.x = -std::abs(velocity.x); }

        hitBox = body.getGlobalBounds();

        if (isFullyEncased())
            body.setFillColor(sf::Color::Cyan);
        else if (snowCoat > 0.f)
            body.setFillColor(sf::Color(200, 150, 50));
        else
            body.setFillColor(sf::Color(255, 200, 80));

        return;
    }

    body.setFillColor(sf::Color(255, 200, 80));
    Botom::update(dt);

    if (!isFullyEncased() && snowCoat == 0.f)
        body.setFillColor(sf::Color(255, 200, 80));
}