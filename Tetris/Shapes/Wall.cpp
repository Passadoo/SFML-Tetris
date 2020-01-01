#include "Wall.h"

Wall::Wall(sf::Vector2f position) {
	mTexture.loadFromFile("Assets/Wall.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(mSprite, states);
}

void Wall::update(float dt)
{

}