#include "Game.h"


int Game::Execute(const char *title) try
{

	graphics = make_shared<Graphics>(WIDTH, HEIGHT, title);
	input = make_shared<Input>();
	mainScreen = make_shared<MainScreen>();
	connectScreen = make_shared<ConnectScreen>();
	serverScreen = make_shared<ServerScreen>();
	serverIn=make_shared<ServerConnection>(25255);
	serverOut=make_shared<ServerConnection>(25256);
	clientIn=make_shared<ClientConnection>(25256);
	clientOut=make_shared<ClientConnection>(25255);
	drawer=make_shared<Drawer>(graphics.get());
	serverInput=shared_ptr<ServerInput>(rawServerInput=new ServerInput);
	clientInput=shared_ptr<ClientInput>(rawClientInput=new ClientInput);



	screen=mainScreen;
	screen->SetController(this,input.get(),graphics.get());

	this->screen->Start();

	while(run)
	{
		input->Update();
		screen->Update();
	}

	return 0;
}
catch (std::string &s)
{
	std::cout<<std::endl<<s<<std::endl<<"Press enter to exit...";
	getchar();
}
catch (const char * c)
{
	std::cout<<std::endl<<c<<std::endl<<"Press enter to exit...";
	getchar();
}
catch (...)
{
	std::cout<<std::endl<<"Unknown error"<<std::endl<<"Press enter to exit...";
	getchar();
}

void Game::SetScreen(shared_ptr<Screen> screen)
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

void Game::CreateServer(Settings s){
	serverIn->AcceptConnection(boost::bind(HandleAccept,&countConnections,_1));
	serverOut->AcceptConnection(boost::bind(HandleAccept,&countConnections,_1));
	settings=s;
}

void Game::CheckNewConnections(){
	serverOut->Poll();
	serverIn->Poll();
	if (countConnections==2)
	{
		stopGameSession=false;
		serverReceiver=make_shared<ServerReceiver>(serverIn,&stopGameSession);
		snake=make_shared<Snake>(drawer, serverOut,settings, &stopGameSession,rawServerInput->GetDirection(),serverReceiver->GetDirection());
		thServer=SDL_CreateThread(ThreadServer,"SNAKE2_Server_Reciever",serverReceiver.get());
		thSnake=SDL_CreateThread(ThreadSnake,"SNAKE2_GameLoop",snake.get());
		SetScreen(serverInput);
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
			stopGameSession=false;
			clientReceiver=make_shared<ClientReceiver>(drawer,clientIn,&stopGameSession);
			thClient=SDL_CreateThread(ThreadClient,"SNAKE2_Client_Reciever",clientReceiver.get());
			rawClientInput->SetConnection(clientOut.get());
			SetScreen(clientInput);
			return false;
		}
		else clientIn->CloseSocket();
	}
	return true;
}

void Game::CloseServer(){
	stopGameSession=true;
	SDL_Delay(15);
	serverIn->StopAccepting();
	serverOut->StopAccepting();
	SDL_WaitThread(thSnake,&tmp);
	thSnake=NULL;
	SDL_WaitThread(thServer,&tmp);
	thServer=NULL;
	serverReceiver.reset();
	snake.reset();
	graphics->SetResolution(WIDTH,HEIGHT);
	SetScreen(mainScreen);
}

void Game::CloseClient(){
	stopGameSession=true;
	SDL_Delay(15);
	clientIn->CloseSocket();
	clientOut->CloseSocket();
	SDL_WaitThread(thClient,&tmp);
	thClient=NULL;
	clientReceiver.reset();
	rawClientInput->SetConnection(NULL);
	graphics->SetResolution(WIDTH,HEIGHT);
	SetScreen(mainScreen);
}


void Game::FinalServerMenu(Section s){
	std::cout<<std::endl<<static_cast<int>(s);	//Dummy
	CloseServer();
}
void Game::FinalClientMenu(Section s){
	std::cout<<std::endl<<static_cast<int>(s);	//Dummy
	CloseClient();
}

bool Game::CheckServerConnections(){
	if (!(serverReceiver->Connection() && snake->Connection()))
	{
		StopGameSession();
		return false;
	}
	return true;
}

bool Game::CheckClientConnections(){
	if (!clientReceiver->Connection())
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
	s=clientReceiver->IsFinished();
	if (s!=FREE) StopGameSession();
	return s;
}

int ThreadClient(void * data){
	static_cast<ClientReceiver*>(data)->Loop();
	return 0;
}
int ThreadSnake(void * data){
	static_cast<Snake*>(data)->GameLoop();
	return 0;
}
int ThreadServer(void * data){
	static_cast<ServerReceiver*>(data)->Loop();
	return 0;
}

void HandleAccept(int* count, const boost::system::error_code & err) {
	if (err) 
	{
		*count=-3;
		return;
	}
	(*count)+=1;
}