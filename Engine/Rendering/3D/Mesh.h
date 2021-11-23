#ifndef MESH_H
#define MESH_H

#include<glew.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"../..//Graphics/MaterialHandler.h"
#include"..//..//Camera/Camera.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

struct SubMesh
{
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh {
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4>& instances_, std::vector<bool>& instancesVisible_);
	std::vector<Vertex> GetVertices();
private:
	void GenerateBuffers();
	SubMesh subMesh;
	GLuint timeLoc;
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projectionLoc;
	GLuint viewPosLoc, lightPosLoc, ambientLoc, diffuseLoc, specularLoc, colourLoc;
	GLuint diffuseMapMatLoc, shininessMatLoc, transparencyMatLoc, ambientMatLoc, diffuseMatLoc, specularMatLoc;
};

#endif //!MESH_H