#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1);
	if (!CoreEngine::GetInstance()->OnCreate("BazinEngine", 800, 600))
	{
		Log::FatalError("Engine failed to initialize","Main.cpp",__LINE__);
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
}