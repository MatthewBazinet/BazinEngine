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
	void CreateUI();
	void DestroyUI();

	bool OnCreate();
	void Update(const float deltaTime_);
	void Render();

private:


};

#endif // !USERINTERFACE_H