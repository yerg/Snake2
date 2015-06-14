#include "Client.h"

void ClientReciever::Loop(){
	std::vector<int> a;
	a.reserve(4);
	clientIn->Recieve(a);
	drawer->Set(a[0],a[1],a[2],a[3]);
	map.reserve(a[0]*a[1]);
	while (!*stopChecker && connection && gameFinished==FREE)
	{
		try 
		{
			clientIn->Recieve(map);
			if (map.front()==MAP) drawer->Draw(map);
			else gameFinished=map.front();
		} 
		catch (...)
		{
			connection=false;
		}
	}
};