#include <iostream>
#include "procedural.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

int main(int argc, char* argv[]) {
    Procedural procedural;

	try {
		procedural.go();
	} catch(Ogre::Exception &e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occurred: " << 
		  e.getFullDescription().c_str() << std::endl;
		std::cin.ignore();
#endif
	}
    return EXIT_SUCCESS;
}