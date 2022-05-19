#pragma once
#pragma once
#include <boost\asio.hpp>
#include <boost\system.hpp>

using namespace boost::asio::ip;

class Server
{
public:
	Server() :	m_socket(m_ioService),
				m_endpoint(address::from_string("127.0.0.1"), 80),
				m_acceptor(m_ioService, m_endpoint)
	{
		m_ioService.run();
	}
	~Server()
	{
		m_ioService.stop();
	}

	void start();
	void stop();
private:
	boost::asio::io_service m_ioService;
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
	tcp::acceptor m_acceptor;
};

void Server::start()
{
	m_socket.connect(m_endpoint);
	m_acceptor.accept(m_socket);
}

void Server::stop()
{
	m_socket.shutdown(tcp::socket::shutdown_both);
}