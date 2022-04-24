// This file is part of the course TPV2@UCM - Samir Genaim

#include "BulletsSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../game/messages_defs.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

BulletsSystem::BulletsSystem() :
		running_(false) {
}

BulletsSystem::~BulletsSystem() {
}

void BulletsSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_SHOOT:
		handleShoot(m);
		break;
	case _m_GAME_OVER:
		handleGameOver(m);
		break;
	case _m_GAME_START:
		handleGameStart(m);
		break;
	default:
		break;
	}
}

void BulletsSystem::initSystem() {
}

void BulletsSystem::update() {
	if (!running_)
		return;

	for (ecs::Entity *b : mngr_->getEntities(ecs::_grp_BULLETS)) {
		auto bTR = mngr_->getComponent<Transform>(b);

		// move the bullet
		bTR->move();

		// disable if exit from window
		if ((bTR->pos_.getX() < -bTR->width_
				|| bTR->pos_.getX() > sdlutils().width())
				|| bTR->pos_.getY() < -bTR->height_
				|| bTR->pos_.getY() > sdlutils().height()) {
			mngr_->setAlive(b, false);
		}

	}
}

void BulletsSystem::handleShoot(const Message &m) {
	ecs::Entity *b = mngr_->addEntity(ecs::_grp_BULLETS);

	// the bottom/center of the bullet
	Vector2D pos = Vector2D(m.shoot.pos.x, m.shoot.pos.y);

	// the velocity of the bullet
	Vector2D vel = Vector2D(m.shoot.vel.x, m.shoot.vel.y);

	// the image rotation
	float rot = Vector2D(0.0f, -1.0f).angle(vel);

	float bh = 18.0f;
	float bw = 6.f;

	// left/top corner of the bullet
	Vector2D bPos = pos + vel.normalize() * (bh / 2.0f)
			- Vector2D(bw / 2.0f, bh / 2.0);

	mngr_->addComponent<Transform>(b, bPos, vel, bw, bh, rot);
	mngr_->addComponent<Image>(b, &sdlutils().images().at("fire"));

	sdlutils().soundEffects().at("gunshot").play();
}

void BulletsSystem::handleGameOver(const Message&) {
	running_ = false;
	for (ecs::Entity *b : mngr_->getEntities(ecs::_grp_BULLETS)) {
		mngr_->setAlive(b, false);
	}
}

void BulletsSystem::handleGameStart(const Message&) {
	running_ = true;
}
