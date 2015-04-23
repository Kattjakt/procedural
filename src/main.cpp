#include <iostream>
#include <Ogre.h>

#include "util.h"

class Procedural {
private:
	Ogre::Root *root;
	Ogre::SceneManager *scenemanager;

public:
	Procedural::Procedural();
	Procedural::~Procedural();
	bool run();
	bool loadConfig();
};

Procedural::Procedural() {
	
}

Procedural::~Procedural() {
	delete root;
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

	Ogre::RenderWindow *window = root->initialise(true, WINDOW_TITLE);
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	scenemanager = root->createSceneManager(Ogre::ST_EXTERIOR_FAR);
	Ogre::Camera *camera = scenemanager->createCamera("mainCamera");
	camera->setPosition(0, 0, 80);
	camera->lookAt(0, 0, -300);
	camera->setNearClipDistance(5);

	Ogre::Viewport *vp = window->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	camera->setAspectRatio(Ogre::Real(vp->getActualWidth() / Ogre::Real(vp->getActualHeight())));

	while(true) {
		Ogre::WindowEventUtilities::messagePump();
		if (window->isClosed()) return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
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