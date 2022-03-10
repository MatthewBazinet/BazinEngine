#include "AlexisBruce.h"
#include "../HurtBox.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
AlexisBruce::AlexisBruce(glm::vec3 position_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/AlexisBruce.obj", "Resources/Materials/AlexisBruce.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), position_)
{
	SceneGraph::GetInstance()->AddModel(model);
	rockModel = nullptr;
}

AlexisBruce::~AlexisBruce()
{
	proj = nullptr;
	delete proj;

	rockModel = nullptr;
	delete rockModel;

	Character::~Character();
}

void AlexisBruce::NotifyOnKeyDown(SDL_Scancode key_)
{
	if (nextActionable > 0.0f) return;
	switch (key_)
	{

	case SDL_SCANCODE_W:
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
			ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
		}
		break;
	case SDL_SCANCODE_A:
		//GetCamera()->SetPosition(GetCamera()->GetPosition() - glm::vec3(0.01f, 0.0f, 0.0f));
		if (isRunning) {
			relativeVel = glm::vec3(-5.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			MovingLeft = true;
			MovingRight = false;
		}

		break;
	case SDL_SCANCODE_S:
		if (isRunning)
		{
			relativeVel = glm::vec3(relativeVel.x, relativeVel.y, 5.0f);

		}
		//GetCamera()->SetPosition(GetCamera()->GetPosition() + glm::vec3(0.0f, 0.0f, 0.01f));
		break;
	case SDL_SCANCODE_D:
		if (isRunning)
		{
			relativeVel = glm::vec3(5.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			MovingRight = true;
			MovingLeft = false;
		}
		break;
	case SDL_SCANCODE_LSHIFT:
		Run(true);
	case SDL_SCANCODE_U:
		Light();
		break;
	case SDL_SCANCODE_I:
		Medium();
		break;
	case SDL_SCANCODE_O:
		Heavy();
		break;
	case SDL_SCANCODE_P:
		Unique();
		break;
	case SDL_SCANCODE_G:
		//proj->SetVelocity(glm::vec3(1.0f, 0.0f, 0.0f));
		//proj->SetPosition(this->GetPosition());
		QCF(0, true);
		break;
	default:
		break;
	}
}

void AlexisBruce::NotifyOnKeyUp(SDL_Scancode key_)
{
	switch (key_)
	{
	case SDL_SCANCODE_W:
		if (relativeVel.z < 0.0f && isRunning)
		{
			relativeVel = glm::vec3(relativeVel.x, relativeVel.y, 0.0f);
		}

		break;
	case SDL_SCANCODE_A:
		if (relativeVel.x < 0.0f && isRunning)
		{
			relativeVel = glm::vec3(0.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			if (MovingLeft)
			{
				dir2D = 0.0f;
			}
		}
		MovingLeft = false;
		break;
	case SDL_SCANCODE_S:
		if (relativeVel.z > 0.0f && isRunning)
		{
			relativeVel = glm::vec3(relativeVel.x, relativeVel.y, 0.0f);
		}
		break;
	case SDL_SCANCODE_D:
		if (relativeVel.x > 0.0f && isRunning)
		{
			relativeVel = glm::vec3(0.0f, relativeVel.y, relativeVel.z);
		}
		else
		{
			if (MovingRight)
			{
				dir2D = 0.0f;
			}
		}
		MovingRight = false;
		break;
	case SDL_SCANCODE_U:

		break;
	case SDL_SCANCODE_I:

		break;
	case SDL_SCANCODE_O:

		break;
	case SDL_SCANCODE_P:

		break;
	case SDL_SCANCODE_Q:

		break;
	case SDL_SCANCODE_E:

		break;
	case SDL_SCANCODE_SPACE:

		break;
	case SDL_SCANCODE_LSHIFT:
		Run(false);
		relativeVel = glm::vec3(0.0f, 0.0f, 0.0f);
	default:
		break;
	}
}

void AlexisBruce::Update(const float deltaTime_)
{
	if (proj) {
		proj->Update(deltaTime_);
	}
	if (hurtBox) {
		hurtBox->Update(deltaTime_);
	}
	Character::Update(deltaTime_);
}

void AlexisBruce::SetModels(Model* rockModel_, Model* hurtBox_)
{
	if (rockModel != nullptr) {
		delete rockModel;
		rockModel = nullptr;
	}
	rockModel = rockModel_;
	hurtBox = new HurtBox(NULL,this->position,this);
	hurtBox->SpawnHurtBox(hurtBox_,this->position, this->position + glm::vec3(0.0f,16.0f,0.0f), 2.0f, 5);
}

void AlexisBruce::QCF(int strength, bool simpleInput)
{
	if (proj == nullptr) {
		proj = new Projectile(rockModel, glm::vec3(1.0f, 0.0f, 1.0f),this);
	}
	//Rock Toss
	if (nextActionable > 0.0f) return;

	if (isAirborne)
	{
		AirQCF(strength, simpleInput);
	}
	if (strength == 0)
	{
		glm::vec3 dir = position - opponent->GetPosition();
		proj->SetTarget(nullptr);
		proj->SetPosition(this->GetPosition());

		proj->SetVelocity(glm::vec3(dir));
		
	}
	else if (strength == 1) {
		glm::vec3 dir = position - opponent->GetPosition();
		proj->SetTarget(nullptr);
		proj->SetPosition(this->GetPosition());
		proj->SetVelocity(glm::vec3(dir));
		//proj->SetScale(proj->GetScale() * glm::vec3(2));
		
	}
	else if(strength == 2)
	{
		glm::vec3 dir = position - opponent->GetPosition();
		proj->SetTarget(opponent);
		proj->SetPosition(this->GetPosition());
		proj->SetScale(proj->GetScale() * glm::vec3(1.5));
		overclock -= 50.0f;
	}
}

void AlexisBruce::QCB(int strength, bool simpleInput)
{
	if (nextActionable > 0.0f) return;

	if (isAirborne)
	{
		AirQCB(strength, simpleInput);
	}
}

void AlexisBruce::Unique()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirUnique();
	}
}

void AlexisBruce::Light()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirLight();
	}
}

void AlexisBruce::Medium()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirMedium();
	}
}

void AlexisBruce::Heavy()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirHeavy();
	}
}

void AlexisBruce::Run(bool isRunning_)
{
	if (nextActionable > 0.0f) return;

	isRunning = isRunning_;
}

void AlexisBruce::Move(glm::vec2 input)
{
	if (nextActionable > 0.0f) return;
}


void AlexisBruce::AirQCF(int strength, bool simpleInput)
{
	if (nextActionable > 0.0f) return;

}

void AlexisBruce::AirQCB(int strength, bool simpleInput)
{
	if (nextActionable > 0.0f) return;

}

void AlexisBruce::AirUnique()
{
	if (nextActionable > 0.0f) return;

}

void AlexisBruce::AirLight()
{
	if (nextActionable > 0.0f) return;

}

void AlexisBruce::AirMedium()
{
	if (nextActionable > 0.0f) return;

}

void AlexisBruce::AirHeavy()
{
	if (nextActionable > 0.0f) return;

}
