#include "Camera.h"
#include "..//Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3()), perspective(glm::mat4()), orthographic(glm::mat4()), fieldOfView(0.0f)
{
	fieldOfView = 45.0f;
	forwardVector = glm::vec3(0.0, 0.0, -1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = upVector;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenSize().x / CoreEngine::GetInstance()->GetScreenSize().y, nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenSize().x, 0.0f, CoreEngine::GetInstance()->GetScreenSize().y, -1.0f, 1.0f);

	updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	updateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	updateCameraVectors();
}

glm::mat4 Camera::GetVeiw() const
{

	return glm::lookAt(position, position + forwardVector, upVector);
}

const glm::mat4 Camera::GetPrespective()
{
	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenSize().x / CoreEngine::GetInstance()->GetScreenSize().y, nearPlane, farPlane);
	return perspective;
}

const glm::mat4 Camera::GetOrthographic()
{
	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenSize().x, 0.0f, CoreEngine::GetInstance()->GetScreenSize().y, -1.0f, 1.0f);
	return orthographic;
}

void Camera::ProcessMouseMovemnet(float xOffSet, float yOffSet)
{
	xOffSet *= 0.5f;
	yOffSet *= 0.5f;

	yaw += xOffSet;
	pitch += yOffSet;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
	if (yaw < 0.0f)
	{
		yaw += 360;
	}
	if (yaw > 360.0f)
	{
		yaw -= 360;
	}
	updateCameraVectors();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0)
	{
		position += static_cast<float>(y_) * (forwardVector * 2.0f);
	}
	updateCameraVectors();
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

void Camera::updateCameraVectors()
{
	forwardVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forwardVector.y = sin(glm::radians(pitch));
	forwardVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forwardVector = glm::normalize(forwardVector);
	rightVector = glm::normalize(glm::cross(forwardVector, worldUp));

	upVector = glm::normalize(glm::cross(rightVector, forwardVector));
}
