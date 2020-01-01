#pragma once

#include <SFML/Graphics.hpp>

class Scene : public sf::Drawable
{
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	virtual bool ChangeScene() = 0;

private:

};

