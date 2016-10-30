// Implementation file for the Mesh Class
#include "mesh.h"

// Default
Mesh::Mesh() {
	index = 0;
	r = g = b = x = y = z = 0.0;
	goal_x = goal_y = goal_z = 0.0;
	speed = 0.003;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

void Mesh::InitMesh(const char *filename) {
	load_obj(filename, Vertices, UVs, Normals);
}

// Parametric Constructor
Mesh::Mesh(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc) {
	// Default index is the start (0).
	index = nindex;
	matrix_loc = nmatrix_loc;
	colorLoc = ncolorLoc;
	InitMesh(filename);
	r = g = b = x = y = z = 0.0;
	goal_x = goal_y = goal_z = 0.0;
	speed = 0.003;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

// Draw the mesh
void Mesh::DrawSolid()
{
	glUniform4f(colorLoc, r, g, b, 1.0);
	// Setting the ModelView matrix
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, ModelView);
	glDrawArrays(GL_TRIANGLES, index, GetVerticesSize());
}

void Mesh::DrawWireframe() {
	glUniform4f(colorLoc, r, g, b, 1.0);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, ModelView);
	for(int i = index; i < GetVertices().size(); i+=3)
		glDrawArrays(GL_LINE_LOOP, i, 3);
}

void Mesh::Move(GLfloat nx, GLfloat ny, GLfloat nz) {
	x = nx;
	y = ny;
	z = nz;
	ModelView = Translate(nx, ny, nz);
}

void Mesh::Move(vec4 where) {
	x = where.x;
	y = where.y;
	z = where.z;
	ModelView = Translate(where);
}

void Mesh::Rotate(int axis, GLfloat theta) {
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

void Mesh::Update()
{

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
		ModelView = (Translate(vec3(x, y, z)));
	}
	last_time = time;
}


// Change goal location for mesh
void Mesh::ChangeGoal(GLfloat nx, GLfloat ny, GLfloat nz) {
  goal_x = nx;
  goal_y = ny;
  goal_z = nz;
}

// Change goal location for Mesh
void Mesh::ChangeGoal(vec3 npos) {
  goal_x = npos.x;
  goal_y = npos.y;
  goal_z = npos.z;
}

void Mesh::SetModelView(mat4 m) {
	ModelView = m;
}