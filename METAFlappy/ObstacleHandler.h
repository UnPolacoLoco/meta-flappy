// ObstacleHandler.h

#ifndef _OBSTACLEHANDLER_h
#define _OBSTACLEHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

class ObstacleHandler
{
public:
	void initialize(Player* player);
	void drawObstacles() const;
	void updateObstacles();;

	bool checkCollision() const;

private:
	Obstacle obstacles[4];
	int16_t obstacleX = 0;
	int16_t NUM_OF_OBSTACLES = 4;
	int16_t SPACE_BETWEEN_OBSTACLES = 36;
	Player* player = nullptr;
};

#endif

