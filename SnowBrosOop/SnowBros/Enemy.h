#pragma once
#include <SFML/Graphics.hpp>

enum class EnemyType { Botom, FlyingFoogaFog, Tornado, Mogera, Gamakichi, MogeraChild };

class Enemy
{
protected:
    sf::RectangleShape body;

    float speed;
    bool flight;
    EnemyType type;
    bool projectile;
    bool boss;

    bool pushable;
    
    sf::Vector2f position;
    sf::Vector2f velocity;
    int health;
    float snowCoat = 0.f;
    bool alive = true;

    float currentspeed = 0.f;
    bool isRolling = false;
    float rollingSpeed = 200.f;
    sf::FloatRect hitBox;
    int bounceCount = 0;
    bool onGround;

protected:
    sf::Vector2f targetPosition;

public:
    int direction = 1;
    bool enemyToDelete = false;

    Enemy(EnemyType type, float speed, sf::Vector2f startPos);
    virtual ~Enemy();
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window, bool debugMode) = 0;

    void checkPlatformCollision(sf::RectangleShape& platform);
    void hitBySnowball(float amount);
    virtual bool isAlive() const;
    bool isFullyEncased() const;
    void explode();

    sf::FloatRect getBounds() const;
    void startRolling(int dir);

    void kill();
    void incrementBounceCount();
    int getBounceCount() const;
    void resetBounceCount();

    EnemyType getType() const;
    virtual void push(float dx);
    bool isPushable() const;
    bool isrolling() const { return isRolling; }
    sf::Vector2f getPosition() const
    {
        return body.getPosition();
    }
    void setTarget(sf::Vector2f target)
    {
        targetPosition = target;
    }
};

class SimpleEnemy : public Enemy
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool textureLoaded = false;

    float velocityY = 0.f;
    float gravity = 800.f;
    bool onGround = false;

public:
    SimpleEnemy(EnemyType t, float spd, sf::Vector2f pos);
    //SimpleEnemy(sf::Vector2f pos);
    void push(float dx) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window, bool debugMode) override;
};
class FlyingEnemy : public Enemy
{
protected:
    float patrolSpeed;
    float amplitude; 
    float frequency; 
    float timeAccum; 
    float baseY;  

public:
    FlyingEnemy(EnemyType t, float spd, sf::Vector2f pos);

    void update(float dt) override;
    void draw(sf::RenderWindow& window, bool debugMode) override;
};