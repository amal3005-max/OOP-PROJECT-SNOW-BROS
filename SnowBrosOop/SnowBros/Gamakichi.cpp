//#include "Gamakichi.h"
//Gamakichi::Gamakichi(sf::Vector2f p) :Enemy(EnemyType::Gamakichi,0.f,p)
//{
//	health = 500; // GamakichiHealth 
//	projectileTimer = 0.f;
//	projectileCount = 0;
//	currentType = healthDecreases;
//}
//void Gamakichi::update (float dt, sf::Vector2f playerPosition)
//{
//	projectileTimer += dt;
//	float interval;
//	if (health > 300)
//		currentType=healthDecreases;
//	else if (health > 100)
//		currentType = colorChanges;
//	else if (health <= 100)
//		currentType = attackSpeed;
//	if (currentType == healthDecreases)
//	{
//		interval= 3.f;
//		if (projectileTimer >= interval)
//		{
//			fireProjectile(playerPosition);
//			projectileTimer = 0.f;
//		}
//	}
//	else if (currentType == colorChanges)
//	{
//		interval = 2.f;
//		if (projectileTimer >= interval)
//		{
//			fireProjectile(playerPosition);
//			projectileTimer = 0.f;
//		}
//	}
//	else if (currentType == attackSpeed)
//	{
//		interval = 1.f;
//		if (projectileTimer >= interval)
//		{
//			fireProjectile(playerPosition);
//			projectileTimer = 0.f;
//		}
//	}
//	else
//	{
//		interval = 3.f;
//		if (projectileTimer > 3.f)
//		{
//			fireProjectile(playerPosition);
//			projectileTimer = 0.f;
//		}
//		
//	}
//	
//}
//void Gamakichi::fireProjectile(sf::Vector2f playerPosition)
//{
//	if (projectileCount > 15)
//		return;
//	else
//	{
//		sf::Vector2f vel = (playerPosition - position) * 200.f;
//		Projectile[projectileCount] = new ProjectileArtillery(position, vel, 20.f, true);
//		projectileCount++;
//	}
//}
//void Gamakichi::draw(sf::RenderWindow& window)
//{
//	sf::RectangleShape rect (sf::Vector2f(200, 200));
//	rect.setPosition(position);
//	rect.setFillColor(sf::Color::Cyan);
//	window.draw(rect);
//	for (int i = 0; i < projectileCount; i++)
//	{
//		Projectile[i]->draw(window);
//
//	}
//	
//}

//
//#include "Gamakichi.h"
//#include <cmath>
//
//Gamakichi::Gamakichi(sf::Vector2f pos)
//    : SimpleEnemy(EnemyType::Gamakichi, 0.f, pos)
//{
//    // Much more health than Mogera (30)
//    health = 100;
//    pushable = false;
//
//    // Large boss body — 200x200
//    body.setSize(sf::Vector2f(200.f, 200.f));
//    body.setFillColor(sf::Color::Cyan);
//    body.setPosition(pos);
//    position = pos;
//
//    phase = GamaPhase::Phase1;
//    projectileTimer = 0.f;
//    fireInterval = getFireInterval();
//
//    playerPosition = sf::Vector2f(400.f, 400.f);
//}
//
//// ── Phase thresholds ─────────────────────────────────────────────────────────
////  Phase1: health > 66  →  slow fire,  1 rocket aimed at player
////  Phase2: health > 33  →  medium fire, 2 rockets (player + spread)
////  Phase3: health <= 33 →  fast fire,  4 rockets in a cross pattern
//void Gamakichi::updatePhase()
//{
//    GamaPhase newPhase;
//    if (health > 66) newPhase = GamaPhase::Phase1;
//    else if (health > 33) newPhase = GamaPhase::Phase2;
//    else                  newPhase = GamaPhase::Phase3;
//
//    if (newPhase != phase)
//    {
//        phase = newPhase;
//        fireInterval = getFireInterval();
//    }
//}
//
//float Gamakichi::getFireInterval() const
//{
//    switch (phase)
//    {
//    case GamaPhase::Phase1: return 3.0f;
//    case GamaPhase::Phase2: return 2.0f;
//    case GamaPhase::Phase3: return 1.0f;
//    }
//    return 3.0f;
//}
//
//// ── Rocket factory ────────────────────────────────────────────────────────────
//void Gamakichi::tryFireRockets(ProjectileArtillery** out, int& outCount)
//{
//    outCount = 0;
//    if (projectileTimer < fireInterval) return;
//    //int burstCount = (phase == GamaPhase::Phase3) ? 2 : 1;
//
//    //for (int i = 0; i < burstCount; i++)
//    //{
//    //    // fire rockets
//    //}
//    projectileTimer = 0.f;
//
//    // Spawn point = centre of Gamakichi's body
//    //sf::Vector2f centre = body.getPosition() +
//    //    sf::Vector2f(body.getSize().x / 2.f,
//    //        body.getSize().y / 2.f);
//
//    sf::Vector2f centre = body.getPosition() +
//        sf::Vector2f(body.getSize().x / 2.f,
//            body.getSize().y / 2.f);
//
//    // variation
//    centre.x += (rand() % 40) - 20;
//    centre.y += (rand() % 40) - 20;
//
//    const float rocketSpeed = 220.f;
//
//    // Helper lambda — normalise a direction then scale
//    auto makeRocket = [&](sf::Vector2f dir)
//        {
//            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//            if (len > 0.f) dir /= len;
//            return new ProjectileArtillery(centre, dir * rocketSpeed);
//        };
//
//    // Direction toward player
//    sf::Vector2f toPlayer = playerPosition - centre;
//
//    switch (phase)
//    {
//    case GamaPhase::Phase1:
//        // 1 rocket aimed at player
//        out[outCount++] = makeRocket(toPlayer);
//        break;
//
//    case GamaPhase::Phase2:
//        // 2 rockets: aimed + 45-degree spread
//        out[outCount++] = makeRocket(toPlayer);
//        //out[outCount++] = makeRocket(sf::Vector2f(toPlayer.x - toPlayer.y,
//        //    toPlayer.y + toPlayer.x)); // +90 rotated
//        //out[outCount++] = makeRocket(sf::Vector2f(-toPlayer.y, toPlayer.x)); // -90 rotated
//        out[outCount++] = makeRocket(toPlayer);
//        out[outCount++] = makeRocket(sf::Vector2f(-toPlayer.y, toPlayer.x));
//        break;
//
//    case GamaPhase::Phase3:
//        // 4 rockets in a cross (up/down/left/right)
//        out[outCount++] = makeRocket(sf::Vector2f(0.f, -1.f)); // up
//        out[outCount++] = makeRocket(sf::Vector2f(0.f, 1.f)); // down
//        out[outCount++] = makeRocket(sf::Vector2f(-1.f, 0.f)); // left
//        out[outCount++] = makeRocket(sf::Vector2f(1.f, 0.f)); // right
//        break;
//    }
//    if (outCount >= 4) return;
//}
//
//// ── update / draw / isAlive ───────────────────────────────────────────────────
//void Gamakichi::update(float dt)
//{
//    projectileTimer += dt;
//    updatePhase();
//    SimpleEnemy::update(dt);
//    // Colour changes per phase (spec: "colour changes")
//    switch (phase)
//    {
//    case GamaPhase::Phase1: body.setFillColor(sf::Color::Cyan);                  break;
//    case GamaPhase::Phase2: body.setFillColor(sf::Color(255, 165, 0));           break; // orange
//    case GamaPhase::Phase3: body.setFillColor(sf::Color::Red);                   break;
//    }
//
//    // Snow-coat override
//    if (isFullyEncased())
//        body.setFillColor(sf::Color::White);
//
//    // Stationary — no movement, just keep hitbox in sync
//    hitBox = body.getGlobalBounds();
//}
//
//void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
//{
//    window.draw(body);
//
//    // Health bar (above body)
//    float barW = body.getSize().x;
//    float fraction = static_cast<float>(health) / 100.f;
//    if (fraction < 0.f) fraction = 0.f;
//
//    sf::RectangleShape hpBg(sf::Vector2f(barW, 12.f));
//    hpBg.setPosition(body.getPosition().x, body.getPosition().y - 18.f);
//    hpBg.setFillColor(sf::Color(60, 60, 60));
//    window.draw(hpBg);
//
//    sf::RectangleShape hpFg(sf::Vector2f(barW * fraction, 12.f));
//    hpFg.setPosition(body.getPosition().x, body.getPosition().y - 18.f);
//    // Red in Phase3, orange in Phase2, green in Phase1
//    sf::Color barCol = (phase == GamaPhase::Phase3) ? sf::Color::Red :
//        (phase == GamaPhase::Phase2) ? sf::Color(255, 165, 0) :
//        sf::Color::Green;
//    hpFg.setFillColor(barCol);
//    window.draw(hpFg);
//
//    // Phase label (small text would need font — draw a coloured indicator square instead)
//    sf::RectangleShape phaseIndicator(sf::Vector2f(20.f, 20.f));
//    phaseIndicator.setPosition(body.getPosition().x + barW + 5.f,
//        body.getPosition().y - 18.f);
//    phaseIndicator.setFillColor(barCol);
//    window.draw(phaseIndicator);
//
//    if (debugMode)
//    {
//        sf::FloatRect b = body.getGlobalBounds();
//        sf::RectangleShape box(sf::Vector2f(b.width, b.height));
//        box.setPosition(b.left, b.top);
//        box.setFillColor(sf::Color::Transparent);
//        box.setOutlineColor(sf::Color::Magenta);
//        box.setOutlineThickness(2.f);
//        window.draw(box);
//    }
//}
//
//bool Gamakichi::isAlive() const
//{
//    return health > 0;
//}

//
//#include "Gamakichi.h"
//#include <cmath>
//#include <cstdlib>
//
//Gamakichi::Gamakichi(sf::Vector2f pos)
//    : SimpleEnemy(EnemyType::Gamakichi, 0.f, pos)
//{
//    health = 100;
//    pushable = false;
//
//    body.setSize(sf::Vector2f(220.f, 220.f));
//    body.setFillColor(sf::Color::Cyan);
//    body.setPosition(pos);
//
//    position = pos;
//
//    phase = GamaPhase::Phase1;
//    projectileTimer = 0.f;
//    fireInterval = getFireInterval();
//
//    playerPosition = sf::Vector2f(0.f, 0.f);
//}
//
//void Gamakichi::updateFirePoints()
//{
//    sf::Vector2f p = body.getPosition();
//    sf::Vector2f s = body.getSize();
//
//    float w = s.x;
//    float h = s.y;
//
//    // ───── TOP ARC (3 points) ─────
//    firePoints[0] = p + sf::Vector2f(w * 0.2f, -10.f);
//    firePoints[1] = p + sf::Vector2f(w * 0.5f, -20.f); // center top peak
//    firePoints[2] = p + sf::Vector2f(w * 0.8f, -10.f);
//
//    // ───── SIDE ARMS (2 points) ─────
//    firePoints[3] = p + sf::Vector2f(-10.f, h * 0.5f);      // left
//    firePoints[4] = p + sf::Vector2f(w + 10.f, h * 0.5f);   // right
//
//    // ───── CORE (1 point) ─────
//    firePoints[5] = p + sf::Vector2f(w * 0.5f, h * 0.4f);
//}
//
//
//void Gamakichi::update(float dt)
//{
//    projectileTimer += dt;
//
//    updatePhase();
//    SimpleEnemy::update(dt);
//
//    updateFirePoints();
//
//    switch (phase)
//    {
//    case GamaPhase::Phase1:
//        body.setFillColor(sf::Color::Cyan);
//        break;
//
//    case GamaPhase::Phase2:
//        body.setFillColor(sf::Color(255, 140, 0));
//        break;
//
//    case GamaPhase::Phase3:
//        body.setFillColor(sf::Color::Red);
//        break;
//    }
//
//    hitBox = body.getGlobalBounds();
//}
//
//
//
//
//void Gamakichi::tryFireRockets(ProjectileArtillery** out, int& outCount)
//{
//    outCount = 0;
//
//    if (projectileTimer < fireInterval)
//        return;
//
//    projectileTimer = 0.f;
//
//    sf::Vector2f target = playerPosition;
//
//    auto fire = [&](int i)
//        {
//            sf::Vector2f dir = target - firePoints[i];
//            out[outCount++] = createRocket(firePoints[i], dir);
//        };
//
//    switch (phase)
//    {
//    case GamaPhase::Phase1:
//        fire(1); // top center only
//        break;
//
//    case GamaPhase::Phase2:
//        fire(0);
//        fire(1);
//        fire(2);
//        fire(5);
//        break;
//
//    case GamaPhase::Phase3:
//        // full semicircle barrage
//        for (int i = 0; i < 6; i++)
//            fire(i);
//        break;
//    }
//}
//
//
//
//
//
//// ────────────────────────────────
//// PHASE SYSTEM
//// ────────────────────────────────
//
//void Gamakichi::updatePhase()
//{
//    GamaPhase newPhase;
//
//    if (health > 66) newPhase = GamaPhase::Phase1;
//    else if (health > 33) newPhase = GamaPhase::Phase2;
//    else newPhase = GamaPhase::Phase3;
//
//    if (newPhase != phase)
//    {
//        phase = newPhase;
//        fireInterval = getFireInterval();
//    }
//}
//
//float Gamakichi::getFireInterval() const
//{
//    switch (phase)
//    {
//    case GamaPhase::Phase1: return 2.5f;
//    case GamaPhase::Phase2: return 1.8f;
//    case GamaPhase::Phase3: return 1.0f;
//    }
//    return 2.5f;
//}
//
//// ────────────────────────────────
//// ROCKET CREATION
//// ────────────────────────────────
//
//ProjectileArtillery* Gamakichi::createRocket(sf::Vector2f origin, sf::Vector2f dir)
//{
//    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//    if (len != 0.f) dir /= len;
//
//    float speed = 240.f;
//
//    return new ProjectileArtillery(origin, dir * speed);
//}
//
//
//void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
//{
//    window.draw(body);
//
//    float hpRatio = std::max(0.f, health / 100.f);
//
//    sf::RectangleShape bg(sf::Vector2f(220.f, 12.f));
//    bg.setPosition(body.getPosition().x, body.getPosition().y - 20.f);
//    bg.setFillColor(sf::Color(60, 60, 60));
//
//    sf::RectangleShape fg(sf::Vector2f(220.f * hpRatio, 12.f));
//    fg.setPosition(body.getPosition().x, body.getPosition().y - 20.f);
//
//    fg.setFillColor(
//        phase == GamaPhase::Phase3 ? sf::Color::Red :
//        phase == GamaPhase::Phase2 ? sf::Color(255, 140, 0) :
//        sf::Color::Green
//    );
//
//    window.draw(bg);
//    window.draw(fg);
//
//    if (debugMode)
//    {
//        sf::RectangleShape box;
//        box.setPosition(hitBox.left, hitBox.top);
//        box.setSize({ hitBox.width, hitBox.height });
//        box.setFillColor(sf::Color::Transparent);
//        box.setOutlineColor(sf::Color::Magenta);
//        box.setOutlineThickness(2.f);
//        window.draw(box);
//    }
//}
//
//bool Gamakichi::isAlive() const
//{
//    return health > 0;
//}


//#include "Gamakichi.h"
//
//Gamakichi::Gamakichi(sf::Vector2f pos)
//    : SimpleEnemy(EnemyType::Gamakichi, 0.f, pos)
//{
//    health = 2000;
//    pushable = false;
//
//    body.setSize(sf::Vector2f(400.f, 250.f)); // ground boss
//    body.setFillColor(sf::Color::Cyan);
//    //body.setPosition(pos);
//
//    position = pos;
//    phase = GamaPhase::Phase1;
//    basePosition = pos;
//    idleTimer = 0.f;
//
//    //cannons[0] = { {-160, -120}, 0.f, 3.8f };
//    //cannons[1] = { {-100, -160}, 0.f, 3.5f };
//    //cannons[2] = { { 0,   -190}, 0.f, 4.0f };
//    //cannons[3] = { {100,  -160}, 0.f, 3.5f };
//    //cannons[4] = { {160,  -120}, 0.f, 3.8f };
//    //cannons[5] = { { 0,   -80},  0.f, 4.5f };
//
//    cannons[0] = { {-160, -120}, 0.f, 5.5f };
//    cannons[1] = { {-100, -160}, 0.f, 6.0f };
//    cannons[2] = { {0,   -190}, 0.f, 6.5f };
//    cannons[3] = { {100,  -160}, 0.f, 6.0f };
//    cannons[4] = { {160,  -120}, 0.f, 5.5f };
//    cannons[5] = { {0,   -80},  0.f, 7.0f };
//}
//
//void Gamakichi::updatePhase()
//{
//    if (health > 1200) phase = GamaPhase::Phase1;
//    else if (health > 600) phase = GamaPhase::Phase2;
//    else phase = GamaPhase::Phase3;
//}
//
//void Gamakichi::update(float dt)
//{
//    idleTimer += dt;
//
//    updatePhase();
//    SimpleEnemy::update(dt);
//    velocity = sf::Vector2f(0.f, 0.f);
//    float floatOffset = std::sin(idleTimer * 0.8f) * 8.f;
//    sf::Vector2f newPos = basePosition;
//    newPos.y += floatOffset;
//
//    body.setPosition(newPos);
//    position = newPos;
//
//    switch (phase)
//    {
//    case GamaPhase::Phase1:
//        body.setFillColor(sf::Color::Cyan);
//        break;
//    case GamaPhase::Phase2:
//        body.setFillColor(sf::Color(255, 140, 0));
//        break;
//    case GamaPhase::Phase3:
//        body.setFillColor(sf::Color::Red);
//        break;
//    }
//
//    hitBox = body.getGlobalBounds();
//}
//
//void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
//{
//    window.draw(body);
//
//    if (debugMode)
//    {
//        sf::RectangleShape box;
//        box.setPosition(hitBox.left, hitBox.top);
//        box.setSize({ hitBox.width, hitBox.height });
//        box.setFillColor(sf::Color::Transparent);
//        box.setOutlineColor(sf::Color::Magenta);
//        box.setOutlineThickness(2.f);
//        window.draw(box);
//    }
//}
//
//bool Gamakichi::isAlive() const
//{
//    return health > 0;
//}
//
//#include <cmath> // make sure this exists at top
////
////void Gamakichi::fireCannons(float dt,
////    sf::Vector2f playerPos,
////    ProjectileArtillery** out,
////    int& outCount)
////{
////    sf::Vector2f center =
////        body.getPosition() +
////        sf::Vector2f(body.getSize().x / 2.f,
////            body.getSize().y / 2.f);
////
////    for (int i = 0; i < MAX_CANNONS; i++)
////    {
////        cannons[i].timer += dt;
////
////        if (cannons[i].timer >= cannons[i].fireRate)
////        {
////            cannons[i].timer = 0.f;
////
////            sf::Vector2f spawnPos = center + cannons[i].offset;
////
////            // scatter effect
////            spawnPos.x += (rand() % 60) - 30;
////            spawnPos.y += (rand() % 30) - 15;
////
////            //sf::Vector2f spawnPos = center + cannons[i].offset;
////
////            // upward + slight aim toward player
////            sf::Vector2f dir = playerPos - spawnPos;
////
////            dir.y -= 200.f; // upward bias
////
////            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
////            if (len != 0) dir /= len;
////
////            out[outCount++] =
////                new ProjectileArtillery(spawnPos, dir * 260.f);
////        }
////    }
////}
//
//void Gamakichi::fireCannons(float dt,
//    sf::Vector2f playerPos,
//    ProjectileArtillery** out,
//    int& outCount)
//{
//    sf::Vector2f center =
//        body.getPosition() +
//        sf::Vector2f(body.getSize().x / 2.f,
//                     body.getSize().y / 2.f);
//
//    for (int i = 0; i < MAX_CANNONS; i++)
//    {
//        cannons[i].timer += dt;
//
//        if (cannons[i].timer >= cannons[i].fireRate)
//        {
//            cannons[i].timer = 0.f;
//
//            sf::Vector2f spawnPos = center + cannons[i].offset;
//
//            spawnPos.x += (rand() % 120) - 60;
//            spawnPos.y = center.y - 200.f;
//
//            out[outCount++] = new GamakichiChild(spawnPos);
//        }
//    }
//}
//
// 
//#include "Gamakichi.h"
//#include <cstdlib>
//
//Gamakichi::Gamakichi(sf::Vector2f pos)
//    : SimpleEnemy(EnemyType::Gamakichi, 0.f, pos)
//{
//    health = 2000;
//    pushable = false;
//
//    body.setSize(sf::Vector2f(400.f, 250.f));
//    body.setFillColor(sf::Color::Cyan);
//
//    position = pos;
//    basePosition = pos;
//
//    phase = GamaPhase::Phase1;
//    idleTimer = 0.f;
//
//    // cannon layout (top-mounted artillery points)
//    cannons[0] = { {-160, -120}, 0.f, 5.5f };
//    cannons[1] = { {-100, -160}, 0.f, 6.0f };
//    cannons[2] = { {0,   -190}, 0.f, 6.5f };
//    cannons[3] = { {100, -160}, 0.f, 6.0f };
//    cannons[4] = { {160, -120}, 0.f, 5.5f };
//    cannons[5] = { {0,   -80},  0.f, 7.0f };
//}
//
//void Gamakichi::updatePhase()
//{
//    if (health > 1200) phase = GamaPhase::Phase1;
//    else if (health > 600) phase = GamaPhase::Phase2;
//    else phase = GamaPhase::Phase3;
//}
//
//void Gamakichi::update(float dt)
//{
//    idleTimer += dt;
//
//    updatePhase();
//    SimpleEnemy::update(dt);
//
//    // idle floating motion
//    float floatOffset = std::sin(idleTimer * 0.8f) * 8.f;
//
//    sf::Vector2f newPos = basePosition;
//    newPos.y += floatOffset;
//
//    body.setPosition(newPos);
//    position = newPos;
//
//    switch (phase)
//    {
//    case GamaPhase::Phase1: body.setFillColor(sf::Color::Cyan); break;
//    case GamaPhase::Phase2: body.setFillColor(sf::Color(255, 140, 0)); break;
//    case GamaPhase::Phase3: body.setFillColor(sf::Color::Red); break;
//    }
//
//    hitBox = body.getGlobalBounds();
//}
//
//void Gamakichi::fireCannons(float dt,
//    GamakichiChild** out,
//    int& outCount)
//{
//    sf::Vector2f center =
//        body.getPosition() +
//        sf::Vector2f(body.getSize().x / 2.f,
//            body.getSize().y / 2.f);
//
//    for (int i = 0; i < MAX_CANNONS; i++)
//    {
//        cannons[i].timer += dt;
//
//        if (cannons[i].timer >= cannons[i].fireRate)
//        {
//            cannons[i].timer = 0.f;
//
//            sf::Vector2f spawnPos = center + cannons[i].offset;
//
//            // scatter ABOVE boss (artillery drop)
//            spawnPos.x += (rand() % 120) - 60;
//            spawnPos.y = center.y - 200.f;
//
//            out[outCount++] = new GamakichiChild(spawnPos);
//        }
//    }
//}
//
//void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
//{
//    window.draw(body);
//
//    if (debugMode)
//    {
//        sf::RectangleShape box;
//        box.setPosition(hitBox.left, hitBox.top);
//        box.setSize({ hitBox.width, hitBox.height });
//        box.setFillColor(sf::Color::Transparent);
//        box.setOutlineColor(sf::Color::Magenta);
//        box.setOutlineThickness(2.f);
//        window.draw(box);
//    }
//}
//
//bool Gamakichi::isAlive() const
//{
//    return health > 0;
//}



#include "Gamakichi.h"
#include <cstdlib>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────────────────────────────────────
Gamakichi::Gamakichi(sf::Vector2f pos)
    : SimpleEnemy(EnemyType::Gamakichi, 0.f, pos)
{
    health = 1000;
    pushable = false;

    body.setSize(sf::Vector2f(400.f, 250.f));
    body.setFillColor(sf::Color::Cyan);
    body.setPosition(pos);

    position = pos;
    basePosition = pos;

    phase = GamaPhase::Phase1;
    idleTimer = 0.f;

    // ── 6 cannons arranged in a TOP semicircle ────────────────────────────
    // Offsets are relative to the CENTRE of the boss body.
    // Angles go from 180° (far left) to 0° (far right), all above centre (y < 0).
    //
    //   index:  0    1    2    3    4    5
    //   angle: 180  144  108   72   36    0  degrees  (left → right)
    //
    float halfW = 120.f;   // half of body width  — radius of the arc
    float halfH = 80.f;   // half of body height — vertical squish factor

    float angles[MAX_CANNONS] = { 180.f, 144.f, 108.f, 72.f, 36.f, 0.f };

    // Fire rates: outer cannons fire faster, inner (top) slower
    //float rates[MAX_CANNONS] = { 3.5f, 4.0f, 5.0f, 5.0f, 4.0f, 3.5f };
    float rates[MAX_CANNONS] =
    {
        8.5f, 9.0f, 9.5f,
        9.5f, 9.0f, 8.5f
    };
    for (int i = 0; i < MAX_CANNONS; i++)
    {
        float rad = angles[i] * 3.14159f / 180.f;

        // cos gives x (−1 at 180°, +1 at 0°), sin gives y (0 at both ends, −1 at 90°)
        float ox = halfW * std::cos(rad);
        float oy = -halfH * std::sin(rad);   // negative → above centre

        cannons[i].offset = sf::Vector2f(ox, oy);
        cannons[i].timer = (float)(i) * 0.8f;  // stagger initial shots
        cannons[i].fireRate = rates[i];
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Phase management
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::updatePhase()
{
    GamaPhase newPhase;
    if (health > 600) newPhase = GamaPhase::Phase1;
    else if (health > 300) newPhase = GamaPhase::Phase2;
    else                    newPhase = GamaPhase::Phase3;

    if (newPhase != phase)
    {
        phase = newPhase;

        // Speed up all cannon fire rates when phase increases
        float multiplier = (phase == GamaPhase::Phase2) ? 0.75f : 0.5f;
        for (int i = 0; i < MAX_CANNONS; i++)
            cannons[i].fireRate *= multiplier;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Update — slow sine float, phase colour
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::update(float dt)
{
    idleTimer += dt;
    updatePhase();

    // Call base for snowball-coat colour / rolling logic (stationary, so fine)
    SimpleEnemy::update(dt);

    // Gentle vertical float
    float floatOffset = std::sin(idleTimer * 0.6f) * 10.f;
    sf::Vector2f newPos = basePosition;
    newPos.y += floatOffset;

    body.setPosition(newPos);
    position = newPos;

    // Phase colour (overrides SimpleEnemy's snowCoat colour when not encased)
    if (!isFullyEncased())
    {
        switch (phase)
        {
        case GamaPhase::Phase1: body.setFillColor(sf::Color::Cyan);             break;
        case GamaPhase::Phase2: body.setFillColor(sf::Color(255, 140, 0));    break;
        case GamaPhase::Phase3: body.setFillColor(sf::Color::Red);              break;
        }
    }

    hitBox = body.getGlobalBounds();
}

// ─────────────────────────────────────────────────────────────────────────────
// fireCannons — called every frame by PlayState
// Each cannon independently ticks; when its timer fires it spawns one
// GamakichiChild launched in a short arc from that cannon mouth.
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::fireCannons(float dt, GamakichiChild** out, int& outCount)
{
    outCount = 0;

    // Boss centre in world space
    sf::Vector2f centre = body.getPosition() +
        sf::Vector2f(body.getSize().x / 2.f,
            body.getSize().y / 2.f);

    for (int i = 0; i < MAX_CANNONS; i++)
    {
        cannons[i].timer += dt;

        if (cannons[i].timer < cannons[i].fireRate)
            continue;

        cannons[i].timer = 0.f;

        // World-space spawn position = cannon mouth
        sf::Vector2f spawnPos = centre + cannons[i].offset;

        // Launch velocity:
        //   Horizontal — same sign as the cannon's x-offset (away from centre),
        //                with a small random spread so shots fan out.
        //   Vertical   — always upward (negative y), giving a parabolic arc.
        //                The child then falls under gravity and lands as a Botom.

        float launchSpeedX = 80.f + (rand() % 60);          // 80-140
        float launchSpeedY = -(250.f + (rand() % 100));      // −250 to −350 (upward)

        // Direction: outward from centre
        float xSign = (cannons[i].offset.x >= 0.f) ? 1.f : -1.f;
        if (cannons[i].offset.x == 0.f)
            xSign = (rand() % 2 == 0) ? 1.f : -1.f;   // top cannon picks randomly

        sf::Vector2f launchVel(xSign * launchSpeedX, launchSpeedY);

        GamakichiChild* child = new GamakichiChild(spawnPos, launchVel);

        out[outCount++] = child;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Draw — boss body + health bar + cannon dots in debug
// ─────────────────────────────────────────────────────────────────────────────
void Gamakichi::draw(sf::RenderWindow& window, bool debugMode)
{
    window.draw(body);

    // Health bar
    float barW = body.getSize().x;
    float fraction = static_cast<float>(health) / 2000.f;
    if (fraction < 0.f) fraction = 0.f;

    sf::RectangleShape hpBg(sf::Vector2f(barW, 12.f));
    hpBg.setPosition(body.getPosition().x, body.getPosition().y - 20.f);
    hpBg.setFillColor(sf::Color(60, 60, 60));
    window.draw(hpBg);

    sf::Color barCol = (phase == GamaPhase::Phase3) ? sf::Color::Red :
        (phase == GamaPhase::Phase2) ? sf::Color(255, 140, 0) :
        sf::Color::Green;

    sf::RectangleShape hpFg(sf::Vector2f(barW * fraction, 12.f));
    hpFg.setPosition(body.getPosition().x, body.getPosition().y - 20.f);
    hpFg.setFillColor(barCol);
    window.draw(hpFg);

    if (debugMode)
    {
        // Hitbox outline
        sf::RectangleShape box;
        box.setPosition(hitBox.left, hitBox.top);
        box.setSize({ hitBox.width, hitBox.height });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Magenta);
        box.setOutlineThickness(2.f);
        window.draw(box);

        // Cannon mouth dots
        sf::Vector2f centre = body.getPosition() +
            sf::Vector2f(body.getSize().x / 2.f,
                body.getSize().y / 2.f);

        for (int i = 0; i < MAX_CANNONS; i++)
        {
            sf::CircleShape dot(5.f);
            dot.setOrigin(5.f, 5.f);
            dot.setPosition(centre + cannons[i].offset);
            dot.setFillColor(sf::Color::Yellow);
            window.draw(dot);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
bool Gamakichi::isAlive() const
{
    return health > 0;
}