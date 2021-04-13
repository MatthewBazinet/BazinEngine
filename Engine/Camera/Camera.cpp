#include "Camera.h"

#include"..//Core/CoreEngine.h"
#include<glm/gtx/transform.hpp>

Camera::Camera() : position(glm::vec3()), fieldOfView(0.0f), forward(glm::vec3()), up(glm::vec3()), right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), roll(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4()), mouseSensitivity(0.0f), zoomSpeed(0.0f)
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	mouseSensitivity = 0.05f;
	zoomSpeed = 2.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenWidth() / CoreEngine::GetInstance()->GetScreenHeight(), nearPlane, farPlane);
	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(), 0.0f, CoreEngine::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);
	UpdateCameraVectors();
}

Camera::~Camera()
{
	if (lightSources.size() > 0)
	{
		for (auto l : lightSources)
		{
			delete l;
			l = nullptr;
		}
	}
	lightSources.clear();
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_, float roll_)
{
	yaw = yaw_;
	pitch = pitch_;
	roll = roll_;
	UpdateCameraVectors();
}

void Camera::SetRotation(glm::vec3 rotation_)
{
	yaw = rotation_.x;
	pitch = rotation_.y;
	roll = rotation_.z;
	UpdateCameraVectors();
}

void Camera::SetZoomSpeed(float speed_)
{
	zoomSpeed = speed_;
}

void Camera::SetMouseSensitivity(float sensitivity_)
{
	mouseSensitivity = sensitivity_;
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

glm::vec3 Camera::GetRotation() const
{
	return glm::vec3(yaw, pitch, roll);
}

float Camera::GetZoomSpeed()
{
	return zoomSpeed;
}

float Camera::GetMouseSensitivity()
{
	return mouseSensitivity;
}

void Camera::AddLightSource(LightSource* light_)
{
	lightSources.push_back(light_);
}

const std::vector<LightSource*> Camera::GetLightSources() const
{
	return lightSources;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= mouseSensitivity;

	yaw += offset_.x;
	pitch -= offset_.y;

	if (pitch > 89.0f) 
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
	if (yaw < 0.0f)
	{
		yaw += 360.0f;
	}
	if (yaw > 360.0f)
	{
		yaw -= 360.0f;
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseZoom(int y_)
{
	if(y_ < 0 || y_ > 0)
	{
		position += static_cast<float>(y_) * (forward * zoomSpeed);
	}
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	glm::vec4 up4 = glm::rotate(roll, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(0, 1, 0, 0);
	up = glm::normalize(glm::vec3(up4.x,up4.y,up4.z));
	right = glm::normalize(glm::cross(forward, up));


	view = glm::lookAt(position, position + forward, up);
}
