#include "Scene2.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "..//../AICharacter.h"
#include "..//Pawn.h"

Scene2::Scene2() : navgrid(GridWithWeights(100, 100))
{
}

Scene2::~Scene2()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool Scene2::OnCreate()
{
	Log::Info("Game Scene initiated", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new BattleCamera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(10.0f, 10.0f, 20.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 1.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 0.0f, 0.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");
	

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	//Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	//Model* rachidaShape = new Model("Resources/Models/tetrahedron.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	//Model* man = new Model("Resources/Models/basecharactermodel.obj", "Resources/Materials/basecharactermodel.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	//SceneGraph::GetInstance()->AddModel(appleModel);
	//SceneGraph::GetInstance()->AddModel(rachidaShape);
	//SceneGraph::GetInstance()->AddModel(man);

	SceneGraph::GetInstance()->AddGameObject(new Character(1.0f, 1.0f, false, false, diceModel, glm::vec3(0.0f, 0.0f, 0.0f)), "char1");
	SceneGraph::GetInstance()->AddGameObject(new Character(50.0f, 1.0f, false, false, diceModel, glm::vec3(0.0f, 0.0f, 0.0f)), "char2");

	//SceneGraph::GetInstance()->AddGameObject(new AICharacter(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), 1.0f, 1.0f, false, false, diceModel, glm::vec3(-10.0f, 0.0f, 0.0f)), "ai1");

	//SceneGraph::GetInstance()->AddGameObject(new Projectile(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)), "projectile");

	// Add Walls
	navgrid = GridWithWeights(100, 100);
	
	// Top Side
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(5.0f, 0.0f, 0.0f)), "wall1");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(7.0f, 0.0f, 0.0f)), "wall2");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(9.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(11.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(12.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(14.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(16.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(17.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(18.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(20.0f, 0.0f, 0.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 0.0f)), "wall3");
	navgrid.addRect(5, 0, 22, 2);
	
	// Right Wall + Gap
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 2.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 7.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 8.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 10.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 12.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(22.0f, 0.0f, 14.0f)), "wall3");
	navgrid.addRect(20, 0, 24, 4);
	navgrid.addRect(20, 5, 24, 16);
	
	// First Wall branching from the top
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(12.0f, 0.0f, 2.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(12.0f, 0.0f, 4.0f)), "wall3");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(12.0f, 0.0f, 5.0f)), "wall3");
	navgrid.addRect(10, 0, 14, 7);
	
	// Single Block
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(17.0f, 0.0f, 5.0f)), "wall3");
	navgrid.addRect(15, 3, 19, 7);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(5.0f, 0.0f, 5.0f)), "wall4");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(5.0f, 0.0f, 7.0f)), "wall6");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(5.0f, 0.0f, 9.0f)), "wall7");
	navgrid.addRect(3, 3, 7, 11);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(7.0f, 0.0f, 5.0f)), "wall5");
	navgrid.addRect(5, 3, 9, 7);
	
	// Bottom Side
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(7.0f, 0.0f, 11.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(9.0f, 0.0f, 11.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(11.0f, 0.0f, 11.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(13.0f, 0.0f, 11.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(15.0f, 0.0f, 11.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(17.0f, 0.0f, 11.0f)), "wall8");
	navgrid.addRect(0, 12, 20, 15);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(17.0f, 0.0f, 13.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(17.0f, 0.0f, 15.0f)), "wall8");
	navgrid.addRect(15, 11, 19, 17);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(19.0f, 0.0f, 15.0f)), "wall8");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(21.0f, 0.0f, 15.0f)), "wall3");
	navgrid.addRect(17, 17, 23, 18);
	
	navgrid.addRoughTerrain(20, 20, 30, 30);
	
	//SceneGraph::GetInstance()->AddGameObject(new Projectile(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)), "projectile");
	//
	//static_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("char1"));

	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(CoreEngine::GetInstance()->GetCamera());
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(CoreEngine::GetInstance()->GetCamera());

	//static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));

	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("ai1")));

	//static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->SetPlayers(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("ai1")));

	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));

	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));

	//dynamic_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("ai1"));

	//TestChar* newChar = new TestChar(2.0f);
	//newChar->runDecisionTree();

	//newChar = nullptr;
	//delete newChar;

	SceneGraph::GetInstance()->AddGameObject(new Pawn(diceModel, glm::vec3(0.0f, 0.0f, 0.0f)), "Pawn");

	SceneGraph::GetInstance()->GetGameObject("Pawn")->SetTargetNumber(0);
	
	dynamic_cast<Pawn*>(SceneGraph::GetInstance()->GetGameObject("Pawn"))->SetTarget(glm::vec3(30.0f, 0.0f, 0.0f), navgrid);

	diceModel = nullptr;
	//appleModel = nullptr;
	//rachidaShape = nullptr;
	//man = nullptr;

	return true;
}

void Scene2::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	//SceneGraph::GetInstance()->GetGameObject("projectile")->SetPosition(SceneGraph::GetInstance()->GetGameObject("char1")->GetPosition());
	//static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->Update(deltaTime_);

}

void Scene2::Render()
{

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void Scene2::HandleEvents(const SDL_Event& sdlEvent)
{
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
}

void Scene2::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
	case SDL_SCANCODE_P:
		static_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("ai1"));
		static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetProjectile(dynamic_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile")));
		break;
	case SDL_SCANCODE_U:
		dynamic_cast<Pawn*>(SceneGraph::GetInstance()->GetGameObject("Pawn"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("char1")->GetPosition(), navgrid);
		break;
	case SDL_SCANCODE_R:
		if (static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->getIsRunning()) {
			static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->Run(false);
		}
		else
		{
			static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->Run(true);
		}
		break;
	case SDL_SCANCODE_LEFT:
		static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::CROSSUP);
		break;
	case SDL_SCANCODE_RIGHT:
		static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::INFRONTFAR);
		break;
	case SDL_SCANCODE_UP:
		static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::SELF);
		break;
	case SDL_SCANCODE_DOWN:
		static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("ai1"))->SetTargetType(TargetType::INFRONTCLOSE);
		break;
	default:
		Character* char1 = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"));
		char1->NotifyOnKeyDown(key_);
		char1 = nullptr;
		break;
	}
}

void Scene2::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{
	default:
		Character* char1 = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"));
		char1->NotifyOnKeyUp(key_);
		char1 = nullptr;
		break;
	}
}
