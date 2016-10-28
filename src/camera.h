#ifndef CAMERA_H
#define CAMERA_H

#include "Angel.h"

struct Camera {
	public:
		Camera(const vec4 &pos, float fov, float aspect, float near, float far) {
			this->pos = pos;
			this->forward = vec4(0.0f, 0.0f, 1.0f, 0.0f);
			this->up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
			this->projection = Perspective(fov, aspect, near, far);
		}

		inline mat4 GetViewProjection() const {
			return projection * LookAt(pos, pos+forward, up);
		}

		void MoveForward(float amt)
		{
			pos += forward * amt;
		}

		void MoveRight(float amt)
		{
			pos += cross(up, forward) * amt;
		}

		// void Pitch(float angle)
		// {
		// 	vec3 right = normalize(cross(up, forward));

		// 	forward = vec3(normalize(rotate(angle, right) * vec4(forward, 0.0)));
		// 	up = normalize(cross(forward, right));
		// }

		void Rotate(float angle)
		{
			static const vec4 UP(0.0f, 1.0f, 0.0f, 0.0f);

			mat4 rotation = RotateY(angle);

			forward = vec4(normalize(rotation * forward));
			up = vec4(normalize(rotation * up));
		}

	private:
		mat4 projection;
		vec4 pos;
		vec4 forward;
		vec4 up;
};

#endif // CAMERA_H