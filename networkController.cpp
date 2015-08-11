#include "networkController.hpp"


#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

NetworkController::NetworkController(int port) : port(port) {
	this->boblightServer = new BobLightServer();
}

NetworkController::~NetworkController(void) {
	delete(boblightServer);
}

void session(socket_ptr sock, BobLightServer *boblightServer) {
	try {
		for (;;) {
			char data[1024];

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(data), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::string request(data, length);
			boost::algorithm::trim_all(request);
			if (request.length() > 0) {
#ifdef DEBUG
				std::cout << "net: received " << request.c_str() << "\n";
#endif
				std::vector<std::string> strs;
				boost::split(strs, request, boost::is_any_of("\n"));
				for (unsigned int i = 0; i<strs.size(); ++i) {
					std::string response = boblightServer->receive(strs[i]);
					if (response.length() > 0) {
#ifdef DEBUG
						std::cout << "net: sending " << response.c_str() << "\n";
#endif
						boost::asio::write(*sock, boost::asio::buffer(response, response.length()));
					}
				}
			}
			else {
				usleep(100);
			}
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void NetworkController::startServer(void) {
	boost::asio::io_service io_service;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	for (;;) {
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(session, sock, boblightServer));
	}
}