#pragma once

#include <SFML/Graphics.hpp>
#include "../Logic/Constants.h"

class Shape : sf::Drawable
{
public:
	enum class Direction {
		eUp = 0,
		eDown,
		eLeft,
		eRight
	};
	Shape();

	Direction GetDirection();

	virtual void Move(sf::Vector2f direction);
	std::vector<sf::Vector2f> GetSpritePositions();

	bool IsFalling()const;
	bool IsBoosting()const;
	void SetIsBoosting(bool val);
	void SetIsFalling(bool val);
	virtual void AllignBlocks() = 0; //Allign blocks to mSprite1 according to mDirection
	virtual void RotateRight() = 0;
	virtual void RotateLeft() = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);

protected:

	Direction mDirection;
	sf::Sprite mSprite1;
	sf::Sprite mSprite2;
	sf::Sprite mSprite3;
	sf::Sprite mSprite4;
	sf::Texture mTexture;
	bool isFalling;
	bool mBoosting;
};

