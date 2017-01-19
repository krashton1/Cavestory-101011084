#include "Player.h"
#include "Graphics.h"
#include "AnimatedSprite.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player()
{

}

Player::Player(Graphics & graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "Content/Sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false)
{
	graphics.loadImage("Content/Sprites/MyChar.png");

	setupAnimations();
	playAnimation("IdleRight");
}


void Player::draw(Graphics & graphics)
{
	AnimatedSprite::draw(graphics, int(_x), int(_y));
}

void Player::update(int elapsedTime)
{
	//apply gravity
	if (_dy <= player_constants::GRAVITY_CAP) {
		_dy += player_constants::GRAVITY*elapsedTime;
	}

	//move by dx
	_x += _dx*elapsedTime;

	//move by dy
	_y += _dy*elapsedTime;

	AnimatedSprite::update(int(elapsedTime));
}

void Player::moveLeft()
{
	_dx = -player_constants::WALK_SPEED;
	playAnimation("RunLeft");
	_facing = LEFT;
}

void Player::moveRight()
{
	_dx = player_constants::WALK_SPEED;
	playAnimation("RunRight");
	_facing = RIGHT;
}

void Player::stopMoving()
{
	_dx = 0;
	if (_facing==RIGHT) {
		playAnimation("IdleRight");
	}
	else if (_facing == LEFT) {
		playAnimation("IdleLeft");
	}
}

void Player::animationDone(std::string currentAnimation)
{

}

void Player::setupAnimations()
{
	addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
	addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
}
/*void handleTileCollisions
handles collisions with all tiles player is interacting with
*/
void Player::handleTileCollisions(std::vector<Rectangle>& others)
{
	//figure out what side collision happened and moved player acocordingly
	for (int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				_y = others.at(i).getBottom()+1;
				_dy = 0;
				break;
			case sides::BOTTOM:
				_y = others.at(i).getTop() - _boundingBox.getHeight()-1;
				_dy = 0;
				_grounded = true;
				break;
			case sides::LEFT:
				_x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				_x = others.at(i).getLeft()-_boundingBox.getWidth() - 1;
				break;
			}
		}
	}
}

const float Player::getX() const
{
	return _x;
}

const float Player::getY() const
{
	return _y;
}
