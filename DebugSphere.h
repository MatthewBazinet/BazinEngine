#pragma once
#include<glm/glm.hpp>
#include <glew.h>
#include <vector>
class DebugSphere
{
private:
	glm::vec3 position;
	float radius;
	GLuint elementbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;
	GLuint vertexbuffer;
	int size = 0;
public:
	inline GLuint getUvBuffer() { return uvbuffer; }

	inline GLuint getElemBuffer() { return elementbuffer; }

	inline GLuint getVertexBuffer() { return vertexbuffer; }

	inline GLuint getNormalBuffer() { return normalbuffer; }

	inline int getSize() { return size; }

	void Create(float Radius, int Resolution);
};

