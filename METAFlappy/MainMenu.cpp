// 
// 
// 

#include "MainMenu.h"
#include "Images.h"

MainMenu::MainMenu()
{
	currentOptions.gameMode = 2; // start with Credits
}

void MainMenu::showMainMenu()
{

	int8_t speedSelectorPositionX = 6;
	int8_t windowHeightSelectorPositionX = 28;

	int8_t arrowPosition = 2;
	int8_t arrowDestination = 0;


	int8_t verticalSelection = 0;
	currentOptions.speed = -1;
	currentOptions.windowHeight = 18;


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
			case 0:
				gb.sound.playOK();

				this->setMode(MODE::IN_GAME);
				this->setSpeed(speedSelectorPositionX == 6 ? -1 : -2);

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

MODE MainMenu::getMode()
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

int8_t MainMenu::getSpeed()
{
	return currentOptions.speed;
}

int8_t MainMenu::getWindowHeight()
{
	return currentOptions.windowHeight;
}

void MainMenu::setMode(MODE newMode)
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

void MainMenu::setSpeed(int8_t newSpeed)
{
	currentOptions.speed = newSpeed;
}

void MainMenu::setWindowHeight(int8_t newHeight)
{
	currentOptions.windowHeight = newHeight;
}
