#include "object.h"

Object::Object() {
	index = 0;
	x = y = z = 0.0;
	goal_x = goal_y = goal_z = 0.0;
	r = g = b = a = 1.0;
	speed = 0.003;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

Object::Object(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc) {
	// Default index is the start (0).
	index = nindex;
	matrix_loc = nmatrix_loc;
	colorLoc = ncolorLoc;
	InitMesh(filename);
	x = y = z = 0.0;
	goal_x = goal_y = goal_z = 0.0;
	r = g = b = a = 1.0;
	speed = 0.003;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

void Object::Move(GLfloat nx, GLfloat ny, GLfloat nz) {
	x = nx;
	y = ny;
	z = nz;
	goal_x = x;
	goal_y = y;
	goal_z = z;
	ModelView = Translate(nx, ny, nz);
} // point form
void Object::Move(vec4 npos) {
	x = npos.x;
	y = npos.y;
	z = npos.z;
	goal_x = x;
	goal_y = y;
	goal_z = z;
	ModelView = Translate(x, y, z);
} // vector form

void Object::Rotate(int axis, GLfloat theta) {
	if(axis==1) {
		ModelView = RotateX(theta);
	}
	else if (axis==2) {
		ModelView = RotateY(theta);
	}
	else if (axis==3) {
		ModelView = RotateZ(theta);
	}
}
void Object::Update() {
	GLint time = glutGet(GLUT_ELAPSED_TIME);
	const GLfloat max_speed = speed; // pixels/msec max speed
	vec4 dir = vec4(goal_x - x, goal_y - y, goal_z - z, 0.0);
	if (length(dir) > 0.2) {
		dir = (time - last_time)*max_speed*normalize(dir);
		// Update location
		x += dir.x; y += dir.y; z += dir.z;
		Move(x, y, z);;
	} else {
		x = goal_x;
		y = goal_y;
		z = goal_z;
		ModelView = Translate(vec3(x, y, z));
	}
	
	last_time = time;
}

// Draw the mesh
void Object::DrawSolid()
{
	glUniform4f(colorLoc, r, g, b, a);
	// Setting the ModelView matrix
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, ModelView);
	glDrawArrays(GL_TRIANGLES, index, GetVerticesSize());
}

void Object::DrawWireframe() {
	glUniform4f(colorLoc, r, g, b, 1.0);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, ModelView);
	for(int i = index; i < index+GetVertices().size(); i+=3)
		glDrawArrays(GL_LINE_LOOP, i, 3);
}