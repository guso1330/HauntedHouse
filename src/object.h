//******************************************************************* 
//                                                                    
//  Class:     Object - contains all of the static or computer
//						controlled entities for the game.
//                                                                     
//  Author:      Gus Oberdick
//  Email:       go125412@ohio.edu
//                                                                    
//                                                                    
//  Description: This class implements all of the movement, updating,
//				 and drawing of static or computer controlled entities.
// 				 Each entity also keeps track of it's own 2d maximally
//				 sized rectangle to detect for collision.
//                                                                    
//  Date:        October 31, 2016 3:41:00pm
//                                                                    
//*******************************************************************

#ifndef OBJECT_H
#define OBJECT_H

#include "mesh.h"
#include <iostream>

class Object : public Mesh {
	public:
		Object();
		Object(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc);

		void Move(GLfloat nx, GLfloat ny, GLfloat nz); // point form
		void MoveOnUpdate(GLfloat nx, GLfloat ny, GLfloat nz); // point form
		void Move(vec4 where); // vector form
		void Rotate(int axis, GLfloat theta);
		void ChangeGoal(GLfloat nx, GLfloat ny, GLfloat nz);
		void ChangeGoal(vec4 npos);
		void Update();
		void DrawSolid();
		void DrawWireframe();

		// Set Functions
		inline void SetSpeed(GLfloat nspeed) { speed = nspeed; }
		inline void SetModelView(mat4 m) { ModelView = m; };
		inline void SetColor(GLfloat nr, GLfloat ng, GLfloat nb) { r = nr; g = ng; b = nb; }
		inline void SetColorAlpha(GLfloat nr, GLfloat ng, GLfloat nb, GLfloat na) { r = nr; g = ng; b = nb; a = na; }

		// Get Functions
		inline vec4 GetPos() const { return vec4(x, y, z, 0.0); }
		inline vec4 GetGoal() const { return vec4(goal_x, goal_y, goal_z, 0.0); }
		inline GLuint GetIndex() const { return index; }
		inline GLfloat GetSpeed() const { return speed; }

	private:
		// GL Variables
		GLuint index;
		GLint matrix_loc;
		GLint colorLoc;
		mat4 ModelView;

		// Object Attributes
		GLfloat x, y, z;
		GLfloat r, g, b, a;
		GLfloat goal_x, goal_y, goal_z;
		GLfloat speed;
		GLint last_time;
};

#endif