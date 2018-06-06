// 
// 
// 

#include "Player.h"

//ctor
Player::Player(float newX, float newY) : x(newX), y(newY) {}

void Player::initialize()
{
	//TODO add switch cases based on use preferences
	gravity = 0.3;
	friction = 0.95;
	speedY = 0;
	score = 0;
	isAlive = true;
	x = 3;
	y = 5;
}

void Player::updatePlayer()
{
	speedY += gravity;
	speedY *= friction;

	
	if (gb.buttons.pressed(BUTTON_A) && buttonCooldownCountDown <= 0)
	{
		speedY -= 4; 
		buttonCooldownCountDown = BUTTON_COOLDOWN;
	}
	else
	{
		buttonCooldownCountDown--;
		buttonCooldownCountDown = constrain(buttonCooldownCountDown, 0, BUTTON_COOLDOWN);
	}

	y += speedY;

}

void Player::drawPlayer()
{
	gb.display.setColor(YELLOW);
	gb.display.fillRect(x, y, width, height);
}

float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}

int8_t Player::getWidth()
{
	return width;
}

int8_t Player::getHeight()
{
	return height;
}

void Player::increaseScore()
{
	score++;
}

int16_t Player::getScore()
{
	return score;
}

bool Player::isPlayerAlive()
{
	return isAlive;
}

void Player::changePlayerState(bool newState)
{
	isAlive = newState;
}
