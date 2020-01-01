#ifndef ISHAPE_H

#include "Shape.h"

class IShape : public Shape
{
public:
	IShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	void Move(sf::Vector2f direction);

	void AllignBlocks();
	void RotateLeft();
	void RotateRight();


private:


};

#endif
