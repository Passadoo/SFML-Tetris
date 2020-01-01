#pragma once

#include "Shape.h"

class ZShape : public Shape
{
public:
	ZShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	void Move(sf::Vector2f direction);

	void AllignBlocks();
	void RotateLeft();
	void RotateRight();

private:

};

