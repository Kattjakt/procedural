#pragma once

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
 

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "util.h"

class Procedural : 
	public Ogre::FrameListener, 
	public Ogre::WindowEventListener, 
	public OIS::KeyListener,
	public OIS::MouseListener,
	public OgreBites::SdkTrayListener
{
public:
	Procedural();
	virtual ~Procedural();
	bool go();
	bool loadConfig();

protected:
	Ogre::Root *root;
	Ogre::SceneManager *scenemanager;
	Ogre::RenderWindow *window;
	Ogre::Camera *camera;
	Ogre::Viewport *viewport;

	OIS::InputManager *inputmanager;
	OIS::Keyboard *keyboard;
	OIS::Mouse *mouse;

	OgreBites::SdkTrayManager* traymanager;
    OgreBites::SdkCameraMan* cameraman;     
    OgreBites::ParamsPanel* paramspanel; 

	virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	virtual bool mouseMoved(const OIS::MouseEvent& evt);
	virtual bool keyPressed(const OIS::KeyEvent& evt);
	virtual bool keyReleased(const OIS::KeyEvent& evt);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
};

