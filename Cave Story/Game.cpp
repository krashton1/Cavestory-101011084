#include <SDL.h>

#include "Game.h"
#include "Graphics.h"
#include "Input.h"

#include <algorithm>

/* Game Class
This class hols all the info for our main game
*/

namespace 
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

Game::~Game() 
{

}

void Game::gameLoop() 
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	_level = Level("Map1", Vector2(100, 100), graphics);
	_player = Player(graphics, _level.getPlayerSpawnPoint());

	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start the game loop
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			_player.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			_player.moveRight();
		}
		
		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			_player.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) 
{
	graphics.clear();

	_level.draw(graphics);
	_player.draw(graphics);

	graphics.flip();
}

void Game::update(int elapsedTime) 
{
	_level.update(elapsedTime);
	_player.update(elapsedTime);

	//Check collisions
	std::vector<Rectangle> others;
	if ((others = _level.checkTileCollisions(_player.getBoundingBox())).size() > 0) {
		//Player collided with at least one tile. Handle it.
		_player.handleTileCollisions(others);
	}
}