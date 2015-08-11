/*
 * Light.hpp
 *
 *  Created on: 07.02.2014
 *      Author: david
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

class Light {
public:
	Light() : red(0), green(0), blue(0), interpolate(true) { }
	virtual ~Light() { }

	unsigned char red, green, blue;

	bool interpolate;
};

#endif /* LIGHT_HPP_ */
