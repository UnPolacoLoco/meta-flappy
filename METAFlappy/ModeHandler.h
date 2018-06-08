// MainMenu.h

#ifndef _MAINMENU_h
#define _MAINMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Globals.h"

class Player;
class ObstacleHandler;

class ModeHandler
{

public:
	ModeHandler();
	void showMainMenu();
	void showCredits();
	MODE getMode();
	int8_t getSpeed();
	int8_t getWindowHeight();

	void setMode(MODE newMode);
	void setSpeed(int8_t newSpeed);
	void setWindowHeight(int8_t newHeight);

private:
	GameOptions currentOptions;

};


#endif

