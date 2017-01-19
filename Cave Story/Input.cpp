#include "Input.h"

#include <SDL.h>

/*Input class
Keeps track of keyboard states
*/

//This function gets called at the beggining of each frame 
//to reset and update keys which are no longer relevant
void Input::beginNewFrame() 
{
	_pressedKeys.clear();
	_releasedKeys.clear();
}

//This gets called when a key is pressed
void Input::keyDownEvent(const SDL_Event& event) 
{
	_pressedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event) 
{
	_releasedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = false;
}

//checks if a key was pressed
bool Input::wasKeyPressed(SDL_Scancode key) 
{
	return _pressedKeys[key];
}

//checks if a key was released
bool Input::wasKeyReleased(SDL_Scancode key) 
{
	return _releasedKeys[key];
}

//Checks if a key is being held
bool Input::isKeyHeld(SDL_Scancode key) 
{
	return _heldKeys[key];
}