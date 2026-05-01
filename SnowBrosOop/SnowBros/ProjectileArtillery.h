//#include "Projectile.h"
//class ProjectileArtillery:public Projectile
//{
//	sf::Vector2f direction;
//public:
//	ProjectileArtillery(sf::Vector2f position, sf::Vector2f velocity, float damage, bool firedbyenemy);
//	void update(float dt) override;
//	void draw(sf::RenderWindow& window) override;
//	void ProjectileHit() override;
//};
//#pragma once
//#include "Projectile.h"
//
//// Artillery rocket fired by Gamakichi.
//// Travels in a straight line, explodes (becomes invisible) on hitting
//// screen edges, platforms, or the player.  PlayState handles player-hit
//// detection the same way it does for Knife.
//class ProjectileArtillery : public Projectile
//{
//private:
//    sf::RectangleShape body;
//    bool exploded;
//
//public:
//    ProjectileArtillery(sf::Vector2f position, sf::Vector2f velocity);
//
//    void update(float dt) override;
//    void draw(sf::RenderWindow& window) override;
//    void ProjectileHit() override;
//
//    bool hasExploded() const { return exploded; }
//};

#pragma once
#include "Projectile.h"

class ProjectileArtillery : public Projectile
{
private:
    sf::RectangleShape body;

    bool exploded;
    float explosionTimer;

public:
    ProjectileArtillery(sf::Vector2f position, sf::Vector2f velocity);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void ProjectileHit() override;

    bool hasExploded() const { return exploded; }
};

#pragma once
#include <SFML/Graphics.hpp>
//#include "ProjectileArtillery.h"

class ArtilleryEmitter
{
private:
    sf::Vector2f position;

    float timer;
    float fireRate;

public:
    ArtilleryEmitter(sf::Vector2f pos, float rate);

    void update(float dt, sf::Vector2f target,
        ProjectileArtillery** out, int& outCount);

    void draw(sf::RenderWindow& window);
};