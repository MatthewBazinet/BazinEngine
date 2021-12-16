#include "OnlineGameScene.h"


OnlineGameScene::OnlineGameScene()
{

}

OnlineGameScene::~OnlineGameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool OnlineGameScene::OnCreate()
{
	Log::Info("Game Scene initiated", "OnlineGameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new BattleCamera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 1.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 0.0f, 0.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);
	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	Model* rachidaShape = new Model("Resources/Models/tetrahedron.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	Model* man = new Model("Resources/Models/basecharactermodel.obj", "Resources/Materials/basecharactermodel.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);
	SceneGraph::GetInstance()->AddModel(rachidaShape);
	SceneGraph::GetInstance()->AddModel(man);



	SceneGraph::GetInstance()->AddGameObject(new Character(1.0f, 1.0f, false, false, diceModel, glm::vec3(1.0f, 0.0f, 0.0f)), "char1");


	SceneGraph::GetInstance()->AddGameObject(new Character(1.0f, 1.0f, false, false, diceModel, glm::vec3(10.0f, 0.0f, 0.0f)), "char2");


	


	static_cast<AICharacter*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));

	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));

	static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->SetPlayers(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));

	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));

	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));


	diceModel = nullptr;
	appleModel = nullptr;
	rachidaShape = nullptr;
	man = nullptr;

	return true;
}

void OnlineGameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);

	static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->Update(deltaTime_);
}

void OnlineGameScene::Render()
{

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());

}

void OnlineGameScene::HandleEvents(const SDL_Event& sdlEvent)
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

void OnlineGameScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{

	default:
		const char* characterName;
		if (NetworkingBase::isServer)
		{
			characterName = "char1";
		}
		else
		{
			characterName = "char2";
		}
		Character* character = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(characterName));
		character->NotifyOnKeyDown(key_);
		character = nullptr;
		break;
	}
}

void OnlineGameScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{
	default:
		const char* characterName;
		if (NetworkingBase::isServer)
		{
			characterName = "char1";
		}
		else
		{
			characterName = "char2";
		}
		Character* character = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(characterName));
		character->NotifyOnKeyUp(key_);
		character = nullptr;
		break;
	}
}

void OnlineGameScene::NetworkGameplayUpdate(NetworkingGameplayPacket packet)
{
}
