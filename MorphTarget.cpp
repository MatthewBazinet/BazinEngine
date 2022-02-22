#include "MorphTarget.h"


MorphTarget::MorphTarget(const std::string& objPath_, const std::string& matPath_)
{
	meshes.reserve(10);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();
}

MorphTarget::~MorphTarget()
{
	for (auto m : meshes)
	{
		delete m;
		m = nullptr;
	}
	meshes.clear();
}

void MorphTarget::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], 0));
	}
	delete obj;
	obj = nullptr;
}


AnimationTarget::AnimationTarget(const std::string& objPath_, const std::string& matPath_) : MorphTarget(objPath_, matPath_)
{
	
}

AnimationTarget::AnimationTarget(const std::string& objPath_, const std::string& matPath_, std::string target_, float animlength_) : AnimationTarget(objPath_, matPath_)
{
	SetNextMorphTarget(target_, animlength_);
}

AnimationTarget::~AnimationTarget()
{
	MorphTarget::~MorphTarget();
}

void AnimationTarget::SetNextMorphTarget(std::string target_, float animLength_)
{
	nextTarget = target_;
	nextTargetAnimLength = animLength_;
}
