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

	mouseSensitivity = 0.1f;
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

float Camera::GetNearPlane() const
{
	return nearPlane;
}

float Camera::GetFarPlane() const
{
	return farPlane;
}

glm::vec3 Camera::GetForward() const
{
	return forward;
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

/*
bool Camera::TestPointAgainstPlanes(glm::vec3 point_, glm::mat4 transform_)
{
	float test = leftPlane.x * point_.x + leftPlane.y * point_.y + leftPlane.z * point_.z + leftPlane.w;

	if (test < 0) { 
		return false; };

	test = rightPlane.x * point_.x + rightPlane.y * point_.y + rightPlane.z * point_.z + rightPlane.w;

	if (test < 0) { 
		return false; };

	test = bottomPlane.x * point_.x + bottomPlane.y * point_.y + bottomPlane.z * point_.z + bottomPlane.w;

	if (test < 0) { 
		return false; };

	test = upPlane.x * point_.x + upPlane.y * point_.y + upPlane.z * point_.z + upPlane.w;

	if (test < 0) { 
		return false; };

	test = nearFRPlane.x * point_.x + nearFRPlane.y * point_.y + nearFRPlane.z * point_.z + nearFRPlane.w;

	if (test < 0) { 
		return false; };

	test = farFRPlane.x * point_.x + farFRPlane.y * point_.y + farFRPlane.z * point_.z + farFRPlane.w;

	if (test < 0) { 
		return false; };

	return true;
}
*/


bool Camera::TestPointAgainstPlanes(glm::vec3 point_, glm::mat4 transform_)
{
	glm::vec4 tmpleftPlane = NormalizePlane(glm::transpose(glm::inverse(transform_)) * leftPlane);
	float test = tmpleftPlane.x * point_.x + tmpleftPlane.y * point_.y + tmpleftPlane.z * point_.z + tmpleftPlane.w;

	if (test < -0.05f) { 
		return false; };

	glm::vec4 tmprightPlane = NormalizePlane(glm::transpose(glm::inverse(transform_)) * rightPlane);
	test = tmprightPlane.x * point_.x + tmprightPlane.y * point_.y + tmprightPlane.z * point_.z + tmprightPlane.w;

	if (test < -0.05f) {
		return false; };

	glm::vec4 tmpbottomPlane = NormalizePlane(glm::transpose(glm::inverse(transform_)) * bottomPlane);
	test = tmpbottomPlane.x * point_.x + tmpbottomPlane.y * point_.y + tmpbottomPlane.z * point_.z + tmpbottomPlane.w;

	if (test < -0.05f) {
		return false; };

	glm::vec4 tmpupPlane = NormalizePlane(glm::transpose(glm::inverse(transform_)) * upPlane);
	test = tmpupPlane.x * point_.x + tmpupPlane.y * point_.y + tmpupPlane.z * point_.z + tmpupPlane.w;

	if (test < -0.05f) {
		return false; };

	glm::vec4 tmpnearFRPlane = NormalizePlane(glm::transpose(glm::inverse(transform_)) * nearFRPlane);
	test = tmpnearFRPlane.x * point_.x + tmpnearFRPlane.y * point_.y + tmpnearFRPlane.z * point_.z + tmpnearFRPlane.w;

	if (test < -0.05f) {
		return false; };

	glm::vec4 tmpfarFRPlane = NormalizePlane(glm::transpose(glm::inverse(transform_)) * farFRPlane);
	test = tmpfarFRPlane.x * point_.x + tmpfarFRPlane.y * point_.y + tmpfarFRPlane.z * point_.z + tmpfarFRPlane.w;

	if (test < -0.05f) {
		return false; };

	return true;
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

	glm::mat4 perspectiveView = perspective * view;
	leftPlane = NormalizePlane(glm::vec4(perspectiveView[0][3] + perspectiveView[0][0],
										 perspectiveView[1][3] + perspectiveView[1][0],
										 perspectiveView[2][3] + perspectiveView[2][0],
										 perspectiveView[3][3] + perspectiveView[3][0]));

	rightPlane = NormalizePlane(glm::vec4(perspectiveView[0][3] - perspectiveView[0][0],
										  perspectiveView[1][3] - perspectiveView[1][0],
										  perspectiveView[2][3] - perspectiveView[2][0],
										  perspectiveView[3][3] - perspectiveView[3][0]));

	bottomPlane = NormalizePlane(glm::vec4(perspectiveView[0][3] + perspectiveView[0][1],
										   perspectiveView[1][3] + perspectiveView[1][1],
										   perspectiveView[2][3] + perspectiveView[2][1],
										   perspectiveView[3][3] + perspectiveView[3][1]));

	upPlane = NormalizePlane(glm::vec4(perspectiveView[0][3] - perspectiveView[0][1],
									   perspectiveView[1][3] - perspectiveView[1][1],
									   perspectiveView[2][3] - perspectiveView[2][1],
									   perspectiveView[3][3] - perspectiveView[3][1]));

	nearFRPlane = NormalizePlane(glm::vec4(perspectiveView[0][3] + perspectiveView[0][2],
										   perspectiveView[1][3] + perspectiveView[1][2],
										   perspectiveView[2][3] + perspectiveView[2][2],
										   perspectiveView[3][3] + perspectiveView[3][2]));

	farFRPlane = NormalizePlane(glm::vec4(perspectiveView[0][3] - perspectiveView[0][2],
										  perspectiveView[1][3] - perspectiveView[1][2],
										  perspectiveView[2][3] - perspectiveView[2][2],
										  perspectiveView[3][3] - perspectiveView[3][2]));
}

glm::vec4 Camera::NormalizePlane(glm::vec4 plane_)
{
	glm::vec4 Result = plane_;
    
	float Distance = sqrtf(plane_.x * plane_.x + plane_.y * plane_.y + plane_.z * plane_.z);
	Result.x = plane_.x / Distance;
	Result.y = plane_.y / Distance;
	Result.z = plane_.z / Distance;
	Result.w = plane_.w / Distance;
	
	return Result;
}
