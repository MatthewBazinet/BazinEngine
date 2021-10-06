#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual bool OnCreate() = 0;
	virtual void Update(const float delataTime_) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& sdlEvent) = 0;
	virtual void NotifyOfKeyDown(const SDL_Scancode key_) = 0;
	virtual void NotifyOfKeyUp(const SDL_Scancode key_) = 0;
};
#endif
