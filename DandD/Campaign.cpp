//! @file 
//! @brief Implementation file for the Campaign class  
//!
#include "Map.h"
#include "Campaign.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


ofstream output;

//! default constructor
//! 
//!	constructor that receives a number of maps and sets the starting them according to their relationship to campaign
//!
//! @param startMap : Map representing starting map
//! @param endingMap : Map representing ending map
//! @param intermediate1Map : Map representing intermediate map (1)
//! @param intermediate2Map : Map representing intermediate map (2)
Campaign::Campaign() {
	Campaign::startingMap = &Map();
	Campaign::intermediateMap1 = &Map();
	Campaign::intermediateMap2 = &Map();
	Campaign::endingMap = &Map();
}

//! constructor for a campaign of size 2 
//!	
//! @param startMap : Map representing starting map
//! @param endingMap : Map representing ending map
Campaign::Campaign(Map startMap, Map endMap) {
	Campaign::startingMap = &startMap;
	Campaign::endingMap = &endMap;
	size = 2;
}
//! constructor for a campaign of size 3 
//!	
//! @param startMap : Map representing starting map
//! @param endingMap : Map representing ending map
//! @param intermediate1Map : Map representing intermediate map (1)
Campaign::Campaign(Map startMap, Map intermediateM1, Map endMap) {
	Campaign::startingMap = &startMap;
	Campaign::endingMap = &endMap;
	Campaign::intermediateMap1 = &intermediateM1;
	size = 3;
}
//! constructor for a campaign of size 4 	
//! @param startMap : Map representing starting map
//! @param endingMap : Map representing ending map
//! @param intermediate1Map : Map representing intermediate map (1)
//! @param intermediate2Map : Map representing intermediate map (2)
Campaign::Campaign(Map startMap, Map intermediateM1, Map intermediateM2, Map endMap) {
	Campaign::startingMap = &startMap;
	Campaign::endingMap = &endMap;
	Campaign::intermediateMap1 = &intermediateM1;
	Campaign::intermediateMap2 = &intermediateM2;
	size = 4;
}
//! method to get display starting map
void Campaign::displayStart() {
	cout << "\nStarting map:\n";
	startingMap->printBoard();
}
//! method to get display intermediate map 1
void Campaign::displayInt1() {
	cout << "\nIntermediate map (1)\n";
	intermediateMap1->printBoard();
}
//! method to get display intermediate map 2
void Campaign::displayInt2() {
	cout << "\nIntermediate map (2)\n";
	intermediateMap2->printBoard();
}
//! method to get display ending map
void Campaign::displayEnd() {
	cout << "\nEnding map\n";
	endingMap->printBoard();
}
//! method to get write starting map to file
void Campaign::toFileStart(string fileName) {
	string campaignContent = "";
	output.open(fileName, ios_base::trunc);
	campaignContent = startingMap->stringContent() + "\n";

	output << campaignContent;

	output.close();
}
//! method to get write intermediate map 1 to file
void Campaign::toFileInt1(string fileName) {
	string campaignContent = "";
	output.open(fileName, ios_base::app);
	campaignContent = intermediateMap1->stringContent() + "\n";

	output << campaignContent;

	output.close();
}
//! method to get write intermediate map 2 to file
void Campaign::toFileInt2(string fileName) {
	string campaignContent = "";
	output.open(fileName, ios_base::app);
	campaignContent = intermediateMap2->stringContent() + "\n";

	output << campaignContent;

	output.close();
}
//! method to get write ending map to file
void Campaign::toFileEnd(string fileName) {
	string campaignContent = "";
	output.open(fileName, ios_base::app);
	campaignContent = campaignContent + endingMap->stringContent() + "\n";

	output << campaignContent;

	output.close();
}
//! method to get starting map
//! @return : starting map
Map* Campaign::getStartM()
{
	return startingMap;
}

void Campaign::setStartM(Map startM)
{
	startingMap = &startM;
}

void Campaign::setInt1M(Map Int1M)
{
	intermediateMap1 = &Int1M;
}
void Campaign::setInt2M(Map Int2M)
{
	intermediateMap2 = &Int2M;
}
void Campaign::setEndM(Map EndM)
{
	endingMap = &EndM;
}

//! method to get ending map
//! @return : ending map
Map* Campaign::getEndM()
{
	return endingMap;
}
//! method to get intermediate map 1
//! @return : intermediate map 1
Map* Campaign::getInt1M()
{
	return intermediateMap1;
}
//! method to get intermediate map 2
//! @return : intermediate map 2
Map* Campaign::getInt2M()
{
	return intermediateMap2;
}
//! method to get swap starting and ending map
void Campaign::swapMap() {
	Map *tempMap;
	tempMap = startingMap;
	startingMap = endingMap;
	endingMap = tempMap;
}

int Campaign::getSize() {
	return size;
}