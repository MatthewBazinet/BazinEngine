#ifndef USERINTERFACE_H
#define USERINTERFACE_H


#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "Engine/Core/CoreEngine.h"
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	void CreateUI();
private:


};

#endif // !USERINTERFACE_H