// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class GameCtrlSystem: public ecs::System {
public:

	enum GameState : uint8_t {
		_RUNNING, _STOPPED
	};

	__SYSID_DECL__(ecs::_sys_GAMECTRL)

		enum Side {
		LEFT = 0, //
		RIGHT
	};

		enum State {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameCtrlSystem();
	virtual ~GameCtrlSystem();


	void initSystem() override;
	void update() override;
	void recieve(const Message &m) override;

	void requestToStartRound();
	void requestToStartGame();
	void startRound();
	void startGame();
	void roundOver();
	void gameOver();
	void stopTheGame();

private:

	void handleBulletHitFighter(const Message&);

	uint8_t state_;
	//std::array<unsigned int, 2> score_;
	//const unsigned int maxScore_;
};

