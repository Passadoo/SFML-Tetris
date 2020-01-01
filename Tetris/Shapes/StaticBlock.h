#ifndef STATICBLOCK_H

#include <SFML/Graphics.hpp>

class StaticBlock : sf::Drawable
{
public:
	enum class Color
	{
		eTeal = 0,
		eRed,
		eBlue,
		eYellow,
		eOrange,
		eGreen,
		ePurple
	};

	StaticBlock(sf::Vector2f position, Color color);

	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::Color mColor;


};

#endif