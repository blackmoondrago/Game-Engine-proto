#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"
#include "../Game/Scene/StartScene.h"
#include "../Game/Scene/GameScene.h"

class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();
	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void OnDestroy();

private:
	Scene* currentScene;
	int sceneNum;

	void BuildScene();
};

#endif // ! GAME1_H
