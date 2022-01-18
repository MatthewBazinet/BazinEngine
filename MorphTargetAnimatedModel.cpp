#include "MorphTargetAnimatedModel.h"

MorphTargetAnimatedModel::MorphTargetAnimatedModel(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : Model(objPath_, matPath_, shaderProgram_)
{
	animationMorphTargets = std::unordered_map<std::string, MorphTarget>();
}

MorphTargetAnimatedModel::~MorphTargetAnimatedModel()
{
}

void MorphTargetAnimatedModel::AddMorphTarget(std::string name_, MorphTarget target_)
{
	animationMorphTargets[name_.c_str()] = target_;
}

void MorphTargetAnimatedModel::SetCurrentMorphTarget(std::string name_, float time_)
{
	previousMorphTarget = currentMorphTarget;
	currentMorphTarget = name_;
	animationTime = timeToMorphComplete = time_;
}

void MorphTargetAnimatedModel::Update(const float deltaTime_)
{
	if (timeToMorphComplete >= 0.0f)
	{
		timeToMorphComplete -= deltaTime_;
		if (timeToMorphComplete < 0.0f)
		{
			timeToMorphComplete = 0.0f;
		}
		for (int i = 0; i < meshes.size(); i++)
		{
			for (int j = 0; j < meshes[i]->subMesh.vertexList.size(); j++)
			{
				Vertex test = meshes[i]->subMesh.vertexList[j];
				meshes[i]->subMesh.vertexList[j] = SubMesh::Lerp(
					animationMorphTargets[previousMorphTarget].meshes[i]->subMesh.vertexList[j], animationMorphTargets[currentMorphTarget].meshes[i]->subMesh.vertexList[j],
					(animationTime - timeToMorphComplete) / animationTime);
				Vertex test2 = meshes[i]->subMesh.vertexList[j];
				int z = 2;
			}
		}
	}
}
/*
meshes[i]->subMesh.vertexList = SubMesh::Lerp(
	animationMorphTargets[previousMorphTarget].meshes[i]->subMesh.vertexList, animationMorphTargets[currentMorphTarget].meshes[i]->subMesh.vertexList,
	(animationTime - timeToMorphComplete) / animationTime);
	*/