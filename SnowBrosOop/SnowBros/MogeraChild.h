
#pragma once

#include "Botttom.h"
enum class ChildType
{
    TOP,
    CENTER,
    BOTTOM
};
class MogeraChild : public Botom
{
//private:
//
//public:
//    MogeraChild(sf::Vector2f mogeraPosition, sf::Vector2f playerPosition);
private:
    ChildType type;

public:
    MogeraChild(sf::Vector2f mogeraPosition,
        sf::Vector2f playerPosition,
        ChildType type);
    // update and draw are fully inherited from Botom — nothing to override
};

// ── GamakichiChild ───────────────────────────────────────────────────────────
// Launched from a cannon with an initial velocity (arc).
// Gravity pulls it down; once it lands it walks like a normal Botom.
class GamakichiChild : public Botom
{
public:
    // pos        — world-space spawn position (cannon mouth)
    // launchVel  — initial velocity: positive x = right, negative y = up
    GamakichiChild(sf::Vector2f pos, sf::Vector2f launchVel);

    void update(float dt) override;
};