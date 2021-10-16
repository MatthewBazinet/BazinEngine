#include "Character.h"

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
			vel = glm::vec3(vel.x, vel.y, -5.0f);

		}
		else
		{
			if (!isAirborne)
			{
				vel = glm::vec3(vel.x, 22.0f, vel.z);
			}
			ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
		}
		break;
	case SDL_SCANCODE_A:
		//GetCamera()->SetPosition(GetCamera()->GetPosition() - glm::vec3(0.01f, 0.0f, 0.0f));
		if (isRunning) {
			vel = glm::vec3(-5.0f, vel.y, vel.z);
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
			vel = glm::vec3(vel.x, vel.y, 5.0f);

		}
		//GetCamera()->SetPosition(GetCamera()->GetPosition() + glm::vec3(0.0f, 0.0f, 0.01f));
		break;
	case SDL_SCANCODE_D:
		if (isRunning) 
		{
			vel = glm::vec3(5.0f, vel.y, vel.z);
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
	default:
		break;
	}
}

void Character::NotifyOnKeyUp(SDL_Scancode key_)
{
	switch (key_)
	{
	case SDL_SCANCODE_W:
		if (vel.z < 0.0f && isRunning)
		{
			vel = glm::vec3(vel.x, vel.y, 0.0f);
		}

		break;
	case SDL_SCANCODE_A:
		if (vel.x < 0.0f && isRunning)
		{
			vel = glm::vec3(0.0f, vel.y, vel.z);
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
		if (vel.z > 0.0f && isRunning)
		{
			vel = glm::vec3(vel.x, vel.y, 0.0f);
		}
		break;
	case SDL_SCANCODE_D:
		if (vel.x > 0.0f && isRunning)
		{
			vel = glm::vec3(0.0f, vel.y, vel.z);
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
	default:
		break;
	}
}

void Character::Update(const float deltaTime_)
{

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
			axisOf2DMovement = glm::normalize(opponent->GetPosition() - position);
			target = opponent->GetPosition();
		}

		glm::vec3 projection = glm::dot(position - target, axisOf2DMovement) * axisOf2DMovement;
		glm::vec3 axisMagProj = glm::length(projection) * axisOf2DMovement;

		if (glm::equal(axisMagProj - projection, glm::vec3(0.0f, 0.0f, 0.0f)).b) {
			if (MovingLeft) {
				dir2D = 1.0f;
			}
			else if (MovingRight)
			{
				dir2D = -1.0f;
			}
			else
			{
				dir2D = 0.0f;
			}
		}
		else
		{
			if (MovingLeft) {
				dir2D = -1.0f;
			}
			else if (MovingRight)
			{
				dir2D = 1.0f;
			}
			else
			{
				dir2D = 0.0f;
			}
		}

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
