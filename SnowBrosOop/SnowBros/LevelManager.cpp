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

    currentLevel = 0;
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


    // ── TEST ONLY LEVEL 1 BACKGROUND ──
    if (!level1Texture.loadFromFile("Default Levels/Default Levels/lvl1.png"))
    {
        std::cout << "Failed to load Level 1 background\n";
    }

    level1Sprite.setTexture(level1Texture);
    level1Sprite.setPosition(0.f, 0.f);
    sf::Vector2u textureSize = level1Texture.getSize();
    sf::Vector2u windowSize = {800, 600};

    level1Sprite.setScale(
        (float)windowSize.x / textureSize.x,
        (float)windowSize.y / textureSize.y
    );

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
    levels[1].platformCount = 8;
    // bottom pair
    levels[1].platforms[0] = { {  80, 460}, {190, 15} };
    levels[1].platforms[1] = { { 530, 460}, {190, 15} };
    // ascending left stair
    levels[1].platforms[2] = { {  80, 370}, {150, 15} };
    levels[1].platforms[3] = { { 240, 290}, {150, 15} };
    // centre top
    levels[1].platforms[4] = { { 330, 210}, {140, 15} };
    // descending right stair
    levels[1].platforms[5] = { { 430, 290}, {150, 15} };
    levels[1].platforms[6] = { { 570, 370}, {150, 15} };
    // centre low shelf
    levels[1].platforms[7] = { { 305, 430}, {190, 15} };


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
    levels[2].platformCount = 9;
    // outer floor shelves
    levels[2].platforms[0] = { {  30, 470}, {140, 15} };
    levels[2].platforms[1] = { { 630, 470}, {140, 15} };
    // inner dip
    levels[2].platforms[2] = { { 200, 430}, {120, 15} };
    levels[2].platforms[3] = { { 480, 430}, {120, 15} };
    // centre floor rise
    levels[2].platforms[4] = { { 310, 395}, {180, 15} };
    // mid tier outer
    levels[2].platforms[5] = { {  80, 305}, {160, 15} };
    levels[2].platforms[6] = { { 560, 305}, {160, 15} };
    // mid tier inner
    levels[2].platforms[7] = { { 265, 220}, {270, 15} };
    // top
    levels[2].platforms[8] = { { 300, 130}, {200, 15} };

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
    levels[3].platformCount = 9;
    levels[3].platforms[0] = { {  60, 460}, {170, 15} };
    levels[3].platforms[1] = { { 570, 460}, {170, 15} };
    levels[3].platforms[2] = { { 200, 395}, {155, 15} };
    levels[3].platforms[3] = { { 445, 395}, {155, 15} };
    levels[3].platforms[4] = { {  60, 320}, {190, 15} };
    levels[3].platforms[5] = { { 550, 320}, {190, 15} };
    levels[3].platforms[6] = { { 255, 240}, {290, 15} };
    levels[3].platforms[7] = { { 100, 160}, {170, 15} };
    levels[3].platforms[8] = { { 530, 160}, {170, 15} };

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
    levels[4].platformCount = 3;
    levels[4].platforms[0] = { { 150, 420}, {500, 20} };   // main arena floor
    levels[4].platforms[1] = { { 250, 280}, {300, 15} };   // upper shelf
    levels[4].platforms[2] = { { 350, 160}, {100, 15} };   // top perch

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
    levels[5].platformCount = 10;
    // main ascending staircase
    levels[5].platforms[0] = { {  20, 490}, {120, 15} };
    levels[5].platforms[1] = { {  90, 430}, {120, 15} };
    levels[5].platforms[2] = { { 180, 370}, {120, 15} };
    levels[5].platforms[3] = { { 290, 310}, {120, 15} };
    levels[5].platforms[4] = { { 420, 250}, {120, 15} };
    levels[5].platforms[5] = { { 560, 190}, {120, 15} };
    // return lower staircase
    levels[5].platforms[6] = { { 540, 380}, {110, 15} };
    levels[5].platforms[7] = { { 410, 440}, {110, 15} };
    levels[5].platforms[8] = { { 270, 490}, {110, 15} };
    // small top perch
    levels[5].platforms[9] = { { 340, 130}, {120, 15} };

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
    levels[6].platformCount = 9;
    // top-left anchor
    levels[6].platforms[0] = { {  20, 150}, {190, 15} };
    // zigzag down
    levels[6].platforms[1] = { { 590, 200}, {190, 15} };
    levels[6].platforms[2] = { {  60, 270}, {175, 15} };
    levels[6].platforms[3] = { { 565, 330}, {175, 15} };
    levels[6].platforms[4] = { { 100, 395}, {190, 15} };
    levels[6].platforms[5] = { { 510, 450}, {190, 15} };
    // centre connector shelves
    levels[6].platforms[6] = { { 250, 340}, {130, 15} };
    levels[6].platforms[7] = { { 420, 270}, {130, 15} };
    levels[6].platforms[8] = { { 300, 480}, {200, 15} };

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
    levels[7].platformCount = 10;
    // outer floor
    levels[7].platforms[0] = { {  30, 490}, { 90, 15} };
    levels[7].platforms[1] = { { 680, 490}, { 90, 15} };
    // lower inner
    levels[7].platforms[2] = { { 160, 450}, {200, 15} };
    levels[7].platforms[3] = { { 440, 450}, {200, 15} };
    // mid outer
    levels[7].platforms[4] = { {  30, 360}, {150, 15} };
    levels[7].platforms[5] = { { 620, 360}, {150, 15} };
    // mid centre
    levels[7].platforms[6] = { { 260, 310}, {280, 15} };
    // upper outer
    levels[7].platforms[7] = { { 100, 230}, {175, 15} };
    levels[7].platforms[8] = { { 525, 230}, {175, 15} };
    // top bridge
    levels[7].platforms[9] = { { 290, 150}, {220, 15} };

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
    levels[8].platformCount = 10;
    // bottom narrow ledges
    levels[8].platforms[0] = { {  40, 490}, { 80, 15} };
    levels[8].platforms[1] = { { 680, 490}, { 80, 15} };
    levels[8].platforms[2] = { { 180, 455}, { 95, 15} };
    levels[8].platforms[3] = { { 525, 455}, { 95, 15} };
    // centre low
    levels[8].platforms[4] = { { 330, 420}, {140, 15} };
    // mid tier
    levels[8].platforms[5] = { {  75, 330}, {115, 15} };
    levels[8].platforms[6] = { { 610, 330}, {115, 15} };
    // upper tier
    levels[8].platforms[7] = { { 200, 245}, {150, 15} };
    levels[8].platforms[8] = { { 450, 245}, {150, 15} };
    // top single
    levels[8].platforms[9] = { { 320, 155}, {160, 15} };

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
    levels[9].platformCount = 5;
    levels[9].platforms[0] = { { 100, 460}, {600, 20} };   // main arena floor
    levels[9].platforms[1] = { {  30, 300}, {140, 15} };   // left tactical ledge
    levels[9].platforms[2] = { { 630, 300}, {140, 15} };   // right tactical ledge
    levels[9].platforms[3] = { { 200, 190}, {180, 15} };   // upper left
    levels[9].platforms[4] = { { 420, 190}, {180, 15} };   // upper right

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
//    // scale to window
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
void LevelManager::drawBackground(sf::RenderWindow& window)
{
    if (currentLevel == 0)
    {
        window.draw(level1Sprite);
    }
}


//
//
//void LevelManager::loadBackgrounds()
//{
//    for (int i = 0; i < totalLevels; i++)
//    {
//        std::string path;
//
//        switch (levels[i].theme)
//        {
//        case LevelTheme::SnowyVillage:      path = "Default Levels / Default Levels / lvl1.png"; break;
//        case LevelTheme::IceCave:           path = "Default Levels / Default Levels / lvl2.png"; break;
//        case LevelTheme::WinterForest:      path = "Default Levels / Default Levels / lvl3.png"; break;
//        case LevelTheme::FrozenLake:        path = "Default Levels / Default Levels / lvl4.png"; break;
//        case LevelTheme::DarkLair:          path = "Default Levels / Default Levels / lvl5.png"; break;
//        case LevelTheme::VolcanicWasteland: path = "Default Levels / Default Levels / lvl6.png"; break;
//        case LevelTheme::HauntedCastle:     path = "Default Levels / Default Levels / lvl7.png"; break;
//        case LevelTheme::AlienPlanet:       path = "Default Levels / Default Levels / lvl8.png"; break;
//        case LevelTheme::StormClouds:       path = "Default Levels / Default Levels / lvl9.png"; break;
//        case LevelTheme::FinalArena:        path = "Default Levels / Default Levels / lvl10.png"; break;
//        }
//
//        if (!backgroundTextures[i].loadFromFile(path))
//        {
//            std::cout << "Failed to load: " << path << std::endl;
//        }
//    }
//}