#include "Character.h"
#include <glm/gtx/rotate_vector.hpp>
Character::Character(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	health = health_;
	meter = meter_;
	isRunning = isRunning_;
	isAirborne = isAirborne_;
	model = model_;
	maxSpeed = 5.0f;
	proj = new Projectile(model, glm::vec3(1.0f,0.0f,1.0f));
	target = glm::vec3();
}

Character::~Character() {
	if (proj) {
		delete proj;
		proj = nullptr;
	}
}

void Character::NotifyOnKeyDown(SDL_Scancode key_)
{
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
		proj->SetVelocity(glm::vec3(1.0f, 0.0f, 0.0f));
		proj->SetPosition(this->GetPosition());
		break;
	default:
		break;
	}
}

void Character::NotifyOnKeyUp(SDL_Scancode key_)
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

void Character::Update(const float deltaTime_)
{
	proj->Update(deltaTime_);

	if(isRunning)vel = glm::vec3(0.0f, vel.y, 0.0f) + glm::rotate(relativeVel, -glm::radians(camera->GetRotation().x + 90.0f), glm::vec3(0.0f,1.0f,0.0f));
	
	if (position.y >= 0.1f)
	{
		isAirborne = true;
	}

	if (position.y <= -0.1f)
	{
		position.y = 0.0f;
		vel.y = 0.0f;
		accel.y = 0.0f;
		isAirborne = false;
	}

	if (getIsAirborne())
	{
		ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
	}

	GameObject::Update(deltaTime_);

	if (!isRunning) {
		if (!opponent->getIsRunning() && getIsAirborne() == false)
		{
			axisOf2DMovement = camera->GetRight();
		}

		dir2D = 0.0f;
		if (MovingLeft) dir2D = -1.0f;
		if (MovingRight) dir2D = 1.0f;


		float preserveY = vel.y;
		vel = axisOf2DMovement * maxSpeed * dir2D;
		vel.y = preserveY;
	}

	
	if(vel != glm::vec3())	angle = atan2(vel.x, vel.z);;


}

void Character::QCF(int strength, bool simpleInput)
{
	if (isAirborne)
	{
		AirQCF(strength, simpleInput);
	}
}

void Character::QCB(int strength, bool simpleInput)
{
	if (isAirborne)
	{
		AirQCB(strength, simpleInput);
	}
}

void Character::Unique()
{
	
	if (isAirborne)
	{
		AirUnique();
	}
}

void Character::Light()
{
	if (isAirborne)
	{
		AirLight();
	}
}

void Character::Medium()
{
	if (isAirborne)
	{
		AirMedium();
	}
}

void Character::Heavy()
{
	if (isAirborne)
	{
		AirHeavy();
	}

}

void Character::Run(bool isRunning)
{
	this->isRunning = isRunning;
}

void Character::Move(glm::vec2 input)
{
}

void Character::AirQCF(int strength, bool simpleInput)
{
}

void Character::AirQCB(int strength, bool simpleInput)
{
}

void Character::AirUnique()
{
}

void Character::AirLight()
{
}

void Character::AirMedium()
{
}

void Character::AirHeavy()
{
}
