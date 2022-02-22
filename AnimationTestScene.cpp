
#include "AnimationTestScene.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "..//../AICharacter.h"
#include "../Engine/Math/CollisionDetection.h"
#include "Tetrahedron.h"

AnimationTestScene::AnimationTestScene()
{

}

AnimationTestScene::~AnimationTestScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool AnimationTestScene::OnCreate()
{
	Log::Info("Game Scene initiated", "AnimationTestScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 1.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 0.0f, 0.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");

	
	MorphTargetAnimatedModel* model1 = new MorphTargetAnimatedModel("Resources/Models/characterAnim1.obj", "Resources/Materials/characterAnim1.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	model1->AddMorphTarget("Target1", new MorphTarget("Resources/Models/characterAnim1.obj", "Resources/Materials/characterAnim1.mtl"));
	model1->AddMorphTarget("Target2", new MorphTarget("Resources/Models/characterAnim2.obj", "Resources/Materials/characterAnim2.mtl"));

	model1->SetCurrentMorphTarget("Target1", 5.0f);
	model1->SetCurrentMorphTarget("Target2", 5.0f);

	//Model* model2 = new Model("Resources/Models/MorphTargetContracted.obj", "Resources/Materials/MorphTargetContracted.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(model1);
	//SceneGraph::GetInstance()->AddModel(model2);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(model1, glm::vec3(0.0f, 0.0f, 0.0f)), "model1");

	SceneGraph::GetInstance()->GetGameObject("model1")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	SceneGraph::GetInstance()->GetGameObject("model1")->SetAngularVelocity(glm::quat( 0.0f, 0.0f, glm::radians(45.0f), 0.0f));


	model1 = nullptr;
	//model2 = nullptr;

	return true;
}

void AnimationTestScene::Update(const float deltaTime_)
{
	static_cast<MorphTargetAnimatedModel*>(SceneGraph::GetInstance()->GetGameObject("model1")->GetModel())->Update(deltaTime_);
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void AnimationTestScene::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (lineMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void AnimationTestScene::HandleEvents(const SDL_Event& sdlEvent)
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

void AnimationTestScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
	case SDL_SCANCODE_Y:
		static_cast<MorphTargetAnimatedModel*>(SceneGraph::GetInstance()->GetGameObject("model1")->GetModel())->SetCurrentMorphTarget("Target1", 1.0f);
		//SceneGraph::GetInstance()->GetGameObject("model1")->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
			break;
	case SDL_SCANCODE_U:
		static_cast<MorphTargetAnimatedModel*>(SceneGraph::GetInstance()->GetGameObject("model1")->GetModel())->SetCurrentMorphTarget("Target2", 1.0f);
		//SceneGraph::GetInstance()->GetGameObject("model1")->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
		break;
	default:
		break;
	}
}

void AnimationTestScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{
	case SDL_SCANCODE_G:
		lineMode = (lineMode) ? false : true;
		break;
	default:
		break;
	}
}
