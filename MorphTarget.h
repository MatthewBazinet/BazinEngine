
#ifndef MORPHTARGET_H
#define MORPHTARGET_H
#include <string>
#include "Engine/Rendering/3D/LoadOBJModel.h"

class MorphTarget
{
	friend class MorphTargetAnimatedModel;
	friend class MorphTargetManager;
public:
	MorphTarget(const std::string& objPath_);
	MorphTarget(const std::string& objPath_, std::string target_, float animlength_);
	~MorphTarget();
	void LoadModel();
	void SetNextMorphTarget(std::string target_, float animLength_);
	std::vector<Mesh*> GetMorphTarget();


protected:

	LoadOBJModel* obj;

	std::string objPath;

	std::string nextTarget;
	float nextTargetAnimLength;
};


#endif

