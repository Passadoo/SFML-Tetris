#include "SceneManager.h"

SceneManager::SceneManager()
{
	mCurrentScene = new MainScene();
}

void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (dynamic_cast<MainScene*>(mCurrentScene) != nullptr)
	{
		auto* thing = dynamic_cast<MainScene*>(mCurrentScene);
		thing->draw(target, states);
	
	}
	else if (dynamic_cast<GameScene*>(mCurrentScene) != nullptr)
	{
		auto* thing = dynamic_cast<GameScene*>(mCurrentScene);
		thing->draw(target, states);
	}
	else if (dynamic_cast<ScoreScene*>(mCurrentScene) != nullptr)
	{
		auto* thing = dynamic_cast<ScoreScene*>(mCurrentScene);
		thing->draw(target, states);
	}
}

void SceneManager::update(float dt)
{
	if (mCurrentScene->ChangeScene())
	{
		if (dynamic_cast<GameScene*>(mCurrentScene) != nullptr)
		{
			int score = dynamic_cast<GameScene*>(mCurrentScene)->GetScore();
			delete mCurrentScene;
			mCurrentScene = new ScoreScene(score);
		}
		else if (dynamic_cast<MainScene*>(mCurrentScene) != nullptr)
		{
			delete mCurrentScene;
			mCurrentScene = new GameScene();
		}
		else if (dynamic_cast<ScoreScene*>(mCurrentScene) != nullptr)
		{
			delete mCurrentScene;
			mCurrentScene = new MainScene();
		}
	}
	else
	{
		if (dynamic_cast<MainScene*>(mCurrentScene) != nullptr)
		{
			auto* thing = dynamic_cast<MainScene*>(mCurrentScene);
			thing->update(dt);

		}
		else if (dynamic_cast<GameScene*>(mCurrentScene) != nullptr)
		{
			auto* thing = dynamic_cast<GameScene*>(mCurrentScene);
			thing->update(dt);
		}
		else if (dynamic_cast<ScoreScene*>(mCurrentScene) != nullptr)
		{
			auto* thing = dynamic_cast<ScoreScene*>(mCurrentScene);
			thing->update(dt);
		}
	}
}
