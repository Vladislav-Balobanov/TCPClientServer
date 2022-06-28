#pragma once
#include "resources.h"

using namespace boost::asio::ip;

class Client
{
public:
	Client(boost::asio::io_service& ioService, 
		tcp::endpoint endpoint) : 
			m_socket(ioService),
			m_endpoint(endpoint)
	{ }
	~Client() { disconnect(); }

	void syncConnect(boost::system::error_code& error_code);
	void asyncConnect(const boost::system::error_code& error_code);
	void connectionHandler(const boost::system::error_code& error_code);
	void writeHandler(const boost::system::error_code& error, size_t bytes_transfered);
	void disconnect();
	void sendMessage(std::string message);
	void asyncSendMessage(std::string message, boost::system::error_code& error_code);
	std::string getString();
private:
	boost::asio::io_service m_ioService;
	tcp::socket m_socket;
	tcp::endpoint m_endpoint;
	std::vector<char> m_buffer;
	std::string m_message;
};

void Client::syncConnect(boost::system::error_code& error_code)
{
	m_socket.connect(m_endpoint, error_code);
}

inline void Client::disconnect()
{
	m_socket.shutdown(tcp::socket::shutdown_both);
}

inline void Client::sendMessage(std::string message)
{
	boost::asio::streambuf buffer;
	std::ostream req_strm(&buffer);
	req_strm << message << "\n";

	boost::asio::write(m_socket, buffer);
	req_strm.clear();
}

inline void Client::asyncSendMessage(std::string message, boost::system::error_code& error_code)
{
	boost::asio::streambuf buffer;
	std::ostream req_strm(&buffer);
	req_strm << message << "\n";
	
	for (auto element : message)
		m_buffer.push_back(element);
	boost::asio::async_write
	(
		m_socket, buffer, 
		boost::bind
		(
			&Client::writeHandler, 
			this, 
			boost::asio::placeholders::error, 
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void Client::writeHandler(const boost::system::error_code& error_code, size_t bytes_transfered)
{
	if (error_code)
		return;
	if (bytes_transfered == m_buffer.size())
		 std::cout << "Sending message succeded.";
	else return;
}

inline std::string Client::getString()
{
	std::array<char, 4096> data;
	std::size_t bytes = 0;
	std::string result;

	bytes = m_socket.read_some(boost::asio::buffer(data));
	
	if (bytes > 0)
	{
		for (auto element : data)
		{
			result += element;
		}
		return result;
	}

	return "Empty.";
}
