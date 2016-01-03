#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP

#include "Light.hpp"

class LedController {
public:
	LedController(void);
	~LedController(void) {
		shouldRun = false;
		delete(lights[0]);
		delete(lights[1]);
		delete(lights[2]);
	}
  
	void writeColor(unsigned char stripe, unsigned char red, unsigned char green, unsigned char blue);
	Light *lights[3];

	bool shouldRun;

	enum Config{
		eConfigRange = 100,
		eConfigStripeCount = 3,
		eConfigColorCount = 3,
	};

private:
	unsigned char ledMap[9];
	void init(void);
};

#endif
