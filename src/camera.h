#ifndef CAMERA_H
#define CAMERA_H

#include "Angel.h"

struct Camera {
	public:
		Camera(const vec4 &pos, float fov, float aspect, float near, float far);

		mat4 GetViewProjection() const;
		void MoveForward(float amt);
		void MoveRight(float amt);
		void RotateYaw(float angle);
		void RotatePitch(float angle);
		void Rotate(float angle);
		void Update();

		inline void SetPos(vec4 npos) { pos = npos; }
		inline void SetDir(vec4 ndir) { dir = ndir; }
		inline void SetYaw(float angle) { yaw = angle; }
		inline void SetPitch(float angle) { pitch = angle; }
		inline void SetDirToForward() { dir = forward; }
		inline vec4 GetPos() { return pos; }
		inline vec4 GetDir() { return dir; }
		inline float GetYaw() { return yaw; }

	private:
		mat4 projection;
		vec4 pos;
		vec4 forward;
		vec4 up;

		vec4 dir;
		float yaw, pitch;
		float strafe_x, strafe_z; // Always gonna be 90 degrees to the direction vector
};

#endif // CAMERA_H