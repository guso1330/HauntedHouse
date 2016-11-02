// Implementation file for the Mesh Class
#include "mesh.h"

// Default
Mesh::Mesh() {}

void Mesh::InitMesh(const char *filename) {
	load_obj(filename, Vertices, UVs, Normals);
	min_x = min_z = min_z = max_x = 0;
	Get2dBoundingBox();
}

// Parametric Constructor
Mesh::Mesh(const char *filename) {
	InitMesh(filename);
}

void Mesh::Get2dBoundingBox() {
	min_x = max_x = Vertices[0].x;
	min_z = max_z = Vertices[0].z;
	if(Vertices.size() > 1) {	
		for(std::vector<vec4>::iterator it=Vertices.begin()+1; it < Vertices.end(); ++it) {
			if((*it).x < min_x) { // get the smallest
				min_x = (*it).x;
			}
			if((*it).x > max_x) {
				max_x = (*it).x;
			}
			if((*it).z < min_z) { // get the smallest
				min_z = (*it).z;
			}
			if((*it).z > max_z) {
				max_z = (*it).z;
			}
		}
	}
	// cout << "min x, z: (" << min_x << ", " << min_z << ")" << endl;
	// cout << "max x, z: (" << max_x << ", " << max_z << ")" << endl;
	// cout << endl;
}