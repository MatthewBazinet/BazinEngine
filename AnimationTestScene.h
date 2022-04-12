#ifndef AnimationTESTSCENE_H
#define AnimationTESTSCENE_H

#include "../Engine/Core/CoreEngine.h"

class AnimationTestScene : public Scene
{
public:
	AnimationTestScene();
	~AnimationTestScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);

	bool lineMode = false;
};

#endif // !AnimationTESTSCENE_H