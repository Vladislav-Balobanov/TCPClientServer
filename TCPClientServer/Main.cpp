#include <iostream>
#include <boost\asio.hpp>
#include <thread>
#include "Server.h"
#include "SyncClient.h"

using namespace boost::asio;

int main()
{
	io_service ioService;
	Server server(ioService);
	SyncClient client;

	client.syncConnect();
	while (true)
	{
		server.start();
		std::thread clientWorkingThread([&]() {client.syncConnect(); client.writeString("Hello! i'm your client!\n"); });
		server.readStringFromClient();
	}

	return 0;
}