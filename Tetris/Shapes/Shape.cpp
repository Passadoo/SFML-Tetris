#include "Shape.h"

Shape::Shape()
{
	isFalling = true;
	mBoosting = false;
	mDirection = Direction::eUp;
}

Shape::Direction Shape::GetDirection()
{
	return mDirection;
}

void Shape::Move(sf::Vector2f direction)
{
	mSprite1.move(direction);
	this->AllignBlocks();
}

std::vector<sf::Vector2f> Shape::GetSpritePositions()
{
	std::vector<sf::Vector2f> positions;
	positions.push_back(mSprite1.getPosition());
	positions.push_back(mSprite2.getPosition());
	positions.push_back(mSprite3.getPosition());
	positions.push_back(mSprite4.getPosition());
	return positions;
}

bool Shape::IsFalling() const
{
	return isFalling;
}

bool Shape::IsBoosting() const
{
	return mBoosting;
}

void Shape::SetIsBoosting(bool val)
{
	mBoosting = val;
}

void Shape::SetIsFalling(bool val)
{
	isFalling = val;
}

void Shape::draw(sf::RenderTarget& target, sf::RenderStates states)const
{

}

void Shape::update(float dt)
{
	if (isFalling)
	{
		if (mSprite1.getPosition().y > 700 ||
			mSprite2.getPosition().y > 700 ||
			mSprite3.getPosition().y > 700 ||
			mSprite4.getPosition().y > 700)
		{
			isFalling = false;
		}
		else
		{
			mSprite1.move(0.0, Constants::GRID_SIZE);
			mSprite2.move(0.0, Constants::GRID_SIZE);
			mSprite3.move(0.0, Constants::GRID_SIZE);
			mSprite4.move(0.0, Constants::GRID_SIZE);
		}
	}
	else
	{
		//The shape has landed and should therefore not move anymore
	}
}
