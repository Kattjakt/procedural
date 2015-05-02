#include "planet.h"

Planet::Planet(float radius) {
	this->radius = radius;
}

void Planet::generate() {
	cube = new Ogre::ManualObject("Planet");
	cube->begin("DebugGreenWireframe", Ogre::RenderOperation::OT_TRIANGLE_LIST); 

#define MAX 20


	float real_x = 0.0f;
	float real_y = 0.0f;
	float real_z = 0.0f;

	std::vector<Ogre::Vector3> positions{0};
	for (float a = 0; a < MAX; a++) {
		for (float b = 0; b < MAX; b++) {

			float _a = real_x - (MAX / 2.0f) + a;
			float _b = real_y - (MAX / 2.0f) + b;
			float _c = real_z - (MAX / 2.0f) + 0.0f;

			positions.push_back({_a, _b, _c});
			positions.push_back({_a, _c, _b});
			positions.push_back({_c, _a, _b});
			positions.push_back({_a, _c + MAX - 1, _b});
			positions.push_back({_c + MAX - 1, _a, _b});
			positions.push_back({_a, _b, _c + MAX - 1});
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