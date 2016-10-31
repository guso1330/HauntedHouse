// Implementation file for the Mesh Class
#include "mesh.h"

// Default
Mesh::Mesh() {}

void Mesh::InitMesh(const char *filename) {
	load_obj(filename, Vertices, UVs, Normals);
}

// Parametric Constructor
Mesh::Mesh(const char *filename) {
	InitMesh(filename);
}