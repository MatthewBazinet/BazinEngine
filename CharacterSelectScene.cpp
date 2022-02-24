#include "CharacterSelectScene.h"
#include "Game/Character.h"
#include "Game/Characters/AlexisBruce.h"
#include "Game/Characters/Hoshi.h"
#include "Projectile.h"
CharacterSelectScene::CharacterSelectScene()
{
}

CharacterSelectScene::~CharacterSelectScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool CharacterSelectScene::OnCreate()
{
	Log::Info("Character Select Scene initiated", "CharacterSelectScene.cpp", __LINE__);
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-5.0f, 12.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");

	Model* Alexis = new Model("Resources/Models/AlexisBruce.obj", "Resources/Materials/AlexisBruce.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Hoshis = new Model("Resources/Models/Hoshi.obj", "Resources/Materials/Hoshi.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Rock.obj", "Resources/Materials/Rock.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Dice = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(Alexis);
	SceneGraph::GetInstance()->AddModel(Hoshis);
	SceneGraph::GetInstance()->AddModel(appleModel);
	SceneGraph::GetInstance()->AddModel(Dice);
	
	/*SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(1.0f, 1.0f, false, false, Alexis, glm::vec3(-8.0f, 0.0f, 0.0f)), "char1");
	dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(appleModel, Dice);
	SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(1.0f, 1.0f, false, false, Alexis, glm::vec3(5.0f, 0.0f, 0.0f)), "char2");*/

	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(-8.0f, 0.0f, 0.0f)), "char1");
	dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(appleModel, Dice);
	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(5.0f, 0.0f, 0.0f)), "char2");

	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));

	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(CoreEngine::GetInstance()->GetCamera());
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(CoreEngine::GetInstance()->GetCamera());

	appleModel = nullptr;
	Alexis = nullptr;
	Dice = nullptr;
	Hoshis = nullptr;
	return true;
}

void CharacterSelectScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void CharacterSelectScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void CharacterSelectScene::HandleEvents(const SDL_Event& sdlEvent)
{

}

void CharacterSelectScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
	default:
		Character* char1 = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"));
		char1->NotifyOnKeyDown(key_);
		char1 = nullptr;
		break;
	}
}

void CharacterSelectScene::NotifyOfKeyUp(const SDL_Scancode key_)
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
