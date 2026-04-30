#include "PlayState.h"
#include "MenuState.h"
#include "Player.h"
#include "FlyingFooga.h"
#include "Tornado.h"

PlayState::PlayState(StateManager& manager)
    : State(manager), player1(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up), player2(nullptr)
{
    if (manager.getMode() == GameMode::TwoPlayer)
    {
        player2 = new Player(sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8);
    }

	enemyCount = 0;
    for (int i = 0; i < MAX_ENEMIES; ++i)
    {
        enemies[i] = nullptr;
    }

    //snowball setup
    isFPressed = false;
    fireTimer = 0.0f;
    fireCooldown = 0.3f;
    snowballCount = 0;
    for (int i = 0; i < MAX_SNOWBALLS; ++i)
    {
        snowballs[i] = nullptr;
    }

    //platform setup
    platforms[0].setSize(sf::Vector2f(200, 15));
    platforms[0].setPosition(200, 450);
    platforms[0].setFillColor(sf::Color::White);
    platformCount = 1;

    //hitbox debug 
    debugMode = false;

   
    //enemy = new Botom(sf::Vector2f(300, 500));
    enemies[enemyCount++] = new Botom(sf::Vector2f(300, 400));
    //enemies[enemyCount++] = new Botom(sf::Vector2f(500, 400));
    //enemies[enemyCount++] = new Botom(sf::Vector2f(700, 400));
    enemies[enemyCount++] = new FlyingFooga(sf::Vector2f(500, 200));
    enemies[enemyCount++] = new Tornado(sf::Vector2f(200, 200));

    //enemyCount = 2;
    //enemies[enemyCount++] = new FlyingFooga(sf::Vector2f(500, 150));

}

PlayState::~PlayState()
{
    delete player2;
    for (int i = 0; i < snowballCount; ++i)
    {
        delete snowballs[i];
    }
    for (int i = 0; i < enemyCount; ++i)
    {
        delete enemies[i];
    }
}

void PlayState::removeEnemy(int index)
{
    delete enemies[index];
    enemies[index] = enemies[--enemyCount];
    enemies[enemyCount] = nullptr;
}

void PlayState::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            manager.changeState(new MenuState(manager));
        }
        if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::H)
        {
            debugMode = !debugMode;
        }
    }
    //firing on press
    if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
    {
        if (!isFPressed)
        {
            isFPressed = true;
            fireTimer = 0.0f; 
            sf::FloatRect b = player1.getBounds();
            spawnSnowball(b.left + b.width / 2.f, b.top + b.height / 2.f, player1.direction);
        }

    }
    //firing for pressing 
    if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::J || event.key.code == sf::Keyboard::Space))
    {
        isFPressed = false;
        fireTimer = 0.0f;
    }
}

void PlayState::update(float deltaTime)
{
    player1.handleInput();
    player1.update(deltaTime);
    if (player2 != nullptr)
    {
        player2->handleInput();
        player2->update(deltaTime);
    }

    for (int i = 0; i < platformCount; i++)
    {
        player1.checkPlatformCollision(platforms[i]);

        if (player2 != nullptr)
        {
            player2->checkPlatformCollision(platforms[i]);
        }
        for (int j = 0; j < enemyCount; ++j)
        {
            if (enemies[j])
            {
                enemies[j]->checkPlatformCollision(platforms[i]);
            }
        }
    }
    // updating snowballs
    for (int i = 0; i < snowballCount; )
    {
        if (!snowballs[i])
        {
            ++i;
            continue;
        }
        snowballs[i]->update(deltaTime);
        sf::FloatRect b = snowballs[i]->getBounds();

        bool expired = snowballs[i]->isWrapped() && snowballs[i]->getLifeTime() >= snowballs[i]->getMaxLifeTime();
        if (expired)
        {
            delete snowballs[i];
            snowballs[i] = snowballs[--snowballCount];
            snowballs[snowballCount] = nullptr;
        }
        else ++i;
    }

    // (duplicate push-to-start rolling block removed)

    // update enemy once per frame so rolling/bounce logic runs even if there are no snowballs
    for (int e = 0; e < enemyCount; ++e)
        if (enemies[e]) enemies[e]->update(deltaTime);

    for (int e = 0; e < enemyCount; )
    {
        if (!enemies[e])
        {
            ++e;
            continue;
        }

        for (int i = 0; i < snowballCount; )
        {
            if (!snowballs[i])
            {
                ++i;
                continue;
            }

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
        {
            removeEnemy(e); 
        }
        else
        {
            ++e;
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

    // auto fire handling
    if (isFPressed)
    {
        fireTimer += deltaTime;
        if (fireTimer >= fireCooldown)
        {
            sf::FloatRect b = player1.getBounds();
            spawnSnowball(b.left + b.width / 2.f, b.top + b.height / 2.f, player1.direction);
            fireTimer = 0.0f;
        }
    }
    for (int i = 0; i < enemyCount; ++i)
    {
        if (!enemies[i] || !enemies[i]->isrolling()) continue;

        for (int j = 0; j < enemyCount; ++j)
        {
            if (i == j || !enemies[j]) continue;

            if (enemies[i]->getBounds().intersects(enemies[j]->getBounds()))
            {
                // hit second enemy
                enemies[j]->hitBySnowball(2.0f); // stronger impact

                // optional: knockback effect
                enemies[j]->push(enemies[i]->direction * 10.f);
            }
        }
    }

}

void PlayState::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    player1.draw(window, debugMode);
    if (player2 != nullptr)
    {
        player2->draw(window, debugMode);
    }

    for (int i = 0; i < platformCount; i++)
    {
        window.draw(platforms[i]);
    }

    for (int i = 0; i < snowballCount; ++i)
    {
        if (snowballs[i])
        {
            snowballs[i]->draw(window, debugMode);
        }
    }

    for (int e = 0; e < enemyCount; ++e)
    {
        if (enemies[e])
        {
            enemies[e]->draw(window, debugMode);
        }
    }
   
}

void PlayState::spawnSnowball(float x, float y, int direction)
{
    if (snowballCount < MAX_SNOWBALLS)
    {
        snowballs[snowballCount++] = new Snowball(x, y, direction);
    }
}
