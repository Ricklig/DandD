#include "MapObserver.h"


MapObserver::MapObserver()
{
	
}

MapObserver::~MapObserver()
{

}

void MapObserver::update()
{
	if (!turnOffLog)
	logMessage(); //!logs messages into GameLog file
}



