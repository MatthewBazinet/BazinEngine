
#ifndef MORPHTARGET_H
#define MORPHTARGET_H
#include <string>
#include "Engine/Rendering/3D/LoadOBJModel.h"

class MorphTarget
{
	friend class MorphTargetAnimatedModel;
public:
	MorphTarget(const std::string& objPath_, const std::string& matPath_);
	~MorphTarget();
	void LoadModel();

protected:

	LoadOBJModel* obj;

	std::vector<Mesh*> meshes;
};

class AnimationTarget : public MorphTarget
{
	friend class MorphTargetAnimatedModel;
public:
	AnimationTarget(const std::string& objPath_, const std::string& matPath_);
	AnimationTarget(const std::string& objPath_, const std::string& matPath_, std::string target_, float animlength_);

	~AnimationTarget();

	void SetNextMorphTarget(std::string target_, float animLength_);

private:
	std::string nextTarget;
	float nextTargetAnimLength;
	
};


#endif

