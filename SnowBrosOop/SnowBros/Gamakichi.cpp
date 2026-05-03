#include "Gamakichi.h"
#include <cstdlib>
#include <cmath>

Gamakichi::Gamakichi(sf::Vector2f pos)
    : SimpleEnemy(EnemyType::Gamakichi, 0.f, pos)
{
    health = 1000;
    pushable = false;

    body.setSize(sf::Vector2f(400.f, 250.f));
    body.setFillColor(sf::Color::Cyan);
    body.setPosition(pos);

    position = pos;
    basePosition = pos;

    phase = GamaPhase::Phase1;
    idleTimer = 0.f;

    float halfW = 120.f; 
    float halfH = 80.f; 

    float angles[MAX_CANNONS] = { 180.f, 144.f, 108.f, 72.f, 36.f, 0.f };
    float rates[MAX_CANNONS] = { 8.5f, 9.0f, 9.5f, 9.5f, 9.0f, 8.5f };

    for (int i = 0; i < MAX_CANNONS; i++)
    {
        float rad = angles[i] * 3.14159f / 180.f;
        float ox = halfW * std::cos(rad);
        float oy = -halfH * std::sin(rad);   

        cannons[i].offset = sf::Vector2f(ox, oy);
        cannons[i].timer = (float)(i) * 0.8f; 
        cannons[i].fireRate = rates[i];
    }
}

void Gamakichi::updatePhase()
{
    GamaPhase newPhase;
    if (health > 600)
    {
        newPhase = GamaPhase::Phase1;
    }
    else if (health > 300)
    {
        newPhase = GamaPhase::Phase2;
    }
    else
    {
        newPhase = GamaPhase::Phase3;
    }
    if (newPhase != phase)
    {
        phase = newPhase;

        float multiplier = (phase == GamaPhase::Phase2) ? 0.75f : 0.5f;
        for (int i = 0; i < MAX_CANNONS; i++)
        {
            cannons[i].fireRate *= multiplier;
        }
    }
}

void Gamakichi::update(float dt)
{
    idleTimer += dt;
    updatePhase();
    SimpleEnemy::update(dt);

    float floatOffset = std::sin(idleTimer * 0.6f) * 10.f;
    sf::Vector2f newPos = basePosition;
    newPos.y += floatOffset;

    body.setPosition(newPos);
    position = newPos;

    if (!isFullyEncased())
    {
        switch (phase)
        {
        case GamaPhase::Phase1: body.setFillColor(sf::Color::Cyan);            
            break;
        case GamaPhase::Phase2: body.setFillColor(sf::Color(255, 140, 0));    
            break;
        case GamaPhase::Phase3: body.setFillColor(sf::Color::Red);              
            break;
        }
    }

    hitBox = body.getGlobalBounds();
}

void Gamakichi::fireCannons(float dt, GamakichiChild** out, int& outCount)
{
    outCount = 0;

    sf::Vector2f centre = body.getPosition() +
        sf::Vector2f(body.getSize().x / 2.f, body.getSize().y / 2.f);

    for (int i = 0; i < MAX_CANNONS; i++)
    {
        cannons[i].timer += dt;

        if (cannons[i].timer < cannons[i].fireRate)
            continue;

        cannons[i].timer = 0.f;

        sf::Vector2f spawnPos = centre + cannons[i].offset;

        float launchSpeedX = 80.f + (rand() % 60);  
        float launchSpeedY = -(250.f + (rand() % 100));  

        float xSign = (cannons[i].offset.x >= 0.f) ? 1.f : -1.f;
        if (cannons[i].offset.x == 0.f)
            xSign = (rand() % 2 == 0) ? 1.f : -1.f;   

        sf::Vector2f launchVel(xSign * launchSpeedX, launchSpeedY);

        GamakichiChild* child = new GamakichiChild(spawnPos, launchVel);

        out[outCount++] = child;
    }
}

void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(body);

    // Health bar
    float barW = body.getSize().x;
    float fraction = static_cast<float>(health) / 1000.f;
    if (fraction < 0.f) fraction = 0.f;

    sf::RectangleShape hpBg(sf::Vector2f(barW, 12.f));
    hpBg.setPosition(body.getPosition().x, body.getPosition().y - 20.f);
    hpBg.setFillColor(sf::Color(60, 60, 60));
    window.draw(hpBg);

    sf::Color barCol = (phase == GamaPhase::Phase3) ? sf::Color::Red :
        (phase == GamaPhase::Phase2) ? sf::Color(255, 140, 0) :
        sf::Color::Green;

    sf::RectangleShape hpFg(sf::Vector2f(barW * fraction, 12.f));
    hpFg.setPosition(body.getPosition().x, body.getPosition().y - 20.f);
    hpFg.setFillColor(barCol);
    window.draw(hpFg);

    if (debugMode)
    {
        sf::RectangleShape box;
        box.setPosition(hitBox.left, hitBox.top);
        box.setSize({ hitBox.width, hitBox.height });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Magenta);
        box.setOutlineThickness(2.f);
        window.draw(box);

        sf::Vector2f centre = body.getPosition() +
            sf::Vector2f(body.getSize().x / 2.f,
                body.getSize().y / 2.f);

        for (int i = 0; i < MAX_CANNONS; i++)
        {
            sf::CircleShape dot(5.f);
            dot.setOrigin(5.f, 5.f);
            dot.setPosition(centre + cannons[i].offset);
            dot.setFillColor(sf::Color::Yellow);
            window.draw(dot);
        }
    }
}

bool Gamakichi::isAlive() const
{
    return health > 0;
}