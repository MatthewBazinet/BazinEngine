#ifndef MORPHTARGETMANAGER
#define MORPHTARGETMANAGER
#include "MorphTarget.h"
#include <unordered_map>

class MorphTargetManager
{
	public:
		MorphTargetManager(const MorphTargetManager&) = delete;
		MorphTargetManager(MorphTargetManager&&) = delete;
		MorphTargetManager& operator=(const MorphTargetManager&) = delete;
		MorphTargetManager& operator=(MorphTargetManager&&) = delete;
		static MorphTargetManager* GetInstance();
		void OnDestroy();

		void AddMorphTarget(std::vector<Mesh*> morph_, std::string objFilePath_);
		const std::vector<Mesh*> GetMorphTarget(const std::string& objFilePath_) const;

	private:
		MorphTargetManager();
		~MorphTargetManager();
		static std::unique_ptr<MorphTargetManager> morphTargetInstance;
		friend std::default_delete<MorphTargetManager>;
		static std::unordered_map<std::string, std::vector<Mesh*>> morphTargets;
};

#endif // !MORPHTARGETMANAGER
