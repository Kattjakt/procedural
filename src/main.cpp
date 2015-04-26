#include <iostream>
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

Procedural::Procedural() {
	
}

Procedural::~Procedural() {
	delete root;
	if (inputmanager) {
		inputmanager->destroyInputObject(mouse);
		inputmanager->destroyInputObject(keyboard);
		OIS::InputManager::destroyInputSystem(inputmanager);
	}
}

bool Procedural::loadConfig() {
	// Load all plugins
	Ogre::ConfigFile cf;
	cf.load(RESOURCE_CFG);
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while (secIt.hasMoreElements()) {
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it = settings->begin(); it != settings->end(); ++it) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(it->second, it->first);
		}	
	} 
	
	// If we couldn't find a config file, show dialog
	if (!(root->restoreConfig() || root->showConfigDialog())) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

bool Procedural::run() {
	root = new Ogre::Root(PLUGINS_CFG);
	if (this->loadConfig() != EXIT_SUCCESS) return EXIT_FAILURE;
	
	window = root->initialise(true, WINDOW_TITLE);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	scenemanager = root->createSceneManager(Ogre::ST_EXTERIOR_FAR);
	camera = scenemanager->createCamera("mainCamera");
	camera->setPosition(0, 0, 80);
	camera->lookAt(0, 0, -300);
	camera->setNearClipDistance(5);

	viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth() / Ogre::Real(viewport->getActualHeight())));

	Ogre::Light* light = scenemanager->createLight("MainLight");
	light->setPosition(20, 80, 50);

	Ogre::Entity *ogreEntity = scenemanager->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode = scenemanager->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	 
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	window->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	inputmanager = OIS::InputManager::createInputSystem(pl);
	
	keyboard = static_cast<OIS::Keyboard*>(inputmanager->createInputObject( OIS::OISKeyboard, false ));
	mouse = static_cast<OIS::Mouse*>(inputmanager->createInputObject( OIS::OISMouse, false ));

	root->addFrameListener(this);
	root->startRendering();
	
	return EXIT_SUCCESS;
}

bool Procedural::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    if(window->isClosed()) return false;
 
    keyboard->capture();
    mouse->capture();
 
    if(keyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
 
    return true;
}
	
int main(int argc, char* argv[]) {
    Procedural *p = new Procedural();
	try {
		p->run();
	} catch(Ogre::Exception &e) {
		std::cerr << "An exception has occurred: " << 
		  e.getFullDescription().c_str() << std::endl;
		std::cin.ignore();
	}

    return EXIT_SUCCESS;
}