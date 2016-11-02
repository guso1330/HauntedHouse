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
//	- Add game instructions at the beginning

#include <iostream>
#include "Angel.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <typeinfo>

#include "src/mesh.h"
#include "src/player.h"
#include "src/object.h"
#include "src/camera.h"
#include "src/utilities.h"

using namespace std;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

//
// GLOBAL CONSTANTS
//

// OBJECTS IN SCENE
Player *Cube;
Object *Pipe;
Object *Level;
Object *LevelFloor;
Object *Door;
Object *Key;
Object *Ghost1;
Object *Ghost2;
Object *Ghost3;

// Window dimension constants
int win_w = 1024;
int win_h = 768;

// Array for keyboard values
bool key[255];
float mouse_sensitivity = 0.4f;

// Array of rotation angles (in degrees) for each coordinate axis
enum {Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3};
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = {0.0, 0.0, 0.0};

//
//	Game State Variables
//
// Array of doors to check
bool Doors[3] = {true, true, true};
int INROOM = 1;
bool PLAYERALIVE = true;
bool HAVEKEY = false;
bool DOOR2LOCKED = true;
bool GHOSTSFLYING = false;
bool DOOR3OPEN = false;

// Global storage devices
vector<vec4> vertices;
int NUMVERTICES = 0;

GLuint program;
GLuint loc;
GLint matrix_loc, projection_loc;

// Declaring the projection and model view
mat4 model_view;
mat4 projection;

// Initialize the camera
vec4 cam_start_pos = vec4(0.0f, 1.0f, 2.0f, 0.0f);
Camera camera(cam_start_pos, 70.0f, (float)win_w/(float)win_h, 0.2f, 100.0f);
Camera FPScam;
float camera_speed = 0.5;
float camera_rotate_speed = M_PI/180*0.2;
bool CameraDebugMode = false;
bool CameraFPSMode = true;

//
// CALLBACKS
//
extern "C" void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the Player Cube
	Cube->DrawSolid();

	// Draw the Level
	Level->DrawSolid();
	LevelFloor->DrawSolid();

	// Draw the key for the first door
	if(HAVEKEY == false)
		Key->DrawSolid();

	// Drawing all doors
	DrawDoors(Door, Doors, HAVEKEY, INROOM);

	//
	// Check the game states
	//
	if(INROOM == 1) {
		CheckCollisionsWithWalls(Cube, Doors, INROOM, GHOSTSFLYING);
	}
	else if(INROOM == 2 && !HAVEKEY) {
		CheckCollisionsWithWalls(Cube, Doors, INROOM, GHOSTSFLYING);
		HAVEKEY = CheckPlayerCollisions(Cube, Key);
		if(HAVEKEY == true) {
			cout << "You collected the key!" << endl;
		}
	}
	else if(INROOM == 3 || HAVEKEY) {
		// GHOSTSFLYING = true;
		CheckCollisionsWithWalls(Cube, Doors, INROOM, GHOSTSFLYING);
		if(GHOSTSFLYING) {
			Ghost1->DrawWireframe();
			Ghost1->SetSpeed(0.003);
			Ghost2->DrawWireframe();
			Ghost2->SetSpeed(0.003);
			Ghost3->DrawWireframe();
			Ghost3->SetSpeed(0.003);
			Ghost1->ChangeGoal(4.0, 1.0, 46.0);
			Ghost2->ChangeGoal(4.0, 1.0, 52.0);
			Ghost3->ChangeGoal(4.0, 1.0, 58.0);
			if((CheckPlayerCollisions(Cube, Ghost1)) || (CheckPlayerCollisions(Cube, Ghost2)) || (CheckPlayerCollisions(Cube, Ghost3))) {
				cout << "YOU LOOSSSSEEEEEE" << endl;
				exit(0);
			}
			else if (Ghost1->GetPos() == Ghost1->GetGoal() && Ghost2->GetPos() == Ghost2->GetGoal() && Ghost3->GetPos() == Ghost3->GetGoal()) {
				// cout << "Door 3 unlocked" << endl;
				GHOSTSFLYING = false;
				Doors[2] = false;
				HAVEKEY = false;
				INROOM = 4;
			}
		}
	}
	else if(INROOM == 4) {
		CheckCollisionsWithWalls(Cube, Doors, INROOM, GHOSTSFLYING);
	}

	// Handle the different camera modes
	//
	// set camera position to behind the cube
	if(CameraDebugMode) {
		ControlCamera(camera, key, camera_speed, camera_rotate_speed);
		camera.Update();
		// camera.PrintDir();
		// Send Camera data
		projection = camera.GetViewProjection();
		glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
	}
	else if(CameraFPSMode) {
		Cube->UpdatePlayer(key);
		// cout << "x, z: " << Cube->GetPos().x << ", " << Cube->GetPos().z << endl;
		FPScam.Update();
		projection = Cube->GetCamera().GetViewProjection();
		glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
	}
	
	glutSwapBuffers();
}

extern "C" void keyDown(unsigned char k, int nx, int ny) {
	vec4 CubePos = Cube->GetPos();
	switch (k) {
		case 27: // escape key
			exit(0);
			break;
		case 't':
		case 'T':
			CameraFPSMode = false;
			CameraDebugMode = !CameraDebugMode;
			cout << "CameraDebugMode set to " << CameraDebugMode << endl;
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(win_w/2, win_h/2);
			break;
		case 'y':
		case 'Y':
			CameraDebugMode = false;
			CameraFPSMode = !CameraFPSMode;
			cout << "CameraFPSMode set to " << CameraFPSMode << endl;
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(win_w/2, win_h/2);
		case 'e':
			CheckToOpenDoors(Cube, Doors, HAVEKEY, INROOM);
		default:
			// Anything else.
			break;
	}

	key[k] = true;

	// Something might have changed requiring redisplay
	glutPostRedisplay();
}

extern "C" void keyUp(unsigned char k, int x, int y) {
	key[k] = false;
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

	Door->Update();
	Ghost1->Update();
	Ghost2->Update();
	Ghost3->Update();

	glutPostRedisplay();
}

extern "C" void motion(int x, int y) {
	static bool just_warped = false;

	// cout << x << ", " << y << endl;

	if(just_warped) {
		just_warped = false;
		return;
	}

	int dx = x - win_w/2;
	int dy = y - win_h/2;

	if(CameraDebugMode) {
		if(dx) { // get rotation in the x direction
			camera.RotateYaw((-camera_rotate_speed*dx) * mouse_sensitivity);
		}
		if(dy) {
			camera.RotatePitch((-camera_rotate_speed*dy) * mouse_sensitivity);
		}

		glutWarpPointer(win_w/2, win_h/2);

		just_warped = true;
	}
	else if(CameraFPSMode) {
		if(dx) {
			Cube->RotateYaw((-camera_rotate_speed*dx)*mouse_sensitivity);
			FPScam.RotateYaw((-camera_rotate_speed*dx)*mouse_sensitivity);
		}

		glutWarpPointer(win_w/2, win_h/2);

		just_warped = true;
	}
}

void GLUTinit() {
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(win_w, win_h);
	glutInitWindowPosition(20,20);
	glutCreateWindow("Haunted House");
	glClearColor(0.0, 0.0, 0.0, 1.0); // Clear screen to black

	/* CALLBACKS */
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
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
	// build the player cube
	Cube = new Player("models/cube.obj", NUMVERTICES, colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Cube->GetVertices());
	Cube->Move(0.0, 0.5, 5.0);
	Cube->SetColor(1.0, 0.0, 0.0);

	
	// Pipe = new Object("models/cube.obj", incrementIndex(NUMVERTICES, Cube->GetVerticesSize()), colorLoc, matrix_loc);
	// combineVec4Vectors(vertices, Pipe->GetVertices());
	// Pipe->Move(0.0, 0.5, 26.0);
	// Pipe->SetColor(0.0, 1.0, 0.0);

	// build the level walls
	Level = new Object("models/level2.obj", incrementIndex(NUMVERTICES, Cube->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Level->GetVertices());
	Level->SetColor((75.0/255.0), (18.0/255.0), (18.0/255.0));

	// build the level's floor
	LevelFloor = new Object("models/level_floor2.obj", incrementIndex(NUMVERTICES, Level->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, LevelFloor->GetVertices());
	LevelFloor->SetColor((22.0/255.0), (55.0/255.0), (21.0/255.0));
	
	// build the door object
	Door = new Object("models/door.obj", incrementIndex(NUMVERTICES, LevelFloor->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Door->GetVertices());
	Door->Rotate(2, 180);
	Door->SetColor((114.0/255.0), (48.0/255.0), (24.0/255.0));

	// build the key object
	Key  = new Object("models/key.obj", incrementIndex(NUMVERTICES, Door->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Key->GetVertices());
	Key->Move(14.0, 0.5, 38.0);
	Key->SetColor(1.0, 9.0, 0.0);

	// Build the ghosts
	Ghost1 = new Object("models/ghost.obj", incrementIndex(NUMVERTICES, Key->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Ghost1->GetVertices());
	Ghost2 = new Object("models/ghost.obj", incrementIndex(NUMVERTICES, Ghost1->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Ghost2->GetVertices());
	Ghost3 = new Object("models/ghost.obj", incrementIndex(NUMVERTICES, Ghost2->GetVerticesSize()), colorLoc, matrix_loc);
	combineVec4Vectors(vertices, Ghost3->GetVertices());
	Ghost1->Move(-22.0, 1.0, 46.0);
	Ghost2->Move(-25.0, 1.0, 52.0);
	Ghost3->Move(-19.0, 1.0, 56.0);

	cout << "Welcome to my 'Haunted House'" << endl << endl;
	cout << "W, A, S, D to move and mouse to look around. E to open doors." << endl;
	cout << "T to switch to the debug camera, and Y to switch back to player view" << endl << endl;
	cout << "Press ESC to quit." << endl;
	cout << "Enjoy!" << endl;

	FPScam = Cube->GetCamera();

	glBufferData(GL_ARRAY_BUFFER, (vertices.size())*sizeof(vec4), &vertices[0], GL_STATIC_DRAW);

	glClearDepth(1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0); // white background
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	// Initializes the GLUT and callbacks 
	GLUTinit();
	glewInit();
	// Initializes the buffers and vao	
	init();
	glutMainLoop(); // enter event loop
	return (EXIT_SUCCESS);
}