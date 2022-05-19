#include <iostream>
#include <boost\asio.hpp>
#include <thread>
#include "Server.h"
#include "SyncClient.h"

using namespace boost::asio;

int main()
{
	boost::asio::io_service ioService;
	Client client(ioService);
	Server server(ioService);

	client.syncConnect();

	return 0;
}