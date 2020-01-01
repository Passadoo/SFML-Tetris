#pragma once

#include "Shape.h"

class TShape : public Shape
{
public:
	TShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	void Move(sf::Vector2f direction);

	void AllignBlocks();
	void RotateLeft();
	void RotateRight();
private:


};

