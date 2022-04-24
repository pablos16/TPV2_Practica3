// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../sdlutils/SDLNetUtils.h"

namespace net {

enum MsgId : Uint8 {
	_CONNECTION_REQUEST, //
	_REQUEST_ACCEPTED, //
	_REQUEST_REFUSED, //
	_FIGHTER0_POS, //
	_FIGHTER1_POS, //
	_START_ROUND_REQUEST, //
	_START_GAME_REQUEST, //
	_START_THE_GAME, //
	_START_THE_ROUND, //
	_BALL_EXIT, //
	_GAME_OVER, //
	_DISCONNECTING
};

struct Message {
	Uint8 id;

	//
	_IMPL_SERIALIAZION_(id)
};

struct ReqAccMsg: Message {

	Uint8 side;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side)
};

struct Fighter0PosMsg: Message {

	Uint8 side;
	float x;
	float y;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y)
};

struct Fighter1PosMsg: Message {

	Uint8 side;
	float x;
	float y;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y)
};

struct StartRequestMsg: Message {

	Uint8 side;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side)
};

}

