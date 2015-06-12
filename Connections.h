#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <boost/asio.hpp>
using boost::asio;

class Connection{
protected:
	io_service service;
	ip::tcp::endpoint ep;
	ip::tcp::socket sock;
public:
	void Send(void* data, size_t  size=1);
	void Recieve();
	virtual bool Connect()=0;
};
class Server : public Connection{
public:
	Server();
	~Server();
};

class Client : public Connection{

public:
	Client();
	~Client();
	bool Connect(const std::string &sIP);


};

#endif