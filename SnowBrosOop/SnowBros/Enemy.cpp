#include "Enemy.h"

Enemy::Enemy(EnemyType type, float speed, sf::Vector2f startPos)
    : speed(speed), flight(false), type(type), projectile(false), boss(false), position(startPos), velocity(0.f, 0.f), health(100), snowCoat(0.f), alive(true)
{
    body.setSize(sf::Vector2f(40.f, 40.f));
    body.setPosition(startPos);
    hitBox = sf::FloatRect(position.x, position.y, 40.f, 40.f);
    pushable = false;
}

Enemy::~Enemy() {}

void Enemy::hitBySnowball(float amount)
{
    if (!alive) return;

    snowCoat += amount;

    if (snowCoat > 5.f)
        snowCoat = 5.f;

    health -= 10;
    if (health <= 0)
        alive = false;
}

bool Enemy::isAlive() const
{
    return alive;
}

bool Enemy::isFullyEncased() const
{
    return snowCoat >= 5.0f;
}

EnemyType Enemy::getType() const
{
    return type;
}
bool Enemy::isPushable() const
{
    return pushable;
}
sf::FloatRect Enemy::getBounds() const
{
    return hitBox; 
}

void Enemy::push(float dx)
{
    position.x += dx;
    hitBox = body.getGlobalBounds();
    hitBox.left = position.x;
}


void Enemy::startRolling(int dir)
{
    if (isRolling) return;

    isRolling = true;
    direction = dir;
    currentspeed = rollingSpeed;
    bounceCount = 0;
}

void Enemy::kill()
{
    alive = false;
}

void Enemy::incrementBounceCount()
{
    ++bounceCount;
}

int Enemy::getBounceCount() const
{
    return bounceCount;
}

void Enemy::resetBounceCount()
{
    bounceCount = 0;
}
void Enemy::checkPlatformCollision(sf::RectangleShape& platform)
{
    sf::FloatRect eb = body.getGlobalBounds();
    sf::FloatRect pb = platform.getGlobalBounds();

    float enemyBottom = eb.top + eb.height;

    if (velocity.y > 0 &&
        enemyBottom >= pb.top &&
        enemyBottom <= pb.top + 10.f &&
        eb.left + eb.width > pb.left &&
        eb.left < pb.left + pb.width)
    {
        body.setPosition(body.getPosition().x, pb.top - eb.height);
        velocity.y = 0.f;
        onGround = true;   
    }
}

FlyingEnemy::FlyingEnemy(EnemyType t, float spd, sf::Vector2f pos)
    : Enemy(t, spd, pos),
    patrolSpeed(spd), amplitude(40.f), frequency(1.5f),
    timeAccum(0.f), baseY(pos.y)
{
    body.setSize(sf::Vector2f(40.f, 40.f));
    body.setFillColor(sf::Color::Magenta);
    body.setPosition(pos);
    flight = true;
    onGround = false;        
    hitBox = body.getGlobalBounds();
}

void FlyingEnemy::update(float dt)
{
    if (isFullyEncased())
        body.setFillColor(sf::Color::Cyan);
    else if (snowCoat > 0)
        body.setFillColor(sf::Color(150, 0, 200));
    else
        body.setFillColor(sf::Color::Magenta);

    if (isRolling)
    {
        // Flying enemy can still be rolled after encasing
        body.move(currentspeed * direction * dt, 0.f);
        position = body.getPosition();

        float x = body.getPosition().x;
        float w = body.getSize().x;
        if (x <= 0.f) { body.setPosition(0.f, body.getPosition().y); direction = 1; incrementBounceCount(); }
        else if (x + w >= 800.f) { body.setPosition(800.f - w, body.getPosition().y); direction = -1; incrementBounceCount(); }
        if (getBounceCount() >= 3) kill();
    }
    else if (!isFullyEncased())
    {
        timeAccum += dt;

        float dx = patrolSpeed * direction * dt;
        body.move(dx, 0.f);

        // Sine-wave vertical float
        float newY = baseY + amplitude * std::sin(frequency * timeAccum);
        body.setPosition(body.getPosition().x, newY);

        // Wall reversal
        float x = body.getPosition().x;
        float w = body.getSize().x;
        if (x <= 0.f) { body.setPosition(0.f, body.getPosition().y); direction = 1; }
        else if (x + w >= 800.f) { body.setPosition(800.f - w, body.getPosition().y); direction = -1; }
    }

    position = body.getPosition();
    hitBox = body.getGlobalBounds();
}

void FlyingEnemy::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(body);

    if (debugMode)
    {
        sf::FloatRect b = body.getGlobalBounds();
        sf::RectangleShape box;
        box.setPosition(b.left, b.top);
        box.setSize({ b.width, b.height });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Yellow);
        box.setOutlineThickness(1.f);
        window.draw(box);
    }
}