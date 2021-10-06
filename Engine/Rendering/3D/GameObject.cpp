#include "GameObject.h"
#include "../../Core/CoreEngine.h"

GameObject::GameObject(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_)
{
	model = model_;
	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
	vel = vel_;
	orientation = orientation_;
	angularVelocity = angularVelocity_;
	hit = false;

	intersects = false;

	mass = 10.0f;
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
	position += vel * deltaTime_ + 0.5f * accel * deltaTime_ * deltaTime_;
	vel = vel + accel * deltaTime_;

	/*BoundingBox temp1 = SceneGraph::GetInstance()->GetGameObject("apple")->GetBoundingBox();
	BoundingBox temp2 = SceneGraph::GetInstance()->GetGameObject("dice")->GetBoundingBox();
	intersects = temp2.Intersects(&temp1);
	if (intersects) {
		SceneGraph::GetInstance()->GetGameObject("apple")->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else {
		SceneGraph::GetInstance()->GetGameObject("apple")->SetVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));
	}*/
	
	SetPosition(position);
	if (orientation == glm::quat(0.0f, 5.0f, 5.0f, 5.0f))
	{
		//SetAngle(angle + 1.0f * deltaTime_);
	}
	else
	{
		orientation += orientation * angularVelocity * (deltaTime_ / 2);
		model->UpdateInstance(modelInstance, position, orientation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
	CheckVisible();
}

void GameObject::ApplyForce(glm::vec3 force_)
{
	accel = force_ / mass;
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

glm::vec3 GameObject::GetVelocity() const
{
	return vel;
}

glm::vec3 GameObject::GetAccel() const
{
	return accel;
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

<<<<<<< HEAD
float GameObject::GetMaxSpeed() const
{
	return maxSpeed;
=======
float GameObject::GetMass() const
{
	return mass;
>>>>>>> 6a6268eabfc0efe993d67520a2708d0aea0c2ac8
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model)
	{
		if (orientation == glm::quat(0.0f, 5.0f, 5.0f, 5.0f))
		{
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		}
		else
		{
			model->UpdateInstance(modelInstance, position, orientation, scale);

		}
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetVelocity(glm::vec3 vel_)
{
	vel = vel_;
}

void GameObject::SetAccel(glm::vec3 accel_)
{
	accel = accel_;
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

void GameObject::SetOrientation(glm::quat orientation_)
{
	orientation = orientation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, orientation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngularVelocity(glm::quat angularVelocity_)
{
	angularVelocity = angularVelocity_;
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		if (orientation == glm::quat(0.0f, 5.0f, 5.0f, 5.0f)) 
		{
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		}
		else 
		{
			model->UpdateInstance(modelInstance, position, orientation, scale);

		}
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

<<<<<<< HEAD
void GameObject::SetMaxSpeed(float maxSpeed_)
{
	maxSpeed = maxSpeed_;
=======
void GameObject::SetMass(float mass_)
{
	mass = mass_;
>>>>>>> 6a6268eabfc0efe993d67520a2708d0aea0c2ac8
}

void GameObject::CheckVisible()
{
	if (CoreEngine::GetInstance()->GetCamera()->TestPointAgainstPlanes(position, glm::mat4())) {
		model->SetInstanceVisiblity(modelInstance, true);
		return;
	}

	glm::mat4 transform;
	transform = glm::translate(transform, position);
	if (orientation == glm::quat(0.0f, 5.0f, 5.0f, 5.0f))
	{

		transform = glm::rotate(transform, angle, rotation);
	}
	else
	{
		transform = glm::rotate(transform, orientation.w, glm::vec3(orientation.x, orientation.y, orientation.z));
	}

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
