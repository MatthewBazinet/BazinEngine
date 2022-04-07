#include "GameObject.h"
#include "../../Core/CoreEngine.h"

GameObject::GameObject(Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_, Tetrahedron shape_)
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
	targetNumber = 0;
	eHitBox = new EnvironmentalHitBox();

	intersects = false;

	shape = shape_;

	mass = 10.0f;
	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);
		
		//std::cout << "Min: " << glm::to_string(boundingBox.minVert) << ", Max: " << glm::to_string(boundingBox.maxVert) << std::endl;
	}
}

GameObject::~GameObject()
{
	model = nullptr;
	eHitBox = nullptr;
	delete eHitBox;
}

void GameObject::Update(const float deltaTime_)
{
	eHitBox->setMaxVert(position);
	eHitBox->setMinVert(position);

	position += vel * deltaTime_ + 0.5f * accel * deltaTime_ * deltaTime_;
	vel = vel + accel * deltaTime_;
	
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


float GameObject::GetMaxSpeed() const
{
	return maxSpeed;
}
/*float GameObject::GetMaxAcceleration() const
{
	return maxAcceleration;
}*/
float GameObject::GetMass() const
{
	return mass;

}

Model* GameObject::GetModel() const
{
	return model;
}

std::vector<Mesh*> GameObject::GetMeshes()
{
	return model->GetMeshes();
}

void GameObject::SetPosition(glm::vec3 position_)
{
	if (!this) return;
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


void GameObject::SetMaxSpeed(float maxSpeed_)
{
	maxSpeed = maxSpeed_;
}
void GameObject::SetMass(float mass_)
{
	mass = mass_;
}

Tetrahedron GameObject::GetShape()
{
	shape.centre = position;
	shape.rotation = orientation;
	shape.Update();
	return shape;
}

void GameObject::SetShape(Tetrahedron shape_)
{
	shape = shape_;
}

void GameObject::CheckVisible()
{
	if (CoreEngine::GetInstance()->GetCamera()->TestPointAgainstPlanes(position, glm::mat4())) {
		if (model) {
			model->SetInstanceVisiblity(modelInstance, true);
		}
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
		if (model) {
			model->SetInstanceVisiblity(modelInstance, true);
		}
		return;
	}

	else if (CoreEngine::GetInstance()->GetCamera()->TestPointAgainstPlanes(boundingBox.maxVert, transform)) {
		if (model) {
			model->SetInstanceVisiblity(modelInstance, true);
		}
		return;
	}

	else {
		if (model) {
			model->SetInstanceVisiblity(modelInstance, false);
		}
	}
};
