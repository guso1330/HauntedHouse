#include "player.h"

Player::Player() {
	index = 0;
	x = y = z = 0.0;
	r = g = b = 1.0;
	goal_x = goal_y = goal_z = 0.0;
	speed = 0.003;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

Player::Player(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc) {
	// Default index is the start (0).
	index = nindex;
	matrix_loc = nmatrix_loc;
	colorLoc = ncolorLoc;
	InitMesh(filename);
	x = y = z = 0.0;
	r = g = b = 1.0;
	goal_x = goal_y = goal_z = 0.0;
	speed = 0.003;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

void Player::Move(GLfloat nx, GLfloat ny, GLfloat nz) {
	x = nx;
	y = ny;
	z = nz;
	ModelView = Translate(nx, ny, nz);
} // point form
void Player::Move(vec4 where) {
	return;
} // vector form
void Player::Rotate(int axis, GLfloat theta) {
	return;
}
void Player::Update() {
	
}
void Player::ChangeGoal(GLfloat nx, GLfloat ny, GLfloat nz) {
	return;
}
void Player::ChangeGoal(vec3 npos) {
	return;
}