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
