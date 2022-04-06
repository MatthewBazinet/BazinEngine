#include "MorphTargetAnimatedModel.h"
#include "MorphTargetManager.h"

MorphTargetAnimatedModel::MorphTargetAnimatedModel(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : Model(objPath_, matPath_, shaderProgram_)
{
	animationMorphTargets = std::unordered_map<std::string, MorphTarget*>();
	prevVertexLists = std::vector<std::vector<Vertex>>();
	for (int i = 0; i < meshes.size(); i++)
	{
		prevVertexLists.push_back(meshes[i]->GetVertices());
	}
}

MorphTargetAnimatedModel::~MorphTargetAnimatedModel()
{
	for (auto m : animationMorphTargets)
	{
		delete m.second;
		m.second = nullptr;
	}
}

void MorphTargetAnimatedModel::AddMorphTarget(std::string name_, MorphTarget* target_)
{
	animationMorphTargets[name_.c_str()] = target_;
}

void MorphTargetAnimatedModel::SetCurrentMorphTarget(std::string name_, float time_)
{
	previousMorphTarget = currentMorphTarget;
	currentMorphTarget = name_;
	animationTime = timeToMorphComplete = time_;
	for (int i = 0; i < meshes.size(); i++)
	{
		prevVertexLists[i] = meshes[i]->GetVertices();
	}
}

void MorphTargetAnimatedModel::Update(const float deltaTime_)
{
	if (timeToMorphComplete >= 0.0f)
	{
		timeToMorphComplete -= deltaTime_;
		if (timeToMorphComplete < 0.0f)
		{
			timeToMorphComplete = 0.0f;
			if (animationMorphTargets[currentMorphTarget]->nextTargetAnimLength > 0.0f)
			{
				SetCurrentMorphTarget(animationMorphTargets[currentMorphTarget]->nextTarget, animationMorphTargets[currentMorphTarget]->nextTargetAnimLength);
			}
		}
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->subMesh.vertexList = SubMesh::Lerp(
				prevVertexLists[i], animationMorphTargets[currentMorphTarget]->GetMorphTarget()[i]->subMesh.vertexList,
				(animationTime - timeToMorphComplete) / animationTime);
		}
	}
}
/*
meshes[i]->subMesh.vertexList = SubMesh::Lerp(
	animationMorphTargets[previousMorphTarget].meshes[i]->subMesh.vertexList, animationMorphTargets[currentMorphTarget].meshes[i]->subMesh.vertexList,
	(animationTime - timeToMorphComplete) / animationTime);
	*/