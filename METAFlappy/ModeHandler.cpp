// 
// 
// 

#include "ModeHandler.h"
#include "Images.h"



ModeHandler::ModeHandler()
{
	currentOptions.gameMode = 2; // start with Credits
	player = Player(3, 5);
	player.initialize();
	obstacleHandler.initializeHandler(&player);
	currentOptions.speed = -1;
	currentOptions.windowHeight = 24;
	
}

void ModeHandler::showMainMenu()
{


	int8_t arrowPosition = 2;
	int8_t arrowDestination = 0;


	int8_t verticalSelection = 0;
	currentOptions.speed = this->getSpeed();
	currentOptions.windowHeight = this->getWindowHeight();


	while (true) 
	{
		while (!gb.update());
		gb.display.clear();

		gb.display.drawImage(0, 0, bg);

		//check buttons
		if (gb.buttons.pressed(BUTTON_UP)) {
			verticalSelection = (verticalSelection - 1) % 4;
			verticalSelection = constrain(verticalSelection, 0, 3);
			gb.sound.playTick();
		}


		//move selector
		if (gb.buttons.pressed(BUTTON_DOWN)) {
			verticalSelection = (verticalSelection + 1) % 4;
			verticalSelection = constrain(verticalSelection, 0, 3);
			gb.sound.playTick();
		}

		if (gb.buttons.repeat(BUTTON_RIGHT, 3) && verticalSelection == 1) 
		{
			speedSelectorPositionX = (speedSelectorPositionX + 19);
			speedSelectorPositionX = constrain(speedSelectorPositionX, 6, 25);
			gb.sound.playTick();
		}

		if (gb.buttons.repeat(BUTTON_LEFT, 3) && verticalSelection == 1) 
		{
			speedSelectorPositionX = (speedSelectorPositionX - 19);
			speedSelectorPositionX = constrain(speedSelectorPositionX, 6, 25);
			gb.sound.playTick();
		}

		if (gb.buttons.repeat(BUTTON_RIGHT, 3) && verticalSelection == 2)
		{
			windowHeightSelectorPositionX = (windowHeightSelectorPositionX + 11);
			windowHeightSelectorPositionX = constrain(windowHeightSelectorPositionX, 6, 39);
			gb.sound.playTick();
		}

		if (gb.buttons.repeat(BUTTON_LEFT, 3) && verticalSelection == 2)
		{
			windowHeightSelectorPositionX = (windowHeightSelectorPositionX - 11);
			windowHeightSelectorPositionX = constrain(windowHeightSelectorPositionX, 6, 39);
			gb.sound.playTick();
		}



		if (gb.buttons.pressed(BUTTON_A)) {
			switch (verticalSelection) 
			{
			case 0: //the final case after pressing "A" on "Play Game"
				gb.sound.playOK();

				switch (windowHeightSelectorPositionX)
				{
				case 6:
					this->setWindowHeight(18);
					break;
				case 17:
					this->setWindowHeight(20);
					break;
				case 28:
					this->setWindowHeight(22);
					break;
				case 39:
					this->setWindowHeight(24);
					break;
				}

				this->setMode(MODE::IN_GAME);
				this->setSpeed(speedSelectorPositionX == 6 ? -1 : -2);
				obstacleHandler.resetObstacles(this->getSpeed(), this->getWindowHeight());
				return; //exit the loop upon pressing "A" on play game
				break;
			case 1:
				break;

			case 2:		
				break;
			case 3:
				this->setMode(MODE::CREDITS);
				return;
				break;
			}
		}

		switch (verticalSelection) {
		case 0:
			arrowDestination = 2;
			break;
		case 1:
			arrowDestination = 10;
			break;
		case 2:
			arrowDestination = 28;
			break;
		case 3:
			arrowDestination = 46;
		}


		//draw arrow on the left side
		gb.display.cursorX = 2;
		gb.display.cursorY = arrowDestination;
		gb.display.print("\20");


		//draw menu text
		gb.display.setColor(WHITE);

		gb.display.cursorX = 6;
		gb.display.cursorY = 2;
		gb.display.print("Play game");

		gb.display.cursorX = 6;
		gb.display.cursorY = 10;
		gb.display.print("Speed:");

		gb.display.cursorX = 6;
		gb.display.cursorY = 28;
		gb.display.print("Window Height:");

		gb.display.cursorX = 6;
		gb.display.cursorY = 46;
		gb.display.print("Credits");

		//speed selection box
		gb.display.drawImage(6, 18, speedSelection);
		gb.display.drawImage(6, 36, widthSelection);

		//draw speed selector
		if (verticalSelection == 1)
		{
			if (gb.frameCount % 2)
			{
				gb.display.drawRect(speedSelectorPositionX, 18, 19, 8);
			}
		}
		else
		{
			gb.display.drawRect(speedSelectorPositionX, 18, 19, 8);
		}

		//draw width selector
		if (verticalSelection == 2)
		{
			if (gb.frameCount % 2)
			{
				gb.display.drawRect(windowHeightSelectorPositionX, 36, 11, 8);
			}
		}
		else
		{
			gb.display.drawRect(windowHeightSelectorPositionX, 36, 11, 8);
		}
		
		gb.display.drawImage(0, gb.display.height() - 5, mapBottom);

	}
}

void ModeHandler::showCredits()
{
	float cursor = gb.display.width() + 10;
	int16_t baseDisplayCounter = 0;

	float logoY = 30;
	float speedY = 0;
	float gravi = 0.25;
	float frict = 0.95;

	while (true)
	{

		while (!gb.update());
		gb.display.clear();

		gb.display.drawImage(baseDisplayCounter, gb.display.height() - 5, mapBottom);
		baseDisplayCounter--;

		if (baseDisplayCounter <= -80)
		{
			baseDisplayCounter = 0;
		}

		cursor-= 1.5;
		speedY = speedY + gravi;
		speedY = speedY * frict;

		logoY = logoY + speedY;

		gb.display.drawImage(cursor, logoY, TwitterHandle);
		gb.display.drawImage(cursor - 30, logoY - 10, twitterLogo);

		if (speedY >= 2)
			speedY -= 6;

		if (cursor < -80)
		{
			this->setMode(MODE::TITLE_SCREEN);
			player.initialize();
			break;
		}

	}
}

void ModeHandler::showInGame()
{
	int16_t mapBaseDisplayCounter = 0;
	int16_t mapBGDisplayCounter = 0;

	while (player.isPlayerAlive())
	{
		while (!gb.update());
		gb.display.clear();

		gb.display.drawImage(mapBGDisplayCounter, 0, bg);

		if (gb.frameCount % 15 == 0)
		{
			mapBGDisplayCounter--;
		}

		if (mapBGDisplayCounter <= -80)
		{
			mapBGDisplayCounter = 0;
		}

		gb.display.drawImage(mapBaseDisplayCounter, gb.display.height() - 5, mapBottom);
		mapBaseDisplayCounter += obstacleHandler.getScrollSpeed();
		if (mapBaseDisplayCounter <= -80)
		{
			mapBaseDisplayCounter = 0;
		}

		player.updatePlayer();
		player.drawPlayer();

		obstacleHandler.drawObstacles();
		obstacleHandler.moveObstacles();

		gb.display.setColor(BLACK);
		gb.display.fillRect(-1, -1, player.getScore() >= 10 ? 10 : 6, 7);
		gb.display.setColor(WHITE);
		gb.display.drawRect(-1, -1, player.getScore() >= 10 ? 10 : 6, 8);
		gb.display.print(player.getScore());


		if (obstacleHandler.checkCollision() || player.checkOutOfBounds()) //if player hits an obstacle or goes out of bounds
		{
			player.changePlayerState(false);

			float playerX = player.getX();

			while (true) //continue moving thr player to display a death animation
			{
				while (!gb.update());
				gb.display.clear();

				gb.display.drawImage(0, gb.display.height() - 5, mapBottom);
				obstacleHandler.drawObstacles();
				player.updatePlayer();
				player.drawDeadPlayer();
				player.setX(playerX++);

				if (player.getY() > gb.display.width())
				{
					return;
				}
			}
		}

	}

	this->setMode(MODE::DEATH_SCREEN);
	obstacleHandler.resetObstacles(this->getSpeed(), this->getWindowHeight());
}

void ModeHandler::showDeathScreen()
{
	gb.display.drawImage(0, 0, bg);
	gb.display.drawImage(0, gb.display.height() - 5, mapBottom);
	gb.display.println("Game OVER!");
	gb.display.print("Mode: ");

	uint8_t index = 0;
	switch (currentOptions.speed)
	{
	case -1:
		if (currentOptions.windowHeight == 18)
		{
			index = 4;
			gb.display.println("Slow - 18");
		}
		else if (currentOptions.windowHeight == 20)
		{
			index = 5;
			gb.display.println("Slow - 20");
		}
		else if (currentOptions.windowHeight == 22)
		{
			index = 6;
			gb.display.println("Slow - 22");
		}
		else if (currentOptions.windowHeight == 24)
		{
			index = 7;
			gb.display.println("Slow - 24");
		}
		break;
	case -2:
		if (currentOptions.windowHeight == 18)
		{
			index = 0;
			gb.display.println("Fast - 18");
		}
		else if (currentOptions.windowHeight == 20)
		{
			index = 1;
			gb.display.println("Fast - 20");
		}
		else if (currentOptions.windowHeight == 22)
		{
			index = 2;
			gb.display.println("Fast - 22");
		}
		else if (currentOptions.windowHeight == 24)
		{
			index = 3;
			gb.display.println("Fast - 24");
		}
		break;

	}
	
	
	gb.display.print("Top score: ");
	gb.display.println(topScores[index]);
	gb.display.println("Your score: ");
	gb.display.setFontSize(2);
	gb.display.print("      ");
	gb.display.setColor(YELLOW);
	gb.display.println(player.getScore());
	if (player.getScore() >= topScores[index])
	{
		topScores[index] = player.getScore();
		gb.display.setFontSize(1);
		gb.display.setColor(RED);
		gb.display.println("\n ! NEW TOP SCORE !");
		gb.save.set(index, topScores[index]);

	}

	gb.display.setFontSize(1);
	gb.display.setColor(YELLOW);
	gb.display.println("Press 'B' to Restart");

	if (gb.buttons.pressed(BUTTON_B))
	{
		player.initialize();
		this->setMode(MODE::TITLE_SCREEN);
	}
}

void ModeHandler::initScore()
{
	for (int i = 0; i < 8; i++)
	{
		topScores[i] = gb.save.get(i);
	}

	// topScoreF18; //F - Fast  : 18 window height : 0 slot
	// topScoreF20; // 1 slot
	// topScoreF22; // 2 slot
	// topScoreF24; // 3 slot

	// topScoreS18; // 4 slot
	// topScoreS20; // 5 slot
	// topScoreS22; // 6 slot
	// topScoreS24; // 7 slot
}
MODE ModeHandler::getMode()
{
	switch (currentOptions.gameMode)
	{
	case 0:
		return MODE::IN_GAME;
		break;
	case 2:
		return MODE::CREDITS;
		break;
	case 3:
		return MODE::DEATH_SCREEN;
		break;
	case 4:
		return MODE::TITLE_SCREEN;
		break;

	}
	
}

int8_t ModeHandler::getSpeed()
{
	return currentOptions.speed;
}

int8_t ModeHandler::getWindowHeight()
{
	return currentOptions.windowHeight;
}

void ModeHandler::setMode(MODE newMode)
{
	switch (newMode)
	{
	case MODE::IN_GAME:
		currentOptions.gameMode = 0;
		break;
	case MODE::CREDITS:
		currentOptions.gameMode = 2;
		break;
	case MODE::DEATH_SCREEN:
		currentOptions.gameMode = 3;
		break;
	case MODE::TITLE_SCREEN:
		currentOptions.gameMode = 4;
		break;
	}
}

void ModeHandler::setSpeed(int8_t newSpeed)
{
	currentOptions.speed = newSpeed;
}

void ModeHandler::setWindowHeight(int8_t newHeight)
{
	currentOptions.windowHeight = newHeight;
}

