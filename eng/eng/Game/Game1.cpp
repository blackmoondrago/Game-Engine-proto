#include "Game1.h"

Game1::Game1()
{
}

Game1::~Game1()
{
	OnDestroy();
}

bool Game1::OnCreate()
{
	delete currentScene;
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		if (!currentScene->OnCreate()) {
			//DEBUG LINE
			return false;
		}
	}
	sceneNum = 0;
	return true;
}

void Game1::Update(const float deltaTime_)
{
	if (sceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();

	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::OnDestroy()
{
	delete currentScene;
	currentScene = nullptr;
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;
	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default: //Case 0
		currentScene = new StartScene();
		break;
	}

	if (!currentScene->OnCreate()) {
		//Either stops the engine, do not include both
		//CoreEngine::GetInstance()->SetGameInstance(nullptr);
		CoreEngine::GetInstance()->SetIsRunning(false);
	}

	sceneNum = CoreEngine::GetInstance()->GetCurrentScene();
}
