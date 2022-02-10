#include "Model.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../../Core/CoreEngine.h"

Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : meshes(std::vector<Mesh*>()), shaderProgram(0), modelInstances(std::vector<glm::mat4>()), obj(nullptr)
{
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstances.reserve(5);
	modelInstancesVisable.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();

}

Model::~Model()
{
	if (meshes.size() > 0) 
	{
		for (auto m : meshes)
		{
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}

	if (modelInstances.size() > 0) {
		modelInstances.clear();
	}
}

void Model::Render(Camera* camera_)
{
	switch (CoreEngine::GetInstance()->GetRendererType())
	{
	case RendererType::OPENGL:
		glUseProgram(shaderProgram);
		
		break;
	case RendererType::VULKAN:
		break;
	case RendererType::DIRECTX11:
		break;
	case RendererType::DIRECTX12:
		break;
	}
	for (auto m : meshes)
	{
		m->Render(camera_, modelInstances, modelInstancesVisable);
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	meshes.push_back(mesh_);
}

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	modelInstancesVisable.push_back(false);
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

void Model::UpdateInstance(unsigned int index_, glm::vec3 position_, glm::quat orientation_, glm::vec3 scale_)
{
	modelInstances[index_] = CreateTransform(position_, orientation_, scale_);
}

void Model::SetInstanceVisiblity(unsigned int index_, bool visible_)
{
	modelInstancesVisable[index_] = visible_;
}

glm::mat4 Model::GetTransform(unsigned int index_) const
{
	return modelInstances[index_];
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

BoundingBox Model::GetBoundingBox() const
{
	return boundingBox;
}

std::vector<Mesh*> Model::GetMeshes()
{
	return meshes;
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	//glm::mat4 model;
	//model = glm::translate(model, position_);
	//model = glm::rotate(model, angle_, rotation_);
	//model = glm::scale(model, scale_);
	glm::mat4 matrix = glm::mat4();
	glm::mat4 mat = glm::translate(matrix, position_)
		* glm::toMat4(glm::angleAxis(angle_, glm::vec3(0, 0, 1)))
		* glm::scale(matrix, scale_);

	return mat;
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, glm::quat orientation_, glm::vec3 scale_) const
{
	orientation_ = glm::normalize(orientation_);
	glm::mat4 model;
	glm::mat4 translate = glm::translate(model, position_);
	glm::mat4 rotate = glm::toMat4(orientation_);
	glm::mat4 scale = glm::scale(model, scale_);
	model = translate * rotate * scale;
	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}
	boundingBox = obj->GetBoundingBox();
	delete obj;
	obj = nullptr;
}
