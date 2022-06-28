#pragma once
#include "resources.h"
#include "Client.h"
#include "Server.h"

using namespace boost::asio::ip;

bool answerChecker(char answer)
{
	if (answer == 'y' || answer == 'Y')
		return true;
	else if (answer == 'n' || answer == 'N')
		return false;
	else
		throw std::exception(WRONG_COMMAND);
}

char getUserAnswer(std::string serviceMessage)
{
	char answer;
	std::cout << serviceMessage;
	std::cin >> answer;
	std::cin.ignore();
	return answer;
}

int main()
{
	// Блок инициализации:
	std::string message;
	boost::asio::io_service ioService;
	tcp::endpoint endpoint(address::from_string("127.0.0.1"), 80);
	boost::system::error_code error;
	boost::thread threadServer;
	boost::thread threadClient;

	// Блок подключения клиента и сервера:
	Client client(ioService, endpoint);
	Server server(ioService, endpoint);
	
	try
	{
		if (answerChecker(getUserAnswer(HELLO_MESSAGE)))
		{
			// Запуск сервера:
			threadServer = boost::thread([&]() {server.start(); });

			// Синхронное подключение клиента:
			threadClient = boost::thread([&]() {client.syncConnect(error); });
		}
		else
		{
			throw std::exception(GOODBY_MESSAGE);
		}

		if (answerChecker(getUserAnswer(CHOICE_METHOD)))
			while (true)
			{
				ioService.run();
				std::cout << "Insert message here: ";
				std::getline(std::cin, message);

				// Асинкхронная запись строки:
				boost::thread([&]() {client.asyncSendMessage(message, error); });

				// Синхронное чтение строки:
				threadServer = boost::thread([&]() {server.print(); });
				threadServer.join();
			}
		else
			while (true)
			{
				std::cout << "Insert message here: ";
				std::getline(std::cin, message);

				// Синкхронная запись строки:
				threadClient = boost::thread([&]() {client.sendMessage(message); });
				threadClient.join();

				// Синхронное чтение строки:
				threadServer = boost::thread([&]() {server.print(); });
				threadServer.join();
			}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	system("pause");
	return 0;
}