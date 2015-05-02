#include "planet.h"

Planet::Planet(float radius) {
	this->radius = radius;
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

			positions.push_back({x + pos_x, y + pos_y, pos_z});
			positions.push_back({x + pos_x, pos_y, y + pos_z});
			positions.push_back({pos_x, x + pos_y, y + pos_z});
			positions.push_back({x + pos_x, pos_y + MAX - 1, y + pos_z});
			positions.push_back({pos_x + MAX - 1, x + pos_y, y + pos_z});
			positions.push_back({x + pos_x, y + pos_y, pos_z + MAX - 1});
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