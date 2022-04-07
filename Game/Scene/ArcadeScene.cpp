#include "ArcadeScene.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "..//../AICharacter.h"
#include "../ParticleSystem.h"
#include "../Component.h"
#include "../XMLDecisionTreeReader.h"
#include "../UserInterface.h"
#include "../Game/Characters/Hoshi.h"
#include "../Characters/AlexisBruce.h"
#include "../Characters/Eldric.h"
#include "../Characters/Wulfrun.h"
#include "../Engine/Math/EnvironmentalCollisionManager.h"
#include "../MatchSettings.h"

ArcadeScene::ArcadeScene()
{
	scale = 1.5f;
}

ArcadeScene::~ArcadeScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool ArcadeScene::OnCreate()
{
	Log::Info("Game Scene initiated", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new BattleCamera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 5.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 1.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 1.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);
	EnvironmentalCollisionManager::GetInstance()->OnCreate(100.0f);

	LoadPlayer1Character();
	LoadPlayer2Character();
	SetPlayerSettings();

	Model* floor = new Model("Resources/Models/Floor.obj", "Resources/Materials/Floor.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(floor, glm::vec3(5.0f, -0.25f, 0.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f)), "floor");
	SceneGraph::GetInstance()->AddModel(floor);

	XMLDecisionTreeReader read;
	read.ReadFile("Tree.xml");

	glm::vec3 s(1.0f);
	glm::vec3 e(6.0f);

	leftPlane = glm::vec4(-1.0f, 0.0f, 0.0f, 15.0f);
	rightPlane = glm::vec4(1.0f, 0.0f, 0.0f, 15.0f);
	northPlane = glm::vec4(0.0f, 0.0f, 1.0f, 15.0f);
	southPlane = glm::vec4(0.0f, 0.0f, -1.0f, 15.0f);
	planes.push_back(leftPlane);
	planes.push_back(rightPlane);
	planes.push_back(northPlane);
	planes.push_back(southPlane);

	return true;
}

void ArcadeScene::LoadPlayer1Character()
{
	inputManager = InputManager();
	Keybinds binds;

	Model* Sphere = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Rock = new Model("Resources/Models/Rock.obj", "Resources/Materials/Rock.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	switch (MatchSettings::GetInstance()->GetPlayer1Character()) {
	case(Player1Characters::Hoshi):
		SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(0.0f, 0.0f, 0.0f), Sphere), "char1");
		break;
	case(Player1Characters::Alexis):
		SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(glm::vec3(0.0f, 0.0f, 0.0f)), "char1");
		dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(Rock, Sphere);
		break;
	case(Player1Characters::Eldric):
		SceneGraph::GetInstance()->AddGameObject(new Eldric(glm::vec3(0.0f, 0.0f, 0.0f), Sphere), "char1");
		break;
	case(Player1Characters::Wulfrun):
		SceneGraph::GetInstance()->AddGameObject(new Wulfrun(glm::vec3(0.0f, 0.0f, 0.0f)), "char1");
		break;
	default:
		break;
	}

	inputManager.SetPlayer1(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	binds.down = SDL_SCANCODE_S;
	binds.up = SDL_SCANCODE_W;
	binds.left = SDL_SCANCODE_A;
	binds.right = SDL_SCANCODE_D;
	binds.run = SDL_SCANCODE_LSHIFT;
	binds.light = SDL_SCANCODE_U;
	binds.medium = SDL_SCANCODE_I;
	binds.heavy = SDL_SCANCODE_O;
	binds.unique = SDL_SCANCODE_P;
	binds.shortcutForward = SDL_SCANCODE_E;
	binds.shortcutBackward = SDL_SCANCODE_Q;
	binds.super = SDL_SCANCODE_Y;

	inputManager.SetPlayer1Keybinds(binds);
}

void ArcadeScene::LoadPlayer2Character()
{
	Model* Sphere = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Rock = new Model("Resources/Models/Rock.obj", "Resources/Materials/Rock.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	switch (MatchSettings::GetInstance()->GetPlayer2Character()) {
	case(Player2Characters::Hoshi):
		SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(0.0f, 0.0f, 0.0f), Sphere), "char2");
		break;
	case(Player2Characters::Alexis):
		SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(glm::vec3(0.0f, 0.0f, 0.0f)), "char2");
		dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetModels(Rock, Sphere);
		break;
	case(Player2Characters::Eldric):
		SceneGraph::GetInstance()->AddGameObject(new Eldric(glm::vec3(0.0f, 0.0f, 0.0f), Sphere), "char2");
		break;
	case(Player2Characters::Wulfrun):
		SceneGraph::GetInstance()->AddGameObject(new Wulfrun(glm::vec3(0.0f, 0.0f, 0.0f)), "char2");
		break;
	default:
		break;
	}

	SceneGraph::GetInstance()->AddModel(Sphere);
	SceneGraph::GetInstance()->AddModel(Rock);

	Rock = nullptr;
	Sphere = nullptr;
}

void ArcadeScene::SetPlayerSettings()
{
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->SetPlayers(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));
}

void ArcadeScene::ResetRound()
{
	UserInterface::GetInstance()->SetTime(300);

	SceneGraph::GetInstance()->GetGameObject("char1")->SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("char2")->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetHealth(1000.0f);
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetHealth(1000.0f);

	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOverclock(0.0f);
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOverclock(0.0f);
}

void ArcadeScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->Update(deltaTime_);
	inputManager.Update(deltaTime_);
	EnvironmentalCollisionManager::GetInstance()->Update(SceneGraph::GetInstance()->GetGameObject("char1"), planes);
	EnvironmentalCollisionManager::GetInstance()->Update(SceneGraph::GetInstance()->GetGameObject("char2"), planes);

	if (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->GetHealth() <= 0.0f)
	{
		std::cout << "player 1 win" << std::endl;
		MatchSettings::GetInstance()->SetP1Points(MatchSettings::GetInstance()->GetP1Points() + 1);
		if (MatchSettings::GetInstance()->GetP1Points() == 2)
		{
			if (static_cast<int>(MatchSettings::GetInstance()->GetPlayer2Character()) + 1 != NULL)
			{
				SceneGraph::GetInstance()->RemoveModel(SceneGraph::GetInstance()->GetGameObject("char2")->GetModel());
				SceneGraph::GetInstance()->RemoveGameObject("char2");
				MatchSettings::GetInstance()->NextMatch();
				LoadPlayer2Character();
				SetPlayerSettings();
				ResetRound();
			}
			else
			{
				CoreEngine::GetInstance()->SetCurrentScene(0);
			}
		}
		else
		{
			std::cout << "round 2" << std::endl;
			ResetRound();
		}
	}
	else if (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetHealth() <= 0.0f)
	{
		std::cout << "player 2 win" << std::endl;
		MatchSettings::GetInstance()->SetP2Points(MatchSettings::GetInstance()->GetP2Points() + 1);
		if (MatchSettings::GetInstance()->GetP2Points() == 2)
		{
			CoreEngine::GetInstance()->SetCurrentScene(0);
		}
		else
		{
			ResetRound();
		}
	}
	else if (UserInterface::GetInstance()->GetTime() <= 0)
	{
		if (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetHealth() > static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->GetHealth())
		{
			std::cout << "player 1 win" << std::endl;
			MatchSettings::GetInstance()->SetP1Points(MatchSettings::GetInstance()->GetP1Points() + 1);
			if (MatchSettings::GetInstance()->GetP1Points() == 2)
			{
				CoreEngine::GetInstance()->SetCurrentScene(0);
			}
			else
			{
				ResetRound();
			}
		}
		else if (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetHealth() < static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->GetHealth())
		{
			std::cout << "player 2 win" << std::endl;
			MatchSettings::GetInstance()->SetP2Points(MatchSettings::GetInstance()->GetP2Points() + 1);
			if (MatchSettings::GetInstance()->GetP2Points() == 2)
			{
				CoreEngine::GetInstance()->SetCurrentScene(0);
			}
			else
			{
				ResetRound();
			}
		}
		else
		{
			std::cout << "tied" << std::endl;
			ResetRound();
		}
	}
}

void ArcadeScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void ArcadeScene::HandleEvents(const SDL_Event& sdlEvent) {}

void ArcadeScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
		break;
	default:
		inputManager.OnKeyDown(key_);
		break;
	}
}

void ArcadeScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{
	default:
		inputManager.OnKeyUp(key_);
		break;
	}
}
