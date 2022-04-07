#include "Wulfrun.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Rendering/SceneGraph.h"
#include "../SlashWave.h"

Wulfrun::Wulfrun(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Wulfrun/Wulfrun.obj", "Resources/Materials/Wulfrun.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle", new MorphTarget("Resources/Models/Wulfrun/WulfrunIdleStance.obj", "Idle2", 1.5f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Idle2", new MorphTarget("Resources/Models/Wulfrun/WulfrunIdleStance2.obj", "Idle", 1.5f));

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Jump", new MorphTarget("Resources/Models/Wulfrun/WulfrunJumpStart.obj", "Fall", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Fall", new MorphTarget("Resources/Models/Wulfrun/WulfrunFall.obj", "Fall", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Block", new MorphTarget("Resources/Models/Wulfrun/WulfrunBlock.obj", "Block", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Hit", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirHit.obj", "Hit", 1.0f));

	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("WalkStart", new MorphTarget("Resources/Models/Wulfrun/WulfrunWalk1.obj", "Walk2", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Walk2", new MorphTarget("Resources/Models/Wulfrun/WulfrunWalk2.obj", "WalkStart", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("RunStart", new MorphTarget("Resources/Models/Wulfrun/WulfrunRun1.obj", "Run2", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Run2", new MorphTarget("Resources/Models/Wulfrun/WulfrunRun2.obj", "RunStart", 1.0f));
	
	//Normals
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightStart", new MorphTarget("Resources/Models/Wulfrun/WulfrunLightStart.obj", "LightEnd", 0.2f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("LightEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunLightEnd.obj", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumStart", new MorphTarget("Resources/Models/Wulfrun/WulfrunMediumStart.obj", "MediumEnd", 0.2f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("MediumEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunMediumEnd.obj", "Idle", 0.1f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("Heavy", new MorphTarget("Resources/Models/Wulfrun/WulfrunHeavyEnd.obj", "Idle", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLight", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirLightStart.obj", "AirLightEnd", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirLightEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirLightEnd.obj", "Fall", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirMedium", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirMedium.obj", "Idle", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavy", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirHeavyStart.obj", "AirHeavyEnd", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("AirHeavyEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunAirHeavyEnd.obj", "Fall", 1.0f));

	//Specials
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashWave", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashWave.obj", "SlashWaveEnd", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashWaveEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashWaveEnd.obj", "Idle", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashWaveOverclocked", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashWave.obj", "SlashWaveOverclocked2", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashWaveOverclocked2", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashWaveEnd.obj", "SlashWaveOverclocked3", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashWaveOverclocked3", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashWaveOverclocked.obj", "Idle", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashKick", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashKick.obj", "SlashKickEnd", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("SlashKickEnd", new MorphTarget("Resources/Models/Wulfrun/WulfrunSlashKickEnd.obj", "Idle", 1.0f));
	static_cast<MorphTargetAnimatedModel*>(model)->AddMorphTarget("DashBite", new MorphTarget("Resources/Models/Wulfrun/WulfrunDashBite.obj", "Idle", 1.0f));


	isCharge = true;

	SceneGraph::GetInstance()->AddModel(model);

	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle2", 0.5f);
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Idle", 0.5f);

	Model* hurtBox_ = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(hurtBox_);

	//HurtBoxes

	hurtBoxes["basic"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["basic"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(1.5f, 15.0f, 0.0f), 1.25f, 5);

	hurtBoxes["running"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["running"]->SpawnHurtBox(hurtBox_, this->position, this->position + glm::vec3(1.5f, 12.0f, 0.0f), 1.25f, 5);

	hurtBoxes["aerial"] = new HurtBox(hurtBox_, this->position, this);
	hurtBoxes["aerial"]->SpawnHurtBox(hurtBox_, this->position + glm::vec3(0.0f, 2.0f, 0.0f), this->position + glm::vec3(0.0f, 15.0f, 0.0f), 1.25f, 5);

	//HitBoxes

	hitBoxes["light"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["light"]->spawnSpheres(this->position + glm::vec3(0.0f, 7.0f, 0.0f), this->position + glm::vec3(4.5f, 7.0f, 0.0f), 0.75f, 3);

	hitBoxes["medium"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["medium"]->spawnSpheres(this->position + glm::vec3(3.0f, 7.0f, 0.0f), this->position + glm::vec3(4.0f, 12.0f, 0.0f), 0.75f, 4);

	hitBoxes["airLight"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["airLight"]->spawnSpheres(this->position + glm::vec3(0.0f, 7.0f, 0.0f), this->position + glm::vec3(3.0f, 6.5f, 0.0f), 1.25f, 4);

	hitBoxes["airMedium"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["airMedium"]->spawnSpheres(this->position + glm::vec3(7.5f, 0.5f, 0.0f), this->position + glm::vec3(7.5f, 0.5f, 0.0f), 1.25f, 2);

	hitBoxes["qcb"] = new HitBox(hurtBox_, this->position, this);
	hitBoxes["qcb"]->spawnSpheres(this->position + glm::vec3(0.0f, 5.0f, 0.0f), this->position + glm::vec3(6.0f, 5.0f, 0.0f), 0.75f, 4);

	hurtBox = hurtBoxes["basic"];

	hurtBox = nullptr;

	frameData["light"] = FrameData(4.0f / 60.0f, 15.0f / 60.0f, 5.0f / 60.0f, 25.0f, 0.25f, 6.0f / 60.0f, glm::vec3(0.5f, 0.0f, 0.0f), 0);
	frameData["medium"] = FrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f, 30.0f, 0.3, 0.0f / 60.0f, glm::vec3(0.5f, 0.0f, 0.0f), 0);
	frameData["heavy"] = FrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);

	frameData["airLight"] = FrameData(4.0f / 60.0f, 15.0f / 60.0f, 5.0f / 60.0f, 30.0f, 0.0f / 60.0f, 0.0f / 60.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);
	frameData["airMedium"] = FrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f, 60.0f, 0.0f / 60.0f, 0.0f / 60.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1);
	frameData["airHeavy"] = FrameData(5.0f / 60.0f, 20.0f / 60.0f, 10.0f / 60.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1);

	frameData["DashBite"] = FrameData(8.0f / 60.0f, 16.0f / 60.0f, 24.0f / 60.0f, 80.0f, 1.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0);

	frameData["SlashWave0"] = FrameData(5.0f / 60.0f, 8.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.0f, 0.0f, glm::vec3(5.0f, 0.0f, 0.0f), 0);
	frameData["SlashWave1"] = FrameData(5.0f / 60.0f, 8.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.0f, 0.0f, glm::vec3(0.0f, 10.0f, 0.0f), 1);
	frameData["SlashWave2"] = FrameData(5.0f / 60.0f, 8.0f / 60.0f, 20.0f / 60.0f, 30.0f, 0.0f, 0.0f, glm::vec3(0.0f, 10.0f, 0.0f), 2);

	// Slide
	frameData["SlashKick0"] = FrameData(4.0f / 60.0f, 6.0f / 60.0f, 30.0f / 60.0f, 130.0f, 1.0f, 20.0f / 60.0f, glm::vec3(1.0f, 4.0f, 0.0f), 0);
	frameData["SlashKick1"] = FrameData(4.0f / 60.0f, 6.0f / 60.0f, 30.0f / 60.0f, 150.0f, 1.0f, 20.0f / 60.0f, glm::vec3(0.0f, 10.0f, 0.0f), 1);
	frameData["SlashKick2"] = FrameData(4.0f / 60.0f, 6.0f / 60.0f, 30.0f / 60.0f, 150.0f, 1.0f, 20.0f / 60.0f, glm::vec3(0.0f, 15.0f, 0.0f), 2);
}

Wulfrun::~Wulfrun()
{
	ResetProjectiles();
	Character::~Character();
}

void Wulfrun::Update(const float deltaTime_)
{
	if (projs.size() > 0)
	{
		for (auto p : projs)
		{
			p->Update(deltaTime_);
		}
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

void Wulfrun::Run(bool isRunning_)
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

void Wulfrun::Move(glm::vec2 input)
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

void Wulfrun::QCF(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCF)) return;

	if (nextActionable > 0.0f) return;

	isIdle = false;

		if (strength == 2 && overclock >= 25.0f)
		{
			overclock -= 25.0f;
			SetFrameData(frameData["SlashWave2"]);
			static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlashWaveOverclocked", 0.5f);
		}
		else
		{
			if (strength == 0)
			{
				overclock += 3.0f;
				SetFrameData(frameData["SlashWave0"]);
			}
			else
			{
				overclock += 5.0f;
				SetFrameData(frameData["SlashWave1"]);
			}
			static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlashWave", 0.5f);
		}
		hurtBox = hurtBoxes["aerial"];
		
		resetCombo();
}

void Wulfrun::QCB(int strength, bool simpleInput)
{
	if (!CheckMoveState(moveState::QCB)) return;

	if (nextActionable > 0.0f) return;

	if (strength == 2 && overclock >= 25.0f)
	{
		overclock -= 25.0f;
		SetFrameData(frameData["SlashKick2"]);
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlashWaveOverclocked", 0.5f);
		ApplyForce(glm::vec3(0.0f, 4.0f, 0.0f));
	}
	else
	{
		static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("SlashWave", 0.5f);
		if (strength == 0)
		{
			overclock += 3.0f;
			SetFrameData(frameData["SlashKick0"]);
			ApplyForce(glm::vec3(0.0f, 4.0f, 0.0f));
		}
		else
		{
			overclock += 5.0f;
			SetFrameData(frameData["SlashKick1"]);
			ApplyForce(glm::vec3(0.0f, 4.0f, 0.0f));
		}
		
	}
	hitBox = hitBoxes["SlashKick"];

	resetCombo();
}

void Wulfrun::Unique()
{
	if (!CheckMoveState(moveState::UNIQUE)) return;

	if (nextActionable > 0.0f) return;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("DashBite", 0.5f);
	hitBox = hitBoxes["DashBite"];
	SetFrameData(frameData["DashBite"]);

	ApplyForce(10.0f * glm::normalize(opponent->GetPosition() - GetPosition()));

	resetCombo();
}

void Wulfrun::Light()
{
	if (nextActionable > 0.0f) return;
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
				//SetFrameData(4.0f / 60.0f, 6.0f / 60.0f, 10.0f / 60.0f);
				SetFrameData(frameData["light"]);
			}
		}
	}
}

void Wulfrun::Medium()
{
	if (nextActionable > 0.0f) return;
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
				//SetFrameData(4.0f / 60.0f, 6.0f / 60.0f, 10.0f / 60.0f);
				SetFrameData(frameData["medium"]);
			}
		}
	}
}

void Wulfrun::Heavy()
{
	if (nextActionable > 0.0f) return;
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
				static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("Heavy", 0.3f);
				hurtBox = hurtBoxes["basic"];
				hitBox = hitBoxes["heavy"];
				//SetFrameData(4.0f / 60.0f, 6.0f / 60.0f, 10.0f / 60.0f);
				SetFrameData(frameData["heavy"]);
			}
		}
	}
}

void Wulfrun::ResetProjectiles()
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

void Wulfrun::RemoveProjectile(std::string tag_)
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
	currentMove = moveState::AIRLIGHT;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLight", 0.5f);
	hitBox = hitBoxes["airlight"];
	SetFrameData(frameData["airLight"]);
}

void Wulfrun::AirMedium()
{
	currentMove = moveState::AIRMEDIUM;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirMedium", 0.5f);
	hitBox = hitBoxes["airMedium"];
	SetFrameData(frameData["airMedium"]);
	glm::vec3 dir = 10.0f * glm::normalize(glm::vec3(position.x - opponent->GetPosition().x, 15.0f, position.z - opponent->GetPosition().z));
	ApplyForce(-dir);
}

void Wulfrun::AirHeavy()
{
	currentMove = moveState::AIRHEAVY;
	static_cast<MorphTargetAnimatedModel*>(model)->SetCurrentMorphTarget("AirLightStart", 0.5f);
	hurtBox = hurtBoxes["aerial"];

	hitBox = nullptr;
	SetFrameData(frameData["airHeavy"]);

}

void Wulfrun::OnQCFActive(int strenth)
{

	Projectile* proj = new SlashWave(frameData["qcf"], 5.0f, glm::vec3(1.0f, 4.0f, 1.0f), this);

	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 0.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));

	projs.push_back(proj);

	proj = nullptr;


}

void Wulfrun::OnQCFRecovery(int strength)
{
	if (strength == 2)
	{
		Projectile* proj = new SlashWave(frameData["qcf"], 5.0f, glm::vec3(1.0f, 4.0f, 1.0f), this);

		glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 0.0f, position.z - opponent->GetPosition().z);
		proj->SetTarget(nullptr);
		proj->SetPosition(this->GetPosition());
		proj->SetVelocity(glm::vec3(-dir));

		projs.push_back(proj);

		proj = nullptr;
	}
}

void Wulfrun::OnQCBActive(int strenth)
{
	
}

void Wulfrun::OnQCBRecovery(int strength)
{
	hurtBox = hurtBoxes["basic"];
	if (strength == 2)
	{
		QCB(0, false);
	}
}

void Wulfrun::OnUniqueActive()
{
}

void Wulfrun::OnAirHeavyActive()
{
	Projectile* proj = new SlashWave(frameData["airHeavy"], 1.0f, glm::vec3(1.0f, 4.0f, 1.0f), this);


	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 15.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));

	projs.push_back(proj);
	proj = nullptr;
}

void Wulfrun::OnHeavyActive()
{
	Projectile* proj = new SlashWave(frameData["airHeavy"], 1.0f, glm::vec3(1.0f, 4.0f, 1.0f), this);


	glm::vec3 dir = glm::vec3(position.x - opponent->GetPosition().x, 15.0f, position.z - opponent->GetPosition().z);
	proj->SetTarget(nullptr);
	proj->SetPosition(this->GetPosition());
	proj->SetVelocity(glm::vec3(-dir));

	projs.push_back(proj);
	proj = nullptr;
}
