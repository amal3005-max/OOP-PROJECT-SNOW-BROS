#pragma once
#include "Enemy.h"
class Botom : public SimpleEnemy 
{
protected:
	sf::Vector2f direction;
	float decisionTimer;
    float decisionInterval;

    bool movingLeft;

    float gravity;

	float jumpStrength;
	float jumpCooldown;
	float jumpTimer;

	float edgeJumpTimer;
	float jumpTimerLocal;
public:
	Botom (sf::Vector2f p);
	void reverse();
	void update(float dt) override;
	void draw(sf::RenderWindow& window, bool debugMode) override;
};
