// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

struct FighterInfo: public ecs::Component {

	__CMPID_DECL__(ecs::_FIGHTERID)

	FighterInfo() :
			id_(0), lastShoot_(0), shootRate_(250) {
	}

	FighterInfo(uint8_t id) :
			id_(id), lastShoot_(0), shootRate_(250) {
	}

	virtual ~FighterInfo() {
	}

	uint8_t id_;
	uint32_t lastShoot_;
	uint32_t shootRate_;
};

