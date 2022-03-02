#include "Character.h"
#include <glm/gtx/rotate_vector.hpp>
#include "../Projectile.h"
#include "../HurtBox.h"

Character::Character(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	health = health_;
	overclock = meter_;
	isRunning = isRunning_;
	isAirborne = isAirborne_;
	model = model_;
	maxSpeed = 5.0f;
	//proj = new Projectile(model, glm::vec3(1.0f,0.0f,1.0f));

	target = glm::vec3();
	hurtBox = new HurtBox(model_);
	hurtBox->SpawnHurtBox(model_,this->position, this->position, 1.0f, 1);
	currentMove = moveState::NONE;

	//combo["light"] = false;
	//combo["medium"] = false;
	//combo["heavy"] = false;
}

Character::~Character() {
	if (hurtBox) {
		delete hurtBox;
		hurtBox = nullptr;
	}
}

void Character::NotifyOnKeyDown(SDL_Scancode key_)
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
			//ApplyForce(glm::vec3(accel.x, -9.81f * mass, accel.z));
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
		break;
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
		break;
	default:
		break;
	}
}

void Character::Update(const float deltaTime_)
{
	if (nextActionable > 0.0f)
	{
		nextActionable -= deltaTime_;

	}
	//proj->Update(deltaTime_);

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

	
	if(vel != glm::vec3())	angle = atan2(vel.x, vel.z);
	//gonna remove once we can damage characters
	health -= 1.0f;
	if (health <= 5.0f) {
		health = 100.0f;
	}	

}

bool Character::CheckMoveState(moveState move_)
{
	// checks current move against the move that is inputted
	switch (currentMove)
	{
	case moveState::NONE:
		currentMove = move_;
		return true;

	case moveState::AIRLIGHT:
	case moveState::AIRMEDIUM:
	case moveState::AIRHEAVY:
	case moveState::GROUNDLIGHT:
	case moveState::GROUNDMEDIUM:
	case moveState::GROUNDHEAVY:
		if (move_ == moveState::QCF || move_ == moveState::QCB || move_ == moveState::HCB || move_ == moveState::CHARGEDOWNUP || move_ == moveState::CHARGEBACKFORWARD)
		{
			currentMove = move_;
			return true;
		}
	default:
		currentMove = moveState::NONE;
		return false;
	}
}

bool Character::CheckRunCancel()
{
	if (currentMove != moveState::NONE && currentMove != moveState::RUN)
	{
		if (overclock >= 50.0f)
		{
			return true;
		}
		return false;
	}
	return true;
}

bool Character::checkComboState(moveState move_)
{
	// make sure move can still go through when going from idle states
	switch (currentMove)
	{
	case moveState::NONE:
	case moveState::RUN:
		resetCombo();
	case moveState::GROUNDHEAVY:
	case moveState::GROUNDMEDIUM:
	case moveState::GROUNDLIGHT:
	case moveState::AIRHEAVY:
	case moveState::AIRMEDIUM:
	case moveState::AIRLIGHT:
		return true;
		break;
	default:
		return false;
	}
	/*switch (move_)
	{
	case moveState::AIRLIGHT:
	case moveState::GROUNDLIGHT:
		if (combo["light"] > 0)
		{
			combo["light"]--;
			return true;
		}
		break;
	case moveState::AIRMEDIUM:
	case moveState::GROUNDMEDIUM:
		if (combo["medium"] > 0)
		{
			combo["medium"]--;
			return true;
		}
		break;
	case moveState::AIRHEAVY:
	case moveState::GROUNDHEAVY:
		if (combo["heavy"] > 0)
		{
			combo["heavy"]--;
			return true;
		}
		break;
	default:
		resetCombo();
		return false;
	}
	*/
}

void Character::QCF(int strength, bool simpleInput)
{
	if(!CheckMoveState(moveState::QCF)) return;

	if (nextActionable > 0.0f) return;

	if (isAirborne)
	{
		AirQCF(strength, simpleInput);
	}
	if (strength < 3)
	{
		//proj->SetTarget(nullptr);
		//proj->SetVelocity(glm::vec3(10.0f, 0.0f, 0.0f));
		//proj->SetPosition(this->GetPosition());
	}
	else
	{
		//proj->SetTarget(opponent);
		//proj->SetPosition(this->GetPosition());
		overclock -= 50.0f;
	}
}

void Character::QCB(int strength, bool simpleInput)
{
	if(!CheckMoveState(moveState::QCB)) return;

	if (nextActionable > 0.0f) return;

	if (isAirborne)
	{
		AirQCB(strength, simpleInput);
	}
}

void Character::Unique()
{
	if (nextActionable > 0.0f) return;

	
	if (isAirborne)
	{
		AirUnique();
	}
}

void Character::Light()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirLight();
	}
}

void Character::Medium()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirMedium();
	}
}

void Character::Heavy()
{
	if (nextActionable > 0.0f) return;


	if (isAirborne)
	{
		AirHeavy();
	}

}

void Character::Run(bool isRunning_)
{
	if (!CheckRunCancel()) return;;

	if (nextActionable > 0.0f) return;

	isRunning = isRunning_;
}

void Character::Move(glm::vec2 input)
{
	if (nextActionable > 0.0f) return;

}

std::vector<Sphere> Character::GetHurtBoxes() const
{
	return hurtBox->GetHurtBoxes();
}



bool Character::IsCharge()
{
	return isCharge;
}

bool Character::FacingLeft()
{
	glm::vec3 dir = position - opponent->position;
	return glm::dot(glm::normalize(dir), camera->GetRight()) < 0;
}

void Character::AirQCF(int strength, bool simpleInput)
{
	if (nextActionable > 0.0f) return;

}

void Character::AirQCB(int strength, bool simpleInput)
{
	if (nextActionable > 0.0f) return;

}

void Character::AirUnique()
{
	if (nextActionable > 0.0f) return;

}

void Character::AirLight()
{
	if (nextActionable > 0.0f) return;

}

void Character::AirMedium()
{
	if (nextActionable > 0.0f) return;

}

void Character::AirHeavy()
{
	if (nextActionable > 0.0f) return;

}

void Character::resetCombo()
{
	combo["light"] = 1;
	combo["medium"] = 1;
	combo["heavy"] = 1;
}