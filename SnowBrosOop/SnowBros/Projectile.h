#include <SFML/Graphics.hpp>
//enum class ProjectileType {KNIFE,SNOWBALL, ARTILLERYROCKET};
//class Projectile
//{
//protected:
//	bool visible=true;
//	bool firedbyenemy = false;
//	float damage;
//	sf::FloatRect hitBox;
//	sf::Vector2f position;
//	sf::Vector2f velocity;
//public:
//	Projectile(sf::Vector2f position, sf::Vector2f velocity, float damage, bool firedbyenemy);
//	virtual void update(float dt) = 0;
//	virtual void draw(sf::RenderWindow& window) = 0;
//	virtual void ProjectileHit() = 0;
//	bool isVisible() const;
//	float getDamage() const;
//}; 

#pragma once
#include <SFML/Graphics.hpp>

enum class ProjectileType { KNIFE, SNOWBALL, ARTILLERYROCKET };

class Projectile
{
protected:
    bool visible;
    bool firedbyenemy;

    float damage;

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::FloatRect hitBox;

public:
    Projectile(sf::Vector2f position, sf::Vector2f velocity, float damage, bool firedbyenemy);

    virtual ~Projectile() {}

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void ProjectileHit() = 0;

    bool isVisible() const;
    float getDamage() const;
    sf::FloatRect getBounds() const;

    void setInvisible();
};