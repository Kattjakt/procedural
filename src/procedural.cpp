#include "procedural.h"

Procedural::Procedural() :
	root(0),
	camera(0),
	scenemanager(0),
	window(0),
	traymanager(0),
	paramspanel(0),
	inputmanager(0),
	mouse(0),
	keyboard(0)
{
	
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
	Ogre::String secName, typeName, archName;
	while (secIt.hasMoreElements()) {
		secName = secIt.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it = settings->begin(); it != settings->end(); ++it) {
			typeName = it->first;
            archName = it->second;
			std::cout << secName << ", " << typeName << ", " << archName << std::endl;
			bool recursive = false;
			if(archName[archName.length()] == '*') recursive = true;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName, recursive);
		}	
	} 
	
	// If we couldn't find a config file, show dialog
	if (!(root->restoreConfig() || root->showConfigDialog())) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

bool Procedural::go() {
	root = new Ogre::Root(PLUGINS_CFG);
	if (this->loadConfig() == EXIT_FAILURE) return EXIT_FAILURE;
	
	window = root->initialise(true, WINDOW_TITLE);

	scenemanager = root->createSceneManager(Ogre::ST_GENERIC);
	scenemanager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	camera = scenemanager->createCamera("mainCamera");
	camera->setPosition(0, 0, 80);
	camera->lookAt(0, 0, -300);
	camera->setNearClipDistance(5);
	cameraman = new OgreBites::SdkCameraMan(camera);

	viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth() / Ogre::Real(viewport->getActualHeight())));

	

	Ogre::OverlaySystem* pOverlaySystem = new Ogre::OverlaySystem();
	scenemanager->addRenderQueueListener(pOverlaySystem);

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Procedural");

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

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

	mouse->setEventCallback(this);
	keyboard->setEventCallback(this);

	windowResized(window);

    Ogre::WindowEventUtilities::addWindowEventListener(window, this);

	OgreBites::InputContext input;
	input.mAccelerometer = NULL;
	input.mKeyboard = keyboard;
	input.mMouse = mouse;
	input.mMultiTouch = NULL;
	
    traymanager = new OgreBites::SdkTrayManager("InterfaceName", window, input, this);
    traymanager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	traymanager->showLogo(OgreBites::TL_BOTTOMRIGHT);
    traymanager->hideCursor();
	
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    paramspanel = traymanager->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    paramspanel->setParamValue(9, "Bilinear");
    paramspanel->setParamValue(10, "Solid");

	root->addFrameListener(this);

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Start rendering ***");
	root->startRendering();
	
	return EXIT_SUCCESS;
}

bool Procedural::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    if(window->isClosed()) return false;
 
    keyboard->capture();
    mouse->capture();
 
	traymanager->frameRenderingQueued(evt);
	cameraman->frameRenderingQueued(evt);
	
    if(keyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
 
    return true;
}




bool Procedural::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
    cameraman->injectMouseDown(evt, id);
    return true;
}
 
bool Procedural::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
    cameraman->injectMouseUp(evt, id);
    return true;
}
 
bool Procedural::mouseMoved(const OIS::MouseEvent& evt) {
    cameraman->injectMouseMove(evt);
    return true;
}
 
bool Procedural::keyPressed(const OIS::KeyEvent& evt) {
    cameraman->injectKeyDown(evt);
    return true;
}
 
bool Procedural::keyReleased(const OIS::KeyEvent& evt) {
    cameraman->injectKeyUp(evt);
    return true;
}