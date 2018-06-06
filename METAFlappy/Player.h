// Player.h

#include <Gamebuino-Meta.h>

#ifndef _PLAYER_h
#define _PLAYER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



class Player
{
public:
	Player(float newX, float newY);
	void updatePlayer();
	void drawPlayer();
	float getX();
	float getY();
	int8_t getWidth();
	int8_t getHeight();

	void increaseScore();
	int16_t getScore();

private:
	float gravity = 0.2;
	float friction = 0.95;
	float x;
	float y;
	float speedY = 0;

	int8_t width = 10;
	int8_t height = 5;
	int16_t buttonCooldownCountDown = 0;
	int16_t BUTTON_COOLDOWN = 8;
	int16_t score = 0;


};

#endif

