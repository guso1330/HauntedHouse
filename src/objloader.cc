#include "objloader.h"

// split_str - Definition for the split_str function
void split_str(const string &s, char* delim, vector<string> &v) {
	// to avoid modifying original string
	// first duplicate the original string and return a char pointer then free the memory
	char *dup = strdup(s.c_str());
	char *token = strtok(dup, delim);
	while(token != NULL){
		v.push_back(string(token));
		// the call is treated as a subsequent calls to strtok:
		// the function continues from where it left in previous invocation
		token = strtok(NULL, delim);
	}
	free(dup);
}

// load_obj - Definition for the load_obj function
void load_obj(const char* filename, vector<vec4> &vertices, vector<vec2> &uvs, vector<vec4> &normals) {
	
	// Temporary storage
	std::vector<unsigned int> vertexIndices, uvIndices,normalIndices;
	vector<vec4> temp_vertices;
	vector<vec2> temp_uvs;
	vector<vec4> temp_normals;

	// create file variable
	ifstream in(filename, ios::in);
	if(!in) {
		cerr << "Cannot open " << filename <<endl;
		exit(EXIT_FAILURE);
	}

	string line; // variable to hold each line
	while(getline(in, line)) {
		if (line.length() > 3) { // make sure that the line is not empty

			// Get the object vertices
			if(line.substr(0, 2) == "v ") {
				istringstream s(line.substr(2));
				vec4 v; // Holds a temporary vertex
				s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f; // get the x, y, and z of the point
				temp_vertices.push_back(v); // add the vertex to the vertices vector
			}
			
			// Get the object vertex normals
			else if (line.substr(0, 3) == "vn ") {
				istringstream s(line.substr(3));
				vec4 n;
				s >> n.x; s >> n.y; s >> n.z; n.w = 0.0f; // get x, y, and z. Since it's a vector w = 0.0
				temp_normals.push_back(n);
			}

			// Get the UV's for the mesh
			else if (line.substr(0,3) == "vt ") {
				istringstream s(line.substr(3));
				vec2 u;
				s >> u.x; s >> u.y; // get the x and y coordinate for the uv
				temp_uvs.push_back(u);
			}
			// Get the faces and how they are made up
			else if (line.substr(0, 2) == "f ") {
				string s  = line.substr(2, line.length());
				vector<string> elems_1; // Will contain the strings after "f ", split by spaces (" ")
				char delim_1[2] = " ";
				char delim_2[2] = "/";
				split_str(s, delim_1, elems_1); // split the string by spaces (" ") and get results in elems_2
				for(size_t i=0; i<elems_1.size(); ++i) {
					// cout << "1: " << elems_1[i] << endl;
					vector<string> elems_2; // Will contain the split up numbers (ex/ 1/1/1 -> 1, 1, 1)
					split_str(elems_1[i], delim_2, elems_2); // split the separated strings by the "/" delimiter
															 // and place the results in elems_2
					// cout << "Elem2 size: " << elems_2.size() << endl << endl;
					for(size_t j=0; j<elems_2.size(); ++j) {
						int a  = atoi( elems_2[j].c_str() ) - 1; // convert the numbers into ints
						// cout << a << " ";
						if(j == 0) {
							vertexIndices.push_back(a);
						}
						else if(j == 1) {
							uvIndices.push_back(a);
						}
						else if(j == 2) {
							normalIndices.push_back(a);
						}
					}	
					// ++count;
				}
				// cout << endl;
			}
			else if(line[0] == '#') {
				// nothing
			}
			else {
				// nothing
			}
		} 
		else { // of the line is empty
			continue;
		}
	}
	// Output the vertices
	for(unsigned int i=0; i<vertexIndices.size(); ++i) {

		unsigned int vIndex = vertexIndices[i];
		unsigned int uIndex = uvIndices[i];
		unsigned int nIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		vec4 vertex = temp_vertices[ vIndex ];
		vec2 uv = temp_uvs[ uIndex ];
		vec4 normal = temp_normals[ nIndex ];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);
	}
}