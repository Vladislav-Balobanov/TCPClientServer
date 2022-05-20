#pragma once
#include <boost\asio.hpp>
#include <boost\system.hpp>
#include <boost\thread.hpp>

using namespace boost::asio::ip;

class Client
{
public:
	Client(boost::asio::io_service& ioService, 
		tcp::endpoint endpoint) : 
			m_socket(ioService),
			m_endpoint(endpoint)
	{}
	~Client() {}

	void syncConnect();
	void disconnect();
	void sendString(std::string message);
private:
	boost::asio::io_service m_ioService;
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
	boost::thread m_thread;
};

void Client::syncConnect()
{
	m_thread = boost::thread([&]() {m_socket.connect(m_endpoint); });
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