// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <string>
#include <algorithm>
#include "game/Game.h"
#include "sdlutils/SDLNetUtils.h"

int main(int, char**) {

	SDLNetUtils::initSDLNet();

	try {
		Game g;
		g.init();
		g.start();
	} catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	SDLNetUtils::closeSDLNet();

	return 0;
}

