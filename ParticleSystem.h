#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <glm/glm.hpp>

#include<glew.h>
#include <vector>

class ParticleSystem
{
public:
	ParticleSystem(int numberOfParticles);
	~ParticleSystem();
	void Render() const;
private:
	GLuint vao, vbo;
	void setupParticles();
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> vel;
	std::vector<glm::vec4> colour;
};

#endif