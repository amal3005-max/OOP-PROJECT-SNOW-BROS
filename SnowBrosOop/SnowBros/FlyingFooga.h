#pragma once
#include "Botttom.h"

class FlyingFooga : public Botom
{
protected:
	bool isFlying;

	float flightTimer;
	float groundTimer;

	sf::Vector2f flightDir;

	float flightSpeedMultiplier;

public:
	FlyingFooga(sf::Vector2f p);

	void update(float dt) override;
	void draw(sf::RenderWindow& window, bool debugMode);
};