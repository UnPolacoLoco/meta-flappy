#include "ObstacleHandler.h"
#include "Obstacle.h"
#include "Player.h"
#include <Gamebuino-Meta.h>

float gravity = 0.3;
float friction = 0.95;

const byte SPLASH_SCREEN = 0;
const byte IN_GAME = 1;
const byte GAMER_OVER = 2;

Player player = Player(3, 5);

ObstacleHandler handler;


void setup() {
  // put your setup code here, to run once:
	gb.begin();
	handler.initialize(&player);
	gb.pickRandomSeed();
}


void loop() {
  // put your main code here, to run repeatedly:
	while (!gb.update());
	gb.display.clear();


	player.updatePlayer();
	player.drawPlayer();
	
	handler.drawObstacles();
	handler.updateObstacles();

	gb.display.print(player.getScore());


	/*if (!handler.checkCollision())
		gb.display.print("SUCCESS");
	else
		gb.display.print("FAIL");*/


	

}
