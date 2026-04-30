//#include "ProjectileArtillery.h"
//ProjectileArtillery::ProjectileArtillery(sf::Vector2f position, sf::Vector2f velocity, float damage, bool firedbyenemy) :Projectile(position, velocity, damage, firedbyenemy)
//{
//	float length = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
//	direction = velocity / length;
//}
//void ProjectileArtillery::update(float dt)
//{
//	position += velocity * dt;
//}
//void ProjectileArtillery::draw(sf::RenderWindow& window)
//{
//	sf::RectangleShape rect (sf::Vector2f(80, 80));
//	rect.setPosition(position);
//	rect.setFillColor(sf::Color::Black);
//	window.draw(rect);
//}
//void ProjectileArtillery::ProjectileHit() 
//{
//	visible = false;
//}