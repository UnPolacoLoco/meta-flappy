// 
// 
// 

#include "ObstacleHandler.h"


void ObstacleHandler::initializeHandler(Player* player)
{
	this->player = player;
	obstacles[0] = Obstacle(30);
	obstacles[0].setObstacleX(gb.display.width());
	obstacleX = obstacles[0].getObstacleX();
	

	for (int i = 1; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i] = Obstacle(40 + random(-15,15));
		obstacles[i].setObstacleX(obstacleX + SPACE_BETWEEN_OBSTACLES);
		obstacleX += SPACE_BETWEEN_OBSTACLES;
	}
}

void ObstacleHandler::resetObstacles()
{
	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i] = 0;

	}

	obstacles[0] = Obstacle(30);
	obstacles[0].setObstacleX(gb.display.width());
	obstacleX = obstacles[0].getObstacleX();

	for (int i = 1; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i] = Obstacle(30 + random(-15, 15));
		obstacles[i].setObstacleX(obstacleX + SPACE_BETWEEN_OBSTACLES);
		obstacleX += SPACE_BETWEEN_OBSTACLES;
	}


}

void ObstacleHandler::resetObstacles(int8_t scrolLSpeed, int8_t windowHeight)
{
	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i] = 0;
	}

	obstacles[0] = Obstacle(30, windowHeight, scrolLSpeed);
	obstacles[0].setObstacleX(gb.display.width());
	obstacleX = obstacles[0].getObstacleX();

	for (int i = 1; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i] = Obstacle(30 + random(-15, 15), windowHeight, scrolLSpeed);
		obstacles[i].setObstacleX(obstacleX + SPACE_BETWEEN_OBSTACLES);
		obstacleX += SPACE_BETWEEN_OBSTACLES;
	}

	drawObstacles();


}

void ObstacleHandler::drawObstacles() const
{
	gb.display.setColor(GREEN);

	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i].drawObstacle();
	}
}

void ObstacleHandler::moveObstacles()
{
	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i].moveObstacle(); //move obstacles along

		if (obstacles[i].getObstacleX() + obstacles[i].getWidth() < 0) //if obstacle leaves the screen behing the player
		{
			byte previousY = 0;
			if (i != 0) //get position of previous window btween the rectangles
				previousY = obstacles[i - 1].getObstacleWindowY();
			else
				previousY = obstacles[3].getObstacleWindowY();

			obstacles[i].resetObstacle(previousY);

			player->increaseScore();
		}
	}
}

void ObstacleHandler::setScrollSpeed(int8_t newScrollSpeed)
{
	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i].changeScrollSpeed(newScrollSpeed);
	}
}

int8_t ObstacleHandler::getScrollSpeed()
{
	return obstacles[0].getScrollSpeed();
}

bool ObstacleHandler::checkCollision() const
{
	if (player == nullptr) { gb.display.print("Player in ObstacleHandler is a nullptr"); }

	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		if (gb.collideRectRect(obstacles[i].getObstacleX(), obstacles[i].getObstacleTopY(), obstacles[i].getWidth(), obstacles[i].getTopHeight(), player->getX(), player->getY(), player->getWidth(), player->getHeight()))
		{
			return true;
		}
		else if (gb.collideRectRect(obstacles[i].getObstacleX(), obstacles[i].getObstacleBottomY(), obstacles[i].getWidth(), obstacles[i].getBottomHeight(), player->getX(), player->getY(), player->getWidth(), player->getHeight()))
		{
			return true;
		}
	}

	return false;
}

void ObstacleHandler::setWindowHeight(int8_t newWindowHight)
{
	for (int i = 0; i < NUM_OF_OBSTACLES; i++)
	{
		obstacles[i].setWindowHeight(newWindowHight);
	}
}
