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

#include <iostream>
#include "Angel.h"
#include <vector>
#include "objloader.h"

//******************************************************************* 
//                                                                    
//  Struct:      Vertex struct
//                                                                     
//  Author:      Gus Oberdick
//  Email:       go125412@ohio.edu
//                                                                    
//                                                                    
//  Description: This class allows each vertex to store it's own
//				 position, texture coordinate, and normal
//                                                                    
//  Date:        October 27, 2016 3:41:00pm
//                                                                    
//*******************************************************************

// ENUM to store the different buffer positions
enum MeshBufferPositions {
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB
};

class Mesh {
	public:
		// Simple constructor that will read in variable
		Mesh(const char* filename);

		// void Draw();
		virtual ~Mesh();

		std::vector<vec4> GetVertices() { return Vertices; }
		std::vector<vec2> GetUVs() { return UVs; }
		std::vector<vec4> GetNormals() { return Normals; }

	private:
		//
		// Private Methods
		//
	    void InitMesh();
		// Equality operator
		void operator=(const Mesh& mesh) {}
		// Copy Constructor
		Mesh(const Mesh& mesh) {}
		
		//
		// Private Variables
		//
		std::vector<vec4> Vertices;
		std::vector<vec2> UVs;
		std::vector<vec4> Normals;

		static const unsigned int NUM_BUFFERS = 3; // Instantiate how many buffers we'll be using
		GLuint MyVAO;
		GLuint MyVertexArrayBuffers[NUM_BUFFERS];
		unsigned int MyNumIndices;
};

#endif // MESH_H