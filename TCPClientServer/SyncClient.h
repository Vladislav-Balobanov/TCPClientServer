#pragma once
#include <iostream>
#include <boost\asio.hpp>

using namespace boost::asio;

class SyncClient
{
public:
	SyncClient();
	void syncConnect();
	void writeString(std::string message);
private:
	boost::asio::io_service m_service;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::ip::tcp::endpoint m_endpoint;
	boost::asio::io_context m_context;
};

SyncClient::SyncClient() :	m_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8001),
							m_socket(m_service)
{ }

inline void SyncClient::syncConnect()
{
	m_socket.connect(m_endpoint);
	std::cout << "connection succeded!" << std::endl;
}

inline void SyncClient::writeString(std::string message)
{
	const std::string msg = message + "\n";
	boost::asio::write(m_socket, boost::asio::buffer(message));
}