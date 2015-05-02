#include "planet.h"

Planet::Planet(float radius) {
	this->radius = radius;
}

void Planet::generate() {
	cube = new Ogre::ManualObject("Planet");
	cube->begin("DebugGreenWireframe", Ogre::RenderOperation::OT_TRIANGLE_LIST); 

#define MAX 20

	float c = 0;

	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			cube->position(a, b, c); //  some side
		}
	}
	
	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			cube->position(a, c, b); // bottom
		}
	}

	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			cube->position(c, a, b); //  some side
		}
	}

	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			cube->position(a, c + MAX - 1, b); // top
		}
	}

	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			cube->position(c + MAX - 1, a, b); //  some side
		}
	}

	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			cube->position(a, b, c + MAX - 1); //  some side
		}
	}

	for (int face = 0; face <= 5; face++) {
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