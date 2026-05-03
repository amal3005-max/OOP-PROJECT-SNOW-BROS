#pragma once
#include "FlyingFooga.h"

class Tornado : public FlyingFooga
{
protected:
    float knifeCooldown;

    float teleportTimer;
    float teleportCooldown;

public:
    float knifeTimer;

    Tornado(sf::Vector2f p);
    bool isFlyingMode() const
    {
        return isFlying;
    }
    void update(float dt) override;
    void draw(sf::RenderWindow& window, bool debugMode) override;
};