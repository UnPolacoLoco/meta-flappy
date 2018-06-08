#include "Globals.h"
#include "MainMenu.h"
#include "Images.h"
#include "ObstacleHandler.h"
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

Player player = Player(3, 10);
ObstacleHandler handler;
MainMenu mainMenu;

int16_t mapBaseDisplayCounter = 0;
int16_t mapBGDisplayCounter = 0;


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


	switch (mainMenu.getMode())
	{
	case MODE::TITLE_SCREEN:
		mainMenu.showMainMenu();
		handler.resetObstacles(mainMenu.getSpeed(), mainMenu.getWindowHeight());
		break;

	case MODE::IN_GAME:
		if (player.isPlayerAlive())
		{
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
			mapBaseDisplayCounter += handler.getScrollSpeed();
			if (mapBaseDisplayCounter <= -80)
			{
				mapBaseDisplayCounter = 0;
			}
			
			player.updatePlayer();
			player.drawPlayer();

			handler.drawObstacles();
			handler.moveObstacles();

			gb.display.print(player.getScore());


			if (handler.checkCollision() || player.checkOutOfBounds())
				player.changePlayerState(false);

		}
		else
		{
			mainMenu.setMode(MODE::DEATH_SCREEN);
			player.initialize();
			handler.resetObstacles(mainMenu.getSpeed(), mainMenu.getWindowHeight());
		}
		break;

	case MODE::DEATH_SCREEN:
		gb.display.println("Death screen.");
		gb.display.println("Press 'B' to restart game");
		
		if (gb.buttons.pressed(BUTTON_B))
			mainMenu.setMode(MODE::TITLE_SCREEN);
		break;


	case MODE::CREDITS:

		int16_t cursor = gb.display.width() + 10;

		while (true)
		{
			
			while (!gb.update());
			gb.display.clear();

			if (gb.frameCount % 15 == 0)
			{
				mapBGDisplayCounter--;
			}

			if (mapBGDisplayCounter <= -80)
			{
				mapBGDisplayCounter = 0;
			}

			gb.display.drawImage(mapBaseDisplayCounter, gb.display.height() - 5, mapBottom);
			mapBaseDisplayCounter--;

			if (mapBaseDisplayCounter <= -80)
			{
				mapBaseDisplayCounter = 0;
			}


			cursor-=2;

			gb.display.drawImage(cursor, 20, TwitterHandle);
			gb.display.drawImage(cursor - 14, 18, Twitter);

			player.initialize();
			player.drawPlayer();

			if (cursor < -90)
			{
				mainMenu.setMode(MODE::TITLE_SCREEN);
				break;
			}

		

		}
		break;
	}
	
	


	

}
