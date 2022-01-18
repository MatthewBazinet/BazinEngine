#ifndef MORPHTARGETANIMATEDMODEL_H
#define MORPHTARGETANIMATEDMODEL_H
#include "Engine/Rendering/3D/Model.h"
#include "MorphTarget.h"
#include <unordered_map>

class MorphTargetAnimatedModel : public Model
{
public:
	MorphTargetAnimatedModel(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~MorphTargetAnimatedModel();
	void AddMorphTarget(std::string name_, MorphTarget target_);
	void SetCurrentMorphTarget(std::string name_, float time_);
	void Update(const float deltaTime_);

private:
	std::unordered_map<std::string, MorphTarget> animationMorphTargets;
	std::string currentMorphTarget;
	std::string previousMorphTarget;
	float timeToMorphComplete;
	float animationTime;

};
#endif

