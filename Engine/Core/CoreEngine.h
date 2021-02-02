#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include <memory>

class CoreEngine
{
public:

	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	static CoreEngine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();

private:
	CoreEngine();
	~CoreEngine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Window* window;
	bool isRunning;

};

#endif