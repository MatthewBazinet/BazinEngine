#include "GameScene.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "..//../AICharacter.h"
#include "../ParticleSystem.h"
#include "../Component.h"
#include "../XMLDecisionTreeReader.h"
#include "../UserInterface.h"
#include "../Game/Characters/Hoshi.h"
#include "../Characters/AlexisBruce.h"
#include "../Characters/Wulfrun.h"
#include "../Characters/Eldric.h";
#include "../Engine/Math/EnvironmentalCollisionManager.h"
#include "../MatchSettings.h"

GameScene::GameScene()
{
	scale = 1.5f;
}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	Log::Info("Game Scene initiated", "GameScene.cpp", __LINE__);
	
	CoreEngine::GetInstance()->SetCamera(new BattleCamera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 5.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 1.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 1.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);
	EnvironmentalCollisionManager::GetInstance()->OnCreate(100.0f);

	LoadCharacters();
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

void GameScene::LoadCharacters()
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

	switch (MatchSettings::GetInstance()->GetPlayer2Character()) {
	case(Player2Characters::Hoshi):
		SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(10.0f, 0.0f, 0.0f), Sphere), "char2");
		//dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetModels(Sphere);
		break;
	case(Player2Characters::Alexis):
		SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(glm::vec3(10.0f, 0.0f, 0.0f)), "char2");
		dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetModels(Rock, Sphere);
		break;
	case(Player2Characters::Eldric):
		SceneGraph::GetInstance()->AddGameObject(new Eldric(glm::vec3(10.0f, 0.0f, 0.0f), Sphere), "char2");
		break;
	case(Player2Characters::Wulfrun):
		SceneGraph::GetInstance()->AddGameObject(new Wulfrun(glm::vec3(10.0f, 0.0f, 0.0f)), "char2");
		break;
	default:
		break;
	}

	inputManager.SetPlayer2(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	binds.down = SDL_SCANCODE_DOWN;
	binds.up = SDL_SCANCODE_UP;
	binds.left = SDL_SCANCODE_LEFT;
	binds.right = SDL_SCANCODE_RIGHT;
	binds.run = SDL_SCANCODE_SPACE;
	binds.light = SDL_SCANCODE_Z;
	binds.medium = SDL_SCANCODE_X;
	binds.heavy = SDL_SCANCODE_C;
	binds.unique = SDL_SCANCODE_V;
	binds.shortcutForward = SDL_SCANCODE_RSHIFT;
	binds.shortcutBackward = SDL_SCANCODE_RCTRL;
	binds.super = SDL_SCANCODE_B;

	inputManager.SetPlayer2Keybinds(binds);

	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->SetPlayers(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));

	SceneGraph::GetInstance()->AddModel(Sphere);
	SceneGraph::GetInstance()->AddModel(Rock);

	Rock = nullptr;
	Sphere = nullptr;
}

void GameScene::ResetRound()
{
	UserInterface::GetInstance()->SetTime(360);

	SceneGraph::GetInstance()->GetGameObject("char1")->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("char2")->SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));

	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetHealth(1000.0f);
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetHealth(1000.0f);

	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOverclock(0.0f);
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOverclock(0.0f);
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	//ptr->Update(deltaTime_);
	//std::cout << dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetHealth() << std::endl;
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
			CoreEngine::GetInstance()->SetCurrentScene(0);
		}
		else
		{
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

void GameScene::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//ptr->Render(CoreEngine::GetInstance()->GetCamera());
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
	
}

void GameScene::HandleEvents(const SDL_Event& sdlEvent)
{
	/*
	if (sdlEvent.type == SDL_KEYDOWN) 
	{
		switch (sdlEvent.key.keysym.scancode) 
		{
		//Controls for Camera: WASD Move, SPACE UP, LEFT CTRL Down, Q/E Yaw, UP/DOWN Pitch, LEFT/RIGHT Roll
		case SDL_SCANCODE_W:

			CoreEngine::GetInstance()->GetCamera()->SetPosition(CoreEngine::GetInstance()->GetCamera()->GetPosition() - glm::vec3(0.0f, 0.0f, 0.01f));
			break;
		case SDL_SCANCODE_A:
			CoreEngine::GetInstance()->GetCamera()->SetPosition(CoreEngine::GetInstance()->GetCamera()->GetPosition() - glm::vec3(0.01f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_S:
			CoreEngine::GetInstance()->GetCamera()->SetPosition(CoreEngine::GetInstance()->GetCamera()->GetPosition() + glm::vec3(0.0f, 0.0f, 0.01f));
			break;
		case SDL_SCANCODE_D:
			CoreEngine::GetInstance()->GetCamera()->SetPosition(CoreEngine::GetInstance()->GetCamera()->GetPosition() + glm::vec3(0.01f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_SPACE:
			CoreEngine::GetInstance()->GetCamera()->SetPosition(CoreEngine::GetInstance()->GetCamera()->GetPosition() + glm::vec3(0.0f, 0.01f, 0.0f));
			break;
		case SDL_SCANCODE_LCTRL:
			CoreEngine::GetInstance()->GetCamera()->SetPosition(CoreEngine::GetInstance()->GetCamera()->GetPosition() - glm::vec3(0.0f, 0.01f, 0.0f));
			break;
		case SDL_SCANCODE_Q:
			CoreEngine::GetInstance()->GetCamera()->SetRotation(CoreEngine::GetInstance()->GetCamera()->GetRotation() - glm::vec3(0.5f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_E:
			CoreEngine::GetInstance()->GetCamera()->SetRotation(CoreEngine::GetInstance()->GetCamera()->GetRotation() + glm::vec3(0.5f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_RIGHT:
			CoreEngine::GetInstance()->GetCamera()->SetRotation(CoreEngine::GetInstance()->GetCamera()->GetRotation() + glm::vec3(0.0f, 0.0f, 0.1f));
			break;
		case SDL_SCANCODE_LEFT:
			CoreEngine::GetInstance()->GetCamera()->SetRotation(CoreEngine::GetInstance()->GetCamera()->GetRotation() - glm::vec3(0.0f, 0.0f, 0.1f));
			break;
		case SDL_SCANCODE_UP:
			CoreEngine::GetInstance()->GetCamera()->SetRotation(CoreEngine::GetInstance()->GetCamera()->GetRotation() + glm::vec3(0.0f, 0.1f, 0.0f));
			break;
		case SDL_SCANCODE_DOWN:
			CoreEngine::GetInstance()->GetCamera()->SetRotation(CoreEngine::GetInstance()->GetCamera()->GetRotation() - glm::vec3(0.0f, 0.1f, 0.0f));
			break;
		default:
			break;
		}
	}
	*/
}

void GameScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
	//case SDL_SCANCODE_P:
		//static_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("ai1"));
		//static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetProjectile(dynamic_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile")));
		//break;
	//case SDL_SCANCODE_R:
		//if (static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->getIsRunning()) {
		//	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->Run(false);
		//}
		//else
		//{
		//	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->Run(true);
		//}
		break;
	default:
		inputManager.OnKeyDown(key_);
		break;
	}
}

void GameScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{
	//case SDL_SCANCODE_LEFT:
	//	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::CROSSUP);
	//	break;
	//case SDL_SCANCODE_RIGHT:
	//	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::INFRONTFAR);
	//	break;
	//case SDL_SCANCODE_UP:
	//	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::SELF);
	//	break;
	//case SDL_SCANCODE_DOWN:
	//	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::INFRONTCLOSE);
	//	break;
	default:
		inputManager.OnKeyUp(key_);
		break;
	}
}
