#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H



#include<glew.h>
#include <vector>
#include<glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "Engine/Camera/Camera.h"
#include "Component.h"
class ParticleSystem : public Component
{
public:
	ParticleSystem(int numberOfParticles, GLuint shaderProgram_, glm::vec3 pos_);
	~ParticleSystem();
	virtual bool OnCreate(GameObject* parent_);
	virtual void OnDestroy();
	void Render(Camera* camera_) const;
	virtual void Update(const float deltaTime_);
private:
	GLuint vao, vbo;
	void setupParticles();
	float totalTime;
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> vel;
	std::vector<glm::vec4> colour;
	GLuint timeLoc;
	GLuint shaderProgram;
	GLuint viewLoc, projLoc;
	Camera* camera;
};

#endif