// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>
#include <string.h>
#include <string>

#include "../ecs/System.h"

struct Transform;

class NetworkSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_NETWORK)

	NetworkSystem();
	virtual ~NetworkSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

	bool connect(); 
	void disconnect(); 

	void addPlayerName(); 

	inline Uint8 getSide() {
		return side_;
	}

	inline bool isReday() {
		return connected_;
	}

	inline bool isHost() {
		return host_;
	}

	inline Uint16 getPort() {
		return port_;
	}

	void sendFighterPosition(Transform *tr);
	void sendBulletPosition(Transform* tr); 
	void addShoot(Transform* tr, float velX, float velY); 

	void sendStarRoundtRequest();
	void sendStarGameRequest();

	std::string getNameHost() { return local; }
	std::string getNameClient() { return cliente; }
	

private:

	bool initHost();
	bool initClient();
	bool initConnection(Uint16 port);

	void handleConnectionRequest();

	void handleFighterPos(); 
	void handleBulletPos(); 

	void createBullet(); 

	void handleStartGameRequest();
	void handleStartRoundRequest();

	void handleStartTheGame();
	void handleStartTheRound();
	void handleGameOver();

	void handleDisconnecting();

	void tellOtherClientToStartRound();
	void tellOtherClientToStartGame();
	void tellOtherClientHasWinLose();

	void string_to_chars(std::string& str, char c_str[11]) {
		auto i = 0u;
		for (; i < str.size() && i < 10; i++) c_str[i] = str[i];
		c_str[i] = 0;
	}

	void chars_to_string(std::string& str, char c_str[11]) {
		c_str[10] = 0;
		str = std::string(c_str);
	}

	bool host_;
	Uint8 side_; // 0 left 1 right
	UDPsocket sock_;
	UDPpacket *p_;
	SDLNet_SocketSet sockSet_;
	Uint16 port_;

	bool connected_;
	IPaddress otherPlayerAddr_;

	std::string name, local, cliente; 
	char namePlayer[11]; 
};

