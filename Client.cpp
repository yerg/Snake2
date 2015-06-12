#include "Client.h"

void ClientInput::Start(){
	direction=FREE;
	last=FREE;
}

void ClientInput::Update(){
	input->CheckDirection(direction);
	if (direction!=last)
	{
		last=direction;
		clientOut->Send(&direction);
	}
}