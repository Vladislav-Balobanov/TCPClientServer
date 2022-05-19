#pragma once
#include <boost\asio.hpp>
#include <boost\system.hpp>

using namespace boost::asio::ip;

class Client
{
public:
	Client() :	m_socket(m_ioService),
				m_endpoint(address::from_string("127.0.0.1"), 80) 
	{}
	void syncConnect();
	void disconnect();
private:
	boost::asio::io_service m_ioService;
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
};