// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

CollisionsSystem::CollisionsSystem() :
		running_(false) {
}

void CollisionsSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_GAME_START:
		handleGameStart(m);
		break;
	case _m_GAME_OVER:
		handleGameOver(m);
		break;
	default:
		break;
	}
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {
	if (!running_)
		return;

	auto &fighters = mngr_->getEntities(ecs::_grp_FIGHTERS);
	auto &bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	for (ecs::Entity *b : bullets) {
		if (!mngr_->isAlive(b))
			continue;

		auto bTR = mngr_->getComponent<Transform>(b);
		for (ecs::Entity *e : fighters) {
			auto eTR = mngr_->getComponent<Transform>(e);


			if (Collisions::collidesWithRotation(bTR->pos_, bTR->width_,
					bTR->height_, bTR->rot_, //
					eTR->pos_, eTR->width_, eTR->height_, eTR->rot_)) {

				Message m;
				m.id = _m_BULLET_HIT_FIGHTER;
				m.bullet_hit.bullet_ = b;
				m.bullet_hit.fighter_ = e;
				mngr_->send(m);

				return;
			}
		}
	}
}

void CollisionsSystem::handleGameStart(const Message&) {
	running_ = true;
}

void CollisionsSystem::handleGameOver(const Message&) {
	running_ = false;
}
