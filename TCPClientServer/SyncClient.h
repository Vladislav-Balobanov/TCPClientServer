#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

class SyncClient
{
public:
	SyncClient();
	~SyncClient();
private:
	boost::asio::io_service m_service;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::ip::tcp::endpoint m_endpoint;
	boost::asio::io_context m_context;
	std::thread m_thread;
};

SyncClient::SyncClient() :	m_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8001),
							m_socket(m_service),
							m_thread([&]() {m_socket.connect(m_endpoint); })
{ }