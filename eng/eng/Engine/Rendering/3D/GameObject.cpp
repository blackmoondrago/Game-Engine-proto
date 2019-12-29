#include "GameObject.h"

GameObject::GameObject(Model* model_) : model(nullptr), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0, 1.0, 0.0)), scale(glm::vec3(1.0f)), ModelInstance(0), tag(""), hit(false)
{
	model = model_;
	if (model) {
		ModelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(ModelInstance);
	}
}

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0, 1.0, 0.0)), scale(glm::vec3(1.0f)), ModelInstance(0)
{
	model = model_;
	position = position_;
	if (model) {
		ModelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(ModelInstance);
	}
}

GameObject::~GameObject()
{
	OnDestroy();
}

void GameObject::Render(Camera* camera)
{
	if (model) {
		model->Render(camera);
	}
}

void GameObject::OnDestroy()
{
	if (model) {
		delete model;
	}
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngel() const
{
	return angle;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

BoundingBox GameObject::GetBoundingBox()
{
	return boundingBox;
}

std::string GameObject::GetTag()
{
	return tag;
}

bool GameObject::GetHit() const
{
	return hit;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model) {
		model->UpdateInstance(ModelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(ModelInstance);
		
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model) {
		model->UpdateInstance(ModelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(ModelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(ModelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(ModelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model) {
		model->UpdateInstance(ModelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(ModelInstance);
		boundingBox.minVert *= scale.x > 1.0f ? scale : scale / 2.0f;
		boundingBox.maxVert *= scale.x > 1.0f ? scale : scale / 2.0f;

	}
}

std::string GameObject::SetTag(std::string tag_)
{
	tag = tag_;
	return tag;
}

void GameObject::SetHit(bool hit_, int ButtonType)
{
	hit = hit_;
	if (hit)
	{
		std::cout << "hit: " << tag << std::endl;
	}
}

