#ifndef UTILITIES_H
#define UTILITIES_H

#include "camera.h"

// Function to control the camera
void CameraControls(unsigned char k, Camera &camera, float camera_speed) {
	if(k == 'w' || k == 'W') {
		camera.MoveForward(camera_speed);
	}
	if(k == 's' || k == 'S') {
		camera.MoveForward(-camera_speed);
	}
	if(k == 'd' || k == 'D') {
		camera.MoveRight(-camera_speed);
	}
	if(k == 'a' || k == 'A') {
		camera.MoveRight(camera_speed);
	}
	if(k == 'r' || k == 'R') {
		camera.Rotate(-5.0);
	}
	if(k == 'e' || k == 'E') {
		camera.Rotate(5.0);
	}
}

#endif
