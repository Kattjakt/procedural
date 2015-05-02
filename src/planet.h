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
	
};