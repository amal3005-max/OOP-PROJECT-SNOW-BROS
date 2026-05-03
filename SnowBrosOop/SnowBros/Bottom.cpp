#include "Botttom.h"

Botom::Botom(sf::Vector2f p)
	: SimpleEnemy(EnemyType::Botom, 80.f, p)
{
	body.setSize(sf::Vector2f(40, 40));
	body.setFillColor(sf::Color::Green);
	body.setPosition(p);

	gravity = 800.f;
	velocity = sf::Vector2f(0.f, 0.f);
	movingLeft = true;
	onGround = false;
	decisionTimer = 0.f;
	decisionInterval = 1.5f;


	//jumpStrength = -350.f;
    jumpStrength = -400.f;
    jumpCooldown = 1.0f;
	//jumpCooldown = 2.0f; 
	jumpTimer = 0.f;

    edgeJumpTimer = 0.f;
    jumpTimerLocal = 0.f;

}

void Botom::update(float dt)
{
    SimpleEnemy::update(dt);

    if (isrolling())
        return;

    float x = body.getPosition().x;
    float width = body.getSize().x;

    velocity.y += gravity * dt;  //gravity

    if (x <= 0.f)   //wall collision
    {
        body.setPosition(0.f, body.getPosition().y);
        movingLeft = false;
        decisionTimer = 0.f;
    }
    else if (x + width >= 800.f)
    {
        body.setPosition(800.f - width, body.getPosition().y);
        movingLeft = true;
        decisionTimer = 0.f;
    }

   
    decisionTimer += dt;      //random direction
    if (decisionTimer >= decisionInterval)
    {
        decisionTimer = 0.f;

        int r = rand() % 100;
        if (r < 50) movingLeft = true;
        else movingLeft = false;
    }

    float currentSpeed = speed;  //speed

    if (snowCoat > 0 && !isFullyEncased())
        currentSpeed *= 0.2f;

    if (isFullyEncased())
        velocity.x = 0.f;
    else
        velocity.x = movingLeft ? -currentSpeed : currentSpeed;

    body.move(velocity* dt);  //move
    position = body.getPosition();

  
    if (body.getPosition().y >= 500.f)   //floor collision
    {
        body.setPosition(body.getPosition().x, 500.f);
        velocity.y = 0.f;
        onGround = true;
    }

    edgeJumpTimer += dt;

    if (onGround)
        jumpTimerLocal += dt;
    else
        jumpTimerLocal = 0.f;

    bool atEdge =
        (movingLeft && x <= 5.f) ||
        (!movingLeft && x + width >= 795.f);

    if (jumpTimerLocal >= jumpCooldown && onGround && !isFullyEncased())
    {
        bool shouldJump = false;

        if (atEdge && edgeJumpTimer >= 0.5f)
        {
            shouldJump = true;
            edgeJumpTimer = 0.f;
        }

        // Random jump
        if (rand() % 100 < 40)
            shouldJump = true;

        if (shouldJump)
        {
            velocity.y = jumpStrength;
            onGround = false;
        }

        jumpTimerLocal = 0.f;
    }
    hitBox = body.getGlobalBounds();
}

void Botom::draw(sf::RenderWindow& window, bool debugMode)
{
	window.draw(body);

	if (debugMode)
	{
		sf::RectangleShape box;
		box.setPosition(hitBox.left, hitBox.top);
		box.setSize({ hitBox.width, hitBox.height });
		box.setFillColor(sf::Color::Transparent);
		box.setOutlineColor(sf::Color::Red);
		box.setOutlineThickness(1.f);

		window.draw(box);
	}
}
void Botom::reverse()
{
	direction.x *= -1;
}
