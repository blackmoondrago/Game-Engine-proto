#include "CollisionHandler.h"
#include "..//Core/CoreEngine.h"
#include <memory>

std::unique_ptr<CollisionHandler> CollisionHandler::collisionHandlerInstance = nullptr;
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpacialPartisioning* CollisionHandler::scenePartision = nullptr;


CollisionHandler::CollisionHandler() 
{

}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionHandlerInstance.get() == nullptr)
	{
		collisionHandlerInstance.reset(new CollisionHandler);
	}
	return collisionHandlerInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
	prevCollisions.clear();
	colliders.clear();
	scenePartision = new OctSpacialPartisioning(worldSize_);
}

void CollisionHandler::AddGameObject(GameObject* gameObject_)
{
	colliders.push_back(gameObject_);
	scenePartision->AddObject(gameObject_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttontype_)
{
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition_, CoreEngine::GetInstance()->GetScreenSize(), CoreEngine::GetInstance()->GetCamera());

	//GameObject* hitResult = nullptr;
	GameObject* hitResult = scenePartision->GetCollision(mouseRay);
	float shortestDistance = FLT_MAX;

	/*for (auto g : colliders)
	{
		if (mouseRay.IsColliding(&g->GetBoundingBox()))
		{
			if (mouseRay.intersectionDistance < shortestDistance)
			{
				hitResult = g;
				shortestDistance = mouseRay.intersectionDistance;
			}
		}
	}*/

	if (hitResult)
	{
		hitResult->SetHit(true, buttontype_);
	}

	

	if (hitResult)
	{
		hitResult->SetHit(true, buttontype_);
	}

	for (auto prev : prevCollisions)
	{
		if (prev != hitResult && prev != nullptr)
		{
			prev->SetHit(false, buttontype_);
			prev = nullptr;
		}
	}

	prevCollisions.clear();

	if (hitResult)
	{
		prevCollisions.push_back(hitResult);
	}





}

void CollisionHandler::OnDestroy()
{
	for (auto entry : colliders)
	{
		entry = nullptr;
	}
	colliders.clear();

	for (auto entry : prevCollisions)
	{
		entry = nullptr;
	}
	prevCollisions.clear();

	delete scenePartision;
	scenePartision = nullptr;
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}
