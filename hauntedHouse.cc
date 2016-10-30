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
//	- Implement a transform class that will handle all rotation of meshes

#include <iostream>
#include "Angel.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <typeinfo>

#include "src/mesh.h"
#include "src/camera.h"
#include "src/utilities.h"

using namespace std;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

//
// GLOBAL CONSTANTS
//

// OBJECTS IN SCENE
Mesh *Cube;
Mesh *Pipe;
Mesh *Level;
Mesh *Door;

// Window dimension constants
int win_w = 1024;
int win_h = 768;

GLfloat incr =0.06;

// Array of rotation angles (in degrees) for each coordinate axis
enum {Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3};
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = {0.0, 0.0, 0.0};

// Global storage devices
vector<vec4> vertices;
vector<vec2> uvs;
vector<vec4> normals;

GLuint program;
GLuint loc;
GLint matrix_loc, projection_loc;

// Declaring the projection and model view
mat4 model_view;
mat4 projection;

// Initialize the camera
Camera camera(vec4(0.0f, 1.0f, -4.0f, 0.0f), 70.0f, (float)win_w/(float)win_h, 0.1f, 100.0f);
float camera_speed = 0.5f;
bool CameraThirdPersonOn = true;

//
// CALLBACKS
//
extern "C" void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Level->DrawWireframe();

	Door->DrawWireframe();

	// Send Camera data
	projection = camera.GetViewProjection();
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

	glutSwapBuffers();
}

extern "C" void key(unsigned char k, int nx, int ny) {
	switch (k) {
		case 27: // escape key
			exit(0);
			break;
		case 'l':
		case 'L':
			CameraThirdPersonOn = !CameraThirdPersonOn;
			cout << "CameraThirdPersonOn set to " << CameraThirdPersonOn;
			break;

		default:
			// Anything else.
			break;
	}

	if(CameraThirdPersonOn) {
		switch(k) {
			// Camera Forward
			case 'w':
			case 'W':
				camera.MoveForward(camera_speed);
				break;

			// Camera Backward
			case 's':
			case 'S':
				camera.MoveForward(-camera_speed);
				break;
			// Camera Right
			case 'd':
			case 'D':
				camera.MoveRight(-camera_speed);
				break;
			// Camera Left
			case 'a':
			case 'A':
				camera.MoveRight(camera_speed);
				break;
			// Camera Rotate right
			case 'e':
				camera.Rotate(-5.0);
				break;
			// Camera Rotate left
			case 'q':
				camera.Rotate(5.0);
				break;
			default:
				break;
		}
	}
	else {
		// Do nothing right now.
	}

	// CameraControls(k, camera, camera_speed);

	// Something might have changed requiring redisplay
	glutPostRedisplay();
}

extern "C" void mouse(int button, int state, int x, int y) {
  if (state == GLUT_DOWN) {
    switch(button) {
    case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
    case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
    case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
    }
  }
}

extern "C" void idle() {

	// Cube->Update();
	// Pipe->Update();

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

	GLint colorLoc;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// get shader program
	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	colorLoc  = glGetUniformLocation(program, "vcolor");
	if (colorLoc==-1) {
		std::cerr << "Unable to find colorLoc parameter" << std::endl;
	}

	loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	matrix_loc = glGetUniformLocation(program, "model_view");
	projection_loc = glGetUniformLocation(program, "projection");

	//
	// Build All Objects In Scene
	//
	Cube = new Mesh("models/cube.obj", 0, colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Cube->GetVertices());
	Cube->Move(-2.0, 0.0, 0.0);
	Cube->SetColor(1.0, 0.0, 0.0);

	Pipe = new Mesh("models/pipe.obj", Cube->GetVerticesSize(), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Pipe->GetVertices());
	Pipe->Move(0.0, 2.0, 0.0);
	Pipe->SetColor(0.0, 1.0, 0.0);

	Level = new Mesh("models/level.obj", Cube->GetVerticesSize()+Pipe->GetVerticesSize(), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Level->GetVertices());
	Level->Rotate(2, 180);

	Door = new Mesh("models/door.obj", Cube->GetVerticesSize()+Pipe->GetVerticesSize()+Level->GetVerticesSize(), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Door->GetVertices());
	Door->Move(0.0, 0.0, 20.0);
	Door->SetColor(1.0, 1.0, 0.0);

	cout << "Verts in vertices: " << vertices.size() << endl;

	glBufferData(GL_ARRAY_BUFFER, (vertices.size())*sizeof(vec4), &vertices[0], GL_STATIC_DRAW);

	glClearColor(0.0, 0.0, 0.0, 1.0); // white background
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	// Initializes the GLUT and callbacks 
	GLUTinit();
	glewInit();
	// Initializes the buffers and vao	
	init();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop(); // enter event loop
	return (EXIT_SUCCESS);
}