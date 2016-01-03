#ifndef BOBLIGHT_SERVER_HPP
#define BOBLIGHT_SERVER_HPP

#include <cstdlib>
#include <string>
#include <map>
#include "ledController.hpp"

class BobLightServer{
public:
	BobLightServer(void);
	~BobLightServer(void) { }

	std::string receive(std::string &s);

private:
	std::map<std::string, int> commands;
	std::map<std::string, int> stripes;
	LedController *ledController;

	enum Command {
		eComHello,
		eComPing,
		eComGet,
		eComSet,
		eComSync,
	};

	enum Stripe {
		eStripeLeft = 2,
		eStripeTop = 1,
		eStripeRight = 3,
	};
};

#endif