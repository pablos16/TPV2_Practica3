// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

namespace ecs {
class Entity;
}

struct Transform;

class FightersSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_FIGHTERS)

	FightersSystem();
	virtual ~FightersSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;
private:
	void handleGameStart(const Message&);
	void handleGameOver(const Message&);
	void handleBulletHitFighter(const Message&);

	Transform *tr0_;
	Transform *tr1_;

	bool running_;
};

