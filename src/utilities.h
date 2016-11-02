#ifndef UTILITIES_H
#define UTILITIES_H

#include "camera.h"
#include "mesh.h"
#include "player.h"
#include "object.h"
#include "Angel.h"
#include <vector>


void ControlCamera(Camera &camera, bool key[], float camera_speed, float camera_rotate_speed);

bool CheckPlayerCollisions(Player* &a, Object* b);
bool rangeInterset(float amin, float amax, float bmin, float bmax);

void CheckCollisionsWithWalls(Player* &player, bool (&doorsclosed)[3], int &INROOM, bool &GHOSTSFLYING);

void DrawDoors(Object* &door, bool (&doorsclosed)[3], bool HAVEKEY, int INROOM);
void CheckToOpenDoors(Player* &player, bool (&doorsclosed)[3], bool HAVEKEY, int &INROOM);

int incrementIndex(int &total, int incr);
void combineVec4Vectors(std::vector<vec4> &a, std::vector<vec4> b);

#endif
