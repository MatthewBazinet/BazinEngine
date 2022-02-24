#include "Hoshi.h"

Hoshi::Hoshi(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Hoshi.obj", "Resources/Materials/Hoshi.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Hoshi/HoshiIdleEnd.obj", "Resources/Materials/Hoshi.mtl"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyStart", new MorphTarget("Resources/Models/Hoshi/HoshiHeavyStart.obj", "Resources/Materials/Hoshi.mtl", "HeavyEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyEnd", new MorphTarget("Resources/Models/Hoshi/HoshiHeavyEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirHeavyStart.obj", "Resources/Materials/Hoshi.mtl", "AirHeavyEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirHeavyEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.5f));

	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

	SceneGraph::GetInstance()->AddModel(model);


}

Hoshi::~Hoshi()
{
	Character::~Character();
}

void Hoshi::Update(const float deltaTime_)
{
	if (hurtBox)
	{
		hurtBox->Update(deltaTime_);
	}
	static_cast<MorphTargetAnimatedModel*>(model)->Update(deltaTime_);
	Character::Update(deltaTime_);
}

void Hoshi::SetModels(Model* model_, Model* hurtBox_)
{
	hitBox = new HitBox(hurtBox_, this->position, this);
	hitBox->spawnSpheres(this->position, this->position + glm::vec3(0.0f, 12.0f, 0.0f), 2.0f, 4);

	//hurtBox = new HurtBox(hurtBox_, this->position, this);
	//hurtBox->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(5.0f, 12.0f, 0.0f), 2.0f, 4);
}

void Hoshi::QCF(int strength, bool simpleInput)
{
}

void Hoshi::QCB(int strength, bool simpleInput)
{
}

void Hoshi::Unique()
{
}

void Hoshi::Light()
{
}

void Hoshi::Medium()
{
}

void Hoshi::Heavy()
{
	if (isAirborne)
	{
		AirHeavy();
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("HeavyStart", 0.5f);
	}

}

void Hoshi::AirQCF(int strength, bool simpleInput)
{
}

void Hoshi::AirQCB(int strength, bool simpleInput)
{
}

void Hoshi::AirUnique()
{
}

void Hoshi::AirLight()
{
}

void Hoshi::AirMedium()
{
}

void Hoshi::AirHeavy()
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirHeavyStart", 0.5f);
}
