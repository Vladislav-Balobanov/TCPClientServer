#pragma once
#include <iostream>
#include <boost\asio.hpp>
#include "Client.h"
#include "Server.h"

using namespace boost::asio::ip;

int main()
{
	boost::asio::io_service ioService;
	tcp::endpoint endpoint(address::from_string("127.0.0.1"), 80);
	Server server(ioService, endpoint);
	Client client(ioService, endpoint);
	server.start();
	client.syncConnect();

	return 0;
}