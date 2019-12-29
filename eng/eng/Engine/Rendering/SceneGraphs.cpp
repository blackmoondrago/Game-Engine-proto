#include "SceneGraphs.h"


std::unique_ptr<SceneGraphs> SceneGraphs::sceneGraphInstance = nullptr;
//std::default_delete<SceneGraphs>;

 std::map<GLuint, std::vector<Model*>> SceneGraphs::sceneModels = std::map<GLuint, std::vector<Model*>>();
 std::map<std::string, GameObject*> SceneGraphs::sceneGameObjects = std::map<std::string, GameObject*>();

 SceneGraphs::SceneGraphs()
 {

 }

void SceneGraphs::Oncreate()
{
}

void SceneGraphs::OnDestroy()
{
	
		if (sceneGameObjects.size() > 0)
		{
			for (auto go : sceneGameObjects)
			{
				delete go.second;
				go.second = nullptr;
			}

			sceneGameObjects.clear();
		}

		if (sceneModels.size() > 0)
		{
			for (auto entry : sceneModels)
			{
				if (entry.second.size())
				{
					for (auto modle : entry.second)
					{
						delete modle;
						modle = nullptr;
					}
				}
			}
			sceneModels.clear();
		}
}



SceneGraphs* SceneGraphs::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr)
	{
		sceneGraphInstance.reset(new SceneGraphs);
	}
	return sceneGraphInstance.get();
}

void SceneGraphs::AddGameObject(GameObject* gameObject_, std::string name_)
{
	if (name_ == "")
	{
		std::string newName = "gameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newName);
		sceneGameObjects[newName] = gameObject_;
	}
	else if (sceneGameObjects.find(name_) == sceneGameObjects.end())
	{
		gameObject_->SetTag(name_);
		sceneGameObjects[name_] = gameObject_;

	}
	else
	{
		Debug::Error("trying to add game object with name" + name_ + "which already exists", "SceneGraph", __LINE__);
			std::string newName = "gameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newName);
		sceneGameObjects[newName] = gameObject_;
	}
}

GameObject* SceneGraphs::GetGameObject(std::string name_)
{
	if (sceneGameObjects.find(name_) != sceneGameObjects.end())
	{
		return sceneGameObjects[name_];
	}
	return nullptr;
}

void SceneGraphs::update(const float deltatime_)
{
	for (auto go : sceneGameObjects)
	{
		go.second->Update(deltatime_);
	}
}

void SceneGraphs::render(Camera* camera)
{
	for (auto entry : sceneModels)
	{
		glUseProgram(entry.first);
			for (auto model : entry.second)
			{
				model->Render(camera);
			}
	}
}

SceneGraphs::~SceneGraphs()
{
}

void SceneGraphs::AddModle(Model* modle)
{
	if (sceneModels.find(modle->GetShaderProgram()) == sceneModels.end())
	{
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(modle->GetShaderProgram(), std::vector<Model*>{modle}));
	}
	else
	{
		sceneModels[modle->GetShaderProgram()].push_back(modle);
	}
}
