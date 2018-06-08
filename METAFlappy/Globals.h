#pragma once

struct GameOptions
{
	int8_t speed;
	int8_t windowHeight;
	int8_t gameMode = 4; //defaults to TITLE_SCREEN (4) upon creation
};

enum class MODE
{
	IN_GAME,
	CREDITS = 2,
	DEATH_SCREEN,
	TITLE_SCREEN,
};
