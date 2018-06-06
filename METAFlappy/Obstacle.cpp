// 
// 
// 

#include "Obstacle.h"
#include <Gamebuino-Meta.h>

Obstacle::Obstacle() {}

Obstacle::Obstacle(int16_t windowY)
{
	resetRectangles(windowY);
}


void Obstacle::moveObstacle()
{
		topRectangle.x += obstacleScrollSpeed;
		bottomRectangle.x += obstacleScrollSpeed;
}

void Obstacle::drawObstacle() const
{
	gb.display.drawRect(topRectangle.x, topRectangle.y, topRectangle.w, topRectangle.l);
	gb.display.drawRect(bottomRectangle.x, bottomRectangle.y, bottomRectangle.w, bottomRectangle.l);
}

void Obstacle::resetObstacle(int8_t previousWindowY)
{
	//set an offset so that the random number doesnt stick to top or bottom for too long. Feed the offsets in the random number generator based on where the previous window was
	int8_t upperOffset;
	int8_t lowerOffset;

	if (previousWindowY > gb.display.height() - 20)
	{
		lowerOffset = -30;
		upperOffset = -10;

	}
	else if (previousWindowY < 20)
	{
		lowerOffset = 10;
		upperOffset = 30;
	}
	else
	{
		lowerOffset = -15;
		upperOffset = 15;
	}

	resetRectangles(previousWindowY + random(lowerOffset, upperOffset));
}

void Obstacle::resetToDefaults()
{
	obstacleScrollSpeed = defaultObstacleScrollSpeed;
	windowHeight = defaultWindowHeight;
}


void Obstacle::setObstacleX(int16_t newX)
{
	topRectangle.x = newX;
	bottomRectangle.x = newX;
}

void Obstacle::setWindowHeight(int8_t newWindowHeight)
{
	windowHeight = newWindowHeight;
}

int16_t Obstacle::getObstacleX() const
{
	return topRectangle.x;
}

int16_t Obstacle::getObstacleTopY() const
{
	return topRectangle.y;
}

int16_t Obstacle::getObstacleBottomY() const
{
	return bottomRectangle.y;
}

int16_t Obstacle::getObstacleWindowY() const
{
	return bottomRectangle.y - windowHeight / 2;
}

int16_t Obstacle::getWidth() const
{
	return topRectangle.w;
}

int16_t Obstacle::getTopHeight() const
{
	return topRectangle.l;
}

int16_t Obstacle::getBottomHeight() const
{
	return bottomRectangle.l;
}

int16_t Obstacle::getWindowHeight() const
{
	return windowHeight;
}

void Obstacle::resetRectangles(int16_t previousWindowY)
{
	topRectangle.x = 4 * 36; //4 (amount of obstacles) * 36 (distance between each in pixels)
	topRectangle.y = 0;
	topRectangle.l = previousWindowY - windowHeight / 2;

	if (topRectangle.l < 0) // if, after the update the top rectangle is too short out of screen, reset it to be 4 long
	{
		topRectangle.l = 4;
	}
	else if (topRectangle.l > gb.display.height() - windowHeight - 3) // if, after the update the top rectangle is too long, reset it so that the bottom rect can be at least 4 long
	{
		topRectangle.l = gb.display.height() - windowHeight - 4;
	}

	bottomRectangle.x = topRectangle.x;
	bottomRectangle.y = topRectangle.l + windowHeight;
	bottomRectangle.l = gb.display.height() - bottomRectangle.y;

}
