#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include <memory>

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
	bool GetIsRunning();

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

};

#endif