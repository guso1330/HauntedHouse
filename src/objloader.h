#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include "Angel.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <typeinfo>

using namespace std;

//******************************************************************
//                                                                  
//  Function:   load_obj
//                                                                  
//  Purpose:    Given a .obj file, this function loads in objects
//				by parsing the file and pulling its vertex and
//				normal information.                             
//                                                                  
//  Parameters: filename - the filename (location)
//				vertices - a vector to the hold the vertices of the obj
//				normals - a vector to hold the object normals
//				elements - the elements of the object
//
//	Adapted from: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
//******************************************************************
void load_obj(const char* filename, vector<vec4> &vertices, vector<vec2> &uvs, vector<vec4> &normals);

//******************************************************************
//                                                                  
//  Function:   split_str
//                                                                  
//  Purpose:    This function takes a string and a delimiter and splits
//				the string into sections then inserts them into a vector<string>
//                                                                  
//  Parameters: s - a string that is to be splitted
//				delim - is the the string delimiter
//				v - is the vector to place the elements
//
//******************************************************************
void split_str(const string &s, char* delim, vector<string> &v);

#endif