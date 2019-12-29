#include "CollisionDetection.h"

#include "Ray.h"
#include "..//Core/CoreEngine.h"

CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::ScreenPosToWorldRay(glm::vec2 mouseCords_, glm::vec2 screenSize_, Camera* camera_)
{

	glm::vec4 rayStart_NDC((mouseCords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEnd_NDC((mouseCords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 Inverse = glm::inverse(camera_->GetPrespective() * camera_->GetVeiw());
	glm::vec4 RayStart_World = Inverse * rayStart_NDC;
	RayStart_World /= RayStart_World.w;

	glm::vec4 rayEnd_World = Inverse * rayEnd_NDC;
	rayEnd_World /= rayEnd_World.w;

	glm::vec3 rayDir_World(rayEnd_World - RayStart_World);

	rayDir_World = glm::normalize(rayDir_World);
	return Ray(glm::vec3(RayStart_World), rayDir_World);
}

bool CollisionDetection::RayOBBIntersection(Ray* ray_, BoundingBox* boundingBox_)
{

	glm::mat4 modelMatrix = boundingBox_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDir = ray_->direction;
	glm::vec3 aabbmin = boundingBox_->minVert;
	glm::vec3 aabbmax = boundingBox_->maxVert;

	float tmin = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().x;
	float tmax = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().y;

	glm::vec3 OBBPosition_World(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);

	glm::vec3 delta = OBBPosition_World - rayOrigin;

	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float e = glm::dot(xAxis, delta);
	float f = glm::dot(rayDir, xAxis);

	if (fabs(f) > 0.001)
	{
		float t1 = (e + aabbmin.x) / f;
		float t2 = (e + aabbmax.x) / f;

		if (t1 > t2)
		{
			float temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t2 < tmax)
		{
			tmax = t2;
		}
		if (t1 > tmin)
		{
			tmin = t1;
		}
		if (tmax < tmin)
		{
			return false;
		}
	}
	else 
	{
		if (-e + aabbmin.x > 0.0f || -e + aabbmax.x < 0.0f)
		{
			return false;
		}
	}

	//y
	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);

	float ye = glm::dot(yAxis, delta);
	float yf = glm::dot(rayDir, yAxis);

	if(fabs(yf) > 0.001f)
	{
		float t1 = (ye + aabbmin.y) / yf;
		float t2 = (ye + aabbmax.y) / yf;

		if (t1 > t2)
		{
			float temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t2 < tmax)
		{
			tmax = t2;
		}
		if (t1 > tmin)
		{
			tmin = t1;
		}
		if (tmax < tmin)
		{
			return false;
		}	
	}
	else
	{
		if (-ye + aabbmin.y > 0.0f || -ye + aabbmax.y < 0.0f)
		{
			return false;
		}
	}
	
	//z
	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);

	
	float ze = glm::dot(zAxis, delta);
	
	float zf = glm::dot(rayDir, zAxis);

	if (fabs(zf) > 0.001f)
	{
		float t1 = (ze + aabbmin.z) / zf;
		float t2 = (ze + aabbmax.z) / zf;

		if (t1 > t2)
		{
			float tmp = t1;
			t1 = t2;
			t2 = tmp;
		}
		if (t2 < tmax)
		{
			tmax = t2;
		}
		if (t1 > tmin)
		{
			tmin = t1;
		}
		if (tmax < tmin)
		{
			return false;
		}
	}
	else
	{
		if (-ze + aabbmin.z > 0.0f || -ze + aabbmax.z < 0.0f)
		{
			return false;
		}
	}

	ray_->intersectionDistance = tmin;
	return true;
}
