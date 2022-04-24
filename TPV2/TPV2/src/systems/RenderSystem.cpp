// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include <SDL_render.h>

#include "../components/FighterInfo.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem() :
		running_(false), over_(false), killedId_() {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::recieve(const Message &m) {
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

void RenderSystem::handleGameStart(const Message&) {
	running_ = true;
	over_ = false;
}

void RenderSystem::handleGameOver(const Message&) {
	running_ = false;
	over_ = true;
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawMsgs();
	if (running_) {
		drawFighters();
		drawBullets();
	}
}

void RenderSystem::drawMsgs() {
	if (!running_) {

		auto &startMsg = sdlutils().msgs().at("start");
		startMsg.render((sdlutils().width() - startMsg.width()) / 2,
				sdlutils().height() / 2 + startMsg.height() * 2);

		if (over_) {
			auto &gameOverMsg = sdlutils().msgs().at("gameover");
			gameOverMsg.render((sdlutils().width() - gameOverMsg.width()) / 2,
					20);

			Texture winnerMsg(sdlutils().renderer(), //
					"Player " + std::to_string(killedId_) + " has been shot!", //
					sdlutils().fonts().at("ARIAL24"), //
					build_sdlcolor(0xffAA44ff));

			winnerMsg.render((sdlutils().width() - winnerMsg.width()) / 2,
					gameOverMsg.height() + 50);
		}

	}

}

void RenderSystem::drawFighters() {
	for (ecs::Entity *e : mngr_->getEntities(ecs::_grp_FIGHTERS)) {
		draw(e);
		drawId(e);
		drawBox(e);
	}
}

void RenderSystem::drawBullets() {
	for (ecs::Entity *e : mngr_->getEntities(ecs::_grp_BULLETS)) {
		draw(e);
	}
}

void RenderSystem::draw(ecs::Entity *e) {
	auto tr = mngr_->getComponent<Transform>(e);
	auto img = mngr_->getComponent<Image>(e);

	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
	img->tex_->render(img->clip_, dest, tr->rot_);
}

void RenderSystem::drawId(ecs::Entity *e) {
	auto id = mngr_->getComponent<FighterInfo>(e)->id_;
	auto tr = mngr_->getComponent<Transform>(e);

	std::string tag = "Player " + std::to_string(id);

	Texture playeTag(sdlutils().renderer(), //
			tag, //
			sdlutils().fonts().at("ARIAL12"), //
			build_sdlcolor(0xff0000ff));

	Vector2D p =
			Vector2D(0.0f, (tr->height_ / 2.0f) + playeTag.height() / 2.0f).rotate(
					tr->rot_) + tr->pos_
					+ Vector2D(tr->width_ / 2.0f, tr->height_ / 2.0f);

	SDL_Rect dest = build_sdlrect(p.getX() - playeTag.width() / 2.0f,
			p.getY() - playeTag.height() / 2.0, playeTag.width(),
			playeTag.height());

	playeTag.render(dest, tr->rot_);

//	SDL_RenderDrawLine(sdlutils().renderer(), , lb.getY() + y, lu.getX() + x,
//			lu.getY() + y);

}

void RenderSystem::drawBox(ecs::Entity *e) {
	SDL_Renderer *renderer = sdlutils().renderer();
	auto tr = mngr_->getComponent<Transform>(e);

	// the rotation angle of the entity
	float angle = tr->rot_;

	// Assuming the (0,0) point is the middle of the entity, the following are
	// vectors to the corners of its bounding rectangle
	Vector2D lu = Vector2D(-tr->width_ / 2.0f, -tr->height_ / 2.0f);
	Vector2D ru = Vector2D(tr->width_ / 2.0f, -tr->height_ / 2.0f);
	Vector2D rb = Vector2D(tr->width_ / 2.0f, tr->height_ / 2.0f);
	Vector2D lb = Vector2D(-tr->width_ / 2.0f, tr->height_ / 2.0f);

	// rotate the corners, so we get a rotated rectangle
	lu = lu.rotate(angle);
	ru = ru.rotate(angle);
	rb = rb.rotate(angle);
	lb = lb.rotate(angle);

	// the center of the entity
	float x = tr->pos_.getX() + tr->width_ / 2.0f;
	float y = tr->pos_.getY() + tr->height_ / 2.0f;

	// draw lines between the corners, after shifting them by (x,y)
	SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0x0000ff00)));
	SDL_RenderDrawLine(renderer, lu.getX() + x, lu.getY() + y, ru.getX() + x,
			ru.getY() + y);
	SDL_RenderDrawLine(renderer, ru.getX() + x, ru.getY() + y, rb.getX() + x,
			rb.getY() + y);
	SDL_RenderDrawLine(renderer, rb.getX() + x, rb.getY() + y, lb.getX() + x,
			lb.getY() + y);
	SDL_RenderDrawLine(renderer, lb.getX() + x, lb.getY() + y, lu.getX() + x,
			lu.getY() + y);

	/*
	 // draw center point
	 SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0xff000000)));
	 SDL_Rect dest = build_sdlrect(x - 1, y - 1, 3, 3);
	 SDL_RenderFillRect(renderer, &dest);

	 // draw velocity vector
	 SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0x00ff0011)));

	 auto vel = tr->vel_;
	 float wh = std::min(tr->height_, tr->width_) / 2.0f; // minimum of width an height
	 vel = vel * wh / 2.0f;
	 SDL_RenderDrawLine(renderer, x, y, vel.getX() + x, vel.getY() + y);
	 */
}

