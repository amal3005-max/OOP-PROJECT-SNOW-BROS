#pragma once

#include "Enemy.h"
#include "MogeraChild.h"

class Mogera : public SimpleEnemy
{
private:
    float spawnTimer;
    float spawnInterval;

    // NOTE: health is already in Enemy base class — we use that directly.
    // childCount / children are NOT needed here anymore:
    // PlayState owns all spawned children inside its enemies[] array.

public:
    Mogera(sf::Vector2f pos);
    sf::Vector2f getTopLeftSpawn() const;
    sf::Vector2f getCenterSpawn() const;
    sf::Vector2f getBottomSpawn() const;

    // Returns a new heap-allocated MogeraChild aimed at playerPosition,
    // or nullptr if the timer hasn't fired yet.
    // PlayState calls this every frame and adds the result to enemies[].
    MogeraChild* trySpawnChild(sf::Vector2f playerPosition);

    void update(float dt) override;                                // matches Enemy pure virtual
    void draw(sf::RenderWindow& window, bool debugMode) override; // matches Enemy pure virtual

    bool isAlive() const override;
};