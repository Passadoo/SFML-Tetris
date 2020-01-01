#pragma once

#include "Scene.h"
#include "../Logic/Constants.h"

class ScoreScene : public Scene
{
public:
	ScoreScene(int score);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void update(float dt);
	bool ChangeScene();
private:
	int mScore;
	bool mChangeScene;
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::Text mMainText;
	sf::Text mSubText;
	sf::Text mSubSubText;
	sf::Font mFont;
};

