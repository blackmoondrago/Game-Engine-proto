#pragma once


#include "Ray.h"
#include "CollisionDetection.h"
#include "..//Rendering/3D/GameObject.h"
#include "..//Core/OctSpacialPartisioning.h"

class CollisionHandler
{
public:

	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();
	void OnCreate(float worldSize_);
	void AddGameObject(GameObject* gameObject_);
	void Update(glm::vec2 mousePosition_, int buttontype_);
	void OnDestroy();
private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionHandlerInstance;
	friend std::default_delete<CollisionHandler>;

	static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> prevCollisions;

	static OctSpacialPartisioning* scenePartision;

};

