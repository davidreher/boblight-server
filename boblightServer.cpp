#include "boblightServer.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>
#include <stdio.h>

BobLightServer::BobLightServer(void) {
	commands["hello"] = eComHello;
	commands["ping"] = eComPing;
	commands["get"] = eComGet;
	commands["set"] = eComSet;
	commands["sync"] = eComSync;

	stripes["left"] = eStripeLeft;
	stripes["top"] = eStripeTop;
	stripes["right"] = eStripeRight;

	ledController = new LedController();
}

std::string BobLightServer::receive(std::string &s) {
#ifdef DEBUG
	printf("bob: processing %s\n", s.c_str());
#endif
	std::vector<std::string> strs;
	boost::split(strs, s, boost::is_any_of(" "));
	std::stringstream ss;
	switch (commands[strs[0]])
	{
	case eComHello:
		ss << "hello";
		break;
	case eComPing:
		ss << "ping 1";
		break;
	case eComGet:
		if (strs[1].compare("version") == 0) {
			ss << "version 5";
		}
		else if (strs[1].compare("lights") == 0) {
			ss << "lights 3"
				<< "\n" << "light right scan 0 100 50 100"
				<< "\n" << "light left scan 0 100 0 50"
				<< "\n" << "light top scan 0 50 0 100";
		}
#ifdef DEBUG
		else {
			printf("bob: received unknown get: %s\n", s.c_str());
		}
#endif
		break;
	case eComSet:
		if (strs[1].compare("light") == 0) {
			int stripe = stripes[strs[2]];
			if (strs[3].compare("rgb") == 0) {
				unsigned char red = (unsigned char)(strtof(strs[4].c_str(), NULL) * 100),
					green = (unsigned char)(strtof(strs[5].c_str(), NULL) * 100),
					blue = (unsigned char)(strtof(strs[6].c_str(), NULL) * 100);
				ledController->setColor(stripe, red, green, blue);
			}
#ifdef INTERPOLATION
			else if(strs[3].compare("interpolation") == 0) {
				ledController->lights[stripe-1]->interpolate = true;
			}
#endif
#ifdef DEBUG
			else {
				printf("bob: received unknown set light: %s\n", s.c_str());
			}
#endif
		}
#ifdef DEBUG
		else {
			printf("bob: received unknown set: %s\n", s.c_str());
		}
#endif
		break;
	case eComSync:
		break;
	default:
#ifdef DEBUG
		printf("bob: received unknown command: %s\n", s.c_str());
#endif
		break;
	}
	if (ss.str().length() > 0) {
		ss << "\n";
	}
	return ss.str();
}
