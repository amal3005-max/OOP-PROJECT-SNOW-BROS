#pragma once
#include "LevelConfig.h"

const int MAX_LEVELS = 30;

class LevelManager
{
private:
    LevelConfig levels[MAX_LEVELS];
    int totalLevels;
    int currentLevel;

    sf::Texture backgroundTextures[MAX_LEVELS];
    sf::Sprite  backgroundSprite;

    int lastRenderedLevel = -1;
public:
    LevelManager();

    LevelConfig& getCurrentLevel();
    void nextLevel();
    bool isLastLevel()   const;
    int getCurrentLevelIndex() const { return currentLevel; }
    int getTotalLevels() const { return totalLevels; }
    void drawBackground(sf::RenderWindow& window);
    void loadBackgrounds();

};
