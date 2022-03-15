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
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkStart", new MorphTarget("Resources/Models/Hoshi/HoshiWalkStart.obj", "Walk1", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk1", new MorphTarget("Resources/Models/Hoshi/HoshiWalk1.obj", "Walk2", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk2", new MorphTarget("Resources/Models/Hoshi/HoshiWalk2.obj", "Walk3", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk3", new MorphTarget("Resources/Models/Hoshi/HoshiWalk3.obj", "WalkEnd", 0.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkEnd", new MorphTarget("Resources/Models/Hoshi/HoshiWalkEnd.obj", "WalkStart", 0.5f));

	// Running
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunStart", new MorphTarget("Resources/Models/Hoshi/HoshiRunStart.obj", "Run1", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run1", new MorphTarget("Resources/Models/Hoshi/HoshiRun1.obj", "Run2", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run2", new MorphTarget("Resources/Models/Hoshi/HoshiRun2.obj", "Run3", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run3", new MorphTarget("Resources/Models/Hoshi/HoshiRun3.obj", "Run4", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run4", new MorphTarget("Resources/Models/Hoshi/HoshiRun4.obj", "Run5", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run5", new MorphTarget("Resources/Models/Hoshi/HoshiRun5.obj", "Run6", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run6", new MorphTarget("Resources/Models/Hoshi/HoshiRun1.obj", "RunEnd", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunEnd", new MorphTarget("Resources/Models/Hoshi/HoshiRunEnd.obj", "Run1", 0.1f));

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

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlideStart", new MorphTarget("Resources/Models/Hoshi/HoshiSlidingStart.obj", "Slide1", 0.25f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Slide1", new MorphTarget("Resources/Models/Hoshi/HoshiSliding1.obj", "SlideEnd", 0.75f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlideEnd", new MorphTarget("Resources/Models/Hoshi/HoshiSlidingEnd.obj", "Idle", 0.1f));
	
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

	SceneGraph::GetInstance()->AddModel(model);

	floating = false;
}

Hoshi::~Hoshi()
{
	proj = nullptr;
	delete proj;

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
	if (!isIdle && currentMove == moveState::NONE)
	{
		if (isAirborne)
		{
			static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Fall", 0.5f);
		}
		else
		{
			static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
		}
		isIdle = true;
	}
	static_cast<MorphTargetAnimatedModel*>(model)->Update(deltaTime_);
	Character::Update(deltaTime_);
}

void Hoshi::SetModels(Model* hurtBox_)
{
	hurtBoxes["basic"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["basic"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(1.5f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["aerial"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["aerial"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(0.0f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["slide"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["slide"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(-7.5f, 0.5f, 0.0f), this->position + glm::vec3(5.0f, 3.5f, 0.0f), 1.25f, 4);

	hitBoxes["light"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["light"]->spawnSpheres(this->position + glm::vec3(0.0f, 7.0f, 0.0f), this->position + glm::vec3(4.5f, 7.0f, 0.0f), 0.75f, 3);

	hitBoxes["medium"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["medium"]->spawnSpheres(this->position + glm::vec3(0.0f, 5.0f, 0.0f), this->position + glm::vec3(6.0f, 5.0f, 0.0f), 0.75f, 4);

	hitBoxes["heavy"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["heavy"]->spawnSpheres(this->position + glm::vec3(0.0f, 7.0f, 0.0f), this->position + glm::vec3(4.5f, 7.0f, 0.0f), 0.75f, 3);
			
	hitBoxes["slide"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["slide"]->spawnSpheres(this->position + glm::vec3(7.5f, 0.5f, 0.0f), this->position + glm::vec3(7.5f, 0.5f, 0.0f), 1.25f, 2);

	hurtBox = hurtBoxes["basic"];
	hitBox = hitBoxes["light"];
}

void Hoshi::Run(bool isRunning_)
{
	if (isRunning_)
	{
		isIdle = false;
		if (nextActionable > 0.0f) return;

		if (!CheckRunCancel()) return;
		if (!isRunning)
		{
			static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("RunStart", 0.5f);
		}
		currentMove = moveState::RUN;
	}
	else
	{
		if (isRunning)
		{
			static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
			currentMove = moveState::NONE;
		}
	}
	isRunning = isRunning_;
}

void Hoshi::Move(glm::vec2 input)
{
	if (nextActionable > 0.0f) return;

	if (input.y > 0)
	{
		//GetCamera()->SetPosition(GetCamera()->GetPosition() - glm::vec3(0.0f, 0.0f, 0.01f));
		if (isRunning)
		{
			relativeVel = glm::vec3(relativeVel.x, relativeVel.y, -5.0f);

		}
		else
		{
			if (!isAirborne)
			{
				vel = glm::vec3(vel.x, 10.0f, vel.z);
			}
			//ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
		}
	}
	else if (input.y < 0)
	{
		if (isRunning)
		{
			relativeVel = glm::vec3(relativeVel.x, relativeVel.y, 5.0f);

		}
	}
	else
	{
		if (isRunning)
		{
			relativeVel = glm::vec3(relativeVel.x, relativeVel.y, 0.0f);
		}
	}

	if (input.x < 0)
	{
		//GetCamera()->SetPosition(GetCamera()->GetPosition() - glm::vec3(0.01f, 0.0f, 0.0f));
		if (isRunning) {
			relativeVel = glm::vec3(-5.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			if(!MovingLeft)	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("WalkStart", 0.5f);
			hurtBox = hurtBoxes["basic"];
			isIdle = false;
			MovingLeft = true;
			MovingRight = false;
		}

	}
	else if (input.x > 0)
	{
		if (isRunning)
		{
			relativeVel = glm::vec3(5.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			if (!MovingRight) static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("WalkStart", 0.5f);
			{
				hurtBox = hurtBoxes["basic"];
				isIdle = false;
				MovingRight = true;
				MovingLeft = false;
			}
		}
	}
	else
	{
		if (isRunning)
		{
			relativeVel = glm::vec3(0.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			dir2D = 0.0f;
			if (lastInput.x != 0.0f)
			{
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
			}
		}
		MovingRight = false;
		MovingLeft = false;
	}

	lastInput = input;
}

void Hoshi::OnLand()
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
}

// Gravity Wave
void Hoshi::QCF(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCF)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("GravityWaveStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];
	SetFrameData(5.0f / 60.0f, 8.0f / 60.0f, 10.0f / 60.0f);

	if (proj == nullptr) {
		proj = new GravityWave(glm::vec3(1.0f, 0.0f, 1.0f), this, strength);
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 0.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));

	resetCombo();
}

// Slide
void Hoshi::QCB(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCB)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlideStart", 0.5f);
	hurtBox = hurtBoxes["slide"];
	hitBox = hitBoxes["slide"];
	SetFrameData(1.0f / 60.0f, 20.0f / 60.0f, 60.0f / 60.0f);

	this->ApplyForce(GetPosition() - opponent->GetPosition());

	if (hitBoxes["slide"]->CheckCollision(GetOpponent()->GetHurtBoxes()))
	{
		//GetOpponent()->Hit(5.0f, 1.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
		if (strength == 0)
		{

		}
		else if (strength == 1)
		{
			GetOpponent()->ApplyForce(glm::vec3(0.0f, 10.0f, 0.0f));
		}
		else if (strength == 2)
		{
			GetOpponent()->ApplyForce(glm::vec3(0.0f, 10.0f, 0.0f));
			//GetOpponent()->setApplyGravity(false);
		}
	}

	resetCombo();
}

void Hoshi::Unique()
{
	if (!CheckMoveState(moveState::UNIQUE)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;
	// fix levitate animations
	floating = !floating;
	if (floating)
	{
		setApplyGravity(false);
		hurtBox = hurtBoxes["aerial"];
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Float", 0.5f);
	}
	else
	{
		setApplyGravity(true);
		hurtBox = hurtBoxes["basic"];
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
				SetFrameData(4.0f / 60.0f, 15.0f / 60.0f, 5.0f / 60.0f);
				//SetFrameData(frameData["light"]);
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
			isIdle = false;

			if (isAirborne)
			{
				AirMedium();
			}
			else
			{
				currentMove = moveState::GROUNDMEDIUM;
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("MediumStart", 0.3f);
				hurtBox = hurtBoxes["basic"];
				hitBox = hitBoxes["medium"];
				SetFrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f);
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
			isIdle = false;

			if (isAirborne)
			{
				AirHeavy();
			}
			else
			{
				currentMove = moveState::GROUNDHEAVY;
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("HeavyStart", 0.5f);
				hurtBox = hurtBoxes["basic"];
				hitBox = hitBoxes["heavy"];
				SetFrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f);
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
	hurtBox = hurtBoxes["aerial"];
}

void Hoshi::AirQCB(int strength, bool simpleInput)
{
	overclock += 25;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlideStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];
}

void Hoshi::AirUnique()
{

}

void Hoshi::AirLight()
{
	currentMove = moveState::AIRLIGHT;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];
	SetFrameData(4.0f / 60.0f, 15.0f / 60.0f, 5.0f / 60.0f);

	if (proj == nullptr) {
		proj = new Kunai(glm::vec3(1.0f, 4.0f, 1.0f), this);
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 15.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));
}

void Hoshi::AirMedium()
{
	currentMove = moveState::AIRMEDIUM;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirMediumStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];
	SetFrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f);

	if (proj == nullptr) {
		proj = new Kunai(glm::vec3(1.0f, 4.0f, 1.0f), this);
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 5.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));
}

void Hoshi::AirHeavy()
{
	currentMove = moveState::AIRHEAVY;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirHeavyStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];
	SetFrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f);

	if (proj == nullptr) {
		proj = new Kunai(glm::vec3(1.0f, 4.0f, 1.0f), this);
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 1.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));
}
