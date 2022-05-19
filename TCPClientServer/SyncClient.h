#pragma once
#include <iostream>
#include <boost\asio.hpp>
#include <boost\thread.hpp>

using namespace boost::asio;

class Client
{
public:
	Client(boost::asio::io_service& ioService);
	void syncConnect();
	void sendString(std::string message);
	std::string getString();
private:
	boost::asio::io_service m_service;
	ip::tcp::socket m_socket;
	ip::tcp::endpoint m_endpoint;
	std::string m_message;
};

Client::Client(boost::asio::io_service& ioService) : m_endpoint(ip::address::from_string("127.0.0.1"), 80),
													 m_socket(ioService),
													 m_message("")
{ }

inline void Client::syncConnect()
{
	m_socket.connect(m_endpoint);
	sendString("Connection!");
	m_message = getString();
}

inline void Client::sendString(std::string sendingMessage)
{
	sendingMessage += "\n";
	m_socket.write_some(boost::asio::buffer(sendingMessage));
}

inline std::string Client::getString()
{
	char buffer[512];
	read_until(m_socket,boost::asio::basic_streambuf(m_message), "\n");
	
	return "";
}