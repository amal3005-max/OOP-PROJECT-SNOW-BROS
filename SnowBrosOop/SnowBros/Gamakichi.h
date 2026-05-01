
#pragma once
#include "Enemy.h"
#include "MogeraChild.h"   
#include <cmath>

enum class GamaPhase { Phase1, Phase2, Phase3 };

class Gamakichi : public SimpleEnemy
{
private:
    struct Cannon
    {
        sf::Vector2f offset;   // position relative to boss CENTRE
        float timer;    // counts up toward fireRate
        float fireRate; // seconds between shots from this cannon
    };

    static const int MAX_CANNONS = 6;
    Cannon cannons[MAX_CANNONS];

    GamaPhase phase;
    float idleTimer;       // drives the sine-wave float
    sf::Vector2f basePosition;    // spawn anchor (never changes)

    void updatePhase();

public:
    Gamakichi(sf::Vector2f pos);

    void update(float dt)override;
    void draw(sf::RenderWindow& window, bool debugMode) override;
    bool isAlive()const override;

    void fireCannons(float dt, GamakichiChild** out, int& outCount);
};