#ifndef PLAYER_H
#define PLAYER_H

#include "mesh.h"
#include <iostream>

class Player : public Mesh {

	public:
		Player();
		Player(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc);

		void Move(GLfloat nx, GLfloat ny, GLfloat nz); // point form
		void Move(vec4 where); // vector form
		void Rotate(int axis, GLfloat theta);
		void Update();
		void ChangeGoal(GLfloat nx, GLfloat ny, GLfloat nz);
		void ChangeGoal(vec3 npos);
	private:
		GLfloat speed;

		GLuint index;
		GLint matrix_loc;

		GLfloat goal_x, goal_y, goal_z;
		GLfloat x, y, z;
		GLfloat r, g, b;
		mat4 ModelView;

		GLint colorLoc;
		GLint last_time;
		std::vector<vec4> Vertices;
		std::vector<vec2> UVs;
		std::vector<vec4> Normals;
};

#endif // PLAYER_H