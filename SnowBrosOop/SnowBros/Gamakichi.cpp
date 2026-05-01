

#include "Gamakichi.h"
#include <cstdlib>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────────────────────────────────────
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

    // ── 6 cannons arranged in a TOP semicircle ────────────────────────────
    // Offsets are relative to the CENTRE of the boss body.
    // Angles go from 180° (far left) to 0° (far right), all above centre (y < 0).
    //
    //   index:  0    1    2    3    4    5
    //   angle: 180  144  108   72   36    0  degrees  (left → right)
    //
    float halfW = 120.f;   // half of body width  — radius of the arc
    float halfH = 80.f;   // half of body height — vertical squish factor

    float angles[MAX_CANNONS] = { 180.f, 144.f, 108.f, 72.f, 36.f, 0.f };

    // Fire rates: outer cannons fire faster, inner (top) slower
    //float rates[MAX_CANNONS] = { 3.5f, 4.0f, 5.0f, 5.0f, 4.0f, 3.5f };
    float rates[MAX_CANNONS] =
    {
        8.5f, 9.0f, 9.5f,
        9.5f, 9.0f, 8.5f
    };
    for (int i = 0; i < MAX_CANNONS; i++)
    {
        float rad = angles[i] * 3.14159f / 180.f;

        // cos gives x (−1 at 180°, +1 at 0°), sin gives y (0 at both ends, −1 at 90°)
        float ox = halfW * std::cos(rad);
        float oy = -halfH * std::sin(rad);   // negative → above centre

        cannons[i].offset = sf::Vector2f(ox, oy);
        cannons[i].timer = (float)(i) * 0.8f;  // stagger initial shots
        cannons[i].fireRate = rates[i];
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Phase management
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::updatePhase()
{
    GamaPhase newPhase;
    if (health > 600) newPhase = GamaPhase::Phase1;
    else if (health > 300) newPhase = GamaPhase::Phase2;
    else                    newPhase = GamaPhase::Phase3;

    if (newPhase != phase)
    {
        phase = newPhase;

        // Speed up all cannon fire rates when phase increases
        float multiplier = (phase == GamaPhase::Phase2) ? 0.75f : 0.5f;
        for (int i = 0; i < MAX_CANNONS; i++)
            cannons[i].fireRate *= multiplier;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Update — slow sine float, phase colour
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::update(float dt)
{
    idleTimer += dt;
    updatePhase();

    // Call base for snowball-coat colour / rolling logic (stationary, so fine)
    SimpleEnemy::update(dt);

    // Gentle vertical float
    float floatOffset = std::sin(idleTimer * 0.6f) * 10.f;
    sf::Vector2f newPos = basePosition;
    newPos.y += floatOffset;

    body.setPosition(newPos);
    position = newPos;

    // Phase colour (overrides SimpleEnemy's snowCoat colour when not encased)
    if (!isFullyEncased())
    {
        switch (phase)
        {
        case GamaPhase::Phase1: body.setFillColor(sf::Color::Cyan);             break;
        case GamaPhase::Phase2: body.setFillColor(sf::Color(255, 140, 0));    break;
        case GamaPhase::Phase3: body.setFillColor(sf::Color::Red);              break;
        }
    }

    hitBox = body.getGlobalBounds();
}

// ─────────────────────────────────────────────────────────────────────────────
// fireCannons — called every frame by PlayState
// Each cannon independently ticks; when its timer fires it spawns one
// GamakichiChild launched in a short arc from that cannon mouth.
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::fireCannons(float dt, GamakichiChild** out, int& outCount)
{
    outCount = 0;

    // Boss centre in world space
    sf::Vector2f centre = body.getPosition() +
        sf::Vector2f(body.getSize().x / 2.f,
            body.getSize().y / 2.f);

    for (int i = 0; i < MAX_CANNONS; i++)
    {
        cannons[i].timer += dt;

        if (cannons[i].timer < cannons[i].fireRate)
            continue;

        cannons[i].timer = 0.f;

        // World-space spawn position = cannon mouth
        sf::Vector2f spawnPos = centre + cannons[i].offset;

        // Launch velocity:
        //   Horizontal — same sign as the cannon's x-offset (away from centre),
        //                with a small random spread so shots fan out.
        //   Vertical   — always upward (negative y), giving a parabolic arc.
        //                The child then falls under gravity and lands as a Botom.

        float launchSpeedX = 80.f + (rand() % 60);          // 80-140
        float launchSpeedY = -(250.f + (rand() % 100));      // −250 to −350 (upward)

        // Direction: outward from centre
        float xSign = (cannons[i].offset.x >= 0.f) ? 1.f : -1.f;
        if (cannons[i].offset.x == 0.f)
            xSign = (rand() % 2 == 0) ? 1.f : -1.f;   // top cannon picks randomly

        sf::Vector2f launchVel(xSign * launchSpeedX, launchSpeedY);

        GamakichiChild* child = new GamakichiChild(spawnPos, launchVel);

        out[outCount++] = child;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Draw — boss body + health bar + cannon dots in debug
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(body);

    // Health bar
    float barW = body.getSize().x;
    float fraction = static_cast<float>(health) / 2000.f;
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
        // Hitbox outline
        sf::RectangleShape box;
        box.setPosition(hitBox.left, hitBox.top);
        box.setSize({ hitBox.width, hitBox.height });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Magenta);
        box.setOutlineThickness(2.f);
        window.draw(box);

        // Cannon mouth dots
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

// ─────────────────────────────────────────────────────────────────────────────
bool Gamakichi::isAlive() const
{
    return health > 0;
}