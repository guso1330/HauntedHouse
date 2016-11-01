#ifndef UTILITIES_H
#define UTILITIES_H

#include "camera.h"
#include "mesh.h"
#include "player.h"
#include "object.h"
#include "Angel.h"
#include <vector>

void ControlCamera(Camera &camera, bool key[], float camera_speed, float camera_rotate_speed);

void CheckCollisions(Player* &player, bool doorsclosed[6]);

void DrawDoors(Object* &door, bool doorsclosed[6]);
void CheckToOpenDoors(Player* &player, bool (&doorsclosed)[6]);

void combineVec4Vectors(std::vector<vec4> &a, std::vector<vec4> b);

#endif
