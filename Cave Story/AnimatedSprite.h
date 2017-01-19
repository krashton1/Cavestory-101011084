#pragma once
#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Globals.h"

class Graphics;

/* Animated Sprite class
Holds logic for animated sprites
*/


class AnimatedSprite : public Sprite 
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);

	/* void playAnimation
	Plays the animation if it is not already playing
	*/
	void playAnimation(std::string animation, bool once = false);

	/* void update
	updates the animated sprite (timer)
	*/
	void update(int elapsedTime);

	/* void draw
	draws the sprite to the screen
	*/
	void draw(Graphics &graphics, int x, int y);

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	/*void addAnimation
	adds animation to the map of animations for a sprite*/
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/*void resetAnimations
	resets all animations associated with this sprite
	*/
	void resetAnimations();

	/*void stopAnimation
	stops the current animation
	*/
	void stopAnimation();

	/*void setVisible
	changes visinility of animated sprite
	*/
	void setVisible(bool visible);

	/*void animationDone
	logic that happens when an animation ends*/
	virtual void animationDone(std::string currentAnimation) = 0;

	/*void setupAnimations
	A required function that sets up all the animations for a sprite
	*/
	virtual void setupAnimations() = 0;

private:
	
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
	
};


#endif // !ANIMATED_SPRITE_H
