#include "Eldric.h"

Eldric::Eldric(glm::vec3 pos_, Model* hurtBox_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Eldric/Eldric.obj", "Resources/Materials/Eldric.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	// Add objs to morph target
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Eldric/EldricIdle.obj"));

	if (CoreEngine::GetInstance()->GetCurrentScene() != 1 || CoreEngine::GetInstance()->GetCurrentScene() != 6 || CoreEngine::GetInstance()->GetCurrentScene() != 8)
	{
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Block", new MorphTarget("Resources/Models/Eldric/EldricBlock.obj"));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Fall", new MorphTarget("Resources/Models/Eldric/EldricFall.obj"));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Hit", new MorphTarget("Resources/Models/Eldric/EldricHit.obj"));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Jump", new MorphTarget("Resources/Models/Eldric/EldricJump.obj", "Fall", 0.2f));

		// Walking
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkStart", new MorphTarget("Resources/Models/Eldric/EldricWalkStart.obj", "Walk1", 0.5f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk1", new MorphTarget("Resources/Models/Eldric/EldricWalk1.obj", "Walk2", 0.5f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk2", new MorphTarget("Resources/Models/Eldric/EldricWalk2.obj", "Walk3", 0.5f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk3", new MorphTarget("Resources/Models/Eldric/EldricWalk3.obj", "Walk4", 0.5f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk3", new MorphTarget("Resources/Models/Eldric/EldricWalk4.obj", "WalkEnd", 0.5f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkEnd", new MorphTarget("Resources/Models/Eldric/EldricWalkEnd.obj", "Walk1", 0.5f));

		// Running
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunStart", new MorphTarget("Resources/Models/Eldric/EldricRunStart.obj", "Run1", 0.1f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run1", new MorphTarget("Resources/Models/Eldric/EldricRun1.obj", "Run2", 0.1f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run2", new MorphTarget("Resources/Models/Eldric/EldricRun2.obj", "Run3", 0.1f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run3", new MorphTarget("Resources/Models/Eldric/EldricRun3.obj", "Run4", 0.1f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run4", new MorphTarget("Resources/Models/Eldric/EldricRun4.obj", "Run5", 0.1f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunEnd", new MorphTarget("Resources/Models/Eldric/EldricRunEnd.obj", "Run1", 0.1f));

		// Grounded
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightStart", new MorphTarget("Resources/Models/Eldric/EldricLightStart.obj", "Light1", 0.3f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Light1", new MorphTarget("Resources/Models/Eldric/EldricLight1.obj", "LightEnd", 0.3f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightEnd", new MorphTarget("Resources/Models/Eldric/EldricLightEnd.obj", "Idle", 0.3f));

		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyStart", new MorphTarget("Resources/Models/Eldric/EldricHeavyStart.obj", "Heavy1", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy1", new MorphTarget("Resources/Models/Eldric/EldricHeavy1.obj", "Heavy2", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy2", new MorphTarget("Resources/Models/Eldric/EldricHeavy2.obj", "Heavy3", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy3", new MorphTarget("Resources/Models/Eldric/EldricHeavy3.obj", "Heavy4", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy4", new MorphTarget("Resources/Models/Eldric/EldricHeavy4.obj", "HeavyEnd", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("HeavyEnd", new MorphTarget("Resources/Models/Eldric/EldricHeavyEnd.obj", "Idle", 0.2f));

		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumStart", new MorphTarget("Resources/Models/Eldric/EldricMediumStart.obj", "Medium1", 0.3f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Medium1", new MorphTarget("Resources/Models/Eldric/EldricMedium1.obj", "MediumEnd", 0.3f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumEnd", new MorphTarget("Resources/Models/Eldric/EldricMediumEnd.obj", "Idle", 0.3f));

		// Aerials
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyStart", new MorphTarget("Resources/Models/Eldric/EldricAirHeavyStart.obj", "AirHeavy1", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavy1", new MorphTarget("Resources/Models/Eldric/EldricAirHeavy1.obj", "AirHeavy2", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavy2", new MorphTarget("Resources/Models/Eldric/EldricAirHeavy2.obj", "AirHeavy3", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavy3", new MorphTarget("Resources/Models/Eldric/EldricAirHeavy3.obj", "AirHeavy4", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavy4", new MorphTarget("Resources/Models/Eldric/EldricAirHeavy4.obj", "AirHeavyEnd", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyEnd", new MorphTarget("Resources/Models/Eldric/EldricAirHeavyEnd.obj", "Idle", 0.2f));

		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightStart", new MorphTarget("Resources/Models/Eldric/EldricAirLightStart.obj", "AirLightEnd", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightEnd", new MorphTarget("Resources/Models/Eldric/EldricAirLightEnd.obj", "Idle", 0.2f));

		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMediumStart", new MorphTarget("Resources/Models/Eldric/EldricAirMediumStart.obj", "AirMedium1", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMedium1", new MorphTarget("Resources/Models/Eldric/EldricAirMedium1.obj", "AirMediumEnd", 0.2f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMediumEnd", new MorphTarget("Resources/Models/Eldric/EldricAirMediumEnd.obj", "Idle", 0.2f));

		// Specials
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("QCB", new MorphTarget("Resources/Models/Eldric/EldricQCB.obj", "Idle", 1.0f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("QCF", new MorphTarget("Resources/Models/Eldric/EldricQCF.obj", "Idle", 1.0f));

		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("UniqueStart", new MorphTarget("Resources/Models/Eldric/EldricUniqueStart.obj", "UniqueEnd", 0.25f));
		static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("UniqueEnd", new MorphTarget("Resources/Models/Eldric/EldricUniqueEnd.obj", "Idle", 0.25f));

		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

		// Hurtboxes
		hurtBoxes["basic"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["basic"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(1.0f, 15.0f, 0.0f), 1.25f, 6);

		hurtBoxes["light"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["light"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(0.0f, 15.0f, 0.0f), 1.25f, 6);

		hurtBoxes["medium"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["medium"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(-1.0f, 15.0f, 0.0f), 1.25f, 6);

		hurtBoxes["heavy"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["heavy"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(-2.5f, 13.0f, 0.0f), 1.25f, 6);

		hurtBoxes["airLight"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["airLight"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(0.0f, 15.0f, 0.0f), 1.25f, 6);

		hurtBoxes["airMedium"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["airMedium"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(-1.0f, 15.0f, 0.0f), 1.25f, 6);

		hurtBoxes["airHeavy"] = new HurtBox(hurtBox_, this->position, this);
		hurtBoxes["airHeavy"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(-2.5f, 13.0f, 0.0f), 1.25f, 6);

		// Hitboxes
		hitBoxes["light"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["light"]->spawnSpheres(this->position + glm::vec3(1.0f, 6.0f, 0.0f), this->position + glm::vec3(5.0f, 8.0f, 0.0f), 0.75f, 6);

		hitBoxes["medium1"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["medium1"]->spawnSpheres(this->position + glm::vec3(1.0f, 6.0f, 0.0f), this->position + glm::vec3(6.0f, 7.0f, 0.0f), 0.75f, 6);

		hitBoxes["medium2"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["medium2"]->spawnSpheres(this->position + glm::vec3(1.0f, 6.0f, 0.0f), this->position + glm::vec3(6.0f, 1.0f, 0.0f), 0.75f, 6);

		hitBoxes["heavy"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["heavy"]->spawnSpheres(this->position + glm::vec3(1.0f, 6.0f, 0.0f), this->position + glm::vec3(5.0f, 7.0f, 0.0f), 0.75f, 4);

		hitBoxes["airLight"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["airLight"]->spawnSpheres(this->position + glm::vec3(0.0f, 6.0f, 0.0f), this->position + glm::vec3(5.0f, 4.0f, 0.0f), 0.75f, 6);

		hitBoxes["airMedium1"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["airMedium1"]->spawnSpheres(this->position + glm::vec3(0.0f, 6.0f, 0.0f), this->position + glm::vec3(6.0f, 8.0f, 0.0f), 0.75f, 6);

		hitBoxes["airMedium2"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["airMedium2"]->spawnSpheres(this->position + glm::vec3(0.0f, 6.0f, 0.0f), this->position + glm::vec3(6.0f, 1.0f, 0.0f), 0.75f, 6);

		hitBoxes["airHeavy"] = new HitBox(hurtBox_, this->position, this);
		hitBoxes["airHeavy"]->spawnSpheres(this->position + glm::vec3(-2.0f, 6.0f, 0.0f), this->position + glm::vec3(5.0f, 6.0f, 0.0f), 0.75f, 6);

		// Framedata
		frameData["light"] = FrameData(4.0f / 60.0f, 30.0f / 60.0f, 20.0f / 60.0f, 25.0f, 0.25f, 0.1f, glm::vec3(0.5f, 0.0f, 0.0f), 0);
		frameData["medium"] = FrameData(5.0f / 60.0f, 15.0f / 60.0f, 40.0f / 60.0f, 30.0f, 0.3, 0.1f, glm::vec3(0.5f, 0.0f, 0.0f), 0);
		frameData["heavy"] = FrameData(5.0f / 60.0f, 30.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.5, 0.25, glm::vec3(0.5f, 0.0f, 0.0f), 0);

		frameData["airLight"] = FrameData(4.0f / 60.0f, 30.0f / 60.0f, 45.0f / 60.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);
		frameData["airMedium"] = FrameData(5.0f / 60.0f, 30.0f / 60.0f, 30.0f / 60.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);
		frameData["airHeavy"] = FrameData(1.0f / 60.0f, 120.0f / 60.0f, 20.0f / 60.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);

		frameData["unique"] = FrameData(4.0f / 60.0f, 15.0f / 60.0f, 5.0f / 60.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);

		// Eel
		frameData["QCF0"] = FrameData(5.0f / 60.0f, 10.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.0f, 0.0f, glm::vec3(5.0f, 0.0f, 0.0f), 0);
		frameData["QCF1"] = FrameData(5.0f / 60.0f, 10.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1);
		frameData["QCF2"] = FrameData(5.0f / 60.0f, 10.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 2);

		// Gaunts
		frameData["QCB0"] = FrameData(1.0f / 60.0f, 20.0f / 60.0f, 60.0f / 60.0f, 70.0f, 1.0f, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f), 0);
		frameData["QCB1"] = FrameData(1.0f / 60.0f, 20.0f / 60.0f, 60.0f / 60.0f, 70.0f, 1.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), 1);
		frameData["QCB2"] = FrameData(1.0f / 60.0f, 20.0f / 60.0f, 60.0f / 60.0f, 70.0f, 1.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), 2);

		hurtBox = hurtBoxes["basic"];
	}
	SceneGraph::GetInstance()->AddModel(model);
}

Eldric::~Eldric()
{
	delete proj;
	proj = nullptr;
	ResetProjectiles();

	Character::~Character();
}

void Eldric::Update(const float deltaTime_)
{
	if (projs.size() > 0)
	{
		for (auto p : projs)
		{
			p->Update(deltaTime_);
		}
	}
	if (proj)
	{
		proj->Update(deltaTime_);
	}

	if (hurtBox)
	{
		hurtBox->Update(deltaTime_);
	}
	if (!isIdle && currentMove == moveState::NONE && !MovingLeft && !MovingRight)
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

void Eldric::Run(bool isRunning_)
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

void Eldric::Move(glm::vec2 input)
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
			if (!MovingLeft)	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("WalkStart", 0.5f);
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

void Eldric::OnLand()
{
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);
}

// Eel
void Eldric::QCF(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCF)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("QCF", 0.5f);
	hurtBox = hurtBoxes["basic"];

	if (strength == 0)
	{
		SetFrameData(frameData["QCF0"]);
	}
	else if (strength == 2 && overclock >= 25.0f)
	{
		SetFrameData(frameData["QCF2"]);
	}
	else
	{
		SetFrameData(frameData["QCF1"]);
	}
}

void Eldric::OnQCFActive(int strength)
{
	Projectile* eel;
	{
		if (strength == 0)
		{
			eel = new Eel(frameData["QCF0"], glm::vec3(1.0f, 0.0f, 1.0f), this);
			eel->SetVelocity(glm::vec3(10.0f, 5.0f, 0.0f));
		}
		else if (strength == 2 && overclock >= 25.0f)
		{
			eel = new Eel(frameData["QCF2"], glm::vec3(1.0f, 0.0f, 1.0f), this);
			eel->SetVelocity(glm::vec3(10.0f, 5.0f, 0.0f));
			overclock -= 25.0f;
		}
		else
		{
			eel = new Eel(frameData["QCF1"], glm::vec3(1.0f, 0.0f, 1.0f), this);
			eel->SetVelocity(glm::vec3(10.0f, 10.0f, 0.0f));
		}
	}

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 0.0f, position.z - opponent->GetPosition().z);
	eel->SetTarget(nullptr);
	eel->SetPosition(this->GetPosition() + (glm::vec3(0.0f, 6.0f, 0.0f)));
	
	projs.push_back(eel);

	eel = nullptr;

	resetCombo();
}

void Eldric::AirQCF(int strength, bool simpleInput)
{

}

void Eldric::OnAirQCFActive(int strength)
{

}

// Gaunts

void Eldric::QCB(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCB)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("QCB", 0.3f);
	hurtBox = hurtBoxes["basic"];

	if (strength == 0)
	{
		SetFrameData(frameData["QCB0"]);
	}
	else if (strength == 2 && overclock >= 25.0f)
	{
		SetFrameData(frameData["QCB2"]);
	}
	else
	{
		SetFrameData(frameData["QCB1"]);
	}
}

void Eldric::OnQCBActive(int strength)
{
	Projectile* nightGaunt;
		if (strength == 0)
		{
			nightGaunt = new NightGaunt(frameData["QCF0"], glm::vec3(1.0f, 0.0f, 1.0f), this);
		}
		else if (strength == 2 && overclock >= 25.0f)
		{
			nightGaunt = new NightGaunt(frameData["QCF2"], glm::vec3(1.0f, 0.0f, 1.0f), this);
			overclock -= 25.0f;
		}
		else
		{
			nightGaunt = new NightGaunt(frameData["QCF1"], glm::vec3(1.0f, 0.0f, 1.0f), this);
		}
	

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 0.0f, position.z - opponent->GetPosition().z);
	nightGaunt->SetTarget(nullptr);
	nightGaunt->SetPosition(this->GetPosition() + (glm::vec3(0.0f, 6.0f, 0.0f)));
	nightGaunt->SetVelocity((glm::vec3(-dir)) * 0.25f);

	projs.push_back(nightGaunt);
	nightGaunt = nullptr;
	resetCombo();
}

void Eldric::AirQCB(int strength, bool simpleInput)
{

}

void Eldric::OnAirQCBActive(int strength)
{

}

void Eldric::Unique()
{
	if (!CheckMoveState(moveState::UNIQUE)) return;

	if (nextActionable > 0.0f) return;
	isIdle = false;

	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("UniqueStart", 0.3f);
	hurtBox = hurtBoxes["basic"];
	SetFrameData(frameData["Unique"]);

	if (proj == nullptr)
	{
		proj = new Spike(frameData["Unique"], glm::vec3(1.0f, 0.0f, 1.0f), this);
		proj->SetVelocity(glm::vec3(0.0f));
		proj->SetPosition(this->GetPosition() + (glm::vec3(4.0f, 0.0f, 0.0f)));
	}
	else
	{
		static_cast<Spike*>(proj)->SetActive(true);
	}
}

void Eldric::OnUniqueActive()
{

}

void Eldric::AirUnique()
{

}

void Eldric::OnAirUniqueActive()
{

}

void Eldric::Light()
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
				SetFrameData(frameData["light"]);
			}
		}
	}
}

void Eldric::OnLightActive()
{

}

void Eldric::AirLight()
{
	currentMove = moveState::AIRLIGHT;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);
	hurtBox = hurtBoxes["basic"];
	hitBox = hitBoxes["airLight"];
	SetFrameData(frameData["airLight"]);
}

void Eldric::OnAirLightActive()
{

}

void Eldric::Medium()
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
				hitBox = hitBoxes["medium1"];
				SetFrameData(frameData["medium"]);
			}
		}
	}
}

void Eldric::OnMediumActive()
{
	
}

void Eldric::AirMedium()
{
	currentMove = moveState::AIRMEDIUM;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirMediumStart", 0.5f);
	hurtBox = hurtBoxes["basic"];
	hitBox = hitBoxes["airMedium1"];
	SetFrameData(frameData["airMedium"]);
}

void Eldric::OnAirMediumActive()
{

}

void Eldric::OnMediumRecovery()
{
	hitBox = hitBoxes["medium2"];
	hurtBox = hurtBoxes["medium"];
}

void Eldric::OnAirMediumRecovery()
{
	hitBox = hitBoxes["airMedium2"];
}

void Eldric::Heavy()
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
				SetFrameData(frameData["heavy"]);
			}
		}
	}
}

void Eldric::ResetProjectile()
{
	delete proj;
	proj = nullptr;
}


void Eldric::ResetProjectiles()
{
	if (projs.size() > 0)
	{
		for (auto p : projs)
		{
			delete p;
			p = nullptr;
		}
	}
	projs.clear();
}

void Eldric::RemoveProjectile(std::string tag_)
{
	for (int i = 0; i < projs.size(); i++)
	{
		if (projs[i]->GetTag() == tag_)
		{
			delete projs[i];
			projs[i] = nullptr;
			projs.erase(projs.begin() + i);
		}
	}
}

void Eldric::OnHeavyActive()
{
	
}

void Eldric::AirHeavy()
{
	currentMove = moveState::AIRHEAVY;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirHeavyStart", 0.5f);
	hurtBox = hurtBoxes["basic"];
	SetFrameData(frameData["airHeavy"]);
}

void Eldric::OnAirHeavyActive()
{
	
}

void Eldric::OnHeavyRecovery()
{
	hitBox = hitBoxes["heavy"];
	hurtBox = hurtBoxes["heavy"];
}

void Eldric::OnAirHeavyRecovery()
{
	hitBox = hitBoxes["airHeavy"];
}