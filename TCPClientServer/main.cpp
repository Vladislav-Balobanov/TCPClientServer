#pragma once
#include <iostream>
#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include "Client.h"
#include "Server.h"

using namespace boost::asio::ip;

int main()
{
	char command;
	while(true)
	{
		// Блок работы с пользователем:
		std::cout << "Hello, do you want to start messageing with server? insert y/n: ";
		std::cin >> command;
		if (command == 'N' || command == 'n')
			break;

		// Блок инициализации:
		boost::asio::io_service ioService;
		tcp::endpoint endpoint(address::from_string("127.0.0.1"), 80);
		boost::system::error_code error;
		boost::thread threadServer;
		boost::thread threadClient;

		// Блок подключения к клиента и сервера:
		Server server(ioService, endpoint);
		Client client(ioService, endpoint);
		
		// Запуск сервера:
		threadServer = boost::thread([&]() {server.start(); });
		// Синхронное подключение клиента:
		client.syncConnect(error);
		// Синкхронная запись строки:
		threadClient = boost::thread([&]() {client.sendString("something!"); });
		threadClient.join();
		// Синхронное чтение строки:
		threadServer = boost::thread([&]() {std::cout << "Getting steing is: \"" << server.getString() << "\"" << std::endl; });
		threadServer.join();

		// Работа с пользователем:
		std::cout << "Hello, do you want to stop messageing with server? insert y/n: ";
		std::cin >> command;
		if (command == 'Y' || command == 'y')
			break;
	}

	return 0;
}