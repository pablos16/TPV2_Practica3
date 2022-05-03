// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../sdlutils/SDLNetUtils.h"

namespace net {

enum MsgId : Uint8 {
	_CONNECTION_REQUEST, //
	_REQUEST_ACCEPTED, //
	_REQUEST_REFUSED, //
	_FIGHTER_POS, //
	_BULLET_POS, //
	_BULLET_SHOOT, //
	_START_ROUND_REQUEST, //
	_START_GAME_REQUEST, //
	_START_THE_GAME, //
	_START_THE_ROUND, //
	_FIGHTER_DEATH, //
	_GAME_OVER, //
	_DISCONNECTING
};

struct Message {
	Uint8 id;
	char name[11];
	//
	_IMPL_SERIALIAZION_(name, id)
};

struct ReqAccMsg: Message {

	Uint8 side;
	char name[11];

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message, name, side)
};

struct FighterPosMsg: Message {

	Uint8 side;
	float x;
	float y;
	float rot; 

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y, rot)
};

struct BulletPosMsg : Message {

	//Uint8 id; 
	Uint8 side;
	float x;
	float y;
	float rot;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message, side, x, y, rot)
};

struct BulletShootMsg : Message {

	//Uint8 id; 
	float x;
	float y;
	float rot;
	float velX; 
	float velY; 
	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message, x, y, velX, velY, rot)
};

struct FighterExplosion : Message {

	Uint8 side;

	_IMPL_SERIALIAZION_WITH_BASE_(Message, side)
};

struct StartRequestMsg: Message {

	Uint8 side;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side)
};

}

