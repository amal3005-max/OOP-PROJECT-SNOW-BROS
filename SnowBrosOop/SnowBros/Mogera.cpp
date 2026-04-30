//#include "Mogera.h"
//
//Mogera::Mogera(sf::Vector2f p) : Enemy(EnemyType::Mogera,0,p)
//{
//	childCount = 0;
//
//	spawnTime = 0.f;  // time to spawn child 
//}
//void Mogera::update(float dt,sf::Vector2f playerPosition)
//{
//	spawnTime += dt;
//	if (spawnTime > 3)
//	{
//		spawnChild(playerPosition);
//		spawnTime = 0;
//	}
//}
//void Mogera::spawnChild(sf::Vector2f playerPosition)
//{
//	if (childCount >= 20)
//		return;
//	children[childCount] = new MogeraChild(playerPosition, position);
//	childCount++;
//}
//void Mogera::draw(sf::RenderWindow& window)
//{
//	sf::RectangleShape rect(sf::Vector2f(100,100));
//	rect.setPosition(position);
//	rect.setFillColor(sf::Color::White);
//	for (int i=0;i<childCount;i++)
//	children[i]->draw(window);
//	window.draw(rect);
//}