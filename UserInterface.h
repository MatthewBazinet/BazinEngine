#ifndef USERINTERFACE_H
#define USERINTERFACE_H


#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "Engine/Core/CoreEngine.h"
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	void CreateUI(float health = 100.0f);
	void DestroyUI();

	bool OnCreate();
	void Update(const float deltaTime_);
	void Render();
	void StartTimer();

private:

	ImGuiBackendFlags flags;
	float progress;
	float damage;
	int time = 60;
};

#endif // !USERINTERFACE_H