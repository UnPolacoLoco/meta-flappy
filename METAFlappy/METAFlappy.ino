#include "Globals.h"
#include "ModeHandler.h"
#include "Images.h"
#include "ObstacleHandler.h"
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

Player player = Player(3, 10);
ObstacleHandler handler;
ModeHandler modeHandler;

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


	switch (modeHandler.getMode())
	{
	case MODE::TITLE_SCREEN:
		modeHandler.showMainMenu();
		handler.resetObstacles(modeHandler.getSpeed(), modeHandler.getWindowHeight());
		break;

	case MODE::IN_GAME:
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
			{
				player.changePlayerState(false);

				float playerX = player.getX();

				while (true) //continue moving thr player to display a death animation
				{
					while (!gb.update());
					gb.display.clear();

					gb.display.drawImage(0, gb.display.height() - 5, mapBottom);
					handler.drawObstacles();
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
		
		modeHandler.setMode(MODE::DEATH_SCREEN);
		player.initialize();
		handler.resetObstacles(modeHandler.getSpeed(), modeHandler.getWindowHeight());
		
		break;

	case MODE::DEATH_SCREEN:
		gb.display.println("Death screen.");
		gb.display.println("Press 'B' to restart game");
		
		if (gb.buttons.pressed(BUTTON_B))
			modeHandler.setMode(MODE::TITLE_SCREEN);
		break;


	case MODE::CREDITS:
		modeHandler.showCredits();
		player.initialize();
		break;
	}
	
	


	

}
