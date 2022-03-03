#include "Hoshi.h"

Hoshi::Hoshi(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Hoshi.obj", "Resources/Materials/Hoshi.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	// Add objs to morph target
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Hoshi/HoshiIdleEnd.obj"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Block", new MorphTarget("Resources/Models/Hoshi/HoshiBlock.obj"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Fall", new MorphTarget("Resources/Models/Hoshi/HoshiFall.obj"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Float", new MorphTarget("Resources/Models/Hoshi/HoshiFloat.obj"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Hit", new MorphTarget("Resources/Models/Hoshi/HoshiHitEnd.obj"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("JumpStart", new MorphTarget("Resources/Models/Hoshi/HoshiJumpStart.obj", "JumpEnd", 0.2f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("JumpEnd", new MorphTarget("Resources/Models/Hoshi/HoshiJumpEnd.obj", "Idle",  0.2f));

	// Walking
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkStart", new MorphTarget("Resources/Models/Hoshi/HoshiWalkStart.obj", "Walk1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk1", new MorphTarget("Resources/Models/Hoshi/HoshiWalk1.obj", "Walk2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk2", new MorphTarget("Resources/Models/Hoshi/HoshiWalk2.obj", "Walk3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk3", new MorphTarget("Resources/Models/Hoshi/HoshiWalk3.obj", "WalkEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkEnd", new MorphTarget("Resources/Models/Hoshi/HoshiWalkEnd.obj", "Idle", 0.1f));

	// Running
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunStart", new MorphTarget("Resources/Models/Hoshi/HoshiRunStart.obj", "Run1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run1", new MorphTarget("Resources/Models/Hoshi/HoshiRun1.obj", "Run2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run2", new MorphTarget("Resources/Models/Hoshi/HoshiRun2.obj", "Run3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run3", new MorphTarget("Resources/Models/Hoshi/HoshiRun3.obj", "Run4", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run4", new MorphTarget("Resources/Models/Hoshi/HoshiRun4.obj", "Run5", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run5", new MorphTarget("Resources/Models/Hoshi/HoshiRun5.obj", "Run6", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run6", new MorphTarget("Resources/Models/Hoshi/HoshiRun1.obj", "RunEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunEnd", new MorphTarget("Resources/Models/Hoshi/HoshiRunEnd.obj", "Idle", 0.1f));

	// Grounded
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightStart", new MorphTarget("Resources/Models/Hoshi/HoshiLightJabStart.obj", "LightEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightEnd", new MorphTarget("Resources/Models/Hoshi/HoshiLightJabEnd.obj", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyStart", new MorphTarget("Resources/Models/Hoshi/HoshiHeavyStart.obj", "HeavyEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyEnd", new MorphTarget("Resources/Models/Hoshi/HoshiHeavyEnd.obj", "Idle", 0.5f));

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumStart", new MorphTarget("Resources/Models/Hoshi/HoshiMediumStart.obj", "Medium1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium1", new MorphTarget("Resources/Models/Hoshi/HoshiMedium1.obj", "Medium2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium2", new MorphTarget("Resources/Models/Hoshi/HoshiMedium2.obj", "Medium3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium3", new MorphTarget("Resources/Models/Hoshi/HoshiMedium3.obj", "MediumEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumEnd", new MorphTarget("Resources/Models/Hoshi/HoshiMedium1.obj", "Idle", 0.1f));

	// Aerials
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirHeavyStart.obj", "AirHeavyEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirHeavyEnd.obj", "Idle", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirLightStart.obj", "AirLightEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirLightEnd.obj", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMediumStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirMedStart.obj", "AirMediumEnd", 0.3f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMediumEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirMedEnd.obj", "Idle", 0.3f));
	
	// Specials
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("GravityWaveStart", new MorphTarget("Resources/Models/Hoshi/HoshiGravityWaveStart.obj", "GravityWaveEnd", 0.3f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("GravityWaveEnd", new MorphTarget("Resources/Models/Hoshi/HoshiGravityWaveEnd.obj", "Idle", 0.3f));

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlideStart", new MorphTarget("Resources/Models/Hoshi/HoshiSlidingStart.obj", "Slide1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Slide1", new MorphTarget("Resources/Models/Hoshi/HoshiSliding1.obj", "SlideEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlideEnd", new MorphTarget("Resources/Models/Hoshi/HoshiSlidingEnd.obj", "Idle", 0.1f));
	
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
	//static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

	SceneGraph::GetInstance()->AddModel(model);

	floating = false;
}

Hoshi::~Hoshi()
{
	proj = nullptr;
	delete proj;
	kunai = nullptr;
	delete kunai;
	Character::~Character();
}

void Hoshi::Update(const float deltaTime_)
{
	if (floating && getIsAirborne())
	{
		this->SetVelocity(glm::vec3(this->GetVelocity().x, 0.0f, this->GetVelocity().z));
	}

	if (proj)
	{
		proj->Update(deltaTime_);
	}

	if (hurtBox)
	{
		hurtBox->Update(deltaTime_);
	}
	static_cast<MorphTargetAnimatedModel*>(model)->Update(deltaTime_);
	Character::Update(deltaTime_);
}

void Hoshi::SetModels(Model* model_, Model* hurtBox_)
{
	kunai = model_;
	hurtBoxes["basic"] = new HurtBox(hurtBox_, this->position, this);
	//hurtBoxes["basic"]->SpawnHurtBox(model_, this->position, this->position + glm::vec3(5.0f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["aerial"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["aerial"]->SpawnHurtBox(model_, this->position, this->position + glm::vec3(5.0f, 12.0f, 0.0f), 1.25f, 5);

	hitBoxes["light"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["light"]->spawnSpheres(this->position + glm::vec3(0.0f, 0.0f, 0.0f), this->position + glm::vec3(5.0f, 8.0f, 0.0f), 1.0f, 5);

	//hurtBox = hurtBoxes["basic"];
	hitBox = hitBoxes["light"];
}

void Hoshi::QCF(int strength, bool simpleInput)
{
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("GravityWaveStart", 0.5f);
	resetCombo();
}

void Hoshi::QCB(int strength, bool simpleInput)
{
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlideStart", 0.5f);
	if (strength == 0)
	{

	}
	else if (strength == 1)
	{

	}
	else if (strength == 2)
	{

	}
	resetCombo();
}

void Hoshi::Unique()
{
	// fix levitate animations
	floating = !floating;
	if (floating)
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Float", 0.5f);
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
	}
}

void Hoshi::Light()
{
	if (checkComboState(moveState::GROUNDLIGHT))
	{
		if (combo["light"] > 0)
		{
			combo["light"] -= 1;

			if (isAirborne)
			{
				AirLight();
			}
			else
			{
				currentMove = moveState::GROUNDLIGHT;
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("LightStart", 0.3f);
			}
		}
	}
}

void Hoshi::Medium()
{
	if (checkComboState(moveState::GROUNDMEDIUM))
	{
		if (combo["medium"] > 0)
		{
			combo["medium"] -= 1;

			if (isAirborne)
			{
				AirMedium();
			}
			else
			{
				currentMove = moveState::GROUNDMEDIUM;
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("MediumStart", 0.3f);
			}
		}
	}
}

void Hoshi::Heavy()
{
	if (checkComboState(moveState::GROUNDHEAVY))
	{
		if (combo["heavy"] > 0)
		{
			combo["heavy"] -= 1;

			if (isAirborne)
			{
				AirHeavy();
			}
			else
			{
				currentMove = moveState::GROUNDHEAVY;
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("HeavyStart", 0.5f);
			}
		}
	}
}

void Hoshi::ResetProjectile()
{
	if(proj) delete proj;
	proj = nullptr;
}

void Hoshi::AirQCF(int strength, bool simpleInput)
{
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("GravityWave", 0.5f);
}

void Hoshi::AirQCB(int strength, bool simpleInput)
{
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlideStart", 0.5f);
}

void Hoshi::AirUnique()
{
	
}

void Hoshi::AirLight()
{
	currentMove = moveState::AIRLIGHT;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);

	if (proj == nullptr) {
		proj = new Kunai(kunai, glm::vec3(1.0f, 0.0f, 1.0f), this);
	}

	glm::vec3 dir = position - opponent->GetPosition();
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));
}

void Hoshi::AirMedium()
{
	currentMove = moveState::AIRMEDIUM;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirMediumStart", 0.5f);
}

void Hoshi::AirHeavy()
{
	currentMove = moveState::AIRHEAVY;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirHeavyStart", 0.5f);
}
