#ifndef NETWORK_CONTROLLER_HPP
#define NETWORK_CONTROLLER_HPP

#include "boblightServer.hpp"

class NetworkController {
public:
	NetworkController(int port);
	~NetworkController(void);

	void startServer(void);
private:
	BobLightServer *boblightServer;
	int port;
};

#endif