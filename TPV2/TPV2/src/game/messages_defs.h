// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_GAME_START, //
	_m_GAME_OVER, //
	_m_SHOOT, //
	_m_BULLET_HIT_FIGHTER
};

struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_GAME_OVER
		struct {
			uint8_t playerId; // 0 or 1
		} killed;

		// _m_BULLET_HIT_FIGHTER
		struct {
			ecs::Entity *bullet_;
			ecs::Entity *fighter_;
		} bullet_hit;

		// _m_SHOOT
		struct {
			struct {
				float x;
				float y;
			} pos;
			struct {
				float x;
				float y;
			} vel;
		} shoot;

	};
};
