#ifndef GAMESCENE_H
#define GAMESCENE_H



#include "../..//Engine/Core/CoreEngine.h"
#include "..//..//Engine/Rendering/3D/GameObject.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void OnDestroy();
private:
	//GameObject* triangle;
	//Model* trianglemodel;
	CollisionHandler* colHandle;
	SceneGraphs* sceneGraph;
	GameObject* object;
	Model* model;
	Model* model2;
};
#endif