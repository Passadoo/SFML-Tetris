#include "ZShape.h"

ZShape::ZShape()
{
	mDirection = Shape::Direction::eLeft;
	mSprite1.setPosition(Constants::WORLD_DIMENSION_X / 2 - 50, 50);
	AllignBlocks();

	mTexture.loadFromFile("Assets/RedSquare.png");
	mSprite1.setTexture(mTexture);
	mSprite2.setTexture(mTexture);
	mSprite3.setTexture(mTexture);
	mSprite4.setTexture(mTexture);
}

void ZShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite1, states);
	target.draw(mSprite2, states);
	target.draw(mSprite3, states);
	target.draw(mSprite4, states);
}

void ZShape::update(float dt)
{
	Shape::update(dt);
}

void ZShape::Move(sf::Vector2f direction)
{
	Shape::Move(direction);
}

void ZShape::AllignBlocks()
{
	mSprite2.setPosition(mSprite1.getPosition());
	mSprite3.setPosition(mSprite1.getPosition());
	mSprite4.setPosition(mSprite1.getPosition());
	if (mDirection == Shape::Direction::eUp)
	{
		mSprite2.move(0.0f, -Constants::GRID_SIZE); //One step above the main block
		mSprite3.move(-Constants::GRID_SIZE, 0.0f); //One step to the left of the main block
		mSprite4.move(-Constants::GRID_SIZE, Constants::GRID_SIZE); //One step below and one step to the left of the main block
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mSprite2.move(0.0f, -Constants::GRID_SIZE); //One step above the main block
		mSprite3.move(-Constants::GRID_SIZE, -Constants::GRID_SIZE); //One step to the left and one step above the main block
		mSprite4.move(Constants::GRID_SIZE, 0.0f); //One step to the right of the main block
	}
}

void ZShape::RotateLeft()
{
	if (mDirection == Shape::Direction::eUp)
	{
		mDirection = Shape::Direction::eLeft;
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mDirection = Shape::Direction::eUp;
	}
	AllignBlocks();
}

void ZShape::RotateRight()
{
	if (mDirection == Shape::Direction::eUp)
	{
		mDirection = Shape::Direction::eLeft;
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mDirection = Shape::Direction::eUp;
	}
	AllignBlocks();
}
