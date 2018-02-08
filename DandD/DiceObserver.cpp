#include "DiceObserver.h"


DiceObserver::DiceObserver()
{
}


DiceObserver::~DiceObserver()
{
}

void DiceObserver::update()
{
	if (!turnOffLog)
	logMessage(); //!logs messages into GameLog file
}
