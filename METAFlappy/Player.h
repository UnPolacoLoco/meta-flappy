// Player.h

#include <Gamebuino-Meta.h>

#ifndef _PLAYER_h
#define _PLAYER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Images.h"



class Player
{
public:
	Player(float newX, float newY);

	void initialize();

	void updatePlayer();
	void drawPlayer();
	void drawDeadPlayer();

	float getX();
	float getY();

	void setX(float newX);
	int8_t getWidth();
	int8_t getHeight();

	void increaseScore();
	int16_t getScore();

	bool checkOutOfBounds();

	bool isPlayerAlive();
	void changePlayerState(bool newState);

private:
	float gravity = 0.25;
	float friction = 0.95;
	float x;
	float y;
	float speedY = 0;

	int8_t width = 10;
	int8_t height = 5;
	int16_t buttonCooldownCountDown = 0;
	int16_t BUTTON_COOLDOWN = 8;
	int16_t score = 0;

	bool isAlive = true;


};

#endif

