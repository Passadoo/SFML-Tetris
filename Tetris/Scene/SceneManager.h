#pragma once

#include "GameScene.h"
#include "MainScene.h"
#include "ScoreScene.h"

class SceneManager
{
public:
	SceneManager();
	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void update(float dt);

private:
	Scene* mCurrentScene;


};

