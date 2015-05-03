#pragma once

#include <Ogre.h>

#include "util.h"

class Planet {
private:
	float radius;
	Ogre::Vector3 position;
	Ogre::ManualObject* manual;

public:
	Planet(float radius);
	void generate();
	void update(Ogre::Vector3 camera);
	Ogre::ManualObject* getManual();
	Ogre::Vector3 map(Ogre::Vector3 val);
};