#include "Connections.h"

void Connection::Send(Section* data, size_t size/* =1 */){
	sock->send(buffer(data,size* sizeof(Section)));
}
void Connection::Send(int* data, size_t size){
	sock->send(buffer(data, size* sizeof(int)));
}

void Connection::Receive(std::vector<Section> &data, int size){
	shared_ptr<Section> buf(new Section [size*sizeof Section]);
	int n;
	n=sock->receive(buffer(buf.get(),size));
	data.assign(buf.get(), buf.get() + n*sizeof Section);
}
void Connection::Receive(std::vector<int> &data){
	int buf[4];
	int n;
	n=sock->receive(buffer(buf));
	data.assign(&buf[0],&buf[n]);
}

void Connection::ReceiveButton(Direction &d){
	Direction buf[1];
	sock->receive(buffer(buf));
	d=buf[0];
}

void Connection::CloseSocket(){
	sock.reset();
}

void ServerConnection::AcceptConnection(std::function<void(const boost::system::error_code&)> handler){
	sock=make_shared<ip::tcp::socket>(service);
	acceptor=make_shared<ip::tcp::acceptor>(service, ip::tcp::endpoint(ip::tcp::v4(),port));
	acceptor->async_accept(*sock,handler);
}

void ServerConnection::StopAccepting(){
	acceptor.reset();
	CloseSocket();
}

bool ClientConnection::Connect(const std::string &sIP){
	try{
		sock=make_shared<ip::tcp::socket>(service);
		ep=ip::tcp::endpoint( ip::address::from_string(sIP), port);
		sock->connect(ep);
		return true;
	} 
	catch (boost::system::system_error) 
	{
		CloseSocket();
		return false;
	}
}
