#pragma once

#include "..//Camera/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDetection
{
public:

	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;

	CollisionDetection() = delete;
	~CollisionDetection();

	static Ray ScreenPosToWorldRay(glm::vec2 mouseCords_, glm::vec2 screenSize_, Camera* camera_);
	static bool RayOBBIntersection(Ray* ray_, BoundingBox* boundingBox_);
};

