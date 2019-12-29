#pragma once

#include <memory>
#include "3D/GameObject.h"
#include "..//Math/CollisionHandler.h"
class SceneGraphs
{

	public:
		SceneGraphs(const SceneGraphs&) = delete;
		SceneGraphs(SceneGraphs&&) = delete;
		SceneGraphs& operator=(const SceneGraphs&) = delete;
		SceneGraphs& operator=(SceneGraphs&&) = delete;
	
		void Oncreate();
		void OnDestroy();
	
		static SceneGraphs* GetInstance();
		void AddModle(Model* modle);
		void AddGameObject(GameObject* gameObject_, std::string name_ = "");
	
		GameObject* GetGameObject(std::string name_);
		void update(const float deltatime_);
		void render(Camera* camera);
	
	private:
		SceneGraphs();
		~SceneGraphs();
	
		static std::unique_ptr<SceneGraphs> sceneGraphInstance;
		friend std::default_delete<SceneGraphs>;
	
		static std::map<GLuint, std::vector<Model*>> sceneModels;
		static std::map<std::string, GameObject*> sceneGameObjects;
	
};

