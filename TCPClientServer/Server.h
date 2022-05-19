#pragma once
#include <boost\asio.hpp>
#include <string>
#include <thread>

using namespace boost::asio;

class Server
{
public:
	Server(io_service& ioService) :	m_socket(ioService), 
									m_acceptor(ioService, ip::tcp::endpoint(ip::tcp::v4(), 8001)) 
	{
		start();
	}
	~Server()
	{
		stop();
	}
	void start();
	void stop();
	std::string readStringFromClient();
	void writeStringForClient(std::string message);
private:
	std::thread m_thread;
	boost::asio::ip::tcp::socket m_socket;
	ip::tcp::acceptor m_acceptor;
};

inline void Server::start()
{
	m_thread = std::thread([&]() {m_acceptor.accept(m_socket); });
}

inline void Server::stop()
{
	m_acceptor.close();
}

std::string Server::readStringFromClient()
{
	boost::asio::streambuf buf;
	boost::asio::read_until(m_socket, buf, "\n");
	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	std::cout << data << std::endl;
	return data;
}

inline void Server::writeStringForClient(std::string message)
{
	const std::string msg = message + "\n";
	boost::asio::write(m_socket, boost::asio::buffer(message));
}