#include <iostream>
#include "procedural.h"

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