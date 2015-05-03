#include "planet.h"

Planet::Planet(float radius) {
	this->radius = radius;
}

Ogre::Vector3 Planet::map(Ogre::Vector3 pos) {
#if PLANET_CUBE
	return pos;
#endif
	float length = pos.normalise();
	Ogre::Vector3 temp = pos / length;
	
	// map cube to unit sphere
	pos.x = temp.x * sqrtf(1.0 - (temp.y*temp.y/2.0) - (temp.z*temp.z/2.0) + (temp.y*temp.y*temp.z*temp.z/3.0));
    pos.y = temp.y * sqrtf(1.0 - (temp.z*temp.z/2.0) - (temp.x*temp.x/2.0) + (temp.z*temp.z*temp.x*temp.x/3.0));
    pos.z = temp.z * sqrtf(1.0 - (temp.x*temp.x/2.0) - (temp.y*temp.y/2.0) + (temp.x*temp.x*temp.y*temp.y/3.0));
	
	return pos * length * this->radius;
}

void Planet::generate() {
	manual = new Ogre::ManualObject("Planet");
	manual->begin("DebugGreenWireframe", Ogre::RenderOperation::OT_TRIANGLE_LIST); 

#define MAX 20

	position = {0.0f, 0.0f, 0.0f};
	std::vector<Ogre::Vector3> positions;
	float offset = (MAX / 2.0f);

	for (float x = 0; x < MAX; x++) {
		for (float y = 0; y < MAX; y++) {

			// map planes into to a 6-faced cube
			std::vector<Ogre::Vector3> temp;
			temp.push_back(map({x - offset,         y - offset,         0.0f - offset}));
			temp.push_back(map({x - offset,         0.0f - offset,      y - offset}));
			temp.push_back(map({0.0f - offset,      x - offset,         y - offset}));
			temp.push_back(map({x - offset,         MAX - 1- offset,    y - offset}));
			temp.push_back(map({MAX - 1 - offset,   x - offset,         y - offset}));
			temp.push_back(map({x - offset,         y - offset,         MAX - 1 - offset}));
	
			// add world coordinates
			for (int i = 0; i < 6; i++) {
				positions.push_back({
					temp.at(i).x + position.x, 
					temp.at(i).y + position.y, 
					temp.at(i).z + position.z
				});
			}
		}
	}

	for (int face = 0; face < 6; face++) {
		// get the shit into the right shitorder
		for (int n = 0; n < pow(MAX, 2); n++) {	
			manual->position(positions.at((6 * n) + face));
		}

		for (int x = 0; x < MAX - 1; x++) {
			for (int y = 0; y < MAX - 1; y++) {
				manual->quad( 
					//   vertex offset           local offset
					(pow(MAX, 2) * face) + ((y + 1) * MAX) + x + 1,
					(pow(MAX, 2) * face) + (y* MAX) + x + 1,
					(pow(MAX, 2) * face) + (y* MAX) + x, 
					(pow(MAX, 2) * face) + ((y + 1) * MAX) + x
				);
			}
		}
	}

	manual->end();
}

void Planet::update(Ogre::Vector3 camera) {
	// std::cout << "Distance: " << camera.distance(this->position) << std::endl;
	float distance = camera.distance(this->position);

}

Ogre::ManualObject* Planet::getManual() {
	return this->manual;
}