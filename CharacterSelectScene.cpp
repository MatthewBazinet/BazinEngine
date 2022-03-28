#include "CharacterSelectScene.h"
#include "Game/Character.h"
#include "Game/Characters/AlexisBruce.h"
#include "Game/Characters/Hoshi.h"
#include "Game/Characters/Wulfrun.h"
#include "Game/Characters/Eldric.h"

#include "Projectile.h"

CharacterSelectScene::CharacterSelectScene()
{
	P1count = 0;
	P2count = 0;
}

CharacterSelectScene::~CharacterSelectScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool CharacterSelectScene::OnCreate()
{
	Log::Info("Character Select Scene initiated", "CharacterSelectScene.cpp", __LINE__);
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 5.0f, 20.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-5.0f, 12.0f, 2.0f), 0.2f, 0.8f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");

	Model* Alexis = new Model("Resources/Models/Alexis/Alexis_Walk_01.obj", "Resources/Materials/AlexisBruce.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//Model* Hoshis = new Model("Resources/Models/Hoshi.obj", "Resources/Materials/Hoshi.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Rock = new Model("Resources/Models/Rock.obj", "Resources/Materials/Rock.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Sphere = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//Model* kunai = new Model("Resources/Models/Kunai.obj", "Resources/Materials/Kunai.mtl", ShaderHandler::GetInstance()->GetShader("basicShader");

	SceneGraph::GetInstance()->AddModel(Alexis);
	//SceneGraph::GetInstance()->AddModel(Hoshis);
	SceneGraph::GetInstance()->AddModel(Rock);
	SceneGraph::GetInstance()->AddModel(Sphere);

	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(-8000.0f, 0.0f, 0.0f), Sphere), "Player1Hoshi");
	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(-8000.0f, 0.0f, 0.0f), Sphere), "Player2Hoshi");
	SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(glm::vec3(-8000.0f, 0.0f, 0.0f)), "Player1Alexis");
	SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(glm::vec3(-8000.0f, 0.0f, 0.0f)), "Player2Alexis");

	SceneGraph::GetInstance()->AddGameObject(new Eldric(glm::vec3(-8000.0f, 0.0f, 0.0f), Sphere), "Player1Eldric");
	SceneGraph::GetInstance()->AddGameObject(new Eldric(glm::vec3(-8000.0f, 0.0f, 0.0f), Sphere), "Player2Eldric");

	//SceneGraph::GetInstance()->AddModel(kunai);


	//kunai = nullptr;
	//dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetModels(Rock, Sphere);

	//SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(-8.0f, 0.0f, 0.0f)), "char1");
	//dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(appleModel, Dice);
	//SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(5.0f, 0.0f, 0.0f)), "char2");
	/*SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(1.0f, 1.0f, false, false, Alexis, glm::vec3(-8.0f, 0.0f, 0.0f)), "char1");
	dynamic_cast<AlexisBruce*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(appleModel, Dice);
	SceneGraph::GetInstance()->AddGameObject(new AlexisBruce(1.0f, 1.0f, false, false, Alexis, glm::vec3(5.0f, 0.0f, 0.0f)), "char2");*/
	
	//SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(5.0f, 0.0f, 0.0f)), "char2");


	AddCharacter("Hoshi1", dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("Player1Hoshi")),Player1Characters::Hoshi,"Hoshi2", dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("Player2Hoshi")),Player2Characters::Hoshi);
	AddCharacter("Alexis1", dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("Player1Alexis")), Player1Characters::Alexis, "Alexis2", dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("Player2Alexis")),Player2Characters::Alexis);

	AddCharacter("Eldric1", dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("Player1Eldric")), Player1Characters::Eldric, "Eldric2", dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("Player2Eldric")), Player2Characters::Eldric);

	Rock = nullptr;
	Alexis = nullptr;
	Sphere = nullptr;
	//Hoshis = nullptr;
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
		P1count++;
		if (P1count > P1names.size() -1) {
			P1count = 0;
		}
		P1selectedCharacter = P1names[P1count];
		break;
	case(SDL_SCANCODE_D):
		P1count--;
		if (P1count < 0) {
			P1count = P1names.size() -1;
		}
		P1selectedCharacter = P1names[P1count];
		break;
	case(SDL_SCANCODE_LEFT):
		P2count++;
		if (P2count > P2names.size() - 1) {
			P2count = 0;
		}
		P2selectedCharacter = P2names[P2count];
		break;
	case(SDL_SCANCODE_RIGHT):
		P2count--;
		if (P2count < 0) {
			P2count = P2names.size() - 1;
		}
		P2selectedCharacter = P2names[P2count];
		break;
	case(SDL_SCANCODE_RETURN):
		std::cout << "enter" << std::endl;
		break;
	default:
		break;
	}
}

void CharacterSelectScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{

	default:
		break;
	}
}

void CharacterSelectScene::AddCharacter(std::string P1Name_, GameObject* P1Character_, Player1Characters P1Enums_, std::string P2Name_, GameObject* P2Character_, Player2Characters P2Enums_)
{
	P1ListOfCharacters[P1Name_] = P1Character_;
	P1names.push_back(P1Name_);
	P1currentCharacter = P1names[0];
	P1selectedCharacter = P1names[0];

	P2ListOfCharacters[P2Name_] = P2Character_;
	P2names.push_back(P2Name_);
	P2currentCharacter = P2names[0];
	P2selectedCharacter = P2names[0];

	P1Enums[P1Name_] = P1Enums_;
	P2Enums[P2Name_] = P2Enums_;

}

void CharacterSelectScene::CharacterSelection()
{
	//Player 1 character selection
	if (P1currentCharacter != P1selectedCharacter) {
		P1ListOfCharacters[P1currentCharacter]->SetPosition(glm::vec3(-100.0f, 0.0f, 0.0f));
		P1currentCharacter = P1selectedCharacter;
		std::cout << P1selectedCharacter << std::endl;
	}
	//Character that player1 sees
	MatchSettings::GetInstance()->SetPlayer1Character(P1Enums[P1currentCharacter]);
	P1ListOfCharacters[P1currentCharacter]->SetPosition(glm::vec3(-8.0f, 0.0f, 0.0f));
	

	//Player 2 character selection
	if (P2currentCharacter != P2selectedCharacter) {
		P2ListOfCharacters[P2currentCharacter]->SetPosition(glm::vec3(-100.0f, 0.0f, 0.0f));
		P2currentCharacter = P2selectedCharacter;
		std::cout << P2selectedCharacter << std::endl;
		
	}
	//Character that player2 sees
	MatchSettings::GetInstance()->SetPlayer2Character(P2Enums[P2currentCharacter]);
	P2ListOfCharacters[P2currentCharacter]->SetPosition(glm::vec3(8.0f, 0.0f, 0.0f));
	
}
