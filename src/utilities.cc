#include "utilities.h"
#include "cmath"

void ControlCamera(Camera &camera, bool key[], float camera_speed, float camera_rotate_speed) {
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
}

void CheckCollisions(Player* &player, bool doorsclosed[6]) {
	vec4 pos = player->GetPos();

	cout << pos.x << " " << pos.z << endl;

	// Room1 Collisions
	if(pos.z < 20) {
		if(pos.x < -1.5) {
			player->SetPos(vec4(-1.5, pos.y, pos.z, pos.w)); // left
		}
		if(pos.x > 1.5) {
			player->SetPos(vec4(1.5, pos.y, pos.z, pos.w)); // right
		}
		if(pos.z <= 0.7) {
			player->SetPos(vec4(pos.x, pos.y, 0.8, pos.w)); // bottom
		}
		if(doorsclosed[0] && pos.z >= 19.2) {
			player->SetPos(vec4(pos.x, pos.y, 18.5, pos.w)); // top
		}
	}
	// Room2 Collisions
	if(pos.z < 36.0) {
		if(pos.x < -17.0) { // left wall
			player->SetPos(vec4(-17.0, pos.y, pos.z, pos.w));
		}
		if(pos.x > 12.5) { // right wall
			player->SetPos(vec4(12.0, pos.y, pos.z, pos.w));
		}
		if(pos.z <= 20.0 && pos.x > 1.7 && doorsclosed[0] == false) { // back wall to the right
			player->SetPos(vec4(pos.x, pos.y, 20.1, pos.w));
		}
		if(pos.z <= 20.0 && pos.x < -1.7 && doorsclosed[0] == false) { // back wall to the left
			player->SetPos(vec4(pos.x, pos.y, 20.1, pos.w));
		}
		if(pos.z >= 35.3 && pos.x > 5.0 && doorsclosed[1]) { // Door is closed to right most top wall section
			player->SetPos(vec4(pos.x, pos.y, 35.1, pos.w));
		}
		if(pos.z >= 35.3 && pos.x > 9.1 && !doorsclosed[1]) { // Door 2 is open and right section
			player->SetPos(vec4(pos.x, pos.y, 35.1, pos.w));
		}
		if(pos.z >= 35.4 && pos.x <= 5.0 && pos.x >= -9.0) { // top wall entire section between doors
			player->SetPos(vec4(pos.x, pos.y, 35.1, pos.w));
		}
		if(pos.z >= 35.3 && pos.x < -9.0 && pos.x > -17.5 && doorsclosed[2]) { // Door 3 to the left most top wall section
			player->SetPos(vec4(pos.x, pos.y, 35.1, pos.w));
		}
		if(pos.z >= 35.3 && pos.x < -13.0 && !doorsclosed[2]) {
			player->SetPos(vec4(pos.x, pos.y, 35.1, pos.w));
		}
	}
}

void combineVec4Vectors(std::vector<vec4> &a, std::vector<vec4> b) {
	for(std::vector<vec4>::iterator it=b.begin(); it < b.end(); ++it) {
		a.push_back(*it);
	}
}

void DrawDoors(Object* &door, bool doorsclosed[6]) {
	if(doorsclosed[0]) {
		door->Move(0.0, 0.0, 20.0);
		door->DrawSolid(); // door 1
	}
	if(doorsclosed[1]) {
		door->Move(7.0, 0.0, 36.0);
		door->DrawSolid(); // door 2
	}
	if(doorsclosed[2]) {
		door->Move(-11.0, 0.0, 36.0); // door 3
		door->DrawSolid();
	}
	if(doorsclosed[3]) {
		door->Move(-11.0, 0.0, 46.0); // door 4
		door->DrawSolid();
	}
	if(doorsclosed[4]) {
		door->Move(-11.0, 0.0, 70.0); // door 5
		door->DrawSolid();
	}
	if(doorsclosed[5]) {
		door->Move(0.0, 0.0, 94.0); // door 6
		door->DrawSolid();
	}
}

void CheckToOpenDoors(Player* &player, bool (&doorsclosed)[6]) {
	vec4 pos = player->GetPos();
	if(pos.z >= 17.0 && doorsclosed[0]) { // Open door
		cout << "Door 1 unlocked" << endl;
		doorsclosed[0] = false;
	}
	if(pos.x <= 9.0 && pos.x >= 5.0 && pos.z >= 35.0 && doorsclosed[1]) {
		cout << "Door 2 unlocked" << endl;
		doorsclosed[1] = false;	
	}
	if(pos.x <= -9.0 && pos.x >= -13.0 && doorsclosed[2]) {
		cout << "Door 3 unclocked" << endl;
		doorsclosed[2] = false;
	}
}