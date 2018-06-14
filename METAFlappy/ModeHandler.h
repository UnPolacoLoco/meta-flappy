// MainMenu.h

#ifndef _MAINMENU_h
#define _MAINMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Globals.h"
#include "Player.h"
#include "ObstacleHandler.h"

class ModeHandler
{

public:
	ModeHandler();
	void showMainMenu();
	void showCredits();
	void showInGame();
	void showDeathScreen();
	void initScore();

	MODE getMode();
	int8_t getSpeed();
	int8_t getWindowHeight();

	void setMode(MODE newMode);
	void setSpeed(int8_t newSpeed);
	void setWindowHeight(int8_t newHeight);

private:

	GameOptions currentOptions;

	Player player;
	ObstacleHandler obstacleHandler;

	int8_t speedSelectorPositionX = 6;
	int8_t windowHeightSelectorPositionX = 39;

	int8_t topScores[8];

};


#endif

