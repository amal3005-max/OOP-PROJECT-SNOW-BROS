#pragma once

#include <SFML/Graphics.hpp>
#include "statemanager.h"
#include "Player.h"
#include "Snowball.h"
#include "Enemy.h"
#include "Botttom.h"
//#include "FlyingFooga.h"
//#include "Tornado.h"

class PlayState : public State
{
private:
    Player player1;
    Player* player2;

	static const int MAX_ENEMIES = 20;
    Enemy* enemies[MAX_ENEMIES];
	int enemyCount;
    //Enemy* enemy;
    //Enemy* bottom;

    sf::RectangleShape platforms[10];
    int platformCount;

    bool debugMode;

    static const int MAX_SNOWBALLS = 1000;
    Snowball* snowballs[MAX_SNOWBALLS];
    int snowballCount;
    bool isFPressed;
    float fireTimer;
    float fireCooldown;

public:
    PlayState(StateManager& manager);
    ~PlayState();

    void removeEnemy(int index);   // removes & deletes enemies[index]

    void handleInput(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void spawnSnowball(float x, float y, int direction);
};
