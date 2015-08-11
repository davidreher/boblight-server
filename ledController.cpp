#include "ledController.hpp"

#include <wiringPi.h>
#include <softPwm.h>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <stdio.h>

LedController::LedController(void) :
    lights { new Light(), new Light(), new Light() },
    shouldRun(true),
		ledMap { 1, 0, 7, 2, 3, 4, 6, 13, 5 } {
	init();
}

void adjustLight(unsigned char &reference, unsigned char &value) {
	if(reference > value) {
		value++;
	}
	if(reference < value) {
		value --;
	}
}

void session(LedController* that) {
	Light *currentLights[] = { new Light(), new Light(), new Light() };
	while (that->shouldRun) {
		for (unsigned char stripe = 0; stripe < that->eConfigStripeCount; stripe++) {
			if(that->lights[stripe]->interpolate) {
				bool changed = false;
				if(that->lights[stripe]->red != currentLights[stripe]->red) {
					changed = true;
					adjustLight(that->lights[stripe]->red, currentLights[stripe]->red);
				}
				if(that->lights[stripe]->green != currentLights[stripe]->green) {
					changed = true;
					adjustLight(that->lights[stripe]->green, currentLights[stripe]->green);
				}
				if(that->lights[stripe]->blue != currentLights[stripe]->blue) {
					changed = true;
					adjustLight(that->lights[stripe]->blue, currentLights[stripe]->blue);
				}
				if(changed) {
					that->writeColor(stripe + 1, currentLights[stripe]->red, currentLights[stripe]->green, currentLights[stripe]->blue);
				}
			}
		}
    usleep(10000);
	}
}

void LedController::init(void) {
	wiringPiSetup();
	for (unsigned char stripe = 0; stripe < eConfigStripeCount; ++stripe) {
		for (unsigned char color = 0; color < eConfigColorCount; ++color) {
			softPwmCreate(ledMap[(stripe * eConfigColorCount + color)], 0, eConfigRange);
		}
	}
	boost::thread t(boost::bind(session, this));
}

void LedController::setColor(unsigned char stripe,
		unsigned char red,
		unsigned char green,
		unsigned char blue) {
	if (true) {
		lights[stripe - 1]->red = red;
		lights[stripe - 1]->green = green;
		lights[stripe - 1]->blue = blue;
	} else {
		this->writeColor(stripe, red, green, blue);
	}
}

void LedController::writeColor(unsigned char stripe,
		unsigned char red,
		unsigned char green,
		unsigned char blue) {
	softPwmWrite(ledMap[(stripe - 1) * eConfigColorCount + 0], red);
	softPwmWrite(ledMap[(stripe - 1) * eConfigColorCount + 1], green);
	softPwmWrite(ledMap[(stripe - 1) * eConfigColorCount + 2], blue);
}
