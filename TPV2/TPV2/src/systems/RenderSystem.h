// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

namespace ecs {
class Entity;
}
class Texture;
struct Transform;

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_RENDER)

	void recieve(const Message&) override;
	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;

private:
	void drawMsgs();
	void drawFighters();
	void drawBullets();
	void draw(ecs::Entity *e);
	void drawId(ecs::Entity *e);

	void handleGameStart(const Message&);
	void handleGameOver(const Message&);
	void drawBox(ecs::Entity *e);

	bool running_;
	bool over_;
	uint8_t killedId_;
};

