#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_);
	GameObject(Model* model_, glm::vec3 position_);
	~GameObject();
	void Render(Camera* camera);
	void OnDestroy();
	void Update(const float deltaTime_);
	
	glm::vec3 GetPosition() const;
	float GetAngel() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox();
	std::string GetTag();
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float scale_);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);
	std::string SetTag(std::string tag_);
	void SetHit(bool hit_, int ButtonType);

private:
	Model* model;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 position;
	float angle;
	bool hit;
	std::string tag;


	int ModelInstance;
	BoundingBox boundingBox;
};
#endif //
