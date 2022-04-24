// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

struct Image: public ecs::Component {

	__CMPID_DECL__(ecs::_IMAGE)

	Image() :
			tex_(nullptr), clip_() {
	}

	Image(Texture *tex_) :
			tex_(tex_) {
		clip_ = { 0, 0, tex_->width(), tex_->height() };
	}

	Image(Texture *tex_, SDL_Rect clip) :
			tex_(tex_), clip_(clip) {
	}

	virtual ~Image() {
	}

	Texture *tex_;
	SDL_Rect clip_;
};
