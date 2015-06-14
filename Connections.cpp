#include "Connections.h"

void ServerConnection::AcceptConnection(AcceptHandler handler){
	sock=make_shared<ip::tcp::socket>(service);
	acceptor.async_accept(*sock,handler);
}

bool ClientConnection::Connect(const std::string &sIP){
	try{
		ep=ip::tcp::endpoint( ip::address::from_string(sIP), 25255);
		sock=make_shared<ip::tcp::socket>(service);
		sock->connect(ep);
		return true;
	} 
	catch (boost::system::system_error) 
	{
		CloseConnection();
		return false;
	}
}

void Connection::CloseConnection(){
	sock->shutdown(socket_base::shutdown_both);
	sock->close();
}

void Connection::Send(Section* data, size_t size/* =1 */){
	sock->send(buffer(data,size));
}

void Connection::Recieve(std::vector<Section> &data){
	sock->receive(buffer(data));
}

