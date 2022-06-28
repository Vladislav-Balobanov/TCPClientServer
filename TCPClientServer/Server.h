#pragma once
#include "resources.h"

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
	~Server() { stop(); }

	void start();
	void stop();
	std::string getMessage();
	void print();
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

inline std::string Server::getMessage()
{
	boost::asio::streambuf buffer;
	std::size_t bytes = 0;
	bytes = boost::asio::read_until(m_socket, buffer, m_delimiter);
	
	if (bytes != 0)
	{
		std::istream is(&buffer);
		std::string line;
		std::getline(is, line);
		return line;
	}
	return "Empty.";
}

inline void Server::print()
{
	std::cout << "Getting string is: \"" << getMessage() << "\"" << std::endl;
}