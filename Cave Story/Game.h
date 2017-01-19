
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "Level.h"

class Graphics;

class Game 
{
public:
	Game();
	~Game();

private:
		void gameLoop();
		void draw(Graphics &graphics);
		void update(int elapsedTime);

		Player _player;
		Level _level;
};

#endif