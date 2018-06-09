// 
// 
// 

#include "Player.h"

//ctor
Player::Player() {}
Player::Player(float newX, float newY) : x(newX), y(newY) {}

void Player::initialize()
{
	gravity = 0.25;
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
	
	if (gb.buttons.pressed(BUTTON_A) && buttonCooldownCountDown <= 0 && isAlive)
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

	if (speedY >= 0) //draw bird going down
	{
		bird.setFrame(1);
		gb.display.drawImage(x, y, bird);
		gb.display.drawImage(x, y - 2, wing);

	}
	else if (speedY < 0) //draw bird going up
	{
		bird.setFrame(0);
		gb.display.drawImage(x,y,bird);
		gb.display.drawImage(x, y + 2, wingDown);
	}

}

void Player::drawDeadPlayer()
{
	gb.display.drawImage(x, y, birdDead);
}

float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}

void Player::setX(float newX)
{
	x = newX;
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
	gb.sound.playTick();
}

int16_t Player::getScore()
{
	return score;
}

bool Player::checkOutOfBounds()
{
	if (y + height >= gb.display.height() - 7)
	{
		return true;
	}
	else if (y <= 0)
	{
		return true;
	}

	return false;
}

bool Player::isPlayerAlive()
{
	return isAlive;
}

void Player::changePlayerState(bool newState)
{
	isAlive = newState;
}
