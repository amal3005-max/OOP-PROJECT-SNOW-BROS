#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "WinState.h"   
#include "GameOver.h"
#include "Player.h"
#include <cmath>

PlayState::PlayState(StateManager& manager) : State(manager),
    player1(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up), player2(nullptr)
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

    font.loadFromFile("arcade.otf");

    livesText1.setFont(font);
    livesText1.setCharacterSize(20);
    livesText1.setFillColor(sf::Color::White);
    livesText1.setPosition(10.f, 10.f);

    livesText2.setFont(font);
    livesText2.setCharacterSize(20);
    livesText2.setFillColor(sf::Color::White);
    livesText2.setPosition(10.f, 40.f);

    loadLevel();
}

// Destructor
PlayState::~PlayState()
{
    delete player2;

    for (int i = 0; i < snowballCount; ++i) delete snowballs[i];
    for (int i = 0; i < projectileCount; ++i) delete projectiles[i];
    for (int i = 0; i < enemyCount; ++i) delete enemies[i];

    delete mogera;
    delete gamakichi;
}

void PlayState::removeEnemy(int index)
{
    totalEnemiesDefeated++;
    totalScore += 100;
    delete enemies[index];
    enemies[index] = enemies[--enemyCount];
    enemies[enemyCount] = nullptr;
}


// Input
void PlayState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            manager.changeState(new MenuState(manager));

        if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::H)
            debugMode = !debugMode;

        if (event.key.code == sf::Keyboard::P)
            manager.pauseState(new PauseState(manager));
    }

    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
    {
        if (!isFPressed)
        {
            isFPressed = true;
            fireTimer = 0.f;
            sf::FloatRect b = player1.getBounds();
            spawnSnowball(b.left + b.width / 2.f, b.top + b.height / 2.f, player1.direction);
        }
    }

    if (event.type == sf::Event::KeyReleased &&
        (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
    {
        isFPressed = false;
        fireTimer = 0.f;
    }
}

// Update
void PlayState::update(float deltaTime)
{
    //player
    player1.handleInput();
    player1.update(deltaTime);

    if (player2)
    {
        player2->handleInput();
        player2->update(deltaTime);
    }


    sf::FloatRect pb = player1.getBounds();
    sf::Vector2f playerCenter(pb.left + pb.width / 2.f, pb.top + pb.height / 2.f);

    for (int e = 0; e < enemyCount; e++)
    {
        if (enemies[e])
            enemies[e]->setTarget(playerCenter);
    }

    // Platform collision 
    for (int i = 0; i < platformCount; i++)
    {
        player1.checkPlatformCollision(platforms[i]);
        if (player2) player2->checkPlatformCollision(platforms[i]);

        for (int j = 0; j < enemyCount; j++)
            if (enemies[j])
                enemies[j]->checkPlatformCollision(platforms[i]);
    }

    // Snowball update & expiry
    for (int i = 0; i < snowballCount; )
    {
        if (!snowballs[i]) { ++i; continue; }
        snowballs[i]->update(deltaTime);

        bool expired = snowballs[i]->isWrapped() &&
            snowballs[i]->getLifeTime() >= snowballs[i]->getMaxLifeTime();
        if (expired)
        {
            delete snowballs[i];
            snowballs[i] = snowballs[--snowballCount];
            snowballs[snowballCount] = nullptr;
        }
        else ++i;
    }

    // Projectile update (knives / artillery)
    for (int i = 0; i < projectileCount; )
    {
        if (!projectiles[i]) { ++i; continue; }
        projectiles[i]->update(deltaTime);

        // Hit player 1
        if (projectiles[i]->getBounds().intersects(player1.getBounds()))
        {
            if (!player1.isInvincible)
                if (player1.loseLife())
                    gameOver = true;

            delete projectiles[i];
            projectiles[i] = projectiles[--projectileCount];
            projectiles[projectileCount] = nullptr;
            continue;
        }

        // Hit platforms
        for (int p = 0; p < platformCount; p++)
            if (projectiles[i]->getBounds().intersects(platforms[p].getGlobalBounds()))
                projectiles[i]->ProjectileHit();

        // Hit player 2
        if (player2 && projectiles[i]->getBounds().intersects(player2->getBounds()))
        {
            if (!player2->isInvincible)
                if (player2->loseLife())
                    gameOver = true;

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

    // Enemy update
    for (int e = 0; e < enemyCount; e++)
        if (enemies[e])
            enemies[e]->update(deltaTime);

    // ── Snowball vs regular enemies ──────────────────────────────────────────────
    for (int e = 0; e < enemyCount; )
    {
        if (!enemies[e]) { ++e; continue; }

        // ── FIX: skip bosses — they have their own death handlers below ──
        if (enemies[e] == mogera || enemies[e] == gamakichi) { ++e; continue; }

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

	//Snowball vs Mogera boss
    if (mogera)
    {
        for (int i = 0; i < snowballCount; )
        {
            if (!snowballs[i]) { ++i; continue; }
            if (snowballs[i]->getBounds().intersects(mogera->getBounds()))
            {
                mogera->hitBySnowball(1.0f);
                delete snowballs[i];
                snowballs[i] = snowballs[--snowballCount];
                snowballs[snowballCount] = nullptr;
            }
            else ++i;
        }

        if (!mogera->isAlive())
        {
            // Remove MogeraChildren from enemies[]
            for (int e = enemyCount - 1; e >= 0; --e)
            {
                if (dynamic_cast<MogeraChild*>(enemies[e]))
                {
                    delete enemies[e];
                    enemies[e] = enemies[--enemyCount];
                    enemies[enemyCount] = nullptr;
                }
            }

            // Remove mogera from enemies[] array
            for (int e = 0; e < enemyCount; e++)
            {
                if (enemies[e] == mogera)
                {
                    enemies[e] = enemies[--enemyCount];
                    enemies[enemyCount] = nullptr;
                    break;
                }
            }

            delete mogera;
            mogera = nullptr;

            if (!levelManager.isLastLevel())
            {
                levelManager.nextLevel();
                loadLevel();
            }
        }
    }



    // Snowball vs Gamakichi boss 

    // Enemy touch damage 
    for (int e = 0; e < enemyCount; ++e)
    {
        if (!enemies[e]) continue;
        if (enemies[e]->isPushable()) continue;
        if (enemies[e] == mogera || enemies[e] == gamakichi) continue; // ← FIX

        if (!player1.isInvincible &&
            enemies[e]->getBounds().intersects(player1.getBounds()))
            if (player1.loseLife()) gameOver = true;

        if (player2 && !player2->isInvincible &&
            enemies[e]->getBounds().intersects(player2->getBounds()))
            if (player2->loseLife()) gameOver = true;
    }

    // Rolling chain reaction 
    for (int i = 0; i < enemyCount; ++i)
    {
        if (!enemies[i] || !enemies[i]->isrolling()) continue;

        float x = enemies[i]->getBounds().left;
        float y = enemies[i]->getBounds().top;

        if (y >= 500.f && (x <= 0.f || x + enemies[i]->getBounds().width >= 800.f))
        {
            for (int j = 0; j < enemyCount; ++j)
                if (i != j && enemies[j]) enemies[j]->hitBySnowball(5.0f);
            enemies[i]->hitBySnowball(5.0f);
        }
    }

    // Push rolling 
    for (int e = 0; e < enemyCount; ++e)
    {
        if (!enemies[e] || !enemies[e]->isPushable()) continue;

        bool p1hit = enemies[e]->getBounds().intersects(player1.getBounds());
        bool p2hit = player2 && enemies[e]->getBounds().intersects(player2->getBounds());

        if (p1hit)
        {
            enemies[e]->direction = player1.direction;
            if (!enemies[e]->isrolling()) enemies[e]->startRolling(player1.direction);
            enemies[e]->push(player1.direction * 20.f);
        }
        if (p2hit)
        {
            enemies[e]->direction = player2->direction;
            if (!enemies[e]->isrolling()) enemies[e]->startRolling(player2->direction);
            enemies[e]->push(player2->direction * 20.f);
        }
    }

    // Tornado knife attack 
    for (int e = 0; e < enemyCount; e++)
    {
        Tornado* t = dynamic_cast<Tornado*>(enemies[e]);
        if (!t || !t->isFlyingMode()) continue;

        t->knifeTimer += deltaTime;
        if (t->knifeTimer >= 3.0f)
        {
            t->knifeTimer = 0.f;
            sf::Vector2f dir = player1.getPosition() - t->getPosition();
            float mag = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (mag != 0) dir /= mag;
            spawnKnife(t->getPosition() + sf::Vector2f(20, 20), dir);
        }
    }

    // Auto fire (hold button)
    if (isFPressed)
    {
        fireTimer += deltaTime;
        if (fireTimer >= fireCooldown)
        {
            sf::FloatRect b = player1.getBounds();
            spawnSnowball(b.left + b.width / 2.f, b.top + b.height / 2.f, player1.direction);
            fireTimer = 0.f;
        }
    }

    if (mogera)
    {
        mogera->update(deltaTime);

            sf::FloatRect pb = player1.getBounds();
            sf::Vector2f  playerCentre(pb.left + pb.width / 2.f, pb.top + pb.height / 2.f);
        
            MogeraChild* child = mogera->trySpawnChild(playerCentre);
            if (child)
            {
                if (enemyCount < MAX_ENEMIES)
                    enemies[enemyCount++] = child;
                else
                    delete child;
            }
        
    }

    // ── GAMAKICHI boss update + child spawning ────────────────────────────────────
    if (gamakichi)
    {
        gamakichi->update(deltaTime);

        GamakichiChild* kids[6];
        int kidCount = 0;
        gamakichi->fireCannons(deltaTime, kids, kidCount);

        for (int i = 0; i < kidCount; i++)
        {
            if (enemyCount < MAX_ENEMIES)
                enemies[enemyCount++] = kids[i];
            else
                delete kids[i];
        }

        // Snowball hits on Gamakichi
        for (int i = 0; i < snowballCount; )
        {
            if (!snowballs[i]) { ++i; continue; }
            if (snowballs[i]->getBounds().intersects(gamakichi->getBounds()))
            {
                gamakichi->hitBySnowball(1.0f);
                delete snowballs[i];
                snowballs[i] = snowballs[--snowballCount];
                snowballs[snowballCount] = nullptr;
            }
            else ++i;
        }

        if (!gamakichi->isAlive())
        {
            // delete all GamakichiChildren from enemies[]
            for (int e = enemyCount - 1; e >= 0; --e)
            {
                if (dynamic_cast<GamakichiChild*>(enemies[e]))
                {
                    delete enemies[e];
                    enemies[e] = enemies[--enemyCount];
                    enemies[enemyCount] = nullptr;
                }
            }

            // remove gamakichi from enemies[] WITHOUT deleting
            for (int e = 0; e < enemyCount; e++)
            {
                if (enemies[e] == gamakichi)
                {
                    enemies[e] = enemies[--enemyCount];
                    enemies[enemyCount] = nullptr;
                    break;
                }
            }

            // now safe to delete 
            delete gamakichi;
            gamakichi = nullptr;
        }
    }

    // ── Game over check ──────────────────────────────────────────────────────
    if (gameOver)
    {
        manager.changeState(new GameOverState(manager));
        return;
    }

    livesText1.setString("P1 Lives: " + std::to_string(player1.getLives()));
    if (player2)
        livesText2.setString("P2 Lives: " + std::to_string(player2->getLives()));

    
    if (enemyCount == 0 && !mogera && !gamakichi && !gameOver)
    {
        if (levelManager.isLastLevel())
        {
            // TRIGGER WIN STATE 
            manager.changeState(new WinState(manager,
                totalScore,
                totalEnemiesDefeated,
                levelManager.getTotalLevels()));
        }
        else 
        {
            levelManager.nextLevel();
            loadLevel();
        }
    
    }

    if (enemyCount == 0 && !gameOver)
    {
        if (!levelManager.isLastLevel())
        {
            levelManager.nextLevel();
            loadLevel();   
        }
        else
        {
            if (manager.getSound()) manager.getSound()->stop();
        }
    }
}

void PlayState::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    levelManager.drawBackground(window);

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
    if (player2) window.draw(livesText2);

    if (mogera)    mogera->draw(window, debugMode);
    if (gamakichi) gamakichi->draw(window, debugMode);
}


// Spawn helpers
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

void PlayState::loadLevel()
{

    if (manager.getSound())
    {
        LevelConfig& lvl = levelManager.getCurrentLevel();
        if (lvl.hasMogera || lvl.hasGamakichi)
            manager.getSound()->play("SnowBrosAssets/Sounds/final_boss_snow_bros.ogg");
        else
            manager.getSound()->play("SnowBrosAssets/Sounds/snow_bros_level.ogg");
    }

    gameOver = false;
    // Clear enemies
    for (int i = 0; i < enemyCount; i++)
    {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemyCount = 0;
    levelManager.loadBackgrounds();
    // Reset boss pointers FIRST
    mogera = nullptr;
    gamakichi = nullptr;

    LevelConfig& lvl = levelManager.getCurrentLevel();

    // ---------------- PLATFORMS ----------------
    platformCount = lvl.platformCount;
    for (int i = 0; i < platformCount; i++)
    {
        platforms[i].setSize(lvl.platforms[i].size);
        platforms[i].setPosition(lvl.platforms[i].position);
        platforms[i].setFillColor(sf::Color(255, 255, 255, 0));
    }

    // ---------------- ENEMIES ----------------
    for (int i = 0; i < lvl.enemyCount; i++)
    {
        EnemySpawn& e = lvl.enemies[i];

        if (e.type == EnemyType::Botom)
            enemies[enemyCount++] = new Botom(e.position);
        else if (e.type == EnemyType::FlyingFoogaFog)
            enemies[enemyCount++] = new FlyingFooga(e.position);
        else if (e.type == EnemyType::Tornado)
            enemies[enemyCount++] = new Tornado(e.position);
    }

    // ---------------- BOSSES ----------------
    if (lvl.hasMogera)
    {
        gSound().play("SnowBrosAssets/Sounds/final_boss_snow_bros.ogg");

        mogera = new Mogera(sf::Vector2f(570, 135));
        enemies[enemyCount++] = mogera;  
    }

    if (lvl.hasGamakichi)
    {
        gSound().play("SnowBrosAssets/Sounds/final_boss_snow_bros.ogg");
        gamakichi = new Gamakichi(sf::Vector2f(200, 310));
        enemies[enemyCount++] = gamakichi;  
    }

}
