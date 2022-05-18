#pragma once
#include <boost\asio.hpp>
#include <string>

using namespace boost::asio;

class Server
{
public:
	Server() :	m_socket(m_ioService), 
				m_acceptor(m_ioService, ip::tcp::endpoint(ip::tcp::v4(), 1234)) { }
	void start();
	std::string readStringFromClient();
	void writeStringForClient(std::string message);
private:
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::io_service m_ioService;
	ip::tcp::acceptor m_acceptor;
};

inline void Server::start()
{
	m_acceptor.accept(m_socket);
}

std::string Server::readStringFromClient()
{
	boost::asio::streambuf buf;
	boost::asio::read_until(m_socket, buf, "\n");
	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	return data;
}

inline void Server::writeStringForClient(std::string message)
{
	const std::string msg = message + "\n";
	boost::asio::write(socket, boost::asio::buffer(message));
}