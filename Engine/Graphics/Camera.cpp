#include "Camera.h"

#include"..//Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3()), fieldOfView(0.0f), forward(glm::vec3()), up(glm::vec3()), right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenWidth() / CoreEngine::GetInstance()->GetScreenHeight(), nearPlane, farPlane);
	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(), 0.0f, CoreEngine::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
}

glm::mat4 Camera::GetView() const
{
	return glm::mat4();
}

glm::mat4 Camera::GetPerspective() const
{
	return glm::mat4();
}

glm::mat4 Camera::GetOrthographic() const
{
	return glm::mat4();
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::UpdateCameraVectors()
{
	//forward.x = cos(glm::radians(yaw) * cos())
}
