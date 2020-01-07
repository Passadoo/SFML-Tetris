#include "GameScene.h"

GameScene::GameScene()
{
	mWasLeftPressedLastFrame = false;
	mWasRightPressedLastFrame = false;
	mWasUpPressedLastFrame = false;
	mWasPPressedLastFrame = false;
	mCurrentTime = 0.0f;
	mUpdateTime = 0.3f;
	mBoostedUpdateTime = 0.05;
	mScore = 0;
	mGameIsActive = true;
	mGameIsPaused = false;
	
	for (int i = 0; i < 16; i++)
	{
		mFallenMatrix[i] = 0;
	}
	srand(time(NULL));
	int val = rand() % 7;
	if (val == 0) //SQUARE
	{
		mCurrentShape = new Square();
	}
	else if (val == 1) // I-SHAPE
	{
		mCurrentShape = new IShape();
	}
	else if (val == 2) //T-SHAPE
	{
		mCurrentShape = new TShape();
	}
	else if (val == 3) //L-SHAPE
	{
		mCurrentShape = new LShape();
	}
	else if (val == 4) //J-Shape
	{
		mCurrentShape = new JShape();
	}
	else if (val == 5) //S-Shape
	{
		mCurrentShape = new SShape();
	}
	else if (val == 6) //Z-Shape
	{
		mCurrentShape = new ZShape();
	}

	mLeftWall = new Wall(sf::Vector2f(0.0, 0.0));
	mRightWall = new Wall(sf::Vector2f((Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH), 0.0f));

	mFont.loadFromFile("Assets/space age.ttf");
	mPauseText.setString("PAUSED");
	mPauseText.setFont(mFont);
	//mPauseText.setScale(1.0f, 1.0f);
	mPauseText.setPosition(Constants::WORLD_DIMENSION_X / 4 + 100, Constants::WORLD_DIMENSION_Y / 3);
}

void GameScene::Cleanup()
{
	delete mLeftWall;
	delete mRightWall;
	delete mCurrentShape;
	for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
	{
		delete (*it);
	}
	
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	mLeftWall->draw(target, states);
	mRightWall->draw(target, states);
	for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
	{
		(*it)->draw(target, states);
	}

	mCurrentShape->draw(target, states);

	if (mGameIsPaused)
	{
		target.draw(mPauseText, states);
	}
}

void GameScene::update(float dt)
{
	if (mGameIsActive)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!mWasPPressedLastFrame)
			{
				mGameIsPaused = !mGameIsPaused;
			}
		}
		if (!mGameIsPaused)
		{
			mCurrentTime += dt;
			//Check for full rows
			if (mFallenMatrix[14] > 0 ||
				mFallenMatrix[15] > 0)
			{
				//Game over
				mGameIsActive = false;
			}
			else
			{
				HandleInput();
				for (int i = 0; i < 16; i++)
				{
					if (mFallenMatrix[i] >= 10)
					{
						//Row is full
						int position = (Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE) - (Constants::GRID_SIZE * i);
						for (auto it = mFallenShapes.begin(); it != mFallenShapes.end();)
						{
							if ((*it)->GetPosition().y == position)
							{
								it = mFallenShapes.erase(it);
							}
							else
							{
								++it;
							}
						}
						mFallenMatrix[i] = 0; //Reset row counter
						mScore += 100; //add 100 to score

						for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++) //Move above StaticBlocks down
						{
							if ((*it)->GetPosition().y < position)
							{
								(*it)->SetPosition(sf::Vector2f((*it)->GetPosition().x, (*it)->GetPosition().y + Constants::GRID_SIZE));
								int arrayIndex = ((Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE) - (*it)->GetPosition().y) / Constants::GRID_SIZE;
								mFallenMatrix[arrayIndex]++;
								mFallenMatrix[arrayIndex + 1]--;
							}
						}
					}
				}
				float timeToCheck;
				if (mCurrentShape->IsBoosting())
				{
					timeToCheck = mBoostedUpdateTime;
				}
				else
				{
					timeToCheck = mUpdateTime;
				}
				if (mCurrentTime >= timeToCheck)
				{
					if (!mCurrentShape->IsFalling())
					{
						auto positions = mCurrentShape->GetSpritePositions();
						bool collision = false;

						for (int i = 0; i < positions.size(); i++)
						{
							for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
							{
								if (positions[i].x == (*it)->GetPosition().x &&
									positions[i].y + Constants::GRID_SIZE == (*it)->GetPosition().y)
								{
									collision = true;
								}
							}
							if (positions[i].y + Constants::GRID_SIZE >= Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE)
							{
								collision = true;
							}
						}
						if (!collision)
						{
							mCurrentShape->SetIsFalling(true);
						}
						else
						{
							auto positions = mCurrentShape->GetSpritePositions();
							for (auto it = positions.begin(); it != positions.end(); it++)
							{
								if ((*it).y > 0)
								{
									StaticBlock::Color color;
									if (dynamic_cast<Square*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::eYellow;
									}
									else if (dynamic_cast<IShape*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::eTeal;
									}
									else if (dynamic_cast<TShape*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::ePurple;
									}
									else if (dynamic_cast<LShape*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::eOrange;
									}
									else if (dynamic_cast<JShape*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::eBlue;
									}
									else if (dynamic_cast<SShape*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::eGreen;
									}
									else if (dynamic_cast<ZShape*>(mCurrentShape) != nullptr)
									{
										color = StaticBlock::Color::eRed;
									}
									mFallenShapes.push_back(new StaticBlock(*it, color));
									int arrayIndex = ((Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE) - (*it).y) / Constants::GRID_SIZE;
									mFallenMatrix[arrayIndex] += 1;
								}
							}
							delete mCurrentShape;
							srand(time(NULL));
							int val = rand() % 7;
							if (val == 0) //SQUARE
							{
								mCurrentShape = new Square();
							}
							else if (val == 1) // I-SHAPE
							{
								mCurrentShape = new IShape();
							}
							else if (val == 2) //T-SHAPE
							{
								mCurrentShape = new TShape();
							}
							else if (val == 3) //L-SHAPE
							{
								mCurrentShape = new LShape();
							}
							else if (val == 4) //J-Shape
							{
								mCurrentShape = new JShape();
							}
							else if (val == 5) //S-Shape
							{
								mCurrentShape = new SShape();
							}
							else if (val == 6)
							{
								mCurrentShape = new ZShape();
							}
						}
					}
					else
					{
						auto positions = mCurrentShape->GetSpritePositions();
						bool collision = false;

						for (int i = 0; i < positions.size(); i++)
						{
							for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
							{
								if (positions[i].x == (*it)->GetPosition().x &&
									positions[i].y + Constants::GRID_SIZE == (*it)->GetPosition().y)
								{
									collision = true;
								}
							}
						}
						if (!collision)
						{
							mCurrentShape->update(dt);
						}
						else
						{
							mCurrentShape->SetIsFalling(false);
						}
					}
					mCurrentTime = 0.0f;
				}
			}
		}
	}
		mWasPPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
}

bool GameScene::ChangeScene()
{
	return !mGameIsActive;
}

int GameScene::GetScore()
{
	return mScore;
}

void GameScene::HandleInput()
{
	mCurrentShape->SetIsBoosting(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!mWasUpPressedLastFrame)
		{
			HandleRotation();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mCurrentShape->SetIsBoosting(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!mWasRightPressedLastFrame)
		{
			auto positions = mCurrentShape->GetSpritePositions();
			bool collision = false;
			for (int i = 0; i < positions.size(); i++) //Check collision with walls
			{
				if (positions[i].x + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
				{
					collision = true;
				}
			}
			if (mFallenShapes.size() > 0 && !collision) //Check collision with fallen shapes
			{
				for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
				{
					for (int i = 0; i < positions.size(); i++)
					{
						if (positions[i].x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
							positions[i].y == (*it)->GetPosition().y)
						{
							collision = true;
						}
					}
				}
				if (!collision)
				{
					mCurrentShape->Move(sf::Vector2f(Constants::GRID_SIZE, 0.0));
				}
			}
			else if (!collision)
			{
				mCurrentShape->Move(sf::Vector2f(Constants::GRID_SIZE, 0.0));
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(!mWasLeftPressedLastFrame)
		{
			auto positions = mCurrentShape->GetSpritePositions();
			bool collision = false;
			for (int i = 0; i < positions.size(); i++)
			{
				if (positions[i].x <= (Constants::WALL_WIDTH))
				{
					collision = true;
				}
			}
			if (mFallenShapes.size() > 0 && !collision)
			{
				for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
				{
					for (int i = 0; i < positions.size(); i++)
					{
						if (positions[i].x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
							positions[i].y == (*it)->GetPosition().y)
						{
							collision = true;
						}
					}
				}
				if (!collision)
				{
					mCurrentShape->Move(sf::Vector2f(-Constants::GRID_SIZE, 0.0));
				}
			}
			else if (!collision)
			{
				mCurrentShape->Move(sf::Vector2f(-Constants::GRID_SIZE, 0.0));
			}
		}
	}

	mWasLeftPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	mWasRightPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	mWasUpPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

void GameScene::HandleRotation()
{
	//Rotate current block right
	bool canRotate = true;
	auto mainBlockPosition = mCurrentShape->GetSpritePositions()[0];
	if (dynamic_cast<IShape*>(mCurrentShape) != nullptr)
	{
		if (mCurrentShape->GetDirection() == Shape::Direction::eRight)
		{
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y ||
						mainBlockPosition.y - (2 * Constants::GRID_SIZE) == (*it)->GetPosition().y ||
						mainBlockPosition.y - (3 * Constants::GRID_SIZE) == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eUp)
		{
			if (mainBlockPosition.x + (3 * Constants::GRID_SIZE) >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
			{
				canRotate = false;
			}
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
				else if (mainBlockPosition.x + (2 * Constants::GRID_SIZE) == (*it)->GetPosition().x &&
					mainBlockPosition.y == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
				else if (mainBlockPosition.x + (3 * Constants::GRID_SIZE) == (*it)->GetPosition().x &&
					mainBlockPosition.y == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
		}
	}
	else if (dynamic_cast<TShape*>(mCurrentShape) != nullptr)
	{
		if (mCurrentShape->GetDirection() == Shape::Direction::eUp)
		{
			//Attempt to rotate to eRight
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y ||
					mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					if (mainBlockPosition.x == (*it)->GetPosition().x)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.y == (*it)->GetPosition().y &&
					mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + 50 >= (Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE))
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eDown)
		{
			//Attempt to rotate to eLeft
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y ||
					mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					if (mainBlockPosition.x == (*it)->GetPosition().x)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.y == (*it)->GetPosition().y &&
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					canRotate = false;
				}
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eRight)
		{
			//Attempt to rotate to eDown
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x ||
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.x == (*it)->GetPosition().x &&
					mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.x - 50 <= Constants::WALL_WIDTH)
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eLeft)
		{
			//Attempt to rotate to eUp
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x ||
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.x == (*it)->GetPosition().x &&
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.x + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
			{
				canRotate = false;
			}
		}
	}
	else if (dynamic_cast<LShape*>(mCurrentShape) != nullptr)
	{
		if (mCurrentShape->GetDirection() == Shape::Direction::eUp)
		{
			//Attempt to rotate to eRight
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x ||
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + Constants::GRID_SIZE >= Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE)
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eDown)
		{
			//Attempt to rotate to eLeft
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x ||
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + Constants::GRID_SIZE > 700)
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x - Constants::GRID_SIZE <= Constants::WALL_WIDTH)
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eRight)
		{
			//Attempt to rotate to eDown
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y ||
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					if (mainBlockPosition.x == (*it)->GetPosition().x)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y &&
					mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE))
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eLeft)
		{
			//Attempt to rotate to eUp
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y ||
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					if (mainBlockPosition.x == (*it)->GetPosition().x)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y &&
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					canRotate = false;
				}
			}
		}
		if (mainBlockPosition.y + Constants::GRID_SIZE >= 750)
		{
			canRotate = false;
		}
		else if (mainBlockPosition.x - Constants::GRID_SIZE <= Constants::WALL_WIDTH)
		{
			canRotate = false;
		}
	}
	else if (dynamic_cast<JShape*>(mCurrentShape) != nullptr)
	{
		if (mCurrentShape->GetDirection() == Shape::Direction::eUp)
		{
			//Attempt to rotate to eRight
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x ||
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + Constants::GRID_SIZE > 700)
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x - Constants::GRID_SIZE <= (Constants::WALL_WIDTH))
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eDown)
		{
			//Attempt to rotate to eLeft
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x ||
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					if (mainBlockPosition.y == (*it)->GetPosition().y)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.x + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eRight)
		{
			//Attempt to rotate to eDown
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y ||
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					if (mainBlockPosition.x == (*it)->GetPosition().x)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y &&
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					canRotate = false;
				}
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eLeft)
		{
			//Attempt to rotate to eUp
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y ||
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					if (mainBlockPosition.x == (*it)->GetPosition().x)
					{
						canRotate = false;
					}
				}
				if (mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y &&
					mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + Constants::GRID_SIZE >= 750)
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x - 50 <= Constants::WALL_WIDTH)
			{
				canRotate = false;
			}
		}
	}
	else if (dynamic_cast<SShape*>(mCurrentShape) != nullptr)
	{
		if (mCurrentShape->GetDirection() == Shape::Direction::eUp)
		{
			//Attempt to rotate to eRight
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
				else if (mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
						mainBlockPosition.y == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.x  <= Constants::WALL_WIDTH)
			{
				canRotate = false;
			}
		}
		else if (mCurrentShape->GetDirection() == Shape::Direction::eRight)
		{
			//Attempt to rotate to eUp
			for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
			{
				if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
				else if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
					mainBlockPosition.y == (*it)->GetPosition().y)
				{
					canRotate = false;
				}
			}
			if (mainBlockPosition.y + Constants::GRID_SIZE >= Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE)
			{
				canRotate = false;
			}
		}
	}
	else if (dynamic_cast<ZShape*>(mCurrentShape) != nullptr)
	{
	if (mCurrentShape->GetDirection() == Shape::Direction::eUp)
	{
		//Attempt to rotate to eLeft
		for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
		{
			if (mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
				mainBlockPosition.y - Constants::GRID_SIZE == (*it)->GetPosition().y)
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x + Constants::GRID_SIZE == (*it)->GetPosition().x &&
				mainBlockPosition.y == (*it)->GetPosition().y)
			{
				canRotate = false;
			}
		}
		if (mainBlockPosition.x + Constants::GRID_SIZE >= (Constants::WORLD_DIMENSION_X - Constants::WALL_WIDTH))
		{
			canRotate = false;
		}
	}
	else if (mCurrentShape->GetDirection() == Shape::Direction::eRight)
	{
		//Attempt to rotate to eUp
		for (auto it = mFallenShapes.begin(); it != mFallenShapes.end(); it++)
		{
			if (mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
				mainBlockPosition.y + Constants::GRID_SIZE == (*it)->GetPosition().y)
			{
				canRotate = false;
			}
			else if (mainBlockPosition.x - Constants::GRID_SIZE == (*it)->GetPosition().x &&
				mainBlockPosition.y == (*it)->GetPosition().y)
			{
				canRotate = false;
			}
		}
		if (mainBlockPosition.y + Constants::GRID_SIZE >= Constants::WORLD_DIMENSION_Y - Constants::GRID_SIZE)
		{
			canRotate = false;
		}
	}
	}
	if (canRotate)
	{
		mCurrentShape->RotateRight();
	}
}
