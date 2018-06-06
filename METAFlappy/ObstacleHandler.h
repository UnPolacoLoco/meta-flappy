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

class ObstacleHandler
{
public:
	void initializeHandler(Player* player);
	void resetObstacles();
	void resetToDefaults();
	void drawObstacles() const;
	void moveObstacles();

	bool checkCollision() const;

	void setWindowHeight(int8_t newWindowHight);

private:
	Obstacle obstacles[4];
	int16_t obstacleX = 0;
	int16_t NUM_OF_OBSTACLES = 4;
	int16_t SPACE_BETWEEN_OBSTACLES = 36;
	Player* player = nullptr;
	
};

#endif

