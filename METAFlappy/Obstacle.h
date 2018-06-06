// Obstacle.h

#ifndef _OBSTACLE_h
#define _OBSTACLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



class Obstacle
{
public:
	Obstacle();
	Obstacle(int16_t WindowY);


	void moveObstacle();
	void drawObstacle() const;
	void resetObstacle(int8_t previousWindowY);
	void resetToDefaults();

	void setObstacleX(int16_t newX);
	void setWindowHeight(int8_t newWindowHeight);

	int16_t getObstacleX() const;
	int16_t getObstacleTopY() const;
	int16_t getObstacleBottomY() const;
	int16_t getObstacleWindowY() const;

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

	int16_t defaultWindowHeight = 24;
	int16_t defaultObstacleScrollSpeed = -1;

	int16_t previousObstacleX;
	int16_t previousWindowY;




};

#endif

