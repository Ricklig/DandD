#include <iostream>
#include<cstdlib>
#include<regex>
#include <string>
#include<time.h>
#include "Dice.h"

using namespace std;


//! Implementation of the rolling dice
//! @param string : a string of the form "xdy[+z]".
//! @return an integer which is the addition of the value of all dice and return -1 when the expression dose not follow he right format

int Dice::roll(string string) {


	Dice myDice;

	smatch sm;
	const regex format1("(\\d+)d(\\d+)\\+(\\d+)$");
	const regex format2("(\\d+)d(\\d+)$");

	int totalScore = 0;
	int lastRoll = 0;
	int numberOfDice;
	int sizeOfDice;
	int bonus;

	//!test to see if input meets format of the first regular expression
	if (regex_search(string, sm, format1)) {

		numberOfDice = stoi(sm[1]); 
		sizeOfDice = stoi(sm[2]); 
		bonus = stoi(sm[3]); 
	
	//!test to see if input meets format of the second regular expression
	} else if (regex_search(string, sm, format2)) {

		numberOfDice = stoi(sm[1]); 
		sizeOfDice = stoi(sm[2]); 
		bonus = 0;

	//!if the user input does no match either expressions, return -1
	} else {

		cout << "Wrong format...." << endl;
		return -1;

	}

	cout << "You have rolled " << numberOfDice << " dice of size: " << sizeOfDice << " and added "
			<< bonus << " to your total score" << endl;
	
	//!loop to roll the dice multiple times.
	for (int i = 0; i < numberOfDice ; i++) {

		lastRoll = (rand() % sizeOfDice) + 1;
		cout << "You rolled " << lastRoll << endl;
		totalScore += lastRoll;

	}

	//!add bonus to total score
	totalScore += bonus;

	cout << "Your total score is: " << totalScore << endl;
	
	message = "Dice was rolled... TotalScore: " + to_string(totalScore) + "\n";
	notify(); //! notify observer that dice has been rolled and write message into GameLog
	return totalScore;
	
}

/*

This was added to give the stats to the different characters, the main dice roll function is above

*/


int Dice::charRoll(string string) {

	smatch sm;
	const regex format1("(\\d+)d(\\d+)\\+(\\d+)$");
	const regex format2("(\\d+)d(\\d+)$");

	int totalScore = 0;
	int lastRoll = 0;
	int numberOfDice;
	int sizeOfDice;
	int bonus;
	int min = 0;
	int temp;

	//!test to see if input meets format of the first regular expression
	if (regex_search(string, sm, format1)) {

		numberOfDice = stoi(sm[1]);
		sizeOfDice = stoi(sm[2]);
		bonus = stoi(sm[3]);

		//!test to see if input meets format of the second regular expression
	}
	else if (regex_search(string, sm, format2)) {

		numberOfDice = stoi(sm[1]);
		sizeOfDice = stoi(sm[2]);
		bonus = 0;

		//!if the user input does no match either expressions, return -1
	}
	else {

		cout << "Wrong format...." << endl;
		return -1;

	}


	//!loop to roll the dice multiple times.
	for (int i = 0; i < numberOfDice; i++) {

		lastRoll = (rand() % sizeOfDice) + 1;
		if (i == 0)
			min = lastRoll;
		else if (lastRoll < min) {
			temp = min;
			min = lastRoll;
			totalScore += temp;
		}
		else
			totalScore += lastRoll;

	}

	//!add bonus to total score
	totalScore += bonus;
	return totalScore;
}


