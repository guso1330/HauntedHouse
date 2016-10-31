#include "player.h"

Player::Player() {
	index = 0;
	x = y = z = 0.0;
	r = g = b = 1.0;
	speed = 0.00005;
	pos = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	forward = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
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
	forward = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	r = g = b = 1.0;
	speed = 0.00005;
	ModelView = mat4();
	last_time=glutGet(GLUT_ELAPSED_TIME);
}

void Player::Move(GLfloat nx, GLfloat ny, GLfloat nz) {
	x = nx, y = ny, z = nz; // Set the new positions
	pos = vec4(x, y, z, 0.0);
	ModelView = Translate(pos);
} // point form
void Player::Move(vec4 npos) {
	x = npos.x, y = npos.y, z = npos.z; // Set the new positions
	pos = npos;
	ModelView = Translate(pos);
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
	pos += forward * amt * ((time - last_time)/15);
	ModelView = Translate(pos);
}

void Player::MoveX(float amt, GLint time, GLint last_time) {
	pos += cross(up, forward) * amt * ((time - last_time)/15);
	ModelView = Translate(pos);
}

void Player::MoveRotate(float angle)
{
	// static const vec4 UP(0.0f, 1.0f, 0.0f, 0.0f);

	// mat4 rotation = RotateY(angle);

	// forward = vec4(normalize(rotation * forward));
	// up = vec4(normalize(rotation * up));

	// ModelView = Translate(pos) * RotateY(angle);
}

void Player::UpdatePlayer(bool key[]) {
	GLint time = glutGet(GLUT_ELAPSED_TIME);

	if(key['w'] || key['W']) {
		// cout << "key w" << endl;
		MoveZ(0.15, time, last_time);
	}
	if(key['s'] || key['S']) {
		// cout << "key s" << endl;
		MoveZ(-0.15, time, last_time);
	}
	if(key['d'] || key['D']) {
		// cout << "key d" << endl;
		MoveX(-0.1, time, last_time);
	}
	if(key['a'] || key['A']) {
		// cout << "key a" << endl;
		MoveX(0.1, time, last_time);
	}
	// if(key['l'] || key['L']) {
	// 	MoveRotate(-5.0);
	// }
	// if(key['k'] || key['K']) {
	// 	MoveRotate(5.0);		
	// }
	
	last_time = time;
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