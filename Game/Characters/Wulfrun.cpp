#include "Wulfrun.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/SceneGraph.h"

Wulfrun::Wulfrun(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Wulfrun/Wulfrun.obj", "Resources/Materials/Wulfrun.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Wulfrun/WulfrunIdleStance.obj", "Resources/Materials/Wulfrun.mtl", "Idle2", 1.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle2", new MorphTarget("Resources/Models/Wulfrun/WulfrunIdleStance2.obj", "Resources/Materials/Wulfrun.mtl", "Idle", 1.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightStart", new MorphTarget("Resources/Models/Wulfrun/WulfrunLightStart.obj", "Resources/Materials/Wulfrun.mtl", "LightEnd", 0.2f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunLightEnd.obj", "Resources/Materials/Wulfrun.mtl", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy", new MorphTarget("Resources/Models/Wulfrun/WulfrunHeavyEnd.obj", "Resources/Materials/Wulfrun.mtl", "Idle", 1.0f));

	SceneGraph::GetInstance()->AddModel(model);

	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle2", 0.5f);
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
}

Wulfrun::~Wulfrun()
{
	Character::~Character();
}

void Wulfrun::Update(const float deltaTime_)
{

	static_cast<MorphTargetAnimatedModel*>(model)->Update(deltaTime_);
	Character::Update(deltaTime_);
}

void Wulfrun::QCF(int strength, bool simpleInput)
{
	if (isAirborne)
	{
		AirQCF(strength, simpleInput);
	}
	else
	{

	}
}

void Wulfrun::QCB(int strength, bool simpleInput)
{
	if (isAirborne)
	{
		AirQCB(strength, simpleInput);
	}
	else
	{

	}
}

void Wulfrun::Unique()
{
	if (isAirborne)
	{
		AirUnique();
	}
	else
	{

	}
}

void Wulfrun::Light()
{
	if (isAirborne)
	{
		AirLight();
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("LightStart", 0.2f);
	}
}

void Wulfrun::Medium()
{
	if (isAirborne)
	{
		AirMedium();
	}
	else
	{

	}
}

void Wulfrun::Heavy()
{
	if (isAirborne)
	{
		AirHeavy();
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Heavy", 0.5f);
	}
}

void Wulfrun::AirQCF(int strength, bool simpleInput)
{
}

void Wulfrun::AirQCB(int strength, bool simpleInput)
{
}

void Wulfrun::AirUnique()
{
}

void Wulfrun::AirLight()
{
}

void Wulfrun::AirMedium()
{
}

void Wulfrun::AirHeavy()
{
}
