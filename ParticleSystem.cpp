#include "ParticleSystem.h"
#include "Randomizer.h"

ParticleSystem::ParticleSystem(int numberOfParticles, GLuint shaderProgram_)
{
	MATH::Randomizer r;
	totalTime = 0.0f;
	shaderProgram = shaderProgram_;
	for (int i = 0; i < numberOfParticles; i++)
	{
		pos.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		//vel.push_back(glm::vec3(r.box_muller(0.0f, 1.0f), r.box_muller(0.0f, 1.0f), r.box_muller(0.0f, 1.0f)));
		vel.push_back(glm::vec3(0.0f,0.0f, 0.0f));
		colour.push_back(glm::vec4(r.rand(0.5f, 1.0f), r.rand(0.5f, 1.0f), r.rand(0.5f, 1.0f), 0.0f));
		//colour.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	}
	setupParticles();
}

ParticleSystem::~ParticleSystem()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void ParticleSystem::Render(Camera* camera_) const
{
	glUseProgram(shaderProgram);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(vao);
	glUniform1f(timeLoc, totalTime);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glDrawArrays(GL_POINTS, 0, pos.size());
	glBindVertexArray(0);
	glDisable(GL_PROGRAM_POINT_SIZE);
	
}

void ParticleSystem::Update(const float deltaTime_)
{
	totalTime += deltaTime_;
}

#define POS_LENGTH (pos.size() * (sizeof(glm::vec3)))
#define VEL_LENGTH (vel.size() * (sizeof(glm::vec3)))
#define COLOUR_LENGTH (colour.size() * (sizeof(glm::vec4)))

void ParticleSystem::setupParticles()
{
	const int posID = 0;
	const int velID = 1;
	const int colourID = 2;

	//create and bind VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//create and initialize VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, POS_LENGTH + VEL_LENGTH + COLOUR_LENGTH, nullptr, GL_STATIC_DRAW);
	//assigns addr of points
	glBufferSubData(GL_ARRAY_BUFFER, 0, POS_LENGTH, &pos[0]);

	glBufferSubData(GL_ARRAY_BUFFER, POS_LENGTH, VEL_LENGTH, &vel[0]);

	glBufferSubData(GL_ARRAY_BUFFER, POS_LENGTH + VEL_LENGTH, COLOUR_LENGTH, &colour[0]);

	glEnableVertexAttribArray(posID);
	glVertexAttribPointer(posID, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
	
	glEnableVertexAttribArray(velID);
	glVertexAttribPointer(velID, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(POS_LENGTH + VEL_LENGTH));

	glEnableVertexAttribArray(colourID);
	glVertexAttribPointer(colourID, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(POS_LENGTH + VEL_LENGTH + COLOUR_LENGTH));


	timeLoc = glGetUniformLocation(shaderProgram, "totalTime");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "projection");
}

#undef POS_LENGTH
#undef VEL_LENGTH
#undef COLOUR_LENGTH