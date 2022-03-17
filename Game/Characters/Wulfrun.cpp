#include "Wulfrun.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../SlashWave.h"

Wulfrun::Wulfrun(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Wulfrun/Wulfrun.obj", "Resources/Materials/Wulfrun.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Wulfrun/WulfrunIdleStance.obj", "Idle2", 1.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle2", new MorphTarget("Resources/Models/Wulfrun/WulfrunIdleStance2.obj", "Idle", 1.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightStart", new MorphTarget("Resources/Models/Wulfrun/WulfrunLightStart.obj", "LightEnd", 0.2f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunLightEnd.obj", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy", new MorphTarget("Resources/Models/Wulfrun/WulfrunHeavyEnd.obj", "Idle", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMedium", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirMedium.obj", "Idle", 1.0f));

	isCharge = true;

	SceneGraph::GetInstance()->AddModel(model);

	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle2", 0.5f);
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

	Model* hurtBox_ = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(hurtBox_);

	hurtBoxes["basic"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["basic"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(1.5f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["running"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["running"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(1.5f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["aerial"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["aerial"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(0.0f, 12.0f, 0.0f), 1.25f, 5);

	hitBoxes["light"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["light"]->spawnSpheres(this->position + glm::vec3(0.0f, 7.0f, 0.0f), this->position + glm::vec3(4.5f, 7.0f, 0.0f), 0.75f, 3);

	hitBoxes["medium"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["medium"]->spawnSpheres(this->position + glm::vec3(0.0f, 5.0f, 0.0f), this->position + glm::vec3(6.0f, 5.0f, 0.0f), 0.75f, 4);

	hitBoxes["heavy"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["heavy"]->spawnSpheres(this->position + glm::vec3(0.0f, 7.0f, 0.0f), this->position + glm::vec3(4.5f, 7.0f, 0.0f), 0.75f, 3);

	hitBoxes["airLight"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["airLight"]->spawnSpheres(this->position + glm::vec3(7.5f, 0.5f, 0.0f), this->position + glm::vec3(-5.0f, 3.5f, 0.0f), 1.25f, 4);

	hitBoxes["airMedium"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["airMedium"]->spawnSpheres(this->position + glm::vec3(7.5f, 0.5f, 0.0f), this->position + glm::vec3(-5.0f, 3.5f, 0.0f), 1.25f, 4);

	hitBoxes["qcb"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["qcb"]->spawnSpheres(this->position + glm::vec3(0.0f, 5.0f, 0.0f), this->position + glm::vec3(6.0f, 5.0f, 0.0f), 0.75f, 4);

	hurtBox = hurtBoxes["basic"];

	hurtBox = nullptr;
}

Wulfrun::~Wulfrun()
{
	if (proj) delete proj;
	proj = nullptr;
	Character::~Character();
}

void Wulfrun::Update(const float deltaTime_)
{

	static_cast<MorphTargetAnimatedModel*>(model)->Update(deltaTime_);
	Character::Update(deltaTime_);
}

void Wulfrun::QCF(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCF)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;
	overclock += 25;

	if (isAirborne)
	{
		AirQCF(strength, simpleInput);
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("GravityWaveStart", 0.5f);
		hurtBox = hurtBoxes["aerial"];

		ResetProjectile();

		if (proj == nullptr) {
			proj = new SlashWave(FrameData(0.5,0.5,0.5,10.0f, 1.0f,0.5f,glm::vec3(1.0f,0.0f,0.0f)), glm::vec3(1.0f, 0.0f, 1.0f), this, strength);
		}

		glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 0.0f, position.z - opponent->GetPosition().z);
		proj->SetTarget(nullptr);
		proj->SetPosition(this->GetPosition());
		proj->SetVelocity(glm::vec3(-dir));

		resetCombo();
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

	if (checkComboState(moveState::GROUNDLIGHT))
	{
		if (combo["light"] > 0)
		{
			combo["light"] -= 1;
			isIdle = false;

			if (isAirborne)
			{
				AirLight();
			}
			else
			{
				currentMove = moveState::GROUNDLIGHT;
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("LightStart", 0.3f);
				hurtBox = hurtBoxes["basic"];
				hitBox = hitBoxes["light"];
				SetFrameData(4.0f / 60.0f, 6.0f / 60.0f, 10.0f / 60.0f);
				//SetFrameData(frameData["light"]);
			}
		}
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

void Wulfrun::ResetProjectile()
{
	if (proj) delete proj;
	proj = nullptr;
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
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirMedium", 0.5f);
	hitBox = hitBoxes["airMedium"];
}

void Wulfrun::AirHeavy()
{
	currentMove = moveState::AIRLIGHT;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];

	hitBox = nullptr;
	SetFrameData(frameData["airHeavy"]);

}

void Wulfrun::OnQCFActive(int strenth)
{
	if (proj == nullptr) {
		proj = new SlashWave(frameData["qcf"], glm::vec3(1.0f, 4.0f, 1.0f), this);
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 15.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));
}

void Wulfrun::OnQCBActive(int strenth)
{
}

void Wulfrun::OnUniqueActive()
{
}

void Wulfrun::OnAirHeavyActive()
{
	if (proj == nullptr) {
		proj = new SlashWave(frameData["airHeavy"], glm::vec3(1.0f, 4.0f, 1.0f), this);
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 15.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));
}

void Wulfrun::OnHeavyActive()
{
}

void Wulfrun::OnAirQCFActive(int strenth)
{
}

void Wulfrun::OnAirQCBActive(int strenth)
{
}

void Wulfrun::OnAirUniqueActive()
{
}
