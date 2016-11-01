#ifndef PLAYER_H
#define PLAYER_H

#include "mesh.h"
#include "camera.h"
#include <iostream>

class Player : public Mesh {

	public:
		Player();
		Player(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc);

		void Move(GLfloat nx, GLfloat ny, GLfloat nz); // point form
		void Move(vec4 npos); // vector form
		void Rotate(int axis, GLfloat theta);
		void MoveZ(float amt, GLint time, GLint last_time);
		void MoveX(float amt, GLint time, GLint last_time);
		void RotateYaw(float angle);
		void UpdatePlayer(bool key[]);
		void Update();
		void DrawSolid();
		void DrawWireframe();

		// Set Functions
		inline void SetSpeed(GLfloat nspeed) { speed = nspeed; }
		inline void SetModelView(mat4 m) { ModelView = m; };
		inline void SetColor(GLfloat nr, GLfloat ng, GLfloat nb) { r = nr; g = ng; b = nb; }

		// Get Functions
		inline vec4 GetPos() const { return pos; }
		inline GLuint GetIndex() const { return index; }
		inline GLfloat GetSpeed() const { return speed; }
		inline Camera GetCamera() const { return MyCamera; }

		// Debug Functions
		void PrintModelView();
		void PrintDir();

	private:
		// GL Variables
		GLuint index;
		GLint matrix_loc;
		GLint colorLoc;
		mat4 ModelView;

		Camera MyCamera;

		// Object Attributes
		GLfloat x, y, z;
		vec4 pos;
		vec4 dir; // The direction that the cube is facing
		GLfloat r, g, b;
		GLfloat speed;
		GLint last_time;

		vec4 forward;
		vec4 up;

		float yaw, pitch;
};

#endif // PLAYER_H