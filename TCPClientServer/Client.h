#pragma once
#include <boost\asio.hpp>
#include <boost\system.hpp>
#include <boost\thread.hpp>

using namespace boost::asio::ip;

enum Commands
{
	serverStart = 1,
	ServerStop = 2
};

class Client
{
public:
	Client(boost::asio::io_service& ioService, 
		tcp::endpoint endpoint) : 
			m_socket(ioService),
			m_endpoint(endpoint)
	{ }
	~Client() {}

	void syncConnect(boost::system::error_code& error_code);
	void disconnect();
	void sendString(std::string message);
	std::string getString();
private:
	boost::asio::io_service m_ioService;
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
	std::vector<std::string> m_commands;
};

void Client::syncConnect(boost::system::error_code& error_code)
{
	m_socket.connect(m_endpoint, error_code);
}

inline void Client::disconnect()
{
	m_socket.shutdown(tcp::socket::shutdown_both);
}

inline void Client::sendString(std::string message)
{
	boost::asio::streambuf buffer;
	std::ostream req_strm(&buffer);
	req_strm << message << "\n";

	boost::asio::write(m_socket, buffer);
	req_strm.clear();
}

inline std::string Client::getString()
{
	char data[4096];
	std::size_t bytes = 0;
	bytes = m_socket.read_some(boost::asio::buffer(data));

	if (bytes > 0)
	{
		return std::string(data, bytes);
	}

	return "Empty.";
}
