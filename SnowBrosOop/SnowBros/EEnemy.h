#include  <SFML/Graphics.hpp>

enum class EnemyType { BOTOM, FlyingFoogaFog, Tornado, Mogera, Gamakichi,MogeraChild };
class Enemy
{
protected:
	
	float speed;
	bool flight;
	EnemyType type;
	bool projectile;
	bool boss;
	sf::Vector2f position;
	sf::Vector2f velocity;
		int health; 
	float snowCoat=0.f;
	bool alive=true;
	sf::FloatRect hitBox;
public:
	Enemy(EnemyType type, float speed, sf::Vector2f startPos);
	virtual void update(float dt) = 0;  
	virtual void draw(sf::RenderWindow& window) = 0;  
	void hitBySnowball(float amount);   
	bool isAlive() const;              
	bool isFullyEncased() const;        
	EnemyType getType() const;          
};
