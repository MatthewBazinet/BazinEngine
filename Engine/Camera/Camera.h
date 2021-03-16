#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "..//FX/LightSource.h"

class Camera {
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_, float roll_ = 0.0f);
	void SetRotation(glm::vec3 rotation_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;

	void AddLightSource(LightSource* light_);
	const std::vector<LightSource*> GetLightSources() const;

private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch, roll;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lightSources;

};

#endif // !CAMERA_H
