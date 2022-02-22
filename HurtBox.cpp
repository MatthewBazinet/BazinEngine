#include "HurtBox.h"
#include "Engine/Rendering/3D/GameObject.h"


HurtBox::HurtBox(Model* model_, glm::vec3 position_, GameObject* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	parent = parent_;
	model = model_;
	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
	vel = vel_;
	orientation = orientation_;
	angularVelocity = angularVelocity_;
	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);

		std::cout << "Min: " << glm::to_string(boundingBox.minVert) << ", Max: " << glm::to_string(boundingBox.maxVert) << std::endl;
	}

}


HurtBox::~HurtBox()
{
	if (this) {
		if (parent) {
			parent = nullptr;
		}
	}

	if (hurtBoxVisual.size() > 0)
	{
		for (auto m : hurtBoxVisual)
		{
			delete m;
			m = nullptr;
		}
		hurtBoxVisual.clear();
	}

}

void HurtBox::Update(const float deltaTime_)
{
	if (parent) {
		for (int i = 0; i < hurtBoxes.size(); i++) {
			hurtBoxes[0].SetPosition(parent->GetPosition());
			hurtBoxVisual[0]->SetPosition(parent->GetPosition());
			if (i != 0) {
				hurtBoxes[i].SetPosition(glm::vec3(parent->GetPosition() + glm::vec3(0.0f,hurtBoxes[i].offset,0.0f)));
				hurtBoxVisual[i]->SetPosition(hurtBoxes[i].position);
			}
		}
		GameObject::Update(deltaTime_);
	}



}





std::vector<Sphere> HurtBox::SpawnHurtBox(Model* model_, glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres)
{

	if (numOfSpheres >= 2) {
		float dist = glm::distance(startingPos_, endingPos_);
		float spacing = dist / numOfSpheres;
		HurtBoxVisual* hurtBoxDebug = new HurtBoxVisual("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
		SceneGraph::GetInstance()->AddModel(hurtBoxDebug);
		for (int i = 0; i < numOfSpheres; i++) {
			glm::vec3 pos = GetPointOnLine(startingPos_, endingPos_, i * spacing / dist);
			hurtBoxes.push_back(Sphere(pos, width_));
			SceneGraph::GetInstance()->AddGameObject(new HurtBox(hurtBoxDebug, pos, parent),std::to_string(i));
			hurtBoxVisual.push_back(SceneGraph::GetInstance()->GetGameObject(std::to_string(i)));
			hurtBoxVisual[i]->SetScale(glm::vec3(width_));
			hurtBoxes[i].SetOffset(glm::distance(parent->GetPosition(), hurtBoxes[i].position));
		}

		return hurtBoxes;
	}
	else {
		hurtBoxes.push_back(Sphere(startingPos_, width_));
		hurtBoxVisual.push_back(new HurtBox(model_, hurtBoxes[0].position, parent));
		return hurtBoxes;
	}

	return std::vector<Sphere>();
}

std::vector<Sphere> HurtBox::GetHurtBoxes() const
{
	if (hurtBoxes.size() > 0) {
		return hurtBoxes;
	}
	return std::vector<Sphere>();
}

void HurtBox::SetPosition(glm::vec3 position_)
{
	position = position_;
}

glm::vec3 HurtBox::GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance)
{
	return x + (y - x) * normalizedDistance;
}


