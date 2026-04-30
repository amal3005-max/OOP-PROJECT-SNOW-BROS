//#include "MogeraChild.h"
//MogeraChild::MogeraChild( sf::Vector2f MogeraPosition,sf::Vector2f playerPosition):Enemy (EnemyType::MogeraChild ,200.f,MogeraPosition)
//{
//	sf::Vector2f dir = playerPosition- MogeraPosition ;
//	
//	
//	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
//	direction = dir / length;
//}
//void MogeraChild::update(float dt)
//{
//	position += speed * dt * direction ; 
//}
//void MogeraChild::draw(sf::RenderWindow& window)
//{
//	sf::RectangleShape rect(sf::Vector2f(40, 40));
//	rect.setPosition(position);
//	rect.setFillColor(sf::Color::Yellow);
//	window.draw(rect); 
//}
