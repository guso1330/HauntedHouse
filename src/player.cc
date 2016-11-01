#include "player.h"

Player::Player() {
	index = 0;
	x = y = z = 0.0;
	r = g = b = 1.0;
	speed = 0.00005;
	pos = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	forward = dir = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	yaw = pitch = 0.0f;

	MyCamera.SetPos(pos + vec4(0.0, 1.0, 0.0, 0.0));

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
	pos = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	forward = dir = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	yaw = pitch = 0.0f;

	MyCamera.SetPos(pos + vec4(0.0, 1.0, 0.0, 0.0));

	r = g = b = 1.0;
	speed = 0.00005;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

void Player::Move(GLfloat nx, GLfloat ny, GLfloat nz) {
	x = nx, y = ny, z = nz; // Set the new positions
	pos = vec4(x, y, z, 0.0);
	ModelView = Translate(pos);
	Update();
} // point form
void Player::Move(vec4 npos) {
	x = npos.x, y = npos.y, z = npos.z; // Set the new positions
	pos = npos;
	ModelView = Translate(pos);
	Update();
} // vector form

void Player::Rotate(int axis, GLfloat theta) {
	if(axis==1) {
		ModelView = Translate(pos) * RotateX(theta);
	}
	else if (axis==2) {
		ModelView = Translate(pos) * RotateY(theta);
	}
	else if (axis==3) {
		ModelView = Translate(pos) * RotateZ(theta);
	}
}
void Player::MoveZ(float amt, GLint time, GLint last_time) {
	float lx = sin(yaw)*cos(pitch);
	float ly = sin(pitch);
	float lz = cos(yaw)*cos(pitch);

	pos.x = pos.x + amt*lx;
	pos.y = pos.y + amt*ly;
	pos.z = pos.z + amt*lz;

	pos += dir * amt * ((time - last_time)/15);
	Update();
	ModelView = Translate(pos);
}

void Player::MoveX(float amt, GLint time, GLint last_time) {
	pos += cross(up, dir) * amt * ((time - last_time)/15);
	Update();
}

void Player::RotateYaw(float angle)
{
	yaw += angle;

	ModelView = Translate(pos) * RotateY(yaw);

	Update();
}

void Player::RotatePitch(float angle) {
	const float limit = 80 * M_PI / 180.0;

	pitch += angle;

	if(pitch < -limit)
		pitch = -limit;

	if(pitch > limit)
		pitch = limit;

	Update();
}

void Player::UpdatePlayer(bool key[]) {
	GLint time = glutGet(GLUT_ELAPSED_TIME);

	if(key['w'] || key['W']) {
		// cout << "key w" << endl;
		MoveZ(0.12, time, last_time);
	}
	if(key['s'] || key['S']) {
		// cout << "key s" << endl;
		MoveZ(-0.12, time, last_time);
	}
	if(key['d'] || key['D']) {
		// cout << "key d" << endl;
		MoveX(-0.1, time, last_time);
	}
	if(key['a'] || key['A']) {
		// cout << "key a" << endl;
		MoveX(0.1, time, last_time);
	}

	Update();
	
	last_time = time;
}

void Player::Update() {

	dir.x = sin(yaw) * cos(pitch);
	dir.y = 0.0;
	dir.z = cos(yaw) * cos(pitch);

	MyCamera.SetPos(pos + vec4(0.0, 0.5, 0.0, 0.0));
	MyCamera.SetDir(dir);
	MyCamera.SetYaw(yaw);
}

// Draw the mesh
void Player::DrawSolid()
{
	glUniform4f(colorLoc, r, g, b, 1.0);
	// Setting the ModelView matrix
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, ModelView);
	glDrawArrays(GL_TRIANGLES, index, GetVerticesSize());
}

void Player::DrawWireframe() {
	glUniform4f(colorLoc, r, g, b, 1.0);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, ModelView);
	for(int i = index; i < index+GetVertices().size(); i+=3)
		glDrawArrays(GL_LINE_LOOP, i, 3);
}

void Player::PrintModelView() {
	for(int i=0; i < 4; ++i) {
		for (int j=0; j<4; ++j) {
			cout << ModelView[i][j] <<  " ";
		}
		cout << endl;
	}
}

void Player::PrintDir() {
	cout << "Dir: " << dir.x << ", " << dir.y << ", " << dir.z << endl;
}