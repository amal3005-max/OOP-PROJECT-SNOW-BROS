//#include "PlayState.h"
//#include "MenuState.h"
//#include "Player.h"
//
//PlayState::PlayState(StateManager& manager)
//    : State(manager), player1(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up), player2(nullptr)
//{
//    if (manager.getMode() == GameMode::TwoPlayer)
//    {
//        player2 = new Player(sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8);
//    }
//
//	enemyCount = 0;
//    for (int i = 0; i < MAX_ENEMIES; ++i)
//    {
//        enemies[i] = nullptr;
//    }
//
//    //snowball setup
//    isFPressed = false;
//    fireTimer = 0.0f;
//    fireCooldown = 0.3f;
//    snowballCount = 0;
//    for (int i = 0; i < MAX_SNOWBALLS; ++i)
//    {
//        snowballs[i] = nullptr;
//    }
//    projectileCount = 0;
//    for (int i = 0; i < MAX_PROJECTILES; ++i)
//    {
//        projectiles[i] = nullptr;
//    }
//
//    //platform setup
//    platforms[0].setSize(sf::Vector2f(200, 15));
//    platforms[0].setPosition(200, 450);
//    platforms[0].setFillColor(sf::Color::White);
//    platformCount = 1;
//
//    //hitbox debug 
//    debugMode = false;
//
//   
//    //enemy = new Botom(sf::Vector2f(300, 500));
//    enemies[enemyCount++] = new Botom(sf::Vector2f(300, 400));
//    //enemies[enemyCount++] = new Botom(sf::Vector2f(500, 400));
//    //enemies[enemyCount++] = new Botom(sf::Vector2f(700, 400));
//    enemies[enemyCount++] = new FlyingFooga(sf::Vector2f(500, 200));
//    enemies[enemyCount++] = new Tornado(sf::Vector2f(200, 200));
//
//    //enemyCount = 2;
//    //enemies[enemyCount++] = new FlyingFooga(sf::Vector2f(500, 150));
//
//}
//
//PlayState::~PlayState()
//{
//    delete player2;
//    for (int i = 0; i < snowballCount; ++i)
//    {
//        delete snowballs[i];
//    }
//    for (int i = 0; i < enemyCount; ++i)
//    {
//        delete enemies[i];
//    }
//}
//
//void PlayState::removeEnemy(int index)
//{
//    delete enemies[index];
//    enemies[index] = enemies[--enemyCount];
//    enemies[enemyCount] = nullptr;
//}
//
//void PlayState::handleInput(sf::Event& event)
//{
//    if (event.type == sf::Event::KeyPressed)
//    {
//        if (event.key.code == sf::Keyboard::Escape)
//        {
//            manager.changeState(new MenuState(manager));
//        }
//        if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::H)
//        {
//            debugMode = !debugMode;
//        }
//    }
//    //firing on press
//    if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
//    {
//        if (!isFPressed)
//        {
//            isFPressed = true;
//            fireTimer = 0.0f; 
//            sf::FloatRect b = player1.getBounds();
//            spawnSnowball(b.left + b.width / 2.f, b.top + b.height / 2.f, player1.direction);
//        }
//
//    }
//    //firing for pressing 
//    if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
//    {
//        isFPressed = false;
//        fireTimer = 0.0f;
//    }
//}
//
//void PlayState::update(float deltaTime)
//{
//    player1.handleInput();
//    player1.update(deltaTime);
//    if (player2 != nullptr)
//    {
//        player2->handleInput();
//        player2->update(deltaTime);
//    }
//
//    for (int i = 0; i < platformCount; i++)
//    {
//        player1.checkPlatformCollision(platforms[i]);
//
//        if (player2 != nullptr)
//        {
//            player2->checkPlatformCollision(platforms[i]);
//        }
//        for (int j = 0; j < enemyCount; ++j)
//        {
//            if (enemies[j])
//            {
//                enemies[j]->checkPlatformCollision(platforms[i]);
//            }
//        }
//    }
//    // updating snowballs
//    for (int i = 0; i < snowballCount; )
//    {
//        if (!snowballs[i])
//        {
//            ++i;
//            continue;
//        }
//        snowballs[i]->update(deltaTime);
//        sf::FloatRect b = snowballs[i]->getBounds();
//
//        bool expired = snowballs[i]->isWrapped() && snowballs[i]->getLifeTime() >= snowballs[i]->getMaxLifeTime();
//        if (expired)
//        {
//            delete snowballs[i];
//            snowballs[i] = snowballs[--snowballCount];
//            snowballs[snowballCount] = nullptr;
//        }
//        else ++i;
//    }
//    for (int i = 0; i < projectileCount; )
//    {
//        if (!projectiles[i])
//        {
//            ++i;
//            continue;
//        }
//
//        projectiles[i]->update(deltaTime);
//
//        if (!projectiles[i]->isVisible())
//        {
//            delete projectiles[i];
//            projectiles[i] = projectiles[--projectileCount];
//            projectiles[projectileCount] = nullptr;
//        }
//
//        else
//            ++i;
//
//    }
//
//    // (duplicate push-to-start rolling block removed)
//
//    // update enemy once per frame so rolling/bounce logic runs even if there are no snowballs
//    for (int e = 0; e < enemyCount; ++e)
//        if (enemies[e]) enemies[e]->update(deltaTime);
//
//    for (int e = 0; e < enemyCount; )
//    {
//        if (!enemies[e])
//        {
//            ++e;
//            continue;
//        }
//
//        for (int i = 0; i < snowballCount; )
//        {
//            if (!snowballs[i])
//            {
//                ++i;
//                continue;
//            }
//
//            if (snowballs[i]->getBounds().intersects(enemies[e]->getBounds()))
//            {
//                enemies[e]->hitBySnowball(1.0f);
//
//                delete snowballs[i];
//                
//                snowballs[i] = snowballs[--snowballCount];
//                snowballs[snowballCount] = nullptr;
//            }
//            else ++i;
//        }
//        if (!enemies[e]->isAlive())
//        {
//            removeEnemy(e); 
//        }
//        else
//        {
//            ++e;
//        }
//    }
//    // ------------------- TORNADO KNIFE LOGIC -------------------
//    for (int e = 0; e < enemyCount; ++e)
//    {
//        Tornado* t = dynamic_cast<Tornado*>(enemies[e]);
//
//        if (!t) continue;
//
//        // only attack while flying (optional but matches spec)
//        if (!t->isFlyingMode()) continue;
//
//        t->knifeTimer += deltaTime;
//
//        if (t->knifeTimer >= 3.0f)
//        {
//            t->knifeTimer = 0.f;
//
//            sf::Vector2f enemyPos = t->getPosition();
//            sf::Vector2f playerPos = player1.getPosition();
//
//            sf::Vector2f dir = playerPos - enemyPos;
//
//            float mag = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//            if (mag != 0)
//                dir /= mag;  // normalize
//
//            spawnKnife(enemyPos + sf::Vector2f(20, 20), dir);
//        }
//
//    }
//
//    for (int i = 0; i < enemyCount; ++i)
//    {
//        if (!enemies[i] || !enemies[i]->isrolling()) continue;
//
//        float x = enemies[i]->getBounds().left;
//        float y = enemies[i]->getBounds().top;
//
//        bool atBottom = (y >= 500.f);
//        bool atEdge = (x <= 0.f || x + enemies[i]->getBounds().width >= 800.f);
//
//        if (atBottom && atEdge)
//        {
//            // trigger chain reaction
//            for (int j = 0; j < enemyCount; ++j)
//            {
//                if (i == j || !enemies[j]) continue;
//
//                // kill all nearby enemies (simple version: kill all)
//                enemies[j]->hitBySnowball(5.0f);
//            }
//
//            // destroy the rolling one too
//            enemies[i]->hitBySnowball(5.0f);
//        }
//    }
//
//
//    for (int e = 0; e < enemyCount; ++e)
//    {
//        if (!enemies[e] || !enemies[e]->isPushable()) continue;
//
//        bool p1hit = enemies[e]->getBounds().intersects(player1.getBounds());
//        bool p2hit = player2 &&
//            enemies[e]->getBounds().intersects(player2->getBounds());
//
//        if (p1hit && enemies[e]->isPushable())
//        {
//            enemies[e]->direction = player1.direction;
//            if (!enemies[e]->isrolling())
//                enemies[e]->startRolling(player1.direction);
//            enemies[e]->push(player1.direction * 20.f);
//        }
//        if (p2hit)
//        {
//            enemies[e]->direction = player2->direction;
//            if (!enemies[e]->isrolling())
//                enemies[e]->startRolling(player2->direction);
//            enemies[e]->push(player2->direction * 20.f);
//        }
//    }
//
//    // auto fire handling
//    if (isFPressed)
//    {
//        fireTimer += deltaTime;
//        if (fireTimer >= fireCooldown)
//        {
//            sf::FloatRect b = player1.getBounds();
//            spawnSnowball(b.left + b.width / 2.f, b.top + b.height / 2.f, player1.direction);
//            fireTimer = 0.0f;
//        }
//    }
//    for (int i = 0; i < enemyCount; ++i)
//    {
//        if (!enemies[i] || !enemies[i]->isrolling()) continue;
//
//        for (int j = 0; j < enemyCount; ++j)
//        {
//            if (i == j || !enemies[j]) continue;
//
//            if (enemies[i]->getBounds().intersects(enemies[j]->getBounds()))
//            {
//                // hit second enemy
//                enemies[j]->hitBySnowball(2.0f); // stronger impact
//
//                // optional: knockback effect
//                enemies[j]->push(enemies[i]->direction * 10.f);
//            }
//        }
//    }
//
//}
//
//void PlayState::render(sf::RenderWindow& window)
//{
//    window.clear(sf::Color::Black);
//
//    player1.draw(window, debugMode);
//    if (player2 != nullptr)
//    {
//        player2->draw(window, debugMode);
//    }
//
//    for (int i = 0; i < platformCount; i++)
//    {
//        window.draw(platforms[i]);
//    }
//
//    for (int i = 0; i < snowballCount; ++i)
//    {
//        if (snowballs[i])
//        {
//            snowballs[i]->draw(window, debugMode);
//        }
//    }
//    for (int i = 0; i < projectileCount; ++i)
//    {
//        if (projectiles[i])
//            projectiles[i]->draw(window);
//    }
//
//    for (int e = 0; e < enemyCount; ++e)
//    {
//        if (enemies[e])
//        {
//            enemies[e]->draw(window, debugMode);
//        }
//    }
//   
//}
//
//void PlayState::spawnSnowball(float x, float y, int direction)
//{
//    if (snowballCount < MAX_SNOWBALLS)
//    {
//        snowballs[snowballCount++] = new Snowball(x, y, direction);
//    }
//}
//void PlayState::spawnKnife(sf::Vector2f pos, sf::Vector2f dir)
//{
//    if (projectileCount < MAX_PROJECTILES)
//    {
//        projectiles[projectileCount++] = new Knife(pos, dir);
//    }
//}

#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOver.h"
#include "Player.h"
#include <cmath>

PlayState::PlayState(StateManager& manager)
    : State(manager),
    player1(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up),
    player2(nullptr)
{
    if (manager.getMode() == GameMode::TwoPlayer)
    {
        player2 = new Player(sf::Keyboard::Numpad4,
            sf::Keyboard::Numpad6,
            sf::Keyboard::Numpad8);
    }

    enemyCount = 0;
    for (int i = 0; i < MAX_ENEMIES; ++i)
        enemies[i] = nullptr;

    snowballCount = 0;
    for (int i = 0; i < MAX_SNOWBALLS; ++i)
        snowballs[i] = nullptr;

    projectileCount = 0;
    for (int i = 0; i < MAX_PROJECTILES; ++i)
        projectiles[i] = nullptr;

    isFPressed = false;
    fireTimer = 0.f;
    fireCooldown = 0.3f;

    platforms[0].setSize(sf::Vector2f(200, 15));
    platforms[0].setPosition(200, 450);
    platforms[0].setFillColor(sf::Color::White);
    platformCount = 1;

    debugMode = false;

    font.loadFromFile("arcade.otf"); // make sure file exists in project folder

    livesText1.setFont(font);
    livesText1.setCharacterSize(20);
    livesText1.setFillColor(sf::Color::White);
    livesText1.setPosition(10.f, 10.f);

    livesText2.setFont(font);
    livesText2.setCharacterSize(20);
    livesText2.setFillColor(sf::Color::White);
    livesText2.setPosition(10.f, 40.f);

    enemies[enemyCount++] = new Botom(sf::Vector2f(100, 400));
    //enemies[enemyCount++] = new FlyingFooga(sf::Vector2f(500, 200));
    //enemies[enemyCount++] = new Tornado(sf::Vector2f(800, 200));
}

PlayState::~PlayState()
{
    delete player2;

    for (int i = 0; i < snowballCount; ++i)
        delete snowballs[i];

    for (int i = 0; i < projectileCount; ++i)
        delete projectiles[i];

    for (int i = 0; i < enemyCount; ++i)
        delete enemies[i];
}

void PlayState::removeEnemy(int index)
{
    delete enemies[index];
    enemies[index] = enemies[--enemyCount];
    enemies[enemyCount] = nullptr;
}

// ---------------- INPUT ----------------
void PlayState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            manager.changeState(new MenuState(manager));

        if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::H)
            debugMode = !debugMode;
    }

    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
    {
        if (!isFPressed)
        {
            isFPressed = true;
            fireTimer = 0.f;

            sf::FloatRect b = player1.getBounds();
            spawnSnowball(b.left + b.width / 2.f,
                b.top + b.height / 2.f,
                player1.direction);
        }
    }

    if (event.type == sf::Event::KeyReleased &&
        (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
    {
        isFPressed = false;
        fireTimer = 0.f;
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            manager.pauseState(new PauseState(manager));
        }
    }
}

// ---------------- UPDATE ----------------
void PlayState::update(float deltaTime)
{
    player1.handleInput();
    player1.update(deltaTime);

    if (player2)
    {
        player2->handleInput();
        player2->update(deltaTime);
    }

    // ---------------- PLATFORM COLLISION ----------------
    for (int i = 0; i < platformCount; i++)
    {
        player1.checkPlatformCollision(platforms[i]);
        if (player2) player2->checkPlatformCollision(platforms[i]);

        for (int j = 0; j < enemyCount; j++)
            if (enemies[j])
                enemies[j]->checkPlatformCollision(platforms[i]);
    }

    // ---------------- SNOWBALL UPDATE ----------------
    for (int i = 0; i < snowballCount; )
    {
        if (!snowballs[i]) { ++i; continue; }

        snowballs[i]->update(deltaTime);

        bool expired =
            snowballs[i]->isWrapped() &&
            snowballs[i]->getLifeTime() >= snowballs[i]->getMaxLifeTime();

        if (expired)
        {
            delete snowballs[i];
            snowballs[i] = snowballs[--snowballCount];
            snowballs[snowballCount] = nullptr;
        }
        else ++i;
    }

    // ---------------- PROJECTILE (KNIFE) UPDATE ----------------
    for (int i = 0; i < projectileCount; )
    {
        if (!projectiles[i]) { ++i; continue; }

        projectiles[i]->update(deltaTime);

        // ===== PLAYER HIT BY KNIFE =====
        if (projectiles[i]->getBounds().intersects(player1.getBounds()))
        {
            if (!player1.isInvincible)
            {
                player1.loseLife();
				if (player1.loseLife())
                {
                    //manager.changeState(new MenuState(manager)); // GAME OVER
                    gameOver = true;
                }
            }
            delete projectiles[i];
            projectiles[i] = projectiles[--projectileCount];
            projectiles[projectileCount] = nullptr;
            continue;
        }

        if (player2 &&
            projectiles[i]->getBounds().intersects(player2->getBounds()))
        {
            if (!player2->isInvincible)
            {
                player2->loseLife();
                if (player2->loseLife())
                {
                    gameOver = true;
                }
            }

            delete projectiles[i];
            projectiles[i] = projectiles[--projectileCount];
            projectiles[projectileCount] = nullptr;
            continue;
        }

        if (!projectiles[i]->isVisible())
        {
            delete projectiles[i];
            projectiles[i] = projectiles[--projectileCount];
            projectiles[projectileCount] = nullptr;
        }
        else ++i;
    }

    // ---------------- ENEMY UPDATE ----------------
    for (int e = 0; e < enemyCount; e++)
        if (enemies[e])
            enemies[e]->update(deltaTime);

    // ---------------- SNOWBALL VS ENEMY ----------------
    for (int e = 0; e < enemyCount; )
    {
        if (!enemies[e]) { ++e; continue; }

        for (int i = 0; i < snowballCount; )
        {
            if (!snowballs[i]) { ++i; continue; }

            if (snowballs[i]->getBounds().intersects(enemies[e]->getBounds()))
            {
                enemies[e]->hitBySnowball(1.0f);

                delete snowballs[i];
                snowballs[i] = snowballs[--snowballCount];
                snowballs[snowballCount] = nullptr;
            }
            else ++i;
        }

        if (!enemies[e]->isAlive())
            removeEnemy(e);
        else
            ++e;
    }

    // ---------------- ENEMY TOUCH DAMAGE (IMPORTANT SPEC) ----------------
    for (int e = 0; e < enemyCount; ++e)
    {
        if (!enemies[e]) continue;
        if (enemies[e]->isPushable()) continue;

        if (!player1.isInvincible &&
            enemies[e]->getBounds().intersects(player1.getBounds()))
        {
            player1.loseLife();
            if (player1.loseLife())
            {
               // manager.changeState(new MenuState(manager)); // GAME OVER
                gameOver = true;
            }
        }

        if (player2 &&
            !player2->isInvincible &&
            enemies[e]->getBounds().intersects(player2->getBounds()))
        {
            player2->loseLife();
            if (player2->loseLife())
            {
               // manager.changeState(new MenuState(manager)); // GAME OVER
                gameOver = true;
            }
        }
    }

        for (int i = 0; i < enemyCount; ++i)
        {
            if (!enemies[i] || !enemies[i]->isrolling()) continue;
    
            float x = enemies[i]->getBounds().left;
            float y = enemies[i]->getBounds().top;
    
            bool atBottom = (y >= 500.f);
            bool atEdge = (x <= 0.f || x + enemies[i]->getBounds().width >= 800.f);
    
            if (atBottom && atEdge)
            {
                // trigger chain reaction
                for (int j = 0; j < enemyCount; ++j)
                {
                    if (i == j || !enemies[j]) continue;
    
                    // kill all nearby enemies (simple version: kill all)
                    enemies[j]->hitBySnowball(5.0f);
                }
    
                // destroy the rolling one too
                enemies[i]->hitBySnowball(5.0f);
            }
        }
    
    
        for (int e = 0; e < enemyCount; ++e)
        {
            if (!enemies[e] || !enemies[e]->isPushable()) continue;
    
            bool p1hit = enemies[e]->getBounds().intersects(player1.getBounds());
            bool p2hit = player2 &&
                enemies[e]->getBounds().intersects(player2->getBounds());
    
            if (p1hit && enemies[e]->isPushable())
            {
                enemies[e]->direction = player1.direction;
                if (!enemies[e]->isrolling())
                    enemies[e]->startRolling(player1.direction);
                enemies[e]->push(player1.direction * 20.f);
            }
            if (p2hit)
            {
                enemies[e]->direction = player2->direction;
                if (!enemies[e]->isrolling())
                    enemies[e]->startRolling(player2->direction);
                enemies[e]->push(player2->direction * 20.f);
            }
        }
    // ---------------- TORNADO KNIVES ----------------
    for (int e = 0; e < enemyCount; e++)
    {
        Tornado* t = dynamic_cast<Tornado*>(enemies[e]);
        if (!t || !t->isFlyingMode()) continue;

        t->knifeTimer += deltaTime;

        if (t->knifeTimer >= 3.0f)
        {
            t->knifeTimer = 0.f;

            sf::Vector2f dir =
                player1.getPosition() - t->getPosition();

            float mag = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (mag != 0) dir /= mag;

            spawnKnife(t->getPosition() + sf::Vector2f(20, 20), dir);
        }
    }

    // ---------------- AUTO FIRE ----------------
    if (isFPressed)
    {
        fireTimer += deltaTime;

        if (fireTimer >= fireCooldown)
        {
            sf::FloatRect b = player1.getBounds();

            spawnSnowball(b.left + b.width / 2.f,
                b.top + b.height / 2.f,
                player1.direction);

            fireTimer = 0.f;
        }
    }

    // ---------------- GAME OVER CONDITION ----------------
    //if (!player1.isAlive() && (!player2 || !player2->isAlive()))
    //{
    //    manager.changeState(new MenuState(manager));
    //    return;
    //}
    if (gameOver)
    {
        manager.changeState(new GameOverState(manager));
        return;
    }
    livesText1.setString("P1 Lives: " + std::to_string(player1.getLives()));

    if (player2)
    {
        livesText2.setString("P2 Lives: " + std::to_string(player2->getLives()));
    }

}

// ---------------- RENDER ----------------
void PlayState::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    player1.draw(window, debugMode);
    if (player2) player2->draw(window, debugMode);

    for (int i = 0; i < platformCount; i++)
        window.draw(platforms[i]);

    for (int i = 0; i < snowballCount; i++)
        if (snowballs[i]) snowballs[i]->draw(window, debugMode);

    for (int i = 0; i < projectileCount; i++)
        if (projectiles[i]) projectiles[i]->draw(window);

    for (int e = 0; e < enemyCount; e++)
        if (enemies[e]) enemies[e]->draw(window, debugMode);

    window.draw(livesText1);

    if (player2)
        window.draw(livesText2);
}

// ---------------- SPAWN ----------------
void PlayState::spawnSnowball(float x, float y, int direction)
{
    if (snowballCount < MAX_SNOWBALLS)
        snowballs[snowballCount++] = new Snowball(x, y, direction);
}

void PlayState::spawnKnife(sf::Vector2f pos, sf::Vector2f dir)
{
    if (projectileCount < MAX_PROJECTILES)
        projectiles[projectileCount++] = new Knife(pos, dir);
}