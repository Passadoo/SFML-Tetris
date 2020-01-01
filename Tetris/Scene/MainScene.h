#pragma once

#include "Scene.h"
#include "../Logic/Constants.h"

class MainScene : public Scene
{
public:
	MainScene();
	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void update(float dt);
	bool ChangeScene();

private:
	bool mChangeScene;
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::Text mMainText;
	sf::Text mSubText;
	sf::Font mFont;
};

