#include "MorphTarget.h"

MorphTarget::MorphTarget()
{
}

MorphTarget::MorphTarget(const std::string& objPath_, const std::string& matPath_)
{
	meshes.reserve(10);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();
}

MorphTarget::~MorphTarget()
{
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
