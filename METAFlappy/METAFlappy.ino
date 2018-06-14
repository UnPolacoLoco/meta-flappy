#include "Globals.h"
#include "ModeHandler.h"
#include "Images.h"
#include "ObstacleHandler.h"
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

ModeHandler modeHandler;


void setup() {
  // put your setup code here, to run once:
	gb.begin();
	modeHandler.initScore();

}


void loop() {
  // put your main code here, to run repeatedly:
	while (!gb.update());
	gb.display.clear();

	switch (modeHandler.getMode())
	{
	case MODE::TITLE_SCREEN:
		modeHandler.showMainMenu();
		break;

	case MODE::IN_GAME:
		modeHandler.showInGame();
		break;

	case MODE::DEATH_SCREEN:
		modeHandler.showDeathScreen();
		break;


	case MODE::CREDITS:
		modeHandler.showCredits();
		break;
	}

}
