#include "camera.h"
// #include <math.h>
#include <iostream>

Camera::Camera(const vec4 &pos, float fov, float aspect, float near, float far) {
	this->pos = pos;
	this->forward = this->dir = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	this->up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	this->projection = Perspective(fov, aspect, near, far);
	yaw = pitch = 0.0;
}

mat4 Camera::GetViewProjection() const { 
	return projection * LookAt(pos, pos+dir, up);
}

void Camera::MoveForward(float amt) {
	float lx = sin(yaw)*cos(pitch);
	float ly = sin(pitch);
	float lz = cos(yaw)*cos(pitch);

	// std::cout << lx << " " << " " << ly << " " << lz << std::endl;

	pos.x = pos.x + amt*lx;
	pos.y = pos.y + amt*ly;
	pos.z = pos.z + amt*lz;

	Update();
}

void Camera::MoveRight(float amt) {
	pos += cross(up, dir) * amt;
	Update();
}

void Camera::RotateYaw(float angle) // Incremental rotate
{
	yaw += angle;

	Update();
}

void Camera::Rotate(float angle) { // General rotate
	static const vec4 UP(0.0f, 1.0f, 0.0f, 0.0f);

	mat4 rotation = RotateY(angle);

	forward = vec4(normalize(rotation * forward));
	up = vec4(normalize(rotation * up));
}

void Camera::Update() {
	dir.x = sin(yaw) * cos(pitch);
	dir.y = sin(pitch);
	dir.z = cos(yaw) * cos(pitch);

	strafe_x = cos(yaw - M_PI_2);
	strafe_z = sin(yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	LookAt(pos, pos+dir, up);
}