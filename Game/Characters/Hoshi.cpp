#include "Hoshi.h"

Hoshi::Hoshi(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Hoshi.obj", "Resources/Materials/Hoshi.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	// Add objs to morph target
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Hoshi/HoshiIdleEnd.obj", "Resources/Materials/Hoshi.mtl"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Block", new MorphTarget("Resources/Models/Hoshi/HoshiBlock.obj", "Resources/Materials/Hoshi.mtl"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Fall", new MorphTarget("Resources/Models/Hoshi/HoshiFall.obj", "Resources/Materials/Hoshi.mtl"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Float", new MorphTarget("Resources/Models/Hoshi/HoshiFloat.obj", "Resources/Materials/Hoshi.mtl"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Hit", new MorphTarget("Resources/Models/Hoshi/HoshiHitEnd.obj", "Resources/Materials/Hoshi.mtl"));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("JumpStart", new MorphTarget("Resources/Models/Hoshi/HoshiJumpStart.obj", "Resources/Materials/Hoshi.mtl", "JumpEnd", 0.2f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("JumpEnd", new MorphTarget("Resources/Models/Hoshi/HoshiJumpEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle",  0.2f));

	// Walking
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkStart", new MorphTarget("Resources/Models/Hoshi/HoshiWalkStart.obj", "Resources/Materials/Hoshi.mtl", "Walk1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk1", new MorphTarget("Resources/Models/Hoshi/HoshiWalk1.obj", "Resources/Materials/Hoshi.mtl", "Walk2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk2", new MorphTarget("Resources/Models/Hoshi/HoshiWalk2.obj", "Resources/Materials/Hoshi.mtl", "Walk3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk3", new MorphTarget("Resources/Models/Hoshi/HoshiWalk3.obj", "Resources/Materials/Hoshi.mtl", "WalkEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkEnd", new MorphTarget("Resources/Models/Hoshi/HoshiWalkEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.1f));

	// Running
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunStart", new MorphTarget("Resources/Models/Hoshi/HoshiRunStart.obj", "Resources/Materials/Hoshi.mtl", "Run1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run1", new MorphTarget("Resources/Models/Hoshi/HoshiRun1.obj", "Resources/Materials/Hoshi.mtl", "Run2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run2", new MorphTarget("Resources/Models/Hoshi/HoshiRun2.obj", "Resources/Materials/Hoshi.mtl", "Run3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run3", new MorphTarget("Resources/Models/Hoshi/HoshiRun3.obj", "Resources/Materials/Hoshi.mtl", "Run4", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run4", new MorphTarget("Resources/Models/Hoshi/HoshiRun4.obj", "Resources/Materials/Hoshi.mtl", "Run5", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run5", new MorphTarget("Resources/Models/Hoshi/HoshiRun5.obj", "Resources/Materials/Hoshi.mtl", "Run6", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run6", new MorphTarget("Resources/Models/Hoshi/HoshiRun1.obj", "Resources/Materials/Hoshi.mtl", "RunEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunEnd", new MorphTarget("Resources/Models/Hoshi/HoshiRunEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.1f));

	// Grounded
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightStart", new MorphTarget("Resources/Models/Hoshi/HoshiLightJabStart.obj", "Resources/Materials/Hoshi.mtl", "LightEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightEnd", new MorphTarget("Resources/Models/Hoshi/HoshiLightJabEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyStart", new MorphTarget("Resources/Models/Hoshi/HoshiHeavyStart.obj", "Resources/Materials/Hoshi.mtl", "HeavyEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyEnd", new MorphTarget("Resources/Models/Hoshi/HoshiHeavyEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.5f));

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumStart", new MorphTarget("Resources/Models/Hoshi/HoshiMediumStart.obj", "Resources/Materials/Hoshi.mtl", "Medium1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium1", new MorphTarget("Resources/Models/Hoshi/HoshiMedium1.obj", "Resources/Materials/Hoshi.mtl", "Medium2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium2", new MorphTarget("Resources/Models/Hoshi/HoshiMedium2.obj", "Resources/Materials/Hoshi.mtl", "Medium3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium3", new MorphTarget("Resources/Models/Hoshi/HoshiMedium3.obj", "Resources/Materials/Hoshi.mtl", "MediumEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumEnd", new MorphTarget("Resources/Models/Hoshi/HoshiMedium1.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.1f));

	// Aerials
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirHeavyStart.obj", "Resources/Materials/Hoshi.mtl", "AirHeavyEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirHeavyEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirLightStart.obj", "Resources/Materials/Hoshi.mtl", "AirLightEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirLightEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMediumStart", new MorphTarget("Resources/Models/Hoshi/HoshiAirMedStart.obj", "Resources/Materials/Hoshi.mtl", "AirMediumEnd", 0.3f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMediumEnd", new MorphTarget("Resources/Models/Hoshi/HoshiAirMedEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.3f));
	
	// Specials
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("GravityWaveStart", new MorphTarget("Resources/Models/Hoshi/HoshiGravityWaveStart.obj", "Resources/Materials/Hoshi.mtl", "GravityWaveEnd", 0.3f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("GravityWaveEnd", new MorphTarget("Resources/Models/Hoshi/HoshiGravityWaveEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.3f));

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlideStart", new MorphTarget("Resources/Models/Hoshi/HoshiSlidingStart.obj", "Resources/Materials/Hoshi.mtl", "Slide1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Slide1", new MorphTarget("Resources/Models/Hoshi/HoshiSliding1.obj", "Resources/Materials/Hoshi.mtl", "SlideEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlideEnd", new MorphTarget("Resources/Models/Hoshi/HoshiSlidingEnd.obj", "Resources/Materials/Hoshi.mtl", "Idle", 0.1f));
	
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
	//static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

	SceneGraph::GetInstance()->AddModel(model);

	floating = false;
}

Hoshi::~Hoshi()
{
	Character::~Character();
}

void Hoshi::Update(const float deltaTime_)
{
	if (floating && getIsAirborne())
	{
		this->SetVelocity(glm::vec3(this->GetVelocity().x, 0.0f, this->GetVelocity().z));
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
	hurtBoxes["basic"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["basic"]->SpawnHurtBox(model_, this->position, this->position + glm::vec3(5.0f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["aerial"] = new HurtBox(hurtBox_, this->position, this);

	hurtBox = hurtBoxes["basic"];

	//hurtBox = new HurtBox(hurtBox_, this->position, this);
	//hurtBox->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(5.0f, 12.0f, 0.0f), 2.0f, 4);
}

void Hoshi::QCF(int strength, bool simpleInput)
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("GravityWaveStart", 0.5f);
	resetCombo();
}

void Hoshi::QCB(int strength, bool simpleInput)
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);
	resetCombo();
}

void Hoshi::Unique()
{
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
	if (isAirborne)
	{
		AirLight();
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("LightStart", 0.3f);
	}

	if (combo["light"] == false)
	{
		combo["light"] = true;
	}
	else if (combo["light"] == true)
	{
		resetCombo();
	}
}

void Hoshi::Medium()
{
	if (isAirborne)
	{
		AirMedium();
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("MediumStart", 0.3f);
	}

	if (combo["medium"] == false)
	{
		combo["medium"] = true;
	}
	else if (combo["medium"] == true)
	{
		resetCombo();
	}
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

	if (combo["heavy"] == false)
	{
		combo["heavy"] = true;
	}
	else if (combo["heavy"] == true)
	{
		resetCombo();
	}
}

void Hoshi::AirQCF(int strength, bool simpleInput)
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("GravityWave", 0.5f);
}

void Hoshi::AirQCB(int strength, bool simpleInput)
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlideStart", 0.5f);
}

void Hoshi::AirUnique()
{
	
}

void Hoshi::AirLight()
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);
}

void Hoshi::AirMedium()
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirMediumStart", 0.5f);
}

void Hoshi::AirHeavy()
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirHeavyStart", 0.5f);
}
