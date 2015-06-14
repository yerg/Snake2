#include "Connections.h"

void Connection::Send(Section* data, size_t size/* =1 */){
	sock->send(buffer(data,size));
}
void Connection::Send(int* data, size_t size){
	sock->send(buffer(data,size));
}

void Connection::Recieve(std::vector<Section> &data){
	sock->receive(buffer(data));
}
void Connection::Recieve(std::vector<int> &data){
	sock->receive(buffer(data));
}

void Connection::CloseConnection(){
	if (sockInit && sock->is_open())
	{
		sock->shutdown(socket_base::shutdown_both);
		sock->close();
	}
}

void ServerConnection::AcceptConnection(std::function<void(const boost::system::error_code&)> handler){
	sock=make_shared<ip::tcp::socket>(service);
	sockInit=true;
	acceptor.async_accept(*sock,handler);
}

void ServerConnection::StopAccepting(){
	acceptor.cancel();
}

bool ClientConnection::Connect(const std::string &sIP){
	try{
		sock=make_shared<ip::tcp::socket>(service);
		sockInit=true;
		ep=ip::tcp::endpoint( ip::address::from_string(sIP), port);
		sock->connect(ep);
		return true;
	} 
	catch (boost::system::system_error) 
	{
		CloseConnection();
		return false;
	}
}
