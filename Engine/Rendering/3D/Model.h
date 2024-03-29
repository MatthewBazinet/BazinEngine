#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include<glm/gtc/matrix_transform.hpp>

#include <string>
#include "LoadOBJModel.h"

class Model {
public:
	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~Model();

	virtual void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	unsigned int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(unsigned int index_, glm::vec3 position_, glm::quat orientation_, glm::vec3 scale_);
	void SetInstanceVisiblity(unsigned int index_, bool visible_);

	glm::mat4 GetTransform(unsigned int index_) const;
	GLuint GetShaderProgram() const;
	BoundingBox GetBoundingBox() const;

	std::vector<Mesh*> GetMeshes();

protected:
	glm::mat4 CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	glm::mat4 CreateTransform(glm::vec3 position_, glm::quat orientation_, glm::vec3 scale_) const;
	void LoadModel();

	LoadOBJModel* obj;
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;
	std::vector<bool> modelInstancesVisable;
	BoundingBox boundingBox;
	
};

#endif //!MODEL_H