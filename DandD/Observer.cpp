#include "Observer.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Observer::Observer()
{
}

Observer::~Observer()
{
}

////logs messages into GameLog file
void Observer::logMessage()
{
	ofstream myfile("GameLog.txt", std::ios::app);

	if (myfile.is_open())
	{
		myfile << subject->message;
		myfile.close();
	}
	else cout << "Unable to open the game log file";
}