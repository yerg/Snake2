#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "Enums.h"
#include "Independent.h"
#include <boost/asio.hpp>

typedef std::function<void(const boost::system::error_code&)> AcceptHandler;

using namespace boost::asio;

class Connection{
protected:
	boost::system::error_code err;
	io_service service;
	shared_ptr<ip::tcp::socket> sock;
public:
	Connection(){}
	void Send(Section* data, size_t  size=1);
	void Recieve(std::vector<Section> &data);
	void CloseConnection();
	~Connection(){CloseConnection();}
};


class ServerConnection : public Connection{
	ip::tcp::acceptor acceptor;
public:
	ServerConnection() : acceptor(service, ip::tcp::endpoint(ip::tcp::v4(),25255)){}
	void AcceptConnection(AcceptHandler handler);
};

class ClientConnection : public Connection{
	ip::tcp::endpoint ep;
public:
	bool Connect(const std::string &sIP);
};

#endif