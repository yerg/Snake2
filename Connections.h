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
public:
	Connection(int port) : port(port){}
	void Send(Section* data, size_t  size=1);
	void Send(int* data, size_t size);
	void Receive(std::vector<Section> &data, int size);
	void Receive(std::vector<int> &data);
	void ReceiveButton(Direction &d);
	void CloseSocket();
};


class ServerConnection : public Connection{
	shared_ptr<ip::tcp::acceptor> acceptor;
public:
	ServerConnection(int port) : Connection(port){}
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