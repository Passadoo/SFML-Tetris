#pragma once

#include "Shape.h"

class Square : public Shape
{
public:
	Square();
	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void update(float dt);
	void Move(sf::Vector2f direction);

	void AllignBlocks();
	void RotateLeft();
	void RotateRight();

private:
	
};

