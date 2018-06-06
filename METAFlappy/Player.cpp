// 
// 
// 

#include "Player.h"

//ctor
Player::Player(float newX, float newY) : x(newX), y(newY) {}

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
