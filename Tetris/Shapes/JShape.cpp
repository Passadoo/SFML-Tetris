#include "JShape.h"

JShape::JShape()
{
	mDirection = Shape::Direction::eUp;
	mSprite1.setPosition(Constants::WORLD_DIMENSION_X / 2 - 50, 50);
	AllignBlocks();

	mTexture.loadFromFile("Assets/BlueSquare.png");
	mSprite1.setTexture(mTexture);
	mSprite2.setTexture(mTexture);
	mSprite3.setTexture(mTexture);
	mSprite4.setTexture(mTexture);
}

void JShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite1, states);
	target.draw(mSprite2, states);
	target.draw(mSprite3, states);
	target.draw(mSprite4, states);
}

void JShape::update(float dt)
{
	Shape::update(dt);
}

void JShape::Move(sf::Vector2f direction)
{
	Shape::Move(direction);
}

void JShape::AllignBlocks()
{
	mSprite2.setPosition(mSprite1.getPosition());
	mSprite3.setPosition(mSprite1.getPosition());
	mSprite4.setPosition(mSprite1.getPosition());
	if (mDirection == Shape::Direction::eUp)
	{
		mSprite2.move(0.0f, 50.0f); //One step above the main block
		mSprite3.move(0.0f, -50.0f); //One step below the main block
		mSprite4.move(50.0f, -50.0f); //One step above and one step to the right of the main block
	}
	else if (mDirection == Shape::Direction::eDown)
	{
		mSprite2.move(0.0f, 50.0f); //One step above the main block
		mSprite3.move(0.0f, -50.0f); //One step below the main block
		mSprite4.move(-50.0f, 50.0f); //One step below and one step to the left of the main block
	}
	else if (mDirection == Shape::Direction::eRight)
	{
		mSprite2.move(-50.0f, 0.0f); //One step to the left of the main block
		mSprite3.move(50.0f, 0.0f); //One step to the right the main block
		mSprite4.move(50.0f, 50.0f); //One step to the right and one step below the main block
	}
	else if (mDirection == Shape::Direction::eLeft)
	{
		mSprite2.move(-50.0f, 0.0f); //One step above of the main block
		mSprite3.move(50.0f, 0.0f); //Two steps above the main block
		mSprite4.move(-50.0f, -50.0f); //One step to the left and one step up from the main block
	}
}

void JShape::RotateLeft()
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

void JShape::RotateRight()
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
