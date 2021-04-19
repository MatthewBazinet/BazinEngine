#include "GameObject.h"
#include "../../Core/CoreEngine.h"

GameObject::GameObject(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	model = model_;
	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
	hit = false;

	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);

		std::cout << "Min: " << glm::to_string(boundingBox.minVert) << ", Max: " << glm::to_string(boundingBox.maxVert) << std::endl;
	}
}

GameObject::~GameObject()
{
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 1.0f * deltaTime_);
	CheckVisible();
	
}

void GameObject::Render(Camera* camera_)
{
	if (model) {
		model->Render(camera_);
	}
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
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

std::string GameObject::GetTag() const
{
	return tag;
}

BoundingBox GameObject::GetBoundingBox() const
{
	return boundingBox;
}

bool GameObject::GetHit() const
{
	return hit;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
		boundingBox.minVert = scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert = scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	hit = hit_;
	if (hit)
	{
		std::cout << tag << " was hit" << std::endl;
	}
}

void GameObject::CheckVisible()
{
	if (CoreEngine::GetInstance()->GetCamera()->TestPointAgainstPlanes(position, glm::mat4())) {
		model->SetInstanceVisiblity(modelInstance, true);
		return;
	}
	
	glm::mat4 transform;
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, angle, rotation);

	if (CoreEngine::GetInstance()->GetCamera()->TestPointAgainstPlanes(boundingBox.minVert, transform)) {
		model->SetInstanceVisiblity(modelInstance, true);
		return;
	}
	
	else if (CoreEngine::GetInstance()->GetCamera()->TestPointAgainstPlanes(boundingBox.maxVert, transform)) {
		model->SetInstanceVisiblity(modelInstance, true);
		return;
	}
	
	else {

		model->SetInstanceVisiblity(modelInstance, false);
	}
}
