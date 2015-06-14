#include "Game.h"

Game::Game()
{
	run = true;
	stopGameSession = true;
}

int Game::Execute(int width, int height, const char *title)
{
	graphics = make_shared<Graphics>(width, height, title);
	input = make_shared<Input>();
	mainScreen = make_shared<MainScreen>();
	connectScreen = make_shared<ConnectScreen>();
	serverScreen = make_shared<ServerScreen>();
	serverIn=make_shared<ServerConnection>(25255);
	serverOut=make_shared<ServerConnection>(25256);
	clientIn=make_shared<ClientConnection>(25256);
	clientOut=make_shared<ClientConnection>(25255);
	drawer=make_shared<Drawer>(graphics.get());


	screen=mainScreen;
	screen->SetController(this,input.get(),graphics.get());

	this->screen->Start();

	while(run)
	{
		input->Update();
		screen->Update();
	}

	screen->Destroy();


	return 0;
}

void Game::SetScreen(shared_ptr<Screen> &screen)
{
	this->screen = screen;
	this->screen->SetController(this,input.get(),graphics.get());
	this->screen->Start();
}

void Game::Exit()
{
	stopGameSession = true;
	run = false;
	SDL_WaitThread(thClient,&tmp);
	SDL_WaitThread(thSnake,&tmp);
	SDL_WaitThread(thServer,&tmp);
}

void Game::CreateServer(int w, int h, int lenght, int penalty, int speed, int acc){
	serverOut->AcceptConnection(boost::bind(HandleAccept,&countConnections,_1));
	serverIn->AcceptConnection(boost::bind(HandleAccept,&countConnections,_1));
	this->w=w; this->h=h; this->lenght=lenght; this->penalty=penalty; this->speed=speed; this->acc=acc;
}

void Game::CheckNewConnections(){
	serverIn->Poll();
	serverOut->Poll();
	if (countConnections==2)
	{
		serverReciever=make_shared<serverReciever>(serverIn,&stopGameSession);
		snake=make_shared<Snake>(drawer, serverOut, w, h, lenght, penalty, speed, acc, &stopGameSession,serverReciever->GetDirection(),s<>serverInput->GetDirection());
	}
	else if (countConnections<0)
	{
		StopServer();
		SetScreen(mainScreen);
	}
}

void Game::StopServer(){
	serverIn->StopAccepting();
	serverOut->StopAccepting();
}

bool Game::ConnectToServer(std::string ipString){
	if(clientIn->Connect(ipString))
	{
		if (clientOut->Connect(ipString))
		{
			clientReciever=make_shared<ClientReciever>(drawer,clientIn,&stopGameSession);
			thClient=SDL_CreateThread(ThreadClient,"Client_Reciever",clientReciever.get());
			SetScreen(clientInput);
			return true;
		}
		else clientIn->CloseConnection();
	}
	return false;
}

void Game::CloseServer(){
	SDL_WaitThread(thSnake,&tmp);
	SDL_WaitThread(thServer,&tmp);
	serverReciever.reset();
	snake.reset();
	SetScreen(mainScreen);
}

void Game::CloseClient(){
	SDL_WaitThread(thClient,&tmp);
	clientReciever.reset();
	SetScreen(mainScreen);
}


void Game::FinalServerMenu(Section s){
	std::cout<<std::endl<<static_cast<char>(s);
	CloseServer();
}
void Game::FinalClientMenu(Section s){
	std::cout<<std::endl<<static_cast<char>(s);
	CloseClient();
}

bool Game::CheckServerConnections(){
	if (!(serverReciever->Connection() && snake->Connection()))
	{
		StopGameSession();
		return false;
	}
	return true;
}

bool Game::CheckClientConnections(){
	if (!clientReciever->Connection())
	{
		StopGameSession();
		return false;
	}
	return true;;
}

Section Game::IsServerFinished(){
	Section s;
	s=snake->IsFinished();
	if (s!=FREE) StopGameSession();
	return s;
}
Section Game::IsClientFinished(){
	Section s;
	s=clientReciever->IsFinished();
	if (s!=FREE) StopGameSession();
	return s;
}

int ThreadClient(void * data){
	static_cast<ClientReciever*>(data)->Loop();
	return 0;
}
int ThreadSnake(void * data){
	static_cast<Snake*>(data)->GameLoop();
	return 0;
}
int ThreadServer(void * data){
	static_cast<ServerReciever*>(data)->Loop();
	return 0;
}

void HandleAccept(int* count, const boost::system::error_code & err) {
	if (err) 
	{
		*count=-2;
		return;
	}
	*count++;
}