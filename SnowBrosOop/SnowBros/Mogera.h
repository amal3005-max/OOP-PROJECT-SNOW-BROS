#pragma once

#include "Enemy.h"
#include "MogeraChild.h"

class Mogera : public SimpleEnemy
{
private:
    float spawnTimer;
    float spawnInterval;
public:
    Mogera(sf::Vector2f pos);
    sf::Vector2f getTopLeftSpawn() const;
    sf::Vector2f getCenterSpawn() const;
    sf::Vector2f getBottomSpawn() const;

    MogeraChild* trySpawnChild(sf::Vector2f playerPosition);

    void update(float dt) override;                               
    void draw(sf::RenderWindow& window, bool debugMode) override;

    bool isAlive() const override;
};