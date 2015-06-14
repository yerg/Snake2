#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "Enums.h"
#include "Independent.h"
#include <boost/asio.hpp>


using namespace boost::asio;

class Connection{
protected:
	boost::system::error_code err;
	io_service service;
	shared_ptr<ip::tcp::socket> sock;
	int port;
	bool sockInit;
public:
	Connection(int port) : port(port), sockInit(false){}
	void Send(Section* data, size_t  size=1);
	void Send(int* data, size_t size);
	void Recieve(std::vector<Section> &data);
	void Recieve(std::vector<int> &data);
	void CloseConnection();
	~Connection(){CloseConnection();}
};


class ServerConnection : public Connection{
	ip::tcp::acceptor acceptor;
public:
	ServerConnection(int port) : Connection(port),acceptor(service, ip::tcp::endpoint(ip::tcp::v4(),port)){}
	void AcceptConnection(std::function<void(const boost::system::error_code&)> handler);
	void Poll(){service.poll();}
	void StopAccepting();
};

class ClientConnection : public Connection{
	ip::tcp::endpoint ep;
public:
	ClientConnection(int port) : Connection(port){}
	bool Connect(const std::string &sIP);
};

#endif