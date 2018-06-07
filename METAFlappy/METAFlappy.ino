#include "Images.h"
#include "ObstacleHandler.h"
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

Player player = Player(3, 5);
ObstacleHandler handler;

const int8_t TITLE_SCREEN = 4;
const int8_t IN_GAME = 0;
const int8_t OPTIONS = 1;
const int8_t CREDITS = 2;
const int8_t DEATH_SCREEN = 3;

int8_t currentMode = TITLE_SCREEN;
int8_t selectedSpeed = -1;
int8_t selectedWindowHeight = 24;

int16_t mapBaseDisplayCounter = 0;
int16_t mapBGDisplayCounter = 0;

const char* titleScreenMenuEntries[] = { "PLAY", "OPTIONS", "CREDITS" };
const char* optionsMenuEntries[] = { "WINDOW SIZE", "SPEED","              APPLY", "               BACK"};
const char* windowSizeOptionsMenuEntries[] = {"18", "20", "24", "               BACK" };
const char* speedOptionsMenuEntries[] = { "NORMAL", "FAST", "               BACK" };




void setup() {
  // put your setup code here, to run once:
	gb.begin();
	handler.initializeHandler(&player);
	player.initialize();
	gb.pickRandomSeed();
}


void loop() {
  // put your main code here, to run repeatedly:
	while (!gb.update());
	gb.display.clear();


	switch (currentMode)
	{
	case TITLE_SCREEN:
		currentMode = gb.gui.menu("METAFlappy", titleScreenMenuEntries);
		break;
	case IN_GAME:
		if (player.isPlayerAlive())
		{
			gb.display.drawImage(mapBGDisplayCounter, 0, bg);

			if (gb.frameCount % 15 == 0)
			{
				mapBGDisplayCounter--;
			}

			if (mapBGDisplayCounter == -80)
			{
				mapBGDisplayCounter = 0;
			}

			gb.display.drawImage(mapBaseDisplayCounter, gb.display.height() - 5, mapBottom);
			mapBaseDisplayCounter += handler.getScrollSpeed();
			if (mapBaseDisplayCounter == -80)
			{
				mapBaseDisplayCounter = 0;
			}
			
			player.updatePlayer();
			player.drawPlayer();

			handler.drawObstacles();
			handler.moveObstacles();

			gb.display.print(player.getScore());

			if (handler.checkCollision())
				player.changePlayerState(false);

		}
		else
		{
			currentMode = DEATH_SCREEN;
			player.initialize();
			handler.resetObstacles(selectedSpeed, selectedWindowHeight);
		}
		break;

	case DEATH_SCREEN:
		gb.display.println("Death screen.");
		gb.display.println("Press 'B' to restart game");
		
		if (gb.buttons.pressed(BUTTON_B))
			currentMode = TITLE_SCREEN;
		break;

	case OPTIONS:
		

		switch (gb.gui.menu("OPTIONS", optionsMenuEntries))
		{
		default:
			gb.display.fontSize = 1;
			gb.display.setCursorY(50);
			gb.display.print("SPEED: %d");
			gb.display.print("HEIGHT: %d");
			break;

		case 0:
			switch (gb.gui.menu("WINDOW SIZE", windowSizeOptionsMenuEntries))
			{
			case 0:
				selectedWindowHeight = 18;
				break;
			case 1:
				selectedWindowHeight = 20;
				break;
			case 2:
				selectedWindowHeight = 24;
				break;
			case 3:
				break;
			}
			break;
		case 1:
			switch (gb.gui.menu("SPEED", speedOptionsMenuEntries))
			{
			case 0:
				selectedSpeed = -1;
				break;
			case 1:
				selectedSpeed = -2;
				break;
			case 2:
				break;
			}
			break;
		case 2: //Accept button
			handler.resetObstacles(selectedSpeed, selectedWindowHeight);
			currentMode = TITLE_SCREEN;
			break;
		case 3: //back button
			currentMode = TITLE_SCREEN;
			break;
		}
	
		break;

	case CREDITS:
		gb.display.println("Credits screen.");
		gb.display.println("Press 'B' to exit");
		if (gb.buttons.pressed(BUTTON_B))
			currentMode = TITLE_SCREEN;
		break;
	}
	
	


	

}
