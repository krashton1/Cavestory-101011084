#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"
#include "Globals.h"

class Graphics;

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	void draw(Graphics &graphics);
	void update(int elapsedTime);

	/*void moveLeft
	moves player left by -dx
	*/
	void moveLeft();
	
	/*void move right
	moves player by +dx
	*/
	void moveRight();
	
	/*void stopMoving
	Stops moving the player
	*/
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector<Rectangle>&others);

	const float getX() const;
	const float getY() const;

private:
	float _dx, _dy;

	Direction _facing;

	bool _grounded;
};

#endif // !PLAYER_H
