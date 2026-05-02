
#pragma once

#include <SFML/Graphics.hpp>
#include "statemanager.h"
#include "Player.h"
#include "Snowball.h"
#include "Enemy.h"
#include "Botttom.h"
#include "FlyingFooga.h"
#include "Tornado.h"
#include "Projectile.h"
#include "Knife.h"
#include "Mogera.h"
#include "Gamakichi.h"
#include "LevelManager.h"
#include "SoundManager.h"    // ← ADD at the top of PlayState.cpp

class PlayState : public State
{
private:
    Player player1;
    Player* player2;

	static const int MAX_ENEMIES = 50;
    Enemy* enemies[MAX_ENEMIES];
	int enemyCount;

    Mogera* mogera = nullptr;
    Gamakichi* gamakichi = nullptr;

    LevelManager levelManager;
    sf::RectangleShape platforms[20];
    int platformCount;

    bool debugMode;

    static const int MAX_SNOWBALLS = 1000;
    Snowball* snowballs[MAX_SNOWBALLS];
    int snowballCount;
    static const int MAX_PROJECTILES = 200;
    Projectile* projectiles[MAX_PROJECTILES];
    int projectileCount;

    bool isFPressed;
    float fireTimer;
    float fireCooldown;

    sf::Font font;
    sf::Text livesText1;
    sf::Text livesText2;
    bool gameOver = false;

    float mogeraSpawnTimer = 0.f;

    // PlayState.h — add these members
    int totalEnemiesDefeated = 0;
    int totalScore = 0;

private:
    void loadLevel();
public:
    PlayState(StateManager& manager);
    ~PlayState();

    void removeEnemy(int index);  

    void handleInput(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void spawnSnowball(float x, float y, int direction);
    void spawnKnife(sf::Vector2f pos, sf::Vector2f dir);

};
