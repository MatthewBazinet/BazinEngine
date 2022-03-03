
#ifndef MORPHTARGET_H
#define MORPHTARGET_H
#include <string>
#include "Engine/Rendering/3D/LoadOBJModel.h"

class MorphTarget
{
	friend class MorphTargetAnimatedModel;
public:
	MorphTarget(const std::string& objPath_);
	MorphTarget(const std::string& objPath_, std::string target_, float animlength_);
	~MorphTarget();
	void LoadModel();
	void SetNextMorphTarget(std::string target_, float animLength_);


protected:

	LoadOBJModel* obj;

	std::vector<Mesh*> meshes;

	std::string nextTarget;
	float nextTargetAnimLength;
};


#endif

