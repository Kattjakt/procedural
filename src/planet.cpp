#include "planet.h"

Planet::Planet(float radius) {
	this->radius = radius;
}

Ogre::Vector3 Planet::map(Ogre::Vector3 pos) {
	float length = pos.normalise();
	Ogre::Vector3 temp = pos / length;
	
	// map cube to unit sphere
	pos.x = temp.x * sqrtf(1.0 - (temp.y*temp.y/2.0) - (temp.z*temp.z/2.0) + (temp.y*temp.y*temp.z*temp.z/3.0));
    pos.y = temp.y * sqrtf(1.0 - (temp.z*temp.z/2.0) - (temp.x*temp.x/2.0) + (temp.z*temp.z*temp.x*temp.x/3.0));
    pos.z = temp.z * sqrtf(1.0 - (temp.x*temp.x/2.0) - (temp.y*temp.y/2.0) + (temp.x*temp.x*temp.y*temp.y/3.0));
	
	return pos * length * this->radius;
}

void Planet::generate() {
	cube = new Ogre::ManualObject("Planet");
	cube->begin("DebugGreenWireframe", Ogre::RenderOperation::OT_TRIANGLE_LIST); 

#define MAX 20

	Ogre::Vector3 position{0.0f, 0.0f, 0.0f};

	std::vector<Ogre::Vector3> positions{0};
	for (float x = 0; x < MAX; x++) {
		for (float y = 0; y < MAX; y++) {

			float pos_x = position.x - (MAX / 2.0f);
			float pos_y = position.y - (MAX / 2.0f);
			float pos_z = position.z - (MAX / 2.0f);

			positions.push_back(map({pos_x + x,       pos_y + y,          pos_z}));
			positions.push_back(map({pos_x + x,       pos_y,              pos_z + y}));
			positions.push_back(map({pos_x,           pos_y + x,          pos_z + y}));
			positions.push_back(map({pos_x + x,       pos_y + MAX - 1,    pos_z + y}));
			positions.push_back(map({pos_x + MAX-1,   pos_y + x,          pos_z + y}));
			positions.push_back(map({pos_x + x,       pos_y + y,          pos_z + MAX - 1}));
		}
	}

	for (int face = 0; face < 6; face++) {
		// get the shit into the right shitorder
		for (int n = 0; n < pow(MAX, 2); n++) {	
			cube->position(positions.at((6 * n) + face));
		}

		for (int x = 0; x < MAX - 1; x++) {
			for (int y = 0; y < MAX - 1; y++) {
				cube->quad( 
					//   vertex offset           local offset
					(pow(MAX, 2) * face) + ((y + 1) * MAX) + x + 1,
					(pow(MAX, 2) * face) + (y* MAX) + x + 1,
					(pow(MAX, 2) * face) + (y* MAX) + x, 
					(pow(MAX, 2) * face) + ((y + 1) * MAX) + x
				);
			}
		}
	}

	cube->end();
}

Ogre::ManualObject* Planet::getManual() {
	return this->cube;
}