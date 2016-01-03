# boblight-server
boblight server implementation for controlling LED Strips attached to RaspberryPi

For more information (in german), see my [blog post](https://blog.brockhaus-ag.de/2015/09/19/ambilight-mit-dem-raspberrypi-2/).

## Files
* networkController - Receives packages over network. If a command is received, it will be forwarded to the boblight server. The port is configured in the main file.
* boblightServer - Handles boblight commands. Commands were extracted from the [boblight client sourcecode](https://code.google.com/p/boblight/source/browse/trunk/src/client.cpp#285). The set commands are forwarded to the led controller.
* ledController - Writes the correct light values to the gpio ports.

## Requirements
boost library, wiringPi
