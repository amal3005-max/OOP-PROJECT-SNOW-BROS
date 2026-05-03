
#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <string>

const int MAX_LEVEL_ENEMIES = 20;
const int MAX_PLATFORMS = 20;

enum class EnemyVariant { Red, Green, Blue, Gold };


enum class LevelTheme
{
    SnowyVillage,
    IceCave,
    WinterForest,
    FrozenLake,
    DarkLair,
    VolcanicWasteland,
    HauntedCastle,
    AlienPlanet,
    StormClouds,
    FinalArena
};

struct EnemySpawn
{
    EnemyType    type;
    sf::Vector2f position;
};

struct PlatformData
{
    sf::Vector2f position;
    sf::Vector2f size;
};

struct LevelConfig
{
    int levelNumber;

    EnemySpawn   enemies[MAX_LEVEL_ENEMIES];
    int          enemyCount;

    PlatformData platforms[MAX_PLATFORMS];
    int          platformCount;

    bool hasMogera;
    bool hasGamakichi;
    bool hasGemRain;
    bool isBonusLevel;

    EnemyVariant variant;
    LevelTheme   theme;

    LevelConfig()
    {
        levelNumber = 0;
        enemyCount = 0;
        platformCount = 0;

        hasMogera = false;
        hasGamakichi = false;
        hasGemRain = false;
        isBonusLevel = false;

        variant = EnemyVariant::Red;
        theme = LevelTheme::SnowyVillage;
    }
};