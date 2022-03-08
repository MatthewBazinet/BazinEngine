#include "GameScene.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "..//../AICharacter.h"
#include "../ParticleSystem.h"
#include "../Component.h"
#include "../XMLDecisionTreeReader.h"
#include "../UserInterface.h"
#include "../Game/Characters/Hoshi.h"
#include "../Engine/Math/EnvironmentalCollisionManager.h"

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
	TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/Textures/CheckerboardTexture.png");

	Vertex v;
	//Square and Coffin Vertices
	/*
	//Square/Rectangle
	std::vector<Vertex> squareVertexList;
	squareVertexList.reserve(6);
	//Top-Right Half
	v.position = glm::vec3(-0.75f, 0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(0.25f, 0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 1.0f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(0.25f, -0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 1.0f, 1.0f);
	squareVertexList.push_back(v);
	//Bottom-Left Half
	v.position = glm::vec3(0.25f, -0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 1.0f, 1.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(-0.75f, -0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 1.0f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(-0.75f, 0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	squareVertexList.push_back(v);

	//Coffin
	std::vector<Vertex> coffinVertexList;
	coffinVertexList.reserve(9);
	//Bottom Left
	v.position = glm::vec3(0.4f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.5f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.8f, 0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.7f, -0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	//Bottom Right
	v.position = glm::vec3(0.7f, -0.5f, 0.0f);
	v.colour = glm::vec3(0.5f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.4f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	//Top
	v.position = glm::vec3(0.6f, 0.7f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.8f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.4f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 0.0f);
	coffinVertexList.push_back(v);
	*/

	//Cube Vertices
	std::vector<Vertex> vertexList;
	vertexList.reserve(36);
	/*{
		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.583f, 0.771f, 0.014f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.609f, 0.115f, 0.436f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.327f, 0.483f, 0.844f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.822f, 0.569f, 0.201f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.435f, 0.602f, 0.223f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.310f, 0.747f, 0.185f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.597f, 0.770f, 0.761f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.559f, 0.436f, 0.730f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.359f, 0.583f, 0.152f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.483f, 0.596f, 0.789f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.559f, 0.861f, 0.639f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.195f, 0.548f, 0.859f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.014f, 0.184f, 0.576f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.771f, 0.328f, 0.970f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.406f, 0.615f, 0.116f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.676f, 0.977f, 0.133f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.971f, 0.572f, 0.833f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.140f, 0.616f, 0.489f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.997f, 0.513f, 0.064f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.945f, 0.719f, 0.592f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.543f, 0.021f, 0.978f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.279f, 0.317f, 0.505f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.167f, 0.620f, 0.077f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.347f, 0.857f, 0.137f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.055f, 0.953f, 0.042f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.714f, 0.505f, 0.345f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.783f, 0.290f, 0.734f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.722f, 0.645f, 0.174f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.302f, 0.455f, 0.848f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.225f, 0.587f, 0.040f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.517f, 0.713f, 0.338f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.053f, 0.959f, 0.120f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.393f, 0.621f, 0.362f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.673f, 0.211f, 0.457f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.820f, 0.883f, 0.371f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.982f, 0.099f, 0.879f);
		vertexList.push_back(v);
	}*/
	//model->AddMesh(new Mesh(squareVertexList, ShaderHandler::GetInstance()->GetShader("colourShader")));
//model->AddMesh(new Mesh(coffinVertexList, ShaderHandler::GetInstance()->GetShader("colourShader")));
//SubMesh subMesh;
//subMesh.vertexList = vertexList;
//subMesh.textureID = TextureHandler::GetInstance()->GetTexture("Checkerboard");
//model->AddMesh(new Mesh(subMesh, ShaderHandler::GetInstance()->GetShader("basicShader")));
//model->SetScale(glm::vec3(0.5f));

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* player = new Model("Resources/Models/AlexisBruce.obj", "Resources/Materials/AlexisBruce.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj","Resources/Materials/Apple.mtl",ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* rachidaShape = new Model("Resources/Models/tetrahedron.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* man = new Model("Resources/Models/basecharactermodel.obj", "Resources/Materials/basecharactermodel.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* Sphere = new Model("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	//Model* pawn = new Model("Resources/Models/basecharactermodel.obj", "Resources/Materials/basecharactermodel.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(player);
	SceneGraph::GetInstance()->AddModel(appleModel);
	SceneGraph::GetInstance()->AddModel(rachidaShape);
	SceneGraph::GetInstance()->AddModel(Sphere);

	XMLDecisionTreeReader read;
	read.ReadFile("Tree.xml");
	
	//SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-2.0f, 0.0f, 0.0f)), "dice");
	//SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)), "apple");
	//Model* rachidaShape = new Model("Resources/Models/tetrahedron.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	/*SceneGraph::GetInstance()->AddGameObject(new GameObject(rachidaShape, glm::vec3(-4.0f, 0.0f, 0.0f)), "model1");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(rachidaShape, glm::vec3(4.0f, 0.0f, 0.0f)), "model2");

	SceneGraph::GetInstance()->GetGameObject("model1")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	SceneGraph::GetInstance()->GetGameObject("model1")->SetAngularVelocity(glm::quat( 0.0f, 0.0f, glm::radians(45.0f), 0.0f));
	SceneGraph::GetInstance()->GetGameObject("model1")->SetVelocity(glm::vec3(1.0f,0.0f,0.0f));
	SceneGraph::GetInstance()->GetGameObject("model2")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	SceneGraph::GetInstance()->GetGameObject("model2")->SetAngularVelocity(glm::quat(0.0f, 0.0f, glm::radians(-45.0f), 0.0f));
	SceneGraph::GetInstance()->GetGameObject("model2")->SetVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));*/

	//SceneGraph::GetInstance()->AddGameObject(new GameObject(player, glm::vec3(4.0f,0.0f, 0.0f)),"apple");
	//SceneGraph::GetInstance()->GetGameObject("apple")->AddComponent<ParticleSystem>(100, ShaderHandler::GetInstance()->GetShader("particleShader"), SceneGraph::GetInstance()->GetGameObject("apple")->GetPosition());
	//ptr = SceneGraph::GetInstance()->GetGameObject("apple")->GetComponent<ParticleSystem>();

	//SceneGraph::GetInstance()->AddGameObject(new Flocking(appleModel, glm::vec3(-2.0f, 0.0f, 0.0f)), "rop");
	

	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(0.0f, 0.0f, 0.0f)), "char1");
	SceneGraph::GetInstance()->AddGameObject(new Hoshi(glm::vec3(10.0f, 0.0f, 0.0f)), "char2");
	dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetModels(Sphere);
	dynamic_cast<Hoshi*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetModels(Sphere);

	//SceneGraph::GetInstance()->AddGameObject(new Character(0.5f, 1.0f, false, false, diceModel, glm::vec3(0.0f, 5.0f, 0.0f)), "char1");

	
	//SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)), "apple");
	//static_cast<Flocking*>(SceneGraph::GetInstance()->GetGameObject("rop"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("char1"));

	//SceneGraph::GetInstance()->AddGameObject(new GameObject(rachidaShape, glm::vec3(-4.0f, 0.0f, 0.0f)), "model1");
	//SceneGraph::GetInstance()->AddGameObject(new GameObject(rachidaShape, glm::vec3(4.0f, 0.0f, 0.0f)), "model2");

	//SceneGraph::GetInstance()->GetGameObject("model1")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	//SceneGraph::GetInstance()->GetGameObject("model1")->SetAngularVelocity(glm::quat( 0.0f, 0.0f, glm::radians(45.0f), 0.0f));
	//SceneGraph::GetInstance()->GetGameObject("model1")->SetVelocity(glm::vec3(1.0f,0.0f,0.0f));
	//SceneGraph::GetInstance()->GetGameObject("model2")->SetOrientation(glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	//SceneGraph::GetInstance()->GetGameObject("model2")->SetAngularVelocity(glm::quat(0.0f, 0.0f, glm::radians(-45.0f), 0.0f));
	//SceneGraph::GetInstance()->GetGameObject("model2")->SetVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));
	//SceneGraph::GetInstance()->AddGameObject(new AICharacter(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), 1.0f, 1.0f, false, false, diceModel, glm::vec3(10.0f, 0.0f, 0.0f)), "ai1");

	//static_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile1"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("char1"));
	//static_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile2"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("projectile1"));
	//static_cast<Projectile*>(SceneGraph::GetInstance()->GetGameObject("projectile3"))->SetTarget(SceneGraph::GetInstance()->GetGameObject("projectile1"));
	
	
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetOpponent(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera())->SetPlayers(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")), dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));
	dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetCamera(static_cast<BattleCamera*>(CoreEngine::GetInstance()->GetCamera()));
	
	UserInterface::GetInstance()->SetPlayer1(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	UserInterface::GetInstance()->SetPlayer2(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2")));
	glm::vec3 s(1.0f);
	glm::vec3 e(6.0f);

	inputManager = InputManager();
	inputManager.SetPlayer1(dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1")));
	Keybinds binds;
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
	

	diceModel = nullptr;
	player = nullptr;
	appleModel = nullptr;
	rachidaShape = nullptr;
	man = nullptr;

	leftPlane = glm::vec4(-1.0f, 0.0f, 0.0f, 15.0f);
	rightPlane = glm::vec4(1.0f, 0.0f, 0.0f, 15.0f);
	northPlane = glm::vec4(0.0f, 0.0f, 1.0f, -15.0f);
	southPlane = glm::vec4(0.0f, 0.0f, -1.0f, 15.0f);
	planes.push_back(leftPlane);
	planes.push_back(rightPlane);
	//planes.push_back(northPlane);
	//planes.push_back(southPlane);

	return true;
}

void GameScene::ResetRound()
{
	SceneGraph::GetInstance()->GetGameObject("char1")->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("char2")->SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));

	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->SetHealth(100.0f);
	static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetHealth(100.0f);

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

	if (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char1"))->GetHealth() <= 0.0f)
	{
		std::cout << "player 1 win" << std::endl;
		ResetRound();
	}
	else if (static_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->GetHealth() <= 0.0f)
	{
		std::cout << "player 2 win" << std::endl;
		ResetRound();
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
