
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
private:
    ChildType type;

public:
    MogeraChild(sf::Vector2f mogeraPosition, sf::Vector2f playerPosition, ChildType type);
    
};

class GamakichiChild : public Botom
{
public:
    GamakichiChild(sf::Vector2f pos, sf::Vector2f launchVel);
    void update(float dt) override;
};