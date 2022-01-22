
#ifndef MORPHTARGET_H
#define MORPHTARGET_H
#include <string>
#include "Engine/Rendering/3D/LoadOBJModel.h"

class MorphTarget
{
	friend class MorphTargetAnimatedModel;
public:
	MorphTarget();
	MorphTarget(const std::string& objPath_, const std::string& matPath_);
	~MorphTarget();
	void LoadModel();

protected:

	LoadOBJModel* obj;

	std::vector<Mesh*> meshes;
};

#endif

