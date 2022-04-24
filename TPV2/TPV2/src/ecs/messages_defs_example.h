// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

/*
 *
 * DO NOT USE/MODIFY THIS FILE, IT IS JUST AN EXAMPLE OF HOW YOUR
 * game/messages_defs.h SHOULD LOOK LIKE
 *
 */


#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_START_GAME, //
	_m_CREATE_STARS
};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_STAR_EATEN
		struct {
			ecs::Entity *e;
		} star_eaten_data;

		// _m_CREATE_STARS
		struct {
			unsigned int n;
		} create_stars_data;

	};
};
