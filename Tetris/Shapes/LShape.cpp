#include "LShape.h"

LShape::LShape()
{
	mDirection = Shape::Direction::eUp;
	mSprite1.setPosition(Constants::WORLD_DIMENSION_X / 2 - 50, 50);
	AllignBlocks();

	mTexture.loadFromFile("Assets/OrangeSquare.png");
	mSprite1.setTexture(mTexture);
	mSprite2.setTexture(mTexture);
	mSprite3.setTexture(mTexture);
	mSprite4.setTexture(mTexture);
}

void LShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite1, states);
	target.draw(mSprite2, states);
	target.draw(mSprite3, states);
	target.draw(mSprite4, states);
}

void LShape::update(float dt)
{
	Shape::update(dt);
}

void LShape::Move(sf::Vector2f direction)
{
	Shape::Move(direction);
}

void LShape::AllignBlocks()
{
	mSprite2.setPosition(mSprite1.getPosition());
	mSprite3.setPosition(mSprite1.getPosition());
	mSprite4.setPosition(mSprite1.getPosition());
	if (mDirection == Shape::Direction::eUp)
	{
		mSprite2.move(0.0f, Constants::GRID_SIZE); //One step above the main block
		mSprite3.move(0.0f, -Constants::GRID_SIZE); //One step below the main block
		mSprite4.move(-Constants::GRID_SIZE, -Constants::GRID_SIZE); //One step above and one step to the left of the main block
	}
	else if (mDirection == Shape::Direction::eDown)
	{
		mSprite2.move(0.0f, Constants::GRID_SIZE); //One step above the main block
		mSprite3.move(0.0f, -Constants::GRID_SIZE); //One step below the main block
		mSprite4.move(Constants::GRID_SIZE, Constants::GRID_SIZE); //One step below and one step to the right of the main block
	}
	else if (mDirection == Shape::Direction::eRight)
	{
		mSprite2.move(-Constants::GRID_SIZE, 0.0f); //One step to the left of the main block
		mSprite3.move(Constants::GRID_SIZE, 0.0f); //One step to the right the main block
		mSprite4.move(Constants::GRID_SIZE, -Constants::GRID_SIZE); //One step to the right and one step above the main block
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mSprite2.move(-Constants::GRID_SIZE, 0.0f); //One step above of the main block
		mSprite3.move(Constants::GRID_SIZE, 0.0f); //Two steps above the main block
		mSprite4.move(-Constants::GRID_SIZE, Constants::GRID_SIZE); //One step to the left and one step down from the main block
	}
}

void LShape::RotateLeft()
{
	if (mDirection == Shape::Direction::eUp)
	{
		mDirection = Shape::Direction::eLeft;
	}
	else if (mDirection == Shape::Direction::eDown)
	{
		mDirection = Shape::Direction::eRight;
	}
	else if (mDirection == Shape::Direction::eRight)
	{
		mDirection = Shape::Direction::eUp;
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mDirection = Shape::Direction::eDown;
	}
	AllignBlocks();
}

void LShape::RotateRight()
{
	if (mDirection == Shape::Direction::eUp)
	{
		mDirection = Shape::Direction::eRight;
	}
	else if (mDirection == Shape::Direction::eDown)
	{
		mDirection = Shape::Direction::eLeft;
	}
	else if (mDirection == Shape::Direction::eRight)
	{
		mDirection = Shape::Direction::eDown;
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mDirection = Shape::Direction::eUp;
	}
	AllignBlocks();
}
