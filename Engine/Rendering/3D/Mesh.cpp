#include "Mesh.h"


Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0), textureLoc(0), viewPosLoc(0), lightPosLoc(0), ambientLoc(0), diffuseLoc(0), specularLoc(0), colourLoc(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);
	const int numOfLights = 10;
	glm::vec3 lightPositions[numOfLights];
	float ambients[numOfLights];
	float diffuses[numOfLights];
	float speculars[numOfLights];
	glm::vec3 colours[numOfLights];

	for (int i = 0; i < camera_->GetLightSources().size(); i++) {
		lightPositions[i] = camera_->GetLightSources()[i]->GetPosition();
		ambients[i] = camera_->GetLightSources()[i]->GetAmbient();
		diffuses[i] = camera_->GetLightSources()[i]->GetDiffuse();
		speculars[i] = camera_->GetLightSources()[i]->GetSpecular();
		colours[i] = camera_->GetLightSources()[i]->GetColour();
	}

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPosLoc, numOfLights, glm::value_ptr(lightPositions[0]));
	glUniform1fv(ambientLoc, numOfLights, (GLfloat*)& ambients[0]);
	glUniform1fv(diffuseLoc, numOfLights, (GLfloat*)& diffuses[0]);
	glUniform1fv(specularLoc, numOfLights, (GLfloat*)& speculars[0]);
	glUniform3fv(colourLoc, numOfLights, glm::value_ptr(colours[0]));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
}


void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);
	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	
	viewPosLoc = glGetUniformLocation(shaderProgram, "cameraPosition");
	lightPosLoc = glGetUniformLocation(shaderProgram, "lightSource.position[0]");
	ambientLoc = glGetUniformLocation(shaderProgram, "lightSource.ambient[0]");
	diffuseLoc = glGetUniformLocation(shaderProgram, "lightSource.diffuse[0]");
	specularLoc = glGetUniformLocation(shaderProgram, "lightSource.specular[0]");
	colourLoc = glGetUniformLocation(shaderProgram, "lightSource.colour[0]");

}
