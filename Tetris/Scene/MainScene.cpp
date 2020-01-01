#include "MainScene.h"

MainScene::MainScene()
{
	mChangeScene = false;
	mTexture.loadFromFile("Assets/MenuBackground.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(125, 150);
	mFont.loadFromFile("Assets/arialbd.ttf");
	mMainText.setString("Welcome to Tetris!");
	mSubText.setString("Press Enter to start the game");
	mMainText.setFont(mFont);
	mSubText.setFont(mFont);
	mMainText.setPosition(Constants::WORLD_DIMENSION_X / 4 + 100, Constants::WORLD_DIMENSION_Y / 3);
	mSubText.setPosition(Constants::WORLD_DIMENSION_X / 4, Constants::WORLD_DIMENSION_Y / 2);
}

#include <iostream>

void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
	target.draw(mMainText, states);
	target.draw(mSubText, states);
}

void MainScene::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		mChangeScene = true;
	}
}

bool MainScene::ChangeScene()
{
	return mChangeScene;
}
