//#include "FlyingFooga.h"
//class Tornado : public FlyingFooga
//{
//protected:
//	float knifeTimer;
//public:
//	Tornado(sf::Vector2f p); // p=position
//	void update(float dt);
//	void draw(sf::RenderWindow &window);
//	
//
//};

#pragma once
#include "FlyingFooga.h"

class Tornado : public FlyingFooga
{
protected:
    float knifeTimer;
    float knifeCooldown;

    float teleportTimer;
    float teleportCooldown;

public:
    Tornado(sf::Vector2f p);

    void update(float dt) override;
    void draw(sf::RenderWindow& window, bool debugMode) override;
};