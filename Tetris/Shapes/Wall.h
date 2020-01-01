#pragma once

#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable
{
public:
	Wall(sf::Vector2f position);

	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
};

