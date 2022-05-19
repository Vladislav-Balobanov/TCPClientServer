#pragma once
#include <iostream>
#include <boost\asio.hpp>

using namespace boost::asio;

class SyncClient
{
public:
	SyncClient(boost::asio::io_service& ioService);
	void syncConnect();
	void writeString(std::string message);
private:
	boost::asio::io_service m_service;
	ip::tcp::socket m_socket;
	ip::tcp::endpoint m_endpoint;
	std::thread m_thread;
};

SyncClient::SyncClient(boost::asio::io_service& ioService) :	m_endpoint(ip::address::from_string("127.0.0.1"), 8001),
																m_socket(ioService)
{ }

inline void SyncClient::syncConnect()
{
	m_thread = std::thread([&]() {m_socket.connect(m_endpoint); });

	std::cout << "connection succeded!" << std::endl;
}

inline void SyncClient::writeString(std::string message)
{
	const std::string msg = message + "\n";
	boost::asio::write(m_socket, boost::asio::buffer(msg));
}