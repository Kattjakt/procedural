#include "planet.h"

Planet::Planet(float radius) {
	this->radius = radius;
}

void Planet::generate() {
	cube = new Ogre::ManualObject("Planet");
	cube->begin("DebugGreenWireframe", Ogre::RenderOperation::OT_TRIANGLE_LIST);

#define MAX 20

	for (int x = 0; x < MAX; x++) {
		for (int y = 0; y < MAX; y++) {
			cube->position(x, y, /* static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 5 */ 0.0f);
		}
	}

	for (int x = 0; x < MAX - 1; x++) {
		for (int y = 0; y < MAX - 1; y++) {
			cube->triangle(
				(y * MAX) + x + 1, 
				((y + 1) * MAX) + x,
				((y + 1) * MAX) + x + 1
			);
			cube->triangle(
				((y + 1) * MAX) + x,
				(y * MAX) + x + 1, 
				(y * MAX) + x
			);
		}
	}
		
	cube->end();
}

Ogre::ManualObject* Planet::getManual() {
	return this->cube;
}