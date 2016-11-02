#include "utilities.h"
#include "cmath"
#include "algorithm"


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

bool rangeInterset(float amin, float amax, float bmin, float bmax) {
	return std::max(amin, amax) >= std::min(bmin, bmax) &&
		   std::min(amin, amax) <= std::max(bmin, bmax);
}

bool CheckPlayerCollisions(Player* &a, Object* b) {
	vec4 aPos = a->GetPos();
	vec4 bPos = b->GetPos();
	float amin_x = aPos.x - std::abs(a->GetMinx()),
		  amax_x = aPos.x + a->GetMaxx(),
		  amin_z = aPos.z - std::abs(a->GetMinz()),
		  amax_z = aPos.z + a->GetMaxz(),
		  bmin_x = bPos.x - std::abs(b->GetMinx()),
		  bmax_x = bPos.x + b->GetMaxx(),
		  bmin_z = bPos.z - std::abs(b->GetMinz()),
		  bmax_z = bPos.z + b->GetMaxz();

	// cout << "amin_x: " << amin_x << endl;
	// cout << "amax_x: " << amax_x << endl;
	// cout << "amin_z: " << amin_z << endl;
	// cout << "amax_z: " << amax_z << endl;
	// cout << "bmin_x: " << bmin_x << endl;
	// cout << "bmax_x: " << bmax_x << endl;
	// cout << "bmin_z: " << bmin_z << endl;
	// cout << "bmax_z: " << bmax_z << endl;
	// cout << "rangeInterset: " << (rangeInterset(amin_x, amax_x, bmin_x, bmax_x)) << endl;
	// cout << "rangeInterset: " << (rangeInterset(amin_z, amax_z, bmin_z, bmax_z)) << endl;

	// if(rangeInterset(amin_x, amax_x, bmin_x, bmax_x) && rangeInterset(amin_z, amax_z, bmin_z, bmax_z)) {
		// cout << "YOU'VE COLLIDED!!" << endl;
	// 	a->PrintDir();

	// 	a->SetPos(aPos + -a->GetDir() * a->GetKeyDir());
		// if(amax_x > bmin_x) {
		// 	cout << "Collide left" << endl;
		// 	a->SetPos(vec4(bmin_x, aPos.y, aPos.z, 0.0));
		// }
		// else if(amin_x < bmax_x) {
		// 	cout << "Collide right" << endl;
		// 	a->SetPos(vec4(bmax_x, aPos.y, aPos.z, 0.0));
		// }
		// else if(amax_z > bmin_z) {
		// 	cout << "Collide top" << endl;
		// 	a->SetPos(vec4(aPos.x, aPos.y, aPos.z - 5.0, 0.0));
		// }
		// else if(amin_z < bmax_z) {
		// 	cout << "Collide bottom" << endl;			
		// 	a->SetPos(vec4(aPos.x, aPos.y, aPos.z + 5.0, 0.0));
		// }
	// }


	return rangeInterset(amin_x, amax_x, bmin_x, bmax_x) &&
		   rangeInterset(amin_z, amax_z, bmin_z, bmax_z);
}

void CheckCollisionsWithWalls(Player* &player, bool (&doorsclosed)[3], int &INROOM, bool &GHOSTSFLYING) {
	vec4 pos = player->GetPos();
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
	// Room2 Collisions (No more then z = 41.5)
	if(pos.z >= 20) {
		if(INROOM < 2)
			INROOM = 2;
		if(pos.x >= 15) {
			player->SetPos(vec4(14.9, pos.y, pos.z, pos.w)); // left
		}
		if(pos.x <= -15) {
			player->SetPos(vec4(-14.9, pos.y, pos.z, pos.w)); // right
		}
		if(pos.x >= 2.0 && pos.z <= 20.3) { // player has reached back left
			player->SetPos(vec4(pos.x, pos.y, 20.5, pos.w)); // bottom
		}
		if(pos.x <= -2.0 && pos.z <= 20.3) { // player has reached back left
			player->SetPos(vec4(pos.x, pos.y, 20.5, pos.w)); // bottom
		}
		if(pos.z >= 40.0 && pos.z <= 41.0 && doorsclosed[1]) {
			player->SetPos(vec4(pos.x, pos.y, 39.8, pos.w)); // back wall
		}
	}
	// Room3 Collisions
	if(pos.z > 41) {
		// cout << INROOM << endl;
		if(pos.z >= 43.0) {
			doorsclosed[1] = true; // close the door behind the player
			INROOM = 3;
			GHOSTSFLYING = true;
		}
		if(pos.z < 41.5) { // back wall
			player->SetPos(vec4(pos.x, pos.y, 41.7, pos.w)); // bottom of room 2
		}
		if(pos.x > -0.2) {
			player->SetPos(vec4(-0.5, pos.y, pos.z, pos.w));
		}
		if(pos.z >= 60.0) {
			player->SetPos(vec4(pos.x, pos.y, 59.5, pos.w)); // top wall of room 2
		}
	}
}

void DrawDoors(Object* &door, bool doorsclosed[3], bool HAVEKEY, int INROOM) {
	if(doorsclosed[0]) {
		door->Move(0.0, 0.0, 20.0);
		door->SetColor((114.0/255.0), (48.0/255.0), (24.0/255.0));
		door->DrawSolid(); // door 1
	}
	if(doorsclosed[1]) {
		door->Move(-13.0, 0.0, 40.0);
		if(HAVEKEY && INROOM!=3)
			door->SetColor((114.0/255.0), (48.0/255.0), (24.0/255.0));
		else 
			door->SetColor((20/255.0), (20.0/255.0), (20.0/255.0));
		door->DrawSolid(); // door 2
	}
	if(doorsclosed[2]) {
		door->Move(-2.0, 0.0, 60.0); // door 3
		door->SetColor((20/255.0), (20.0/255.0), (20.0/255.0));
		door->DrawSolid();
	}
}

void CheckToOpenDoors(Player* &player, bool (&doorsclosed)[3], bool HAVEKEY, int &INROOM) {
	vec4 pos = player->GetPos();
	if(pos.z >= 17.0 && doorsclosed[0]) { // Open door 1 if close enough
		cout << "Door 1 opened" << endl;
		doorsclosed[0] = false;
	}
	if(pos.x <= -13.0 && pos.x >= -15.0 && pos.z >= 38.0 && pos.z < 41.0 && doorsclosed[1] && HAVEKEY == true) { // Open door 2 if you're close enough
		cout << "Door 2 unlocked, and opened" << endl;
		doorsclosed[1] = false;
	}
	// if(pos.x <= -9.0 && pos.x >= -13.0 && pos.z >= 35.0 && doorsclosed[2]) { // Open door 3 if you're close enough
	// 	cout << "Door 3 unclocked" << endl;
	// 	doorsclosed[2] = false;
	// }
}

int incrementIndex(int &total, int incr) {
	return total += incr;
}

void combineVec4Vectors(std::vector<vec4> &a, std::vector<vec4> b) {
	for(std::vector<vec4>::iterator it=b.begin(); it < b.end(); ++it) {
		a.push_back(*it);
	}
}