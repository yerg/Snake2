#include "GameScreens.h"

void ServerInput::Start(){
	direction=UP;
	newDirection=UP;
}

void ServerInput::Update(){
	finish=game->IsServerFinished();
	if (finish!=FREE) 
	{
		game->StopGameSession();
		game->FinalServerMenu(finish);
	}
	else if (game->CheckServerConnections()) 
	{
		input->CheckDirection(newDirection);
		if (direction!=newDirection) newDirection=direction;
		if (input->IsExit()) game->Exit();
	}
	else 
	{
		game->StopGameSession();
		game->CloseServer();
	}
}

void ClientInput::Start(){
	direction=DOWN;
	last=DOWN;
}

void ClientInput::Update(){
	finish=game->IsClientFinished();
	if (finish!=FREE) 
	{
		game->StopGameSession();
		game->FinalClientMenu(finish);
	}
	else if (game->CheckClientConnections())
	{
		input->CheckDirection(direction);
		if (direction!=last)
		{
			last=direction;
			try
			{
				clientOut->Send(&direction);
			}
			catch (...)
			{
				game->StopGameSession();
				game->CloseClient();
			}
		}
	}
	else 
	{
		game->StopGameSession();
		game->CloseClient();
	}
}