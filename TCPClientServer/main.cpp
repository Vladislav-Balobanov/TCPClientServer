#pragma once
#include <iostream>
#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <string>
#include "Client.h"
#include "Server.h"

using namespace boost::asio::ip;

int main()
{
	std::string message;
	std::cout << "Isert message here: ";
	std::getline(std::cin, message);

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
	threadClient = boost::thread([&]() {client.sendString(message); });
	threadClient.join();
	// Синхронное чтение строки:
	threadServer = boost::thread([&]() {std::cout << "Getting string is: \"" << server.getString() << "\"" << std::endl; });
	threadServer.join();

	system("pause");
	return 0;
}