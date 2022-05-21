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
		m_acceptor(ioService, m_endpoint),
		m_delimiter("\n")
	{}
	~Server() {}

	void start();
	void stop();
	std::string getString();
	void sebdString(std::string message);
private:
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
	tcp::acceptor m_acceptor;
	std::string m_delimiter;
};

void Server::start()
{
	m_acceptor.accept(m_socket);
}

void Server::stop()
{
	m_socket.shutdown(tcp::socket::shutdown_both);
}

inline std::string Server::getString()
{
	boost::asio::streambuf buffer;
	std::size_t bytes = 0;
	bytes = boost::asio::read_until(m_socket, buffer, m_delimiter);
	
	if (bytes == 0)
		return "Empty.";
	else
	{
		std::istream is(&buffer);
		std::string line;
		std::getline(is, line);
		return line;
	}
}

inline void Server::sebdString(std::string message)
{
	m_socket.write_some(boost::asio::buffer(message));
}