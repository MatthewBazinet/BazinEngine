#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Log.h"
#include "GameInterface.h"
#include "Scene.h"

#include "..//Rendering/3D/GameObject.h"

class CoreEngine
{
public:
	//Delete the copy and move operators
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	//Aquires the instance of CoreEngine or creates one if it doesn't exist
	static CoreEngine* GetInstance();

	//Setup a Window
	bool OnCreate(std::string name_, int width_, int height_);
	
	//Calls Update and Render
	void Run();
	void Exit();
	bool GetIsRunning() const;
	int GetCurrentScene() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);

private:
	CoreEngine();
	~CoreEngine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	//A unique pointer to the only instance of the CoreEngine
	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Window* window;
	bool isRunning;
	Timer* timer;
	unsigned int fps;
	GameInterface* gameInterface;

	int currentSceneNum;

};

#endif