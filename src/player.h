//******************************************************************* 
//                                                                    
//  Class:     Player - is the user controlled entity
//                                                                     
//  Author:      Gus Oberdick
//  Email:       go125412@ohio.edu
//                                                                    
//                                                                    
//  Description: This class controls all user controlled entities.
// 				 It allows for controlled movement. It also implements
//				 it's own FPS style camera.
//                                                                    
//  Date:        October 31, 2016 3:41:00pm
//                                                                    
//*******************************************************************

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
		void Rotate(int axis, GLfloat theta); // Rotates the player
		void MoveZ(float amt, GLint time, GLint last_time); // Moves the player incrementally so that it can be updated
		void MoveX(float amt, GLint time, GLint last_time); // Moves the player incrementally so that it can be updated
		void RotateYaw(float angle); // doens't work properly
		void RotatePitch(float angle); // doesn't work properly
		void UpdatePlayer(bool key[]); // Updates the player based on defined controls
		void Update(); // Updates player position and direction
		void DrawSolid(); // Draws the shape in solid mode
		void DrawWireframe(); // draws the shape in wireframe mode

		// Set Functions
		inline void SetSpeed(GLfloat nspeed) { speed = nspeed; }
		inline void SetModelView(mat4 m) { ModelView = m; };
		inline void SetColor(GLfloat nr, GLfloat ng, GLfloat nb) { r = nr; g = ng; b = nb; }
		inline void SetPos(vec4 npos) { pos = npos; }

		// Get Functions
		inline vec4 GetPos() const { return pos; }
		inline GLuint GetIndex() const { return index; }
		inline GLfloat GetSpeed() const { return speed; }
		inline Camera GetCamera() const { return MyCamera; }
		inline vec4 GetDir() const { return dir; }
		inline vec4 GetKeyDir() const { return keydir; }

		// Debug Functions
		void PrintModelView();
		void PrintDir();
		void PrintPos() {
			std::cout << pos.x << ", " << pos.z << endl;
		}

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
		vec4 keydir;
		GLfloat r, g, b;
		GLfloat speed;
		GLint last_time;

		vec4 forward;
		vec4 up;

		float yaw, pitch;
};

#endif // PLAYER_H