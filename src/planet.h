#pragma once

#include <Ogre.h>

class Planet {
private:
	float radius;
	Ogre::ManualObject* cube;

public:
	Planet(float radius);
	void generate();
	Ogre::ManualObject* getManual();
	Ogre::Vector3 map(Ogre::Vector3 val);
};