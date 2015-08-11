#include "networkController.hpp"

int main(int argc, char * argv[]) {
	NetworkController *server = new NetworkController(19333);

	server->startServer();
}