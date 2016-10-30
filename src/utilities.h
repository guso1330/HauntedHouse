#ifndef UTILITIES_H
#define UTILITIES_H

#include "camera.h"
#include "mesh.h"
#include <vector>

float camera_speed = 0.5f;

void ControlCamera(Camera &camera, bool key[]) {
	if(key['w'] || key['W']) {
		camera.MoveForward(camera_speed);
	}
	if(key['s'] || key['S']) {
		camera.MoveForward(-camera_speed);
	}
	if(key['d'] || key['D']) {
		camera.MoveRight(-camera_speed);
	}
	if(key['a'] || key['A']) {
		camera.MoveRight(camera_speed);
	}
	if(key['l'] || key['L']) {
		camera.Rotate(-8.0);
	}
	if(key['k'] || key['K']) {
		camera.Rotate(8.0);
	}
}


void ControlPlayer(Mesh *object, bool key[]) {
	vec4 currentPos = object->GetPos();
	if(key['w'] || key['W']) {
		object->Move(currentPos.x, currentPos.y, currentPos.z += 1.0f);
	}
	if(key['s'] || key['S']) {
		object->Move(currentPos.x, currentPos.y, currentPos.z -= 1.0f);
	}
	if(key['d'] || key['D']) {
		object->Move(currentPos.x -= 1.0f, currentPos.y, currentPos.z);
	}
	if(key['a'] || key['A']) {
		object->Move(currentPos.x += 1.0f, currentPos.y, currentPos.z);
	}
	if(key['l'] || key['L']) {
		
	}
	if(key['k'] || key['K']) {
		
	}
}

void combineVec4Vectors(std::vector<vec4> &a, std::vector<vec4> b) {
	for(std::vector<vec4>::iterator it=b.begin(); it < b.end(); ++it) {
		a.push_back(*it);
	}
}

#endif
