#pragma once

#include "Enemy.h"
#include "MogeraChild.h"
//class Mogera :public Enemy 
//{
//private:
//	int childCount;
//	MogeraChild* children[20];
//	float spawnTime;
//	void spawnChild(sf::Vector2f playerPosition);
//public:
//	Mogera(sf::Vector2f p);
//	void update(float dt,sf::Vector2f playerPosition);
//	void draw(sf::RenderWindow& window);
//	
//};
//
//#pragma once
//#include "Enemy.h"
//#include "MogeraChild.h"
//
//class Mogera : public SimpleEnemy
//{
//private:
//    int health;
//    float spawnTimer;
//    float spawnInterval;
//
//    static const int MAX_CHILDREN = 20;
//    MogeraChild* children[MAX_CHILDREN];
//    int childCount;
//
//    //void spawnChild(sf::Vector2f playerPosition);
//
//public:
//    Mogera(sf::Vector2f pos);
//    MogeraChild* spawnChild(sf::Vector2f playerPosition);
//
//    void update(float dt, sf::Vector2f playerPosition);
//    void draw(sf::RenderWindow& window, bool debugMode);
//
//    virtual void setTarget(sf::Vector2f playerPos) {};
//
//    bool isAlive() const override;
//};

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