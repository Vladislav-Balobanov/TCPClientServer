#pragma once
#include <boost\asio.hpp>
#include <boost\system.hpp>

using namespace boost::asio::ip;

class Client
{
public:
	Client() :	m_socket(m_ioService),
				m_endpoint(address::from_string("127.0.0.1"), 80) 
	{
		m_ioService.run();
	}
	~Client() 
	{
		m_ioService.stop();
	}
	void syncConnect();
	void disconnect();
	void sendString(std::string message);
private:
	boost::asio::io_service m_ioService;
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
};

void Client::syncConnect()
{
	m_socket.connect(m_endpoint);
}

inline void Client::disconnect()
{
	m_socket.shutdown(tcp::socket::shutdown_both);
}

inline void Client::sendString(std::string message)
{
	message += "\n";
	boost::asio::write(m_socket, boost::asio::buffer(message));
}