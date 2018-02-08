//! @file 
//! @brief Header file for the Campaign class  
//!
#pragma once
#include "Map.h"	
using namespace std;

int const CAMPAIGN_SIZE = 4;

//! class for the implementation of a campaign that is made of between 2 and 4 maps
class Campaign
{
public:
	//Constructors
	Campaign();
	Campaign(Map startMap, Map endMap);
	Campaign(Map startMap, Map intermediateM1, Map endMap);
	Campaign(Map startMap, Map intermediateM1, Map intermediateM2, Map endMap);
	//display campaign maps
	void displayStart();
	void displayInt1();
	void displayInt2();
	void displayEnd();
	//write to file
	void toFileStart(string fileName);
	void toFileInt1(string fileName);
	void toFileInt2(string fileName);
	void toFileEnd(string fileName);
	//return campaign maps
	Map* getStartM();
	void setStartM(Map startM);
	Map* getInt1M();
	void setInt1M(Map int1M);
	Map* getInt2M();
	void setInt2M(Map int2M);
	Map* getEndM();
	void setEndM(Map endM);
	//swap starting and ending map
	void Campaign::swapMap();
	int getSize();

private:
	Map *startingMap, *endingMap, *intermediateMap1, *intermediateMap2;
	int size;
};

