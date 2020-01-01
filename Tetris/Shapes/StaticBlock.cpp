#include "StaticBlock.h"

StaticBlock::StaticBlock(sf::Vector2f position, Color color)
{
	mSprite.setPosition(position);

	if (color == Color::eRed)
	{
		mTexture.loadFromFile("Assets/RedSquare.png");
	}
	else if (color == Color::eYellow)
	{
		mTexture.loadFromFile("Assets/YellowSquare.png");
	}
	else if (color == Color::eBlue)
	{
		mTexture.loadFromFile("Assets/BlueSquare.png");
	}
	else if (color == Color::eGreen)
	{
		mTexture.loadFromFile("Assets/GreenSquare.png");
	}
	else if (color == Color::eOrange)
	{
		mTexture.loadFromFile("Assets/OrangeSquare.png");
	}
	else if (color == Color::ePurple)
	{
		mTexture.loadFromFile("Assets/PurpleSquare.png");
	}
	else if (color == Color::eTeal)
	{
		mTexture.loadFromFile("Assets/TealSquare.png");
	}
	mSprite.setTexture(mTexture);
}

void StaticBlock::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(mSprite, states);
}

void StaticBlock::update(float dt)
{
}

sf::Vector2f StaticBlock::GetPosition()
{
	return mSprite.getPosition();
}

void StaticBlock::SetPosition(sf::Vector2f position)
{
	mSprite.setPosition(position);
}
