#include "Square.h"

Square::Square() : Shape() 
{
	mSprite1.setPosition(Constants::WORLD_DIMENSION_X / 2 - 50, 50);
	AllignBlocks();

	mTexture.loadFromFile("Assets/YellowSquare.png");
	mSprite1.setTexture(mTexture);
	mSprite2.setTexture(mTexture);
	mSprite3.setTexture(mTexture);
	mSprite4.setTexture(mTexture);
}

void Square::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(mSprite1, states);
	target.draw(mSprite2, states);
	target.draw(mSprite3, states);
	target.draw(mSprite4, states);
}

void Square::update(float dt)
{
	Shape::update(dt);
}

void Square::Move(sf::Vector2f direction)
{
	Shape::Move(direction);
}

void Square::AllignBlocks()
{
	mSprite2.setPosition(mSprite1.getPosition().x + 50, mSprite1.getPosition().y); // To the right of the main block
	mSprite3.setPosition(mSprite1.getPosition().x, mSprite1.getPosition().y - 50); // Above the main block
	mSprite4.setPosition(mSprite1.getPosition().x + 50, mSprite1.getPosition().y - 50); //Above and to the right of the main block
}

void Square::RotateLeft()
{
}

void Square::RotateRight()
{
}
