//******************************************************************* 
//                                                                    
//  Program:     Haunted House                                        
//                                                                     
//  Author:      Gus Oberdick
//  Email:       go125412@ohio.edu
//                                                                    
//                                                                    
//  Description: // Fill int                    
//                                                                    
//  Date:        October 31, 2016
//                                                                    
//*******************************************************************

// TO DO:
//	- Watch thebennybox - Intro to Modern OpenGL Tutorial #6: Camera and Perspective	
//		- There's also a guy name Jamie King who does good opengl tutorials
//

#include <iostream>
#include "Angel.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <typeinfo>

#include "src/objloader.h"
#include "src/mesh.h"
#include "src/camera.h"

using namespace std;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

//
// GLOBAL CONSTANTS
//

// OBJECTS IN SCENE
// Mesh Cube("models/cube.obj");
// Mesh Pipe("models/pipe.obj");

// Window dimension constants
int win_w = 1024;
int win_h = 768;

GLfloat incr =0.06;

// Array of rotation angles (in degrees) for each coordinate axis
enum {Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3};
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = {0.0, 0.0, 0.0};

vector<vec4> vertices;
vector<vec2> uvs;
vector<vec4> normals;

GLuint program;

GLuint loc;
GLint matrix_loc, projection_loc;

point4 at = vec4(0.0, 0.0, 0.0, 1.0);
point4 eye = vec4(0.0, 0.0, 2.0, 1.0);
vec4 up = vec4(0.0, 1.0, 0.0, 0.0);

GLfloat l= -2.0, r=2.0, top=2.0, bottom= -2.0, near= -100.0, far=100.0;

// Declaring the projection and model view
mat4 model_view;
mat4 projection;

// Initialize the camera
Camera camera(vec4(0.0f, 0.0f, -2.0f, 0.0f), 70.0f, (float)win_w/(float)win_h, 0.1f, 100.0f);
float camera_speed = 0.5f;

//
// CALLBACKS
//
extern "C" void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//  Generate tha model-view matrixn

	const vec3 viewer_pos(0.0, 0.0, 1.0);

	model_view = (Translate(-viewer_pos)*
				RotateX(Theta[Xaxis]) *
				RotateY(Theta[Yaxis]) *
				RotateZ(Theta[Zaxis]));

	projection = camera.GetViewProjection();
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, model_view);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

	
	// For wireframe rendering
	for(int i = 0; i<vertices.size(); i+=3) glDrawArrays(GL_LINE_LOOP, i, 3);
	// for(int i = 0; i<Pipe.GetVertices().size(); i+=3) glDrawArrays(GL_LINE_LOOP, i, 3);

	// For solid rendering
	// glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glutSwapBuffers();
}

extern "C" void key(unsigned char k, int nx, int ny) {
	switch (k) {
		case 'q':
		case 'Q': 
			exit(0);
			break;
		case 'w':
		case 'W':
			camera.MoveForward(camera_speed);
			break;
		case 's':
		case 'S':
			camera.MoveForward(-camera_speed);
			break;
		case 'd':
		case 'D':
			camera.MoveRight(-camera_speed);
			break;
		case 'a':
		case 'A':
			camera.MoveRight(camera_speed);
			break;
		case 'r':
			camera.Rotate(-5.0);
			break;
		case 'e':
			camera.Rotate(5.0);
			break;

		default:
			// Anything else.
			break;
	}
	// Something might have changed requiring redisplay
	glutPostRedisplay();
}

extern "C" void mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    switch(button) {
    case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
    case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
    case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
    }
  }
}
extern "C" void idle()
{
	static GLint time=glutGet(GLUT_ELAPSED_TIME);
	Theta[Axis] += incr*(glutGet(GLUT_ELAPSED_TIME)-time);
	time = glutGet(GLUT_ELAPSED_TIME);

	if (Theta[Axis] > 360.0) {
		Theta[Axis] -= 360.0;
	}

	glutPostRedisplay();
}

void GLUTinit() {	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(win_w, win_h);
	glutInitWindowPosition(20,20);

	glutCreateWindow("Haunted House");

	glClearColor(0.0, 0.0, 0.0, 1.0); // Clear screen to black

	/* CALLBACKS */
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc (mouse);

	// glutMotionFunc (motion);
	// glutPassiveMotionFunc (passivemotion);
	glutKeyboardFunc(key);
	// glutReshapeFunc (myReshape);
}

void init() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vec4), &vertices[0], GL_STATIC_DRAW);

	// glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	// glBufferData(GL_ARRAY_BUFFER, Pipe.GetVertices().size()*sizeof(vec4), &Pipe.GetVertices()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// get shader program
	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	loc = glGetAttribLocation(program, "vPosition");

	matrix_loc = glGetUniformLocation(program, "model_view");
	projection_loc = glGetUniformLocation(program, "projection");

	glClearColor(0.0, 0.0, 0.0, 1.0); // white background
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);

	load_obj("models/pipe.obj", vertices, uvs, normals);
	
	// Initializes the GLUT and callbacks 
	GLUTinit();

	glewInit();

	// Initializes the buffers and vao	
	init();

	glEnable(GL_DEPTH_TEST);

	glutMainLoop(); // enter event loop

	return (EXIT_SUCCESS);
}