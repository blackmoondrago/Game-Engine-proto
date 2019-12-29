#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3);
	void SetRotation(float pitch_, float yaw_);
	glm::mat4 GetVeiw() const;
	const glm::mat4 GetPrespective();
	const glm::mat4 GetOrthographic();

	void ProcessMouseMovemnet(float xOffSet, float yOffSet);
	void ProcessMouseZoom(int y_);

	glm::vec2 GetClippingPlanes() const;

private:
	void updateCameraVectors();

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float yaw, pitch;
	float fieldOfView;
	float nearPlane, farPlane;
	glm::vec3 forwardVector, upVector, rightVector, worldUp;

};

