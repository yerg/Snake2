#include "Client.h"

void ClientReceiver::Loop(){
	std::vector<int> a;
	if (!*stopChecker) try 
	{
		clientIn->Receive(a);
		drawer->Set(a[0],a[1],a[2],a[3]);
		map.reserve(a[0]*a[1]+2);
	}
	catch (...)
	{
		connection=false;
	}

	while (!*stopChecker && connection && gameFinished==FREE)
	{
		try 
		{
			clientIn->Receive(map, a[0]*a[1]+2);
		} 
		catch (...)
		{
			connection=false;
		}
		drawer->Draw(map);
		if (map.front()!=MAP) gameFinished=map.front();
	}
};