#include "LevelManager.h"
//
//LevelManager::LevelManager()
//{
//    currentLevel = 0;
//    totalLevels = 10;
//
//    // ================= LEVEL 1 =================
//    levels[0].levelNumber = 1;
//
//    // Platforms (from your image)
//    levels[0].platformCount = 5;
//    levels[0].platforms[0] = { {200, 450}, {200, 15} };
//    levels[0].platforms[1] = { {450, 450}, {200, 15} };
//    levels[0].platforms[2] = { {250, 350}, {150, 15} };
//    levels[0].platforms[3] = { {500, 350}, {150, 15} };
//    levels[0].platforms[4] = { {300, 250}, {200, 15} };
//
//    // Enemies
//    levels[0].enemyCount = 2;
//    levels[0].enemies[0] = { EnemyType::Botom, {100, 400} };
//    levels[0].enemies[1] = { EnemyType::Botom, {600, 400} };
//
//    levels[0].hasMogera = false;
//    levels[0].hasGamakichi = false;
//    levels[0].hasGemRain = false;
//
//
//    // ================= LEVEL 2 =================
//    levels[1].levelNumber = 2;
//
//    levels[1].platformCount = 4;
//    levels[1].platforms[0] = { {150, 450}, {200, 15} };
//    levels[1].platforms[1] = { {450, 450}, {200, 15} };
//    levels[1].platforms[2] = { {300, 300}, {200, 15} };
//    levels[1].platforms[3] = { {300, 150}, {200, 15} };
//
//    levels[1].enemyCount = 3;
//    levels[1].enemies[0] = { EnemyType::Botom, {100, 400} };
//    levels[1].enemies[1] = { EnemyType::FlyingFoogaFog, {400, 200} };
//    levels[1].enemies[2] = { EnemyType::Botom, {650, 400} };
//
//    levels[1].hasMogera = false;
//    levels[1].hasGamakichi = false;
//    levels[1].hasGemRain = false;
//
//
//    // ================= LEVEL 5 (MOGERA) =================
//    levels[4].levelNumber = 5;
//    levels[4].platformCount = 2;
//    levels[4].platforms[0] = { {200, 400}, {400, 20} };
//    levels[4].platforms[1] = { {250, 200}, {300, 15} };
//
//    levels[4].enemyCount = 0;
//    levels[4].hasMogera = true;
//    levels[4].hasGamakichi = false;
//    levels[4].hasGemRain = false;
//
//
//    // ================= LEVEL 10 (GAMAKICHI) =================
//    levels[9].levelNumber = 10;
//    levels[9].platformCount = 1;
//    levels[9].platforms[0] = { {100, 450}, {600, 20} };
//
//    levels[9].enemyCount = 0;
//    levels[9].hasMogera = false;
//    levels[9].hasGamakichi = true;
//    levels[9].hasGemRain = true;
//}
//
//
//
//LevelConfig& LevelManager::getCurrentLevel()
//{
//    return levels[currentLevel];
//}
//
//void LevelManager::nextLevel()
//{
//    if (currentLevel < totalLevels - 1)
//        currentLevel++;
//}
//
//bool LevelManager::isLastLevel() const
//{
//    return currentLevel == totalLevels - 1;
//}

#include "LevelManager.h"
#include <cstdlib>
#include <ctime>

#include "LevelManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Shorthand to set all boolean/enum flags at once
#define SET_FLAGS(idx, mog, gama, gems, bonus, var, thm) \
    levels[idx].hasMogera    = mog;   \
    levels[idx].hasGamakichi = gama;  \
    levels[idx].hasGemRain   = gems;  \
    levels[idx].isBonusLevel = bonus; \
    levels[idx].variant      = var;   \
    levels[idx].theme        = thm;

LevelManager::LevelManager()
{

    currentLevel = 9;
    totalLevels = 10;

    srand((time(0)));


    // ── Randomly pick 2 non-boss levels as bonus levels each playthrough ─────
    // eligible indices: 0,1,2,3,5,6,7,8  (levels 1-4 and 6-9)
    int eligible[8] = { 0, 1, 2, 3, 5, 6, 7, 8 };
    for (int i = 7; i >= 6; --i)
    {
        int j = rand() % (i + 1);
        int t = eligible[i]; eligible[i] = eligible[j]; eligible[j] = t;
    }
    int bonus1 = eligible[7];
    int bonus2 = eligible[6];


    //// ── TEST ONLY LEVEL 1 BACKGROUND ──
    //if (!level1Texture.loadFromFile("Default Levels/Default Levels/lvl1.png"))
    //{
    //    std::cout << "Failed to load Level 1 background\n";
    //}

    //level1Sprite.setTexture(level1Texture);
    //level1Sprite.setPosition(0.f, 0.f);
    //sf::Vector2u textureSize = level1Texture.getSize();
    //sf::Vector2u windowSize = {800, 600};

    //level1Sprite.setScale(
    //    (float)windowSize.x / textureSize.x,
    //    (float)windowSize.y / textureSize.y
    //);

    //loadBackgrounds();
    // =========================================================================
    // LEVEL 1  — NES Floor 1
    // Symmetric two-shelf + centre top bridge.  Introductory pace.
    // Theme: Snowy Village
    // =========================================================================
    levels[0].levelNumber = 1;
    levels[0].platformCount = 0;
    // bottom row — two wide outer shelves
    levels[0].platforms[levels[0].platformCount++] = { {  00, 440}, {200, 15} };
    levels[0].platforms[levels[0].platformCount++] = { { 600, 440}, {200, 15} };
    levels[0].platforms[levels[0].platformCount++] = {{300, 440}, {200, 15}};

    // mid row — slightly narrower, inset
    levels[0].platforms[levels[0].platformCount++] = { { 150, 360}, {500, 20} };
    // upper row
    levels[0].platforms[levels[0].platformCount++] = { { 000, 280}, {350, 20} };
    levels[0].platforms[levels[0].platformCount++] = { { 450, 280}, {350, 20} };
    // top centre bridge
    levels[0].platforms[levels[0].platformCount++] = { { 200, 160}, {400, 70} };
    levels[0].platforms[levels[0].platformCount++] = { { 100, 200}, {600, 30} };

    levels[0].platforms[levels[0].platformCount++] = { { 0, 520}, {800, 15} };



    levels[0].enemyCount = 3;
    levels[0].enemies[0] = { EnemyType::Botom, {  80, 400} };
    levels[0].enemies[1] = { EnemyType::Botom, { 700, 40} };
    levels[0].enemies[2] = { EnemyType::Botom, { 350, 120} };

    SET_FLAGS(0, false, false, false, (0 == bonus1 || 0 == bonus2),
        EnemyVariant::Red, LevelTheme::SnowyVillage)

        // =========================================================================
        // LEVEL 2  — NES Floor 2
        // Staircase / offset grid rising left → right then back.
        // Theme: Ice Cave
        // =========================================================================
        levels[1].levelNumber = 2;
    levels[1].platformCount = 9;
    // bottom pair
    levels[1].platforms[0] = { {  110, 388}, {90, 130} };
    levels[1].platforms[1] = { { 110, 480}, {540, 35} };
    // ascending left stair
    levels[1].platforms[2] = { { 610, 290}, {90, 130} };
    levels[1].platforms[3] = { { 300, 390}, {400, 35} };
    
    // centre top
    levels[1].platforms[4] = { { 155, 130}, {350, 35} };
    
    // descending right stair
    levels[1].platforms[5] = { { 110, 220}, {90, 130} };
    levels[1].platforms[6] = { { 110, 310}, {400, 35} };
    // centre low shelf
    levels[1].platforms[7] = { { 610, 140}, {90, 130} };
    levels[1].platforms[8] = { { 300, 210}, {400, 35} };


    levels[1].enemyCount = 4;
    levels[1].enemies[0] = { EnemyType::Botom,          { 100, 420} };
    levels[1].enemies[1] = { EnemyType::Botom,          { 600, 420} };
    levels[1].enemies[2] = { EnemyType::FlyingFoogaFog, { 360, 170} };
    levels[1].enemies[3] = { EnemyType::Botom,          { 260, 250} };

    SET_FLAGS(1, false, false, false, (1 == bonus1 || 1 == bonus2),
        EnemyVariant::Red, LevelTheme::IceCave)

        // =========================================================================
        // LEVEL 3  — NES Floor 3
        // Symmetric W-shape — three descending mid-shelves, outer pillars.
        // Theme: Winter Forest
        // =========================================================================
        levels[2].levelNumber = 3;
    levels[2].platformCount = 16;
    // upper 3
    levels[2].platforms[0] = { { 160, 125}, {480, 50} };
    levels[2].platforms[1] = { { 200, 220}, {390, 35} };

    levels[2].platforms[2] = { { 160, 300}, {100, 130} };
    levels[2].platforms[3] = { { 550, 300}, {100, 130} };

    levels[2].platforms[4] = { {   0, 220}, {100, 35} };
    levels[2].platforms[5] = { { 700, 220}, {100, 35} };

    //lower three 
    levels[2].platforms[6] = { { 350, 300}, {95, 50} };
    levels[2].platforms[7] = { { 350, 390}, {95, 50} };

    levels[2].platforms[8] = { {   0, 300}, { 50, 40} };
    levels[2].platforms[9] = { {   0, 390}, { 50, 40} };

    levels[2].platforms[10] = { { 750, 300}, { 50, 40} };
    levels[2].platforms[11] = { { 750, 390}, { 50, 40} };

    levels[2].platforms[12] = { { 250, 470}, { 300, 40} };
    levels[2].platforms[13] = { {   0, 470}, { 150, 40} };
    levels[2].platforms[14] = { {   650, 470}, { 150, 40} };
    levels[2].platforms[15] = { {   0, 565}, { 800, 40} };


    levels[2].enemyCount = 5;
    levels[2].enemies[0] = { EnemyType::Botom,          {  50, 430} };
    levels[2].enemies[1] = { EnemyType::Botom,          { 650, 430} };
    levels[2].enemies[2] = { EnemyType::FlyingFoogaFog, { 200, 265} };
    levels[2].enemies[3] = { EnemyType::FlyingFoogaFog, { 560, 265} };
    levels[2].enemies[4] = { EnemyType::Botom,          { 360,  90} };

    SET_FLAGS(2, false, false, false, (2 == bonus1 || 2 == bonus2),
        EnemyVariant::Red, LevelTheme::WinterForest)

        // =========================================================================
        // LEVEL 4  — NES Floor 4
        // Offset multi-row grid — introduces Tornado.
        // Theme: Frozen Lake
        // =========================================================================
        levels[3].levelNumber = 4;
    levels[3].platformCount = 12;
    levels[3].platforms[0] = { { 250, 125}, {450, 50} };
    levels[3].platforms[1] = { { 650, 125}, {50, 220} };
    levels[3].platforms[2] = { { 350, 300}, {350, 50} };

    levels[3].platforms[3] = { { 100, 210}, {450, 50} };
    levels[3].platforms[4] = { { 100, 210}, {50, 140} };
    levels[3].platforms[5] = { { 100, 300}, {100, 50} };

    levels[3].platforms[6] = { {   0, 390}, {350, 50} };
    levels[3].platforms[7] = { {   0, 390}, {100, 140} };
    levels[3].platforms[8] = { {   0, 480}, {350, 50} };

    levels[3].platforms[9] = { { 450, 390}, {350, 50} };
    levels[3].platforms[10] = { { 700, 390}, {100, 140} };
    levels[3].platforms[11] = { { 450, 480}, {350, 50} };

    levels[3].enemyCount = 6;
    levels[3].enemies[0] = { EnemyType::Botom,   {  80, 420} };
    levels[3].enemies[1] = { EnemyType::Botom,   { 600, 420} };
    levels[3].enemies[2] = { EnemyType::Botom,   { 215, 355} };
    levels[3].enemies[3] = { EnemyType::Tornado,  { 460, 355} };
    levels[3].enemies[4] = { EnemyType::Botom,   { 300, 200} };
    levels[3].enemies[5] = { EnemyType::Tornado,  { 550, 120} };

    SET_FLAGS(3, false, false, false, (3 == bonus1 || 3 == bonus2),
        EnemyVariant::Red, LevelTheme::FrozenLake)

        // =========================================================================
        // LEVEL 5  — NES Floor 10  →  BOSS: Mogera
        // Open arena with wide central platform and upper perch.
        // Theme: Dark Underground Lair
        // =========================================================================
        levels[4].levelNumber = 5;
    levels[4].platformCount = 8;
    levels[4].platforms[0] = { {   0, 200}, {350, 40} }; 
    levels[4].platforms[1] = { { 160, 300}, {350, 40} }; 
    levels[4].platforms[3] = { {   0, 390}, {350, 40} };   
    levels[4].platforms[4] = { { 160, 470}, {300, 40} }; 
    levels[4].platforms[5] = { { 550, 340}, {250, 40} };
    levels[4].platforms[6] = { { 550, 390}, {250, 40} }; 
    levels[4].platforms[7] = { {   0, 560}, {800, 40} }; 


    levels[4].enemyCount = 0;
    SET_FLAGS(4, true, false, false, false,
        EnemyVariant::Red, LevelTheme::DarkLair)

        // =========================================================================
        // LEVEL 6  — NES Floor 11
        // Ascending diagonal staircase left → right (purple/volcanic theme).
        // Variant: Green  (speed x1.25, +1 hit to encase)
        // Theme: Volcanic Wasteland
        // =========================================================================
        levels[5].levelNumber = 6;
    levels[5].platformCount = 14;
    // main ascending staircase
    levels[5].platforms[0] = { { 150, 130}, {490, 45} };
    levels[5].platforms[1] = { { 300, 130}, {200, 80} };

    levels[5].platforms[2] = { { 200, 305}, {150, 135} };
    levels[5].platforms[3] = { { 450, 305}, {150, 135} };

    levels[5].platforms[4] = { {   0, 215}, {200, 40} };
    levels[5].platforms[5] = { { 600, 215}, {200, 40} };

    levels[5].platforms[6] = { {   0, 300}, {100, 40} };
    levels[5].platforms[7] = { { 700, 300}, {100, 40} };

    levels[5].platforms[8] = { {   0, 390}, {100, 40} };
    levels[5].platforms[9] = { { 700, 390}, {100, 40} };

    levels[5].platforms[10] = { {   0, 480}, {100, 40} };
    levels[5].platforms[11] = { { 700, 480}, {100, 40} };

    levels[5].platforms[12] = { { 200, 480}, {400, 40} };
    levels[5].platforms[13] = { {   0, 570}, {800, 35} };


    levels[5].enemyCount = 6;
    levels[5].enemies[0] = { EnemyType::Botom,          {  40, 450} };
    levels[5].enemies[1] = { EnemyType::FlyingFoogaFog, { 310, 270} };
    levels[5].enemies[2] = { EnemyType::FlyingFoogaFog, { 590, 150} };
    levels[5].enemies[3] = { EnemyType::Botom,          { 430, 400} };
    levels[5].enemies[4] = { EnemyType::Tornado,         { 160, 330} };
    levels[5].enemies[5] = { EnemyType::Botom,          { 370,  90} };

    SET_FLAGS(5, false, false, false, (5 == bonus1 || 5 == bonus2),
        EnemyVariant::Green, LevelTheme::VolcanicWasteland)

        // =========================================================================
        // LEVEL 7  — NES Floor 12
        // Zigzag descending — platforms alternate left/right.
        // Variant: Green → Blue boundary — use Blue here for variety
        // Theme: Haunted Castle
        // =========================================================================
        levels[6].levelNumber = 7;
    levels[6].platformCount = 14;
    // top-left anchor
    levels[6].platforms[0] = { {   0, 130}, { 250, 40} };
    levels[6].platforms[1] = { { 600, 220}, { 200, 40} };

    levels[6].platforms[2] = { { 100, 300}, {200, 40} };
    levels[6].platforms[3] = { { 350, 180}, {200, 40} };
    levels[6].platforms[4] = { { 150, 220}, {250, 40} };

    levels[6].platforms[5] = { { 100, 300}, {100, 40} };
    levels[6].platforms[6] = { { 160, 350}, {150, 40} };
    levels[6].platforms[7] = { { 250, 390}, {200, 40} };

    levels[6].platforms[8] = { {   0, 440}, {150, 40} };
    levels[6].platforms[9] = { { 100, 480}, {250, 40} };

    levels[6].platforms[10] = { { 400, 300}, {250, 40} };
    levels[6].platforms[11] = { { 600, 350}, {200, 40} };

    levels[6].platforms[12] = { { 450, 480}, {250, 40} };
    levels[6].platforms[13] = { { 650, 440}, {150, 40} };

    levels[6].enemyCount = 6;
    levels[6].enemies[0] = { EnemyType::Botom,          {  40, 110} };
    levels[6].enemies[1] = { EnemyType::Botom,          { 610, 160} };
    levels[6].enemies[2] = { EnemyType::FlyingFoogaFog, {  80, 230} };
    levels[6].enemies[3] = { EnemyType::Tornado,         { 580, 290} };
    levels[6].enemies[4] = { EnemyType::Botom,          { 270, 300} };
    levels[6].enemies[5] = { EnemyType::Botom,          { 530, 410} };

    SET_FLAGS(6, false, false, false, (6 == bonus1 || 6 == bonus2),
        EnemyVariant::Blue, LevelTheme::HauntedCastle)

        // =========================================================================
        // LEVEL 8  — NES Floor 13
        // Interlocking H-frame — dense multi-row grid.
        // Variant: Blue  (speed x1.5, +2 hits to encase)
        // Theme: Alien Planet
        // =========================================================================
        levels[7].levelNumber = 8;
    levels[7].platformCount = 12;
    // outer floor
    levels[7].platforms[0] = { { 250, 170}, { 310, 80} };
    levels[7].platforms[1] = { { 155, 215}, { 490, 40} };
    
    levels[7].platforms[2] = { {   0, 310}, {350, 40} };
    levels[7].platforms[3] = { { 100, 390}, {250, 40} };
    levels[7].platforms[4] = { { 300, 310}, {45, 125} };

    levels[7].platforms[5] = { { 455, 310}, {335, 40} };
    levels[7].platforms[6] = { { 455, 395}, {245, 40} };
    levels[7].platforms[7] = { { 455, 310}, {45, 125} };

    levels[7].platforms[8] = { {   0, 480}, {110, 40} };
    levels[7].platforms[9] = { { 690, 480}, {110, 40} };

    levels[7].platforms[10] = { { 210, 480}, {385, 40} };
    levels[7].platforms[11] = { {   0, 565}, {790, 40} };


    levels[7].enemyCount = 7;
    levels[7].enemies[0] = { EnemyType::Botom,          {  50, 450} };
    levels[7].enemies[1] = { EnemyType::Botom,          { 700, 450} };
    levels[7].enemies[2] = { EnemyType::FlyingFoogaFog, {  50, 320} };
    levels[7].enemies[3] = { EnemyType::FlyingFoogaFog, { 640, 320} };
    levels[7].enemies[4] = { EnemyType::Tornado,         { 360, 270} };
    levels[7].enemies[5] = { EnemyType::Botom,          { 120, 190} };
    levels[7].enemies[6] = { EnemyType::Botom,          { 545, 190} };

    SET_FLAGS(7, false, false, false, (7 == bonus1 || 7 == bonus2),
        EnemyVariant::Blue, LevelTheme::AlienPlanet)

        // =========================================================================
        // LEVEL 9  — NES Floor 14
        // Narrow ledges + large gaps — high-speed enemies, tight platforming.
        // Variant: Gold  (speed x1.75, +3 hits to encase)
        // Theme: Storm Clouds
        // =========================================================================
        levels[8].levelNumber = 9;
    levels[8].platformCount = 16;
    // bottom narrow ledges
    levels[8].platforms[0] = { { 205, 130}, { 395, 40} };
    levels[8].platforms[1] = { { 205, 220}, { 395, 40} };
    levels[8].platforms[2] = { { 200, 135}, { 100, 125} };
    levels[8].platforms[3] = { { 500, 135}, { 100, 125} };
    // centre low
    levels[8].platforms[4] = { { 650, 390}, {150, 40} };
    levels[8].platforms[5] = { { 450, 470}, {350, 40} };
    levels[8].platforms[6] = { { 700, 390}, {100, 125} };
    // upper tier
    levels[8].platforms[7] = { {   0, 390}, {150, 40} };
    levels[8].platforms[8] = { {   0, 470}, {350, 40} };
    levels[8].platforms[9] = { {   0, 390}, {100, 125} };

    levels[8].platforms[10] = { {  0, 220}, {100, 125} };
    levels[8].platforms[11] = { {  0, 305}, {345, 40} };
    // upper tier
    levels[8].platforms[12] = { { 700, 220}, {100, 125} };
    levels[8].platforms[13] = { { 450, 300}, {350, 40} };
    // top single
    levels[8].platforms[14] = { { 245, 390}, {300, 40} };
    levels[8].platforms[15] = { {   0, 560}, {800, 34} };


    levels[8].enemyCount = 8;
    levels[8].enemies[0] = { EnemyType::Botom,          {  60, 450} };
    levels[8].enemies[1] = { EnemyType::Botom,          { 700, 450} };
    levels[8].enemies[2] = { EnemyType::Tornado,         { 200, 415} };
    levels[8].enemies[3] = { EnemyType::FlyingFoogaFog, { 545, 415} };
    levels[8].enemies[4] = { EnemyType::Botom,          { 360, 380} };
    levels[8].enemies[5] = { EnemyType::FlyingFoogaFog, {  95, 290} };
    levels[8].enemies[6] = { EnemyType::Tornado,         { 630, 290} };
    levels[8].enemies[7] = { EnemyType::Botom,          { 395, 210} };

    SET_FLAGS(8, false, false, false, (8 == bonus1 || 8 == bonus2),
        EnemyVariant::Gold, LevelTheme::StormClouds)

        // =========================================================================
        // LEVEL 10  — NES Floor 20  →  BOSS: Gamakichi
        // Wide open final arena — side tactical ledges for player.
        // hasGemRain = true so gems fall on boss defeat.
        // Theme: Final Arena
        // =========================================================================
        levels[9].levelNumber = 10;
    levels[9].platformCount = 6;
    levels[9].platforms[0] = { { 100, 260}, {580, 40} };   // main arena floor
    levels[9].platforms[1] = { {   0, 350}, {290, 30} };   // left tactical ledge
    levels[9].platforms[2] = { { 495, 350}, {310, 30} };   // right tactical ledge
    levels[9].platforms[3] = { { 100, 435}, { 90, 30} };   // upper left
    levels[9].platforms[4] = { { 595, 435}, { 90, 30} };   // upper right
    levels[9].platforms[5] = { {   0, 510}, {800, 85} };   // upper right

    levels[9].enemyCount = 0;
    SET_FLAGS(9, false, true, true, false,
        EnemyVariant::Red, LevelTheme::FinalArena)

      
    //loadBackgrounds();
}

LevelConfig& LevelManager::getCurrentLevel()
{
    return levels[currentLevel];
}

void LevelManager::nextLevel()
{
    if (currentLevel < totalLevels - 1)
        currentLevel++;
}

bool LevelManager::isLastLevel() const
{
    return currentLevel == totalLevels - 1;
}
//void LevelManager::drawBackground(sf::RenderWindow& window)
//{
//    backgroundSprite.setTexture(backgroundTextures[currentLevel]);
//
//    sf::Vector2u textureSize = backgroundTextures[currentLevel].getSize();
//    sf::Vector2u windowSize = window.getSize();
//
//    backgroundSprite.setScale(
//        (float)windowSize.x / textureSize.x,
//        (float)windowSize.y / textureSize.y
//    );
//
//    backgroundSprite.setPosition(0.f, 0.f);
//
//    window.draw(backgroundSprite);
//}
// 

void LevelManager::drawBackground(sf::RenderWindow& window)
{
    //if (lastRenderedLevel != currentLevel)
    //{
    //    backgroundSprite.setTexture(backgroundTextures[currentLevel], true);
    //    lastRenderedLevel = currentLevel;
    //}
    backgroundSprite.setTexture(backgroundTextures[currentLevel], true);
    lastRenderedLevel = currentLevel;
    sf::Vector2u textureSize = backgroundTextures[currentLevel].getSize();
    sf::Vector2u windowSize = window.getSize();

    backgroundSprite.setScale(
        (float)windowSize.x / textureSize.x,
        (float)windowSize.y / textureSize.y
    );

    backgroundSprite.setPosition(0.f, 0.f);

    window.draw(backgroundSprite);
    //if (backgroundTextures[currentLevel].getSize().x == 0) return; // skip if not loaded

    //std::cout << "Drawing background for level " << currentLevel << " size: "
    //    << backgroundTextures[currentLevel].getSize().x << "x"
    //    << backgroundTextures[currentLevel].getSize().y << std::endl;
}
//void LevelManager::drawBackground(sf::RenderWindow& window)
//{
//    if (currentLevel == 0)
//    {
//        window.draw(level1Sprite);
//    }
//}



void LevelManager::loadBackgrounds()
{
    for (int i = 0; i < totalLevels; i++)
    {
        std::string path;

        switch (levels[i].theme)
        {
        case LevelTheme::SnowyVillage:      path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl1.png"; break;
        case LevelTheme::IceCave:           path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl2.png"; break;
        case LevelTheme::WinterForest:      path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl3.png"; break;
        case LevelTheme::FrozenLake:        path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl4.png"; break;
        case LevelTheme::DarkLair:          path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl10.png"; break;
        case LevelTheme::VolcanicWasteland: path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl6.png"; break;
        case LevelTheme::HauntedCastle:     path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl7.png"; break;
        case LevelTheme::AlienPlanet:       path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl8.png"; break;
        case LevelTheme::StormClouds:       path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl9.png"; break;
        case LevelTheme::FinalArena:        path = "C:/Users/Amal Asif/Downloads/SFML_VS_Setup_2026 (1)/SFML_VS_Setup_2026/SFML_VS_Setup_2026/Default Levels/Default Levels/lvl20.png"; break;
        }

        if (!backgroundTextures[i].loadFromFile(path))
        {
            std::cout << "Failed to load: " << path << std::endl;
        }
    }
}