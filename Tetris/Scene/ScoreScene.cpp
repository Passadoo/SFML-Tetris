#include "ScoreScene.h"

ScoreScene::ScoreScene(int score): mScore(score), mChangeScene(false)
{
	mChangeScene = false;
	mTexture.loadFromFile("Assets/ScoreBackground.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(125, 150);
	mFont.loadFromFile("Assets/arialbd.ttf");
	mMainText.setString("Game Over!\nYour Score:   " + std::to_string(mScore));
	mSubText.setString("Highscores:");
	mSubSubText.setString("Press Space to return to the main menu");
	mMainText.setFont(mFont);
	mSubText.setFont(mFont);
	mSubSubText.setFont(mFont);
	mMainText.setPosition(Constants::WORLD_DIMENSION_X / 4, (Constants::WORLD_DIMENSION_Y / 4));
	mSubText.setPosition(mMainText.getPosition());
	mSubText.move(0, 75);
	mSubSubText.setPosition(Constants::WORLD_DIMENSION_X / 5, (Constants::WORLD_DIMENSION_Y / 4) * 3);
}

void ScoreScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
	target.draw(mMainText, states);
	target.draw(mSubText, states);
	target.draw(mSubSubText, states);
}

void ScoreScene::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mChangeScene = true;
	}
}

bool ScoreScene::ChangeScene()
{
	return mChangeScene;
}
