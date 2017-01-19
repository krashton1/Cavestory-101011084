

#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "globals.h"


/* Graphics class
Holds all information dealing with graphics for the game
*/

Graphics::Graphics() 
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Cavestory");
}

Graphics::~Graphics() 
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) 
{
	if (_spriteSheets.count(filePath) == 0) {
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) 
{
	SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() 
{
	SDL_RenderPresent(_renderer);
}

void Graphics::clear() 
{
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const 
{
	return _renderer;
}