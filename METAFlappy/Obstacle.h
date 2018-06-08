// Obstacle.h

#ifndef _OBSTACLE_h
#define _OBSTACLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Gamebuino-Meta.h>
#include "Images.h"

class Obstacle
{
public:
	Obstacle();
	Obstacle(int16_t WindowY);
	Obstacle(int16_t windowY, int8_t windowHeight, int8_t scrollSpeed);


	void moveObstacle();
	void drawObstacle() const;
	void resetObstacle(int8_t previousWindowY);

	void setObstacleX(int16_t newX);
	void setWindowHeight(int8_t newWindowHeight);
	void changeScrollSpeed(int8_t newScrollSpeed);
	int8_t getScrollSpeed();

	int16_t getObstacleX() const;
	int16_t getObstacleTopY() const;
	int16_t getObstacleBottomY() const;
	int16_t getObstacleWindowY() const;
	void setObstacleWindowY(int8_t newWindowY);

	int16_t getWidth() const;
	int16_t getTopHeight() const;
	int16_t getBottomHeight() const;
	int16_t getWindowHeight() const;

	

private:

	struct Rectangle
	{
		int16_t x;
		int16_t y;
		int16_t w = 8;
		int16_t l;
	};

	void resetRectangles(int16_t previousWindowY);

	Rectangle topRectangle;
	Rectangle bottomRectangle;

	int16_t windowHeight = 24;
	int16_t obstacleScrollSpeed = -1;

	int16_t previousObstacleX;
	int16_t previousWindowY;

};

#endif

