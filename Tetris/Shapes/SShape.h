#pragma once

#include "Shape.h"

class SShape : public Shape
{
public:
	SShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	void Move(sf::Vector2f direction);

	void AllignBlocks();
	void RotateLeft();
	void RotateRight();
private:

};

