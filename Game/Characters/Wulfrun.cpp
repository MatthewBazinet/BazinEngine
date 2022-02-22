#include "Wulfrun.h"
#include "../../Engine/Graphics/ShaderHandler.h"

Wulfrun::Wulfrun(glm::vec3 pos_) : Character(1000.0f, 0.0f, false, false, new MorphTargetAnimatedModel("Resources/Models/Wulfrun.obj", "Resources/Materials/Wulfrun.mtl", ShaderHandler::GetInstance()->GetShader("basicShader")), pos_)
{

}

Wulfrun::~Wulfrun()
{
	Character::~Character();
}

void Wulfrun::QCF(int strength, bool simpleInput)
{
}

void Wulfrun::QCB(int strength, bool simpleInput)
{
}

void Wulfrun::Unique()
{
}

void Wulfrun::Light()
{
}

void Wulfrun::Medium()
{
}

void Wulfrun::Heavy()
{
}
