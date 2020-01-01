#include "IShape.h"

IShape::IShape() : Shape()
{
	mDirection = Shape::Direction::eRight;
	mSprite1.setPosition(Constants::WORLD_DIMENSION_X / 2 - 50, 50);
	AllignBlocks();

	mTexture.loadFromFile("Assets/TealSquare.png");
	mSprite1.setTexture(mTexture);
	mSprite2.setTexture(mTexture);
	mSprite3.setTexture(mTexture);
	mSprite4.setTexture(mTexture);
}



void IShape::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(mSprite1, states);
	target.draw(mSprite2, states);
	target.draw(mSprite3, states);
	target.draw(mSprite4, states);
}

void IShape::update(float dt)
{
	Shape::update(dt);
}

void IShape::AllignBlocks()
{
	if (mDirection == Shape::Direction::eUp || mDirection == Shape::Direction::eDown)
	{
		mSprite2.setPosition(mSprite1.getPosition().x, mSprite1.getPosition().y - 50); //One block above main block
		mSprite3.setPosition(mSprite2.getPosition().x, mSprite2.getPosition().y - 50); //Two blocks above main block
		mSprite4.setPosition(mSprite3.getPosition().x, mSprite3.getPosition().y - 50); //Three blocks above main block
	}
	else
	{
		mSprite2.setPosition(mSprite1.getPosition().x + 50, mSprite1.getPosition().y); //One block to the right of the main block
		mSprite3.setPosition(mSprite2.getPosition().x + 50, mSprite2.getPosition().y); //Two blocks to the right of the main block
		mSprite4.setPosition(mSprite3.getPosition().x + 50, mSprite3.getPosition().y); //Three blocks to the right of the main block
	}
}

void IShape::RotateLeft()
{
	if (mDirection == Shape::Direction::eUp)
	{
		mDirection = Shape::Direction::eRight;
		AllignBlocks();
	}
	else if (mDirection == Shape::Direction::eRight)
	{
		mDirection = Shape::Direction::eUp;
		AllignBlocks();
	}
}

void IShape::RotateRight()
{
	if (mDirection == Shape::Direction::eUp)
	{
		mDirection = Shape::Direction::eRight;
		AllignBlocks();
	}
	else if (mDirection == Shape::Direction::eRight)
	{
		mDirection = Shape::Direction::eUp;
		AllignBlocks();
	}
}

void IShape::Move(sf::Vector2f direction)
{
	Shape::Move(direction);
}
