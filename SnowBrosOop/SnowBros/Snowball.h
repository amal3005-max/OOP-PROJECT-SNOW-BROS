#pragma once

#include <SFML/Graphics.hpp>

class Snowball
{
private:
    sf::CircleShape shape;
    float speed;
    int direction; 
    bool wrapped;

    float lifeTime;
    float maxLifeTime;
public:

    Snowball(float x, float y, int dir);

    void update(float dt);
    void draw(sf::RenderWindow& window, bool debugMode);

    sf::FloatRect getBounds() const;
    bool isWrapped() const;
    float getLifeTime() const;
    float getMaxLifeTime() const;
};