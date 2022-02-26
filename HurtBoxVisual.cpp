#include "HurtBoxVisual.h"

HurtBoxVisual::HurtBoxVisual(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : Model(objPath_,matPath_,shaderProgram_)
{
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstances.reserve(5);
	modelInstancesVisable.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();
	isEnabled = false;
}

HurtBoxVisual::~HurtBoxVisual()
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

void HurtBoxVisual::Render(Camera* camera_)
{
	if (isEnabled) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(1.0f, 1.0f, 1.0f);
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
