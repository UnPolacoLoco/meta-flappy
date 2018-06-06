#include "ObstacleHandler.h"
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

//float gravity = 0.3;
//float friction = 0.95;


Player player = Player(3, 5);
ObstacleHandler handler;

const int8_t TITLE_SCREEN = 4;
const int8_t IN_GAME = 0;
const int8_t OPTIONS = 1;
const int8_t CREDITS = 2;
const int8_t DEATH_SCREEN = 3;

int8_t currentMode = TITLE_SCREEN;

const char* titleScreenMenuEntries[] = { "Play", "Options", "Credits" };
const char* optionsMenuEntries[] = { "Window Size", "Speed", "RST to defaults", "BACK"};
const char* windowSizeOptionsMenuEntries[] = { "8", "24" };
const char* speedOptionsMenuEntries[] = { "Normal", "Fast" };




void setup() {
  // put your setup code here, to run once:
	gb.begin();
	handler.initializeHandler(&player);
	player.initialize();
	gb.pickRandomSeed();
	switch (gb.gui.menu("Window Size", windowSizeOptionsMenuEntries))
	{
	case 0:
		gb.display.print("SETTING WINDOW HEIGHT!");
		handler.setWindowHeight(8);
		handler.resetObstacles();
		break;
	case 1:
		handler.setWindowHeight(24);
		break;
	}



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
			handler.resetObstacles();
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
		case 0:
			switch (gb.gui.menu("Window Size", windowSizeOptionsMenuEntries))
			{
			case 0:
				gb.display.print("SETTING WINDOW HEIGHT!");
				handler.setWindowHeight(8);
				handler.resetObstacles();
				break;
			case 1:
				handler.setWindowHeight(24);
				break;
			}
			break;
		case 1:
			gb.display.println("Speed");
			switch (gb.gui.menu("Speed", speedOptionsMenuEntries))
			break;
		case 2:
			gb.display.println("Defaults");
			break;
		case 3:
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
