//******************************************************************* 
//                                                                    
//  Class:     Mesh - contains the vertex class
//                                                                     
//  Author:      Gus Oberdick
//  Email:       go125412@ohio.edu
//                                                                    
//                                                                    
//  Description: This class builds a simple mesh object that reads
//				 in vertices from a .obj file.
//                                                                    
//  Date:        October 27, 2016 3:41:00pm
//                                                                    
//*******************************************************************
#ifndef MESH_H
#define MESH_H

#include "Angel.h"
#include <iostream>
#include <vector>
#include "objloader.h"

class Mesh {
	public:
		// CONSTRUCTORs
		Mesh(); // default constructor
		Mesh(const char *filename); // Parametric constructor

		// Manipulator Functions
		void InitMesh(const char *filename);

		// Accessor functions
		inline vector<vec4> GetVertices() const { return Vertices; }
		inline unsigned int GetVerticesSize() const { return Vertices.size(); }

		// Virtual Functions
		virtual void DrawSolid() = 0;
		virtual void DrawWireframe() = 0;

		// Debug functions
		void PrintVertices() {
			for(size_t i=0; i<Vertices.size(); ++i) {
				cout << Vertices[i] << " ";
			}
			cout << endl;
		}

	protected:
		std::vector<vec4> Vertices;
		std::vector<vec2> UVs;
		std::vector<vec4> Normals;
};

// // Functions from square.h
// class Mesh {
// 	public:
// 		// CONSTRUCTORs
// 		Mesh(); // default constructor
// 		Mesh(const char *filename, GLuint nindex, GLint ncolorLoc, GLint nmatrix_loc); // Parametric constructor

// 		// Manipulator Functions
// 		void InitMesh(const char *filename);
// 		void DrawSolid();
// 		void DrawWireframe();
// 		virtual void Move(GLfloat nx, GLfloat ny, GLfloat nz); // point form
// 		virtual void Move(vec4 where); // vector form
// 		virtual void Rotate(int axis, GLfloat theta);
// 		virtual void Update();

// 		// Set Functions
// 		virtual void SetModelView(mat4 m);
// 		inline void SetSpeed(GLfloat nspeed) { speed = nspeed; }
// 		void SetColor(GLfloat nr, GLfloat ng, GLfloat nb) { r = nr; g = ng; b = nb; }
// 		void ChangeGoal(GLfloat nx, GLfloat ny, GLfloat nz);
// 		void ChangeGoal(vec3 npos);

// 		// Accessor functions
// 		inline vector<vec4> GetVertices() const { return Vertices; }
// 		inline unsigned int GetVerticesSize() const { return Vertices.size(); }
// 		inline vec3 GetPos() const { return vec3(x, y, z); }
// 		inline GLuint GetIndex() const { return index; }
// 		inline GLfloat GetSpeed() const { return speed; }

// 		// Debug functions
// 		void PrintVertices() {
// 			for(size_t i=0; i<Vertices.size(); ++i) {
// 				cout << Vertices[i] << " ";
// 			}
// 			cout << endl;
// 		}

// 	protected:
// 		// GLfloat speed;
// 		// GLfloat goal_x, goal_y, goal_z;
// 		// GLfloat x, y, z;
// 		// GLfloat r, g, b;

// 		GLuint index;
// 		GLint matrix_loc;
// 		GLint colorLoc;
		
// 		// GLint last_time;

// 		std::vector<vec4> Vertices;
// 		std::vector<vec2> UVs;
// 		std::vector<vec4> Normals;
// 		mat4 ModelView;

// 	private:
// };

#endif // MESH_H