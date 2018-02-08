#include "CharacterObserver.h"
#include "Character.h"

CharacterObserver::CharacterObserver()
{

}

CharacterObserver::~CharacterObserver()
{

}

void CharacterObserver::update()
{
	

		auto status = ((Character*)subject)->calcStats();
		std::cout << ((Character*)subject)->getCurrentHitPoints() << " = HP;" << endl <<
			status[0] << " = strength" << endl <<
			status[1] << " = dexterity" << endl <<
			status[2] << " = constitution" << endl <<
			status[3] << " = intelligence" << endl <<
			status[4] << " = wisdom" << endl <<
			status[5] << " = charisma" << endl << endl << endl;

		if (!turnOffLog)
	logMessage(); //!logs messages into GameLog file

}



