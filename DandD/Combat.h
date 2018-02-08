/*!
*  Created on: Nov 27, 2016
*  Author: yasmine chiter
*	ID: 27175299
*
*  Game Rules:
*  The game uses dice which are denoted by their number of sides, 4, 6, 8, 10, 12, 20 or 100.
*  The most commonly used die is the d20, which determines whether or not a character succeeds at a given action.
*  The d6s are used to determine ability scores of players. The other dice are most
*  often used when determining how much damage a successful attack does.
*  Most actions are assigned a target that the player tries to roll over on the d20.
*  For example, a player attacking an opponent with an armor class of 15 might need to roll a 15 or higher
*  in order to hit that opponent. He might also have bonuses he can add to that attack roll.
*
*  Design:
*  The design for this part of the project was to create an Oberserver Class which the MapObserver class, CharacterObserver class and DiceObserver class can implement in
*  order to notify() changes that occur throughout the game. The purpose of this is to be able to log the changes into a unified game log. Changes include game setup, and takedown procedures.
*
*  Libraries used:
*  <iostream> in order to take input from user
*  <cstdlib> in order to use he random number generator
*  <ctime> in order to seed the random number generator
*  <regex> in order to parse the input using required regular expression
*  <stdio.h> in order to take input from user
*	<cppunit/TestCase.h> to perfrom the unit tests
*	<vector> To hold the objects
*
*/
#pragma once
#include "Character.h"
#include "NPC.h"

class Combat {
public:	
	bool fighting(Character&, NPC&);

};