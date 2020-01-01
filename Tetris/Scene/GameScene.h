#ifndef GAMESCENE_H

#include "Scene.h"
#include "../Shapes/StaticBlock.h"
#include "../Shapes/Square.h"
#include "../Shapes/IShape.h"
#include "../Shapes/TShape.h"
#include "../Shapes/LShape.h"
#include "../Shapes/JShape.h"
#include "../Shapes/SShape.h"
#include "../Shapes/ZShape.h"
#include "../Shapes/Wall.h"
#include <math.h>
#include <time.h>
#include <iostream>


class GameScene : public Scene
{
public:
	GameScene();
	void Cleanup();

	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void update(float dt);
	bool ChangeScene();
	int GetScore();

private:
	void HandleInput();
	void HandleRotation();
private:
	Shape* mCurrentShape;
	std::vector<StaticBlock*> mFallenShapes;
	int mFallenMatrix[16];
	Wall* mLeftWall;
	Wall* mRightWall;

	float mCurrentTime;
	float mUpdateTime;
	float mBoostedUpdateTime;
	int mScore;
	bool mGameIsActive;
	bool mGameIsPaused;

	bool mWasLeftPressedLastFrame;
	bool mWasRightPressedLastFrame;
	bool mWasUpPressedLastFrame;
	bool mWasPPressedLastFrame;
};

#endif

