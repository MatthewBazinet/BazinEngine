#include "MorphTargetManager.h"
#include "Engine/Core/Log.h"

std::unique_ptr<MorphTargetManager> MorphTargetManager::morphTargetInstance = nullptr;
std::unordered_map<std::string, std::vector<Mesh*>> MorphTargetManager::morphTargets = std::unordered_map<std::string, std::vector<Mesh*>>();

MorphTargetManager::MorphTargetManager()
{
	morphTargets.reserve(40);
}

MorphTargetManager::~MorphTargetManager()
{
	OnDestroy();
}

MorphTargetManager* MorphTargetManager::GetInstance()
{
	if (morphTargetInstance.get() == nullptr)
	{
		morphTargetInstance.reset(new MorphTargetManager);
	}
	return morphTargetInstance.get();
}

void MorphTargetManager::OnDestroy()
{
		for (auto entry : morphTargets)
		{
			if (morphTargets.size() > 0)
			{
				if (entry.second.size() > 0)
				{
					for (auto m : entry.second)
					{
						delete m;
						m = nullptr;
					}
				}
				entry.second.clear();
			}
		}
		morphTargets.clear();
}


void MorphTargetManager::AddMorphTarget(std::vector<Mesh*> morph_, std::string objFilePath_)
{
	morphTargets[objFilePath_] = morph_;
}

const std::vector<Mesh*> MorphTargetManager::GetMorphTarget(const std::string& objFilePath_) const
{
	if (morphTargets.count(objFilePath_) > 0)
	{
		return morphTargets[objFilePath_];
	}
	Log::Error("MorphTarget " + objFilePath_ + " was not found. Using Default MorphTarget.", "MorphTargetManager.cpp", __LINE__);
	return std::vector<Mesh*>();
}