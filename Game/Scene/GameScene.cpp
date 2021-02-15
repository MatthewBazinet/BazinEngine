#include "GameScene.h"

GameScene::GameScene() : shape(nullptr)
{
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Log::Info("Game Scene initiated", "GameScene.cpp", __LINE__);

	Vertex v;

	//Square/Rectangle
	std::vector<Vertex> squareVertexList;
	squareVertexList.reserve(6);
	//Top-Right Half
	v.position = glm::vec3(-0.75f, 0.5f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(0.25f, 0.5f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(0.25f, -0.5f, 0.0f);
	squareVertexList.push_back(v);
	//Bottom-Left Half
	v.position = glm::vec3(0.25f, -0.5f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(-0.75f, -0.5f, 0.0f);
	squareVertexList.push_back(v);
	v.position = glm::vec3(-0.75f, 0.5f, 0.0f);
	squareVertexList.push_back(v);

	//Coffin
	std::vector<Vertex> coffinVertexList;
	coffinVertexList.reserve(9);
	//Bottom Left
	v.position = glm::vec3(0.4f, 0.5f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.8f, 0.5f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.7f, -0.5f, 0.0f);
	coffinVertexList.push_back(v);
	//Bottom Right
	v.position = glm::vec3(0.7f, -0.5f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.4f, 0.5f, 0.0f);
	coffinVertexList.push_back(v);
	//Top
	v.position = glm::vec3(0.6f, 0.7f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.8f, 0.5f, 0.0f);
	coffinVertexList.push_back(v);
	v.position = glm::vec3(0.4f, 0.5f, 0.0f);
	coffinVertexList.push_back(v);

	Model* model = new Model();
	model->AddMesh(new Mesh(squareVertexList));
	model->AddMesh(new Mesh(coffinVertexList));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
}

void GameScene::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shape->Render();
}
