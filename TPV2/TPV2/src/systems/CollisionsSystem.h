// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class CollisionsSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_COLLISIONS)

	CollisionsSystem();
	virtual ~CollisionsSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

private:
	void handleGameStart(const Message&);
	void handleGameOver(const Message&);

	bool running_;
};

