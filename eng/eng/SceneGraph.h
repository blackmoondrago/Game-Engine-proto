#pragma once
#include <memory>
#include "Engine/Rendering/3D/GameObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph GetInstance();
	void AddModle(Model* modle*);
	void AddGameObject(GameObject* gameObject_, std::string name_ = "");

	GameObject * GetGameObject(std::string name_);
	void update(const float deltatime_);
	void render(Camera camera);

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphe;
	friend std::denorm_absent<SceneGraph>;

	static std::map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;
};

