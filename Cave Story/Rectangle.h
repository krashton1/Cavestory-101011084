#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Globals.h"

class Rectangle {
public:
	Rectangle() {}

	Rectangle(int x, int y, int width, int height) :
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{}

	const int getCenterX() const { return this->_x + this->_width / 2; }
	const int getCenterY() const { return this->_y + this->_height / 2; }

	const int getLeft() const { return this->_x; }
	const int getRight() const { return this->_x + this->_width; }
	const int getTop() const { return this->_y; }
	const int getBottom() const { return this->_y + this->_height; }

	const int getWidth() const { return this->_width; }
	const int getHeight() const { return this->_height; }

	const int getSide(const sides::Side side) const {
		return
			side == sides::LEFT ? this->getLeft() :
			side == sides::RIGHT ? this->getRight() :
			side == sides::TOP ? this->getTop() :
			side == sides::BOTTOM ? this->getBottom() :
			sides::NONE;
	}

	/*bool collidesWith
	takes in another rectangle and checks if two are colliding
	*/
	const bool  collidesWith(const Rectangle &other) const {
		return
			getRight() >= other.getLeft() &&
			getLeft() <= other.getRight() &&
			getTop() <= other.getBottom() &&
			getBottom() >= other.getTop();
	}

	const bool isValidRectangle() const {
		return (_x >= 0 && _y >= 0 && _width >= 0 && _height >= 0);
	}

private:
	int _x, _y, _width, _height;

};



#endif // !RECTANGLE_H;
