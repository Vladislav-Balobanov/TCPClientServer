#pragma once
#pragma once
#include <boost\asio.hpp>
#include <boost\system.hpp>
#include <boost\thread.hpp>

using namespace boost::asio::ip;

class Server
{
public:
	Server(boost::asio::io_service& ioService, 
		tcp::endpoint endpoint) : 
			m_socket(ioService),
			m_endpoint(endpoint),
			m_acceptor(ioService, m_endpoint)
	{}
	~Server() {}

	void start();
	void stop();
private:
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
	tcp::acceptor m_acceptor;
	boost::thread m_thread;
};

void Server::start()
{
	m_thread = boost::thread([&]() {m_acceptor.accept(m_socket); });
}

void Server::stop()
{
	m_socket.shutdown(tcp::socket::shutdown_both);
}