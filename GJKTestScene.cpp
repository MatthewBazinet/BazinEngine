
#include "GJKTestScene.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "..//../AICharacter.h"
#include "../Engine/Math/CollisionDetection.h"
#include "Tetrahedron.h"

GJKTestScene::GJKTestScene()
{

}

GJKTestScene::~GJKTestScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GJKTestScene::OnCreate()
{
	Log::Info("Game Scene initiated", "GJKTestScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 1.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(-2.0f, -2.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, -1.0f, 2.0f), 0.1f, 0.5f, 0.5, glm::vec3(1.0f, 0.0f, 0.0f)));

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");

	
	Model* rachidaShape = new Model("Resources/Models/tetrahedron.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));


	SceneGraph::GetInstance()->AddModel(rachidaShape);

	Tetrahedron tetra;
	tetra.points[0] = glm::vec3(-0.2068f, -0.3484f, -0.2400f);
	tetra.points[1] = glm::vec3(-0.2068f, -0.6516f, -0.2400f);
	tetra.points[2] = glm::vec3(0.7932f, -0.3484f, -0.2400f);
	tetra.points[3] = glm::vec3(-0.2068f, -0.3484f, 0.7600f);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(rachidaShape, glm::vec3(-4.0f, 0.0f, 0.0f)), "model1");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(rachidaShape, glm::vec3(4.0f, 0.0f, 0.0f)), "model2");

	SceneGraph::GetInstance()->GetGameObject("model1")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	SceneGraph::GetInstance()->GetGameObject("model1")->SetAngularVelocity(glm::quat( 0.0f, 0.0f, glm::radians(45.0f), 0.0f));
	SceneGraph::GetInstance()->GetGameObject("model1")->SetVelocity(glm::vec3(1.0f,0.0f,0.0f));
	SceneGraph::GetInstance()->GetGameObject("model2")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	SceneGraph::GetInstance()->GetGameObject("model2")->SetAngularVelocity(glm::quat(0.0f, 0.0f, glm::radians(-45.0f), 0.0f));
	SceneGraph::GetInstance()->GetGameObject("model2")->SetVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));

	SceneGraph::GetInstance()->GetGameObject("model1")->SetShape(tetra);
	SceneGraph::GetInstance()->GetGameObject("model2")->SetShape(tetra);



	rachidaShape = nullptr;

	return true;
}

void GJKTestScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	CollisionDetection::GJK<Tetrahedron, Tetrahedron> gjk = CollisionDetection::GJK<Tetrahedron, Tetrahedron>(SceneGraph::GetInstance()->GetGameObject("model1")->GetShape(), SceneGraph::GetInstance()->GetGameObject("model2")->GetShape());
	if (gjk.GJKIntersection())
	{
		if (!colliding)
		{
			std::cout << "Tetrahedrons Collided!\n";
			colliding = true;
		}
	}
	else
	{
		if (colliding)
		{
			std::cout << "Tetrahedrons Stopped Colliding!\n";
			colliding = false;
		}
	}
}

void GJKTestScene::Render()
{

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void GJKTestScene::HandleEvents(const SDL_Event& sdlEvent)
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

void GJKTestScene::NotifyOfKeyDown(const SDL_Scancode key_)
{
	switch (key_)
	{
	}
}

void GJKTestScene::NotifyOfKeyUp(const SDL_Scancode key_)
{
	switch (key_)
	{

	}
}
