// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_scancode.h>
#include "../ecs/Component.h"

struct CtrlKeys: public ecs::Component {

	__CMPID_DECL__(ecs::_CTRLKEYS)

	CtrlKeys() :
			up_(SDL_SCANCODE_UP), //
			down_(SDL_SCANCODE_DOWN), //
			left_(SDL_SCANCODE_LEFT), //
			right_(SDL_SCANCODE_RIGHT), //
			shoot_(SDL_SCANCODE_S) {
	}

	CtrlKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left,
			SDL_Scancode right, SDL_Scancode shoot) :
			up_(up), //
			down_(down), //
			left_(left), //
			right_(right), //
			shoot_(shoot) {
	}

	virtual ~CtrlKeys() {
	}

	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode left_;
	SDL_Scancode right_;
	SDL_Scancode shoot_;
};
