//******************************************************************* 
//                                                                    
//  File:     Utilities
//                                                                     
//  Author:      Gus Oberdick
//  Email:       go125412@ohio.edu
//                                                                    
//                                                                    
//  Description: Just random game logic functions.
//                                                                    
//  Date:        October 31, 2016 3:41:00pm
//                                                                    
//*******************************************************************

#ifndef UTILITIES_H
#define UTILITIES_H

#include "camera.h"
#include "mesh.h"
#include "player.h"
#include "object.h"
#include "Angel.h"
#include <vector>


void ControlCamera(Camera &camera, bool key[], float camera_speed, float camera_rotate_speed); // Controls the debug camera

bool CheckPlayerCollisions(Player* &a, Object* b); // Checks for collision between the player and any object
bool rangeInterset(float amin, float amax, float bmin, float bmax); // Used to detect the intersection of the player and other objects
																	// bounding boxes

void CheckCollisionsWithWalls(Player* &player, bool (&doorsclosed)[3], int &INROOM, bool &GHOSTSFLYING); // Checks for collisions
																										// between walls

void DrawDoors(Object* &door, bool (&doorsclosed)[3], bool HAVEKEY, int INROOM); // Draws all the doors and handles any coloring
void CheckToOpenDoors(Player* &player, bool (&doorsclosed)[3], bool HAVEKEY, int &INROOM); // Checks to see whether or not doors are opened

int incrementIndex(int &total, int incr); // Increment the index for the buffers
void combineVec4Vectors(std::vector<vec4> &a, std::vector<vec4> b); // Combine the vertices of meshes with the main vertices vector

#endif
