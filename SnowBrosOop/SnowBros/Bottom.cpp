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

//
//
//void Botom::update(float dt)
//{
//    SimpleEnemy::update(dt);
//
//    if (isrolling())
//        return;
//
//    float x = body.getPosition().x;
//    float width = body.getSize().x;
//
//    bool nearLeftEdge = (x <= 5.f);
//    bool nearRightEdge = (x + width >= 795.f);
//
//    //jumpTimer += dt;
//
//    //if (jumpTimer >= jumpCooldown && onGround && !isFullyEncased())
//    //{
//    //    bool shouldJump = false;
//
//    //    float x = body.getPosition().x;
//    //    float width = body.getSize().x;
//
//    //    if ((movingLeft && x <= 5.f) || (!movingLeft && x + width >= 795.f))
//    //    {
//    //        shouldJump = true;
//    //    }
//
//    //    if (rand() % 100 < 20)
//    //    {
//    //        shouldJump = true;
//    //    }
//
//    //    if (shouldJump)
//    //    {
//    //        velocity.y = jumpStrength;
//    //    }
//
//    //    jumpTimer = 0.f;
//    //}
//
//    //onGround = false;
//
//    velocity.y += gravity * dt;
//
//    decisionTimer += dt;
//    if (decisionTimer >= decisionInterval)
//    {
//        decisionTimer = 0.f;
//
//        int r = rand() % 100;
//        if (r < 40) movingLeft = true;
//        else if (r < 80) movingLeft = false;
//    }
//
//    float currentSpeed = speed;
//
//    if (snowCoat > 0 && !isFullyEncased())
//        currentSpeed *= 0.2f;
//
//    if (isFullyEncased())
//        velocity.x = 0.f;
//    else
//        velocity.x = movingLeft ? -currentSpeed : currentSpeed;
//
//    body.move(velocity * dt);
//    position = body.getPosition();
//
//    if (body.getPosition().y >= 500.f)
//    {
//        body.setPosition(body.getPosition().x, 500.f);
//        velocity.y = 0;
//    }
//
//    float a = body.getPosition().x;
//    float wwidth = body.getSize().x;
//
//    if (a <= 0.f)
//    {
//        body.setPosition(0.f, body.getPosition().y);
//        movingLeft = false;
//    }
//    else if (a + wwidth >= 800.f)
//    {
//        body.setPosition(800.f - wwidth, body.getPosition().y);
//        movingLeft = true;
//    }
//
//    // ─── JUMP LOGIC ───
//    jumpTimer += dt;
//
//    if (jumpTimer >= jumpCooldown && onGround && !isFullyEncased())
//    {
//        bool shouldJump = false;
//
//        float x = body.getPosition().x;
//        float width = body.getSize().x;
//
//        // Edge jump
//        if ((movingLeft && x <= 5.f) || (!movingLeft && x + width >= 795.f))
//            shouldJump = true;
//
//        //  KEY FIX: jump if player is above
//        if (targetPosition.y < position.y - 40.f)
//            shouldJump = true;
//
//        // Random jump
//        if (rand() % 100 < 30)
//            shouldJump = true;
//
//        if (shouldJump)
//        {
//            velocity.y = jumpStrength;
//            onGround = false;
//        }
//
//        jumpTimer = 0.f;
//    }
//
//
//    hitBox = body.getGlobalBounds();
//}
//

//void Botom::update(float dt)
//{
//    SimpleEnemy::update(dt);
//
//    if (isrolling())
//        return;
//
//    float x = body.getPosition().x;
//    float width = body.getSize().x;
//
//    // ─────────────────────────────
//    // GRAVITY
//    // ─────────────────────────────
//    velocity.y += gravity * dt;
//
//    // ─────────────────────────────
//    // WALL BOUNCE + DIRECTION FLIP
//    // ─────────────────────────────
//    if (x <= 0.f)
//    {
//        body.setPosition(0.f, body.getPosition().y);
//        movingLeft = false;
//        decisionTimer = 0.f;
//    }
//    else if (x + width >= 800.f)
//    {
//        body.setPosition(800.f - width, body.getPosition().y);
//        movingLeft = true;
//        decisionTimer = 0.f;
//    }
//
//    // ─────────────────────────────
//    // RANDOM WALK DIRECTION
//    // ─────────────────────────────
//    decisionTimer += dt;
//    if (decisionTimer >= decisionInterval)
//    {
//        decisionTimer = 0.f;
//
//        int r = rand() % 100;
//        if (r < 50) movingLeft = true;
//        else movingLeft = false;
//    }
//
//    // ─────────────────────────────
//    // MOVE HORIZONTALLY
//    // ─────────────────────────────
//    float currentSpeed = speed;
//
//    if (snowCoat > 0 && !isFullyEncased())
//        currentSpeed *= 0.2f;
//
//    if (isFullyEncased())
//        velocity.x = 0.f;
//    else
//        velocity.x = movingLeft ? -currentSpeed : currentSpeed;
//
//    // ─────────────────────────────
//    // APPLY MOVEMENT
//    // ─────────────────────────────
//    body.move(velocity * dt);
//    position = body.getPosition();
//
//    // ─────────────────────────────
//    // FLOOR FALLBACK
//    // ─────────────────────────────
//    if (body.getPosition().y >= 500.f)
//    {
//        body.setPosition(body.getPosition().x, 500.f);
//        velocity.y = 0.f;
//        onGround = true;
//    }
//
//    // IMPORTANT:
//    // onGround is also set by platform collisions in PlayState
//
//    // ─────────────────────────────
//    // JUMP TIMERS (GLOBAL BEHAVIOR)
//    // ─────────────────────────────
//    jumpTimer += dt;
//    edgeJumpTimer += dt;
//
//    // ─────────────────────────────
//    // EDGE DETECTION
//    // ─────────────────────────────
//    bool atEdge =
//        (movingLeft && x <= 5.f) ||
//        (!movingLeft && x + width >= 795.f);
//
//    // ─────────────────────────────
//    // JUMP LOGIC (UNIFORM ON ALL SURFACES)
//    // ─────────────────────────────
//    if (jumpTimer >= jumpCooldown && onGround && !isFullyEncased())
//    {
//        bool shouldJump = false;
//
//        // edge jump (always valid)
//        if (atEdge && edgeJumpTimer >= 0.5f)
//        {
//            shouldJump = true;
//            edgeJumpTimer = 0.f;
//        }
//
//        // random jump (SAME everywhere: ground OR platform)
//        if (rand() % 100 < 40)
//        {
//            shouldJump = true;
//        }
//
//        if (shouldJump)
//        {
//            velocity.y = jumpStrength;
//            onGround = false;
//        }
//
//        jumpTimer = 0.f;
//    }
//
//    // ─────────────────────────────
//    // HITBOX UPDATE
//    // ─────────────────────────────
//    hitBox = body.getGlobalBounds();
//}
void Botom::update(float dt)
{
    SimpleEnemy::update(dt);

    if (isrolling())
        return;

    float x = body.getPosition().x;
    float width = body.getSize().x;

    // ─────────────────────────────
    // GRAVITY
    // ─────────────────────────────
    velocity.y += gravity * dt;

    // ─────────────────────────────
    // WALL COLLISION (TURN AROUND)
    // ─────────────────────────────
    if (x <= 0.f)
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

    // ─────────────────────────────
    // RANDOM DIRECTION CHANGE
    // ─────────────────────────────
    decisionTimer += dt;
    if (decisionTimer >= decisionInterval)
    {
        decisionTimer = 0.f;

        int r = rand() % 100;
        if (r < 50) movingLeft = true;
        else movingLeft = false;
    }

    // ─────────────────────────────
    // SPEED CONTROL
    // ─────────────────────────────
    float currentSpeed = speed;

    if (snowCoat > 0 && !isFullyEncased())
        currentSpeed *= 0.2f;

    if (isFullyEncased())
        velocity.x = 0.f;
    else
        velocity.x = movingLeft ? -currentSpeed : currentSpeed;

    // ─────────────────────────────
    // MOVE
    // ─────────────────────────────
    body.move(velocity* dt);
    position = body.getPosition();

    // ─────────────────────────────
    // FLOOR COLLISION
    // ─────────────────────────────
    if (body.getPosition().y >= 500.f)
    {
        body.setPosition(body.getPosition().x, 500.f);
        velocity.y = 0.f;
        onGround = true;
    }

    // IMPORTANT:
    // DO NOT reset onGround here
    // PlayState + platform collision handles it

    // ─────────────────────────────
    // JUMP TIMERS
    // ─────────────────────────────
    //static float edgeJumpTimer = 0.f;
    //static float jumpTimerLocal = 0.f;

    edgeJumpTimer += dt;

    if (onGround)
        jumpTimerLocal += dt;
    else
        jumpTimerLocal = 0.f;

    // ─────────────────────────────
    // JUMP LOGIC
    // ─────────────────────────────
    bool atEdge =
        (movingLeft && x <= 5.f) ||
        (!movingLeft && x + width >= 795.f);

    if (jumpTimerLocal >= jumpCooldown && onGround && !isFullyEncased())
    {
        bool shouldJump = false;

        // Edge jump (controlled)
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

    // ─────────────────────────────
    // UPDATE HITBOX
    // ─────────────────────────────
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
