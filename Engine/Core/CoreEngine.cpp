#include "CoreEngine.h"
#include "../../Character.h"
std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() :window(nullptr), isRunning(false), fps(60), timer(nullptr), gameInterface(nullptr), currentSceneNum(0),userInterface(nullptr)
{
}

CoreEngine::~CoreEngine()
{
}

CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Log::OnCreate();
	window = new Window();
	userInterface = new UserInterface();

	if (!window->OnCreate(name_, width_, height_)) {
		Log::FatalError("Window failed to initialize", "CoreEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}
	Log::Info("Window Created Succesfully", "CoreEngine.cpp", __LINE__);

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);
	KeyboardEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shader/ColourVertexShader.glsl", "Engine/Shader/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shader/VertexShader.glsl", "Engine/Shader/FragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("particleShader", "Engine/Shader/ParticleVertexShader.glsl", "Engine/Shader/ParticleFragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Log::FatalError("Game failed tp initialize", "CoreEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}
	if (userInterface) {
		if (!userInterface->OnCreate()) {
			Log::FatalError("UserInterface failed tp initialize", "CoreEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}

	}
	
	Log::Info("Game Created Succesfully", "CoreEngine.cpp", __LINE__);
	timer = new Timer();
	timer->Start();
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning)
	{
		timer->UpdateFrameTicks();
		EventListener::Update();
		Update(timer->GetDeltaTime());
		Render();
		SDL_Delay(timer->GetSleepTime(fps));
	}
	//if (!isRunning)
	//{
	OnDestroy();
	//}
}

void CoreEngine::Exit()
{
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

int CoreEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float CoreEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float CoreEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

SDL_Window* CoreEngine::GetWindow() const
{
	return window->GetWindow();;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_)
{
}

void CoreEngine::NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::ivec2 mouse_)
{
	if (camera)
	{
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera)
	{
		camera->ProcessMouseZoom(y_);
	}
}

void CoreEngine::NotifyOfKeyDown(SDL_Scancode key_)
{
	switch (key_)
	{
		//Controls for Camera: WASD Move, SPACE UP, LEFT CTRL Down, Q/E Yaw, UP/DOWN Pitch, LEFT/RIGHT Roll

/*
	case SDL_SCANCODE_SPACE:
		GetCamera()->SetPosition(GetCamera()->GetPosition() + glm::vec3(0.0f, 0.01f, 0.0f));
		break;
	case SDL_SCANCODE_LCTRL:
		GetCamera()->SetPosition(GetCamera()->GetPosition() - glm::vec3(0.0f, 0.01f, 0.0f));
		break;
	case SDL_SCANCODE_Q:
		GetCamera()->SetRotation(GetCamera()->GetRotation() - glm::vec3(0.5f, 0.0f, 0.0f));
		break;
	case SDL_SCANCODE_E:
		GetCamera()->SetRotation(GetCamera()->GetRotation() + glm::vec3(0.5f, 0.0f, 0.0f));
		break;
	case SDL_SCANCODE_RIGHT:
		GetCamera()->SetRotation(GetCamera()->GetRotation() + glm::vec3(0.0f, 0.0f, 0.1f));
		break;
	case SDL_SCANCODE_LEFT:
		GetCamera()->SetRotation(GetCamera()->GetRotation() - glm::vec3(0.0f, 0.0f, 0.1f));
		break;
	case SDL_SCANCODE_UP:
		GetCamera()->SetRotation(GetCamera()->GetRotation() + glm::vec3(0.0f, 0.1f, 0.0f));
		break;
	case SDL_SCANCODE_DOWN:
		GetCamera()->SetRotation(GetCamera()->GetRotation() - glm::vec3(0.0f, 0.1f, 0.0f));
		break;
		*/
	case SDL_SCANCODE_1:
		CoreEngine::GetInstance()->SetCurrentScene(1);
		break;
	case SDL_SCANCODE_2:
		CoreEngine::GetInstance()->SetCurrentScene(2);
		break;
	case SDL_SCANCODE_3:
		CoreEngine::GetInstance()->SetCurrentScene(3);
	default:
		gameInterface->NotifyOfKeyDown(key_);
		break;
	}
}

void CoreEngine::NotifyOfKeyRelease(SDL_Scancode key_)
{
	switch (key_)
	{
		//Controls for Camera: WASD Move, SPACE UP, LEFT CTRL Down, Q/E Yaw, UP/DOWN Pitch, LEFT/RIGHT Roll
		
	default:
		gameInterface->NotifyOfKeyUp(key_);
		break;
	}
}

void CoreEngine::Update(const float deltaTime_)
{
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}
	if (userInterface) {
		userInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render()
{
	//Paints the backround colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface)
	{
		gameInterface->Render();
	}
	if (userInterface) {
		userInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}


void CoreEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	userInterface->DestroyUI();

	delete userInterface;
	userInterface = nullptr;
	delete gameInterface;
	gameInterface = nullptr;
	delete camera;
	camera = nullptr;
	delete timer;
	timer = nullptr;
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
