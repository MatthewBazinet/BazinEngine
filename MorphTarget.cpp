#include "MorphTarget.h"
#include "MorphTargetManager.h"


MorphTarget::MorphTarget(const std::string& objPath_)
{
	objPath = objPath_;
	if (MorphTargetManager::GetInstance()->GetMorphTarget(objPath).size() > 0)
	{
	}
	else
	{
		obj = new LoadOBJModel();
		obj->LoadModelMaterialLess(objPath_);
		LoadModel();
	}
	nextTargetAnimLength = 0.0f;
	nextTarget = "";
}

MorphTarget::MorphTarget(const std::string& objPath_, std::string target_, float animlength_) : MorphTarget(objPath_)
{
	SetNextMorphTarget(target_, animlength_);
}

MorphTarget::~MorphTarget()
{

}

void MorphTarget::LoadModel()
{
	std::vector<Mesh*> meshes;
	for (int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], 0));
	}
	MorphTargetManager::GetInstance()->AddMorphTarget(meshes, objPath);
	delete obj;
	obj = nullptr;
}

void MorphTarget::SetNextMorphTarget(std::string target_, float animLength_)
{
	nextTarget = target_;
	nextTargetAnimLength = animLength_;
}

std::vector<Mesh*> MorphTarget::GetMorphTarget()
{
	return MorphTargetManager::GetInstance()->GetMorphTarget(objPath);
}
