#pragma once

#include <Ogre.h>
#include <OIS.h>

#include "util.h"

class Procedural : public Ogre::FrameListener {
private:
	Ogre::Root *root;
	Ogre::SceneManager *scenemanager;
	Ogre::RenderWindow *window;
	Ogre::Camera *camera;
	Ogre::Viewport *viewport;

	OIS::InputManager *inputmanager;
	OIS::Keyboard *keyboard;
	OIS::Mouse *mouse;

public:
	Procedural::Procedural();
	Procedural::~Procedural();
	bool run();
	bool loadConfig();
	bool renderOneFrame();

protected:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
};

