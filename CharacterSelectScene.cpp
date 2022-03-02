#include "CharacterSelectScene.h"
#include "Game/Character.h"
#include "Game/Characters/AlexisBruce.h"
#include "Game/Characters/Hoshi.h"
#include "Game/Characters/Wulfrun.h"
#include "Projectile.h"

CharacterSelectScene::CharacterSelectScene()
{
	count = 0;
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
	Model* Rock = new Model("Resources/Models/Rock.obj", "Resources/Materials/Rock.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Sphere = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(Alexis);
	SceneGraph::GetInstance()->AddModel(Hoshis);
	SceneGraph::GetInstance()->AddModel(Rock);
	SceneGraph::GetInstance()->AddModel(Sphere);

	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(100.0f, 0.0f, 0.0f)), "char1");
	dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(Rock, Sphere);
	SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(glm::vec3(1000.0f, 0.0f, 0.0f)), "char2");

	//dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetModels(Rock, Sphere);

	//SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(-8.0f, 0.0f, 0.0f)), "char1");
	//dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(appleModel, Dice);
	//SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(5.0f, 0.0f, 0.0f)), "char2");
	/*SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(1.0f, 1.0f, false, false, Alexis, glm::vec3(-8.0f, 0.0f, 0.0f)), "char1");
	dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(appleModel, Dice);
	SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(1.0f, 1.0f, false, false, Alexis, glm::vec3(5.0f, 0.0f, 0.0f)), "char2");*/
	
	//SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(5.0f, 0.0f, 0.0f)), "char2");

	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(CoreEngine::GetInstance()->GetCamera());
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(CoreEngine::GetInstance()->GetCamera());

	AddCharacter("Hoshi", dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	AddCharacter("Alexis", dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2")));

	Rock = nullptr;
	Alexis = nullptr;
	Sphere = nullptr;
	Hoshis = nullptr;
	return true;
}

void CharacterSelectScene::Update(const float deltaTime_)
{
	CharacterSelection();
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
	case(SDL_SCANCODE_A):
		count++;
		if (count > names.size() -1) {
			count = 0;
		}
		selectedCharacter = names[count];
		break;
	case(SDL_SCANCODE_D):
		count--;
		if (count < 0) {
			count = names.size() -1;
		}
		selectedCharacter = names[count];
		break;
	default:
		//AlexisBruce* c1 = dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2"));
		//c1->NotifyOnKeyDown(key_);
		//c1 = nullptr;
		break;
	}
}

void CharacterSelectScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{

	default:
		//AlexisBruce* char1 = dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2"));
		//char1->NotifyOnKeyUp(key_);
		//char1 = nullptr;
		break;
	}
}

void CharacterSelectScene::AddCharacter(std::string name_, Character* character_)
{
	listOfCharacters[name_] = character_;
	names.push_back(name_);
	currentCharacter = names[0];
	selectedCharacter = names[0];
}

void CharacterSelectScene::CharacterSelection()
{
	if (currentCharacter != selectedCharacter) {
		listOfCharacters[currentCharacter]->SetPosition(glm::vec3(-100.0f, 0.0f, 0.0f));
		currentCharacter = selectedCharacter;
	}
	//Character that player sees
	listOfCharacters[currentCharacter]->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}
