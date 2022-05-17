#pragma once
#include <boost/asio.hpp>

class SyncClient
{
public:
	SyncClient();
	~SyncClient();
private:
	boost::asio::io_service m_service;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::ip::tcp::endpoint m_endpoint;
};

