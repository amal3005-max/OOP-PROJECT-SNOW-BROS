#include "Mogera.h"
#include <cmath>

Mogera::Mogera(sf::Vector2f p)
    : SimpleEnemy(EnemyType::Mogera, 0.f, p)
{
    health = 1000;           // requires multiple hits
    spawnTimer = 0.f;
    spawnInterval = 3.f;   // spawn a child every 3 seconds
    pushable = false;

    // Set large boss body
    body.setSize(sf::Vector2f(200.f, 200.f));
    body.setFillColor(sf::Color::White);
    body.setPosition(p);
    position = p;
}

MogeraChild* Mogera::trySpawnChild(sf::Vector2f playerPosition)
{
    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.f;
        int r = rand() % 3;

        if (r == 0)
            return new MogeraChild(getTopLeftSpawn(), playerPosition, ChildType::TOP);

        else if (r == 1)
            return new MogeraChild(getCenterSpawn(), playerPosition, ChildType::CENTER);

        else
            return new MogeraChild(getBottomSpawn(), playerPosition, ChildType::BOTTOM);
    }

    return nullptr;
}

void Mogera::update(float dt)
{
    // Advance spawn timer — trySpawnChild() checks it from PlayState
    spawnTimer += dt;

    // Mogera is stationary; call base only for snowball-coat colour logic
    SimpleEnemy::update(dt);
}

void Mogera::draw(sf::RenderWindow& window, bool debugMode)
{
    // Boss body
    window.draw(body);

    // Health bar — grey background + red foreground
    float barW = body.getSize().x;
    float fraction = static_cast<float>(health) / 1000.f;
    if (fraction < 0.f) fraction = 0.f;

    sf::RectangleShape hpBg(sf::Vector2f(barW, 10.f));
    hpBg.setPosition(body.getPosition().x, body.getPosition().y - 15.f);
    hpBg.setFillColor(sf::Color(80, 80, 80));
    window.draw(hpBg);

    sf::RectangleShape hpFg(sf::Vector2f(barW * fraction, 10.f));
    hpFg.setPosition(body.getPosition().x, body.getPosition().y - 15.f);
    hpFg.setFillColor(sf::Color::Red);
    window.draw(hpFg);

    if (debugMode)
    {
        sf::FloatRect b = body.getGlobalBounds();
        sf::RectangleShape box(sf::Vector2f(b.width, b.height));
        box.setPosition(b.left, b.top);
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Cyan);
        box.setOutlineThickness(2.f);
        window.draw(box);
    }
}

bool Mogera::isAlive() const
{
    return health > 0;
}

sf::Vector2f Mogera::getTopLeftSpawn() const
{
    return body.getPosition() + sf::Vector2f(20.f, 20.f);
}

sf::Vector2f Mogera::getCenterSpawn() const
{
    return body.getPosition() + sf::Vector2f(100.f, 100.f);
}

sf::Vector2f Mogera::getBottomSpawn() const
{
    return body.getPosition() + sf::Vector2f(100.f, 180.f);
}