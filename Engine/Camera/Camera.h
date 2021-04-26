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
	void SetZoomSpeed(float speed_);
	void SetMouseSensitivity(float sensitivity_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	float GetNearPlane() const;
	float GetFarPlane() const;
	glm::vec3 GetForward() const;

	float GetZoomSpeed();
	float GetMouseSensitivity();

	void AddLightSource(LightSource* light_);
	const std::vector<LightSource*> GetLightSources() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

	bool TestPointAgainstPlanes(glm::vec3 point_, glm::mat4 transform_);

private:
	void UpdateCameraVectors();
	glm::vec4 NormalizePlane(glm::vec4 plane_);
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch, roll;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	glm::vec4 leftPlane, rightPlane, bottomPlane, upPlane, nearFRPlane, farFRPlane;

	std::vector<LightSource*> lightSources;

	float mouseSensitivity;
	float zoomSpeed;

};

#endif // !CAMERA_H
