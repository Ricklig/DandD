//! @file 
//! @brief Implementation file for the NPC class  
//!
#include <iostream>;
#include "NPC.h"
using namespace std;


//! default constructor
NPC::NPC()
{
	abilityScores[0] = 2;
	abilityScores[1] = 2;
	abilityScores[2] = 2;
	abilityScores[3] = 2;
	abilityScores[4] = 2;
	abilityScores[5] = 2;

	//! and set hit points to 10 + con
	currentHitPoints = 10 + abilityScores[2]; // +dice::roll(1d10[0]);

											  // set armor class to base 10 + dex
	armorClass = 10 + abilityScores[1];

	//! set Attack Bonus to level + str + dex
	attackBonus = level + abilityScores[0] + abilityScores[1];

	//! set damage bonus to base + str
	damageBonus = 10 + abilityScores[0];

	aggro = false;
	alive = true;
}

//! Constructor: passes values to each ability score and set hit points to 10
NPC::NPC(int str, int dex, int con, int intel, int wis, int cha, bool aggroSet)
{
	abilityScores[0] = str;
	abilityScores[1] = dex;
	abilityScores[2] = con;
	abilityScores[3] = intel;
	abilityScores[4] = wis;
	abilityScores[5] = cha;

	level = 1;

	//! and set hit points to 10 + con
	currentHitPoints = 10 + abilityScores[2]; // +dice::roll(1d10[0]);

											  // set armor class to base 10 + dex
	armorClass = 10 + abilityScores[1];

	//! set Attack Bonus to level + str + dex
	attackBonus = level + abilityScores[0] + abilityScores[1];

	//! set damage bonus to base + str
	damageBonus = 10 + abilityScores[0];

	aggro = aggroSet;
	alive = true;
}


//! Implementation of taking damage
//! @param int: damage sustained by the character
void NPC::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;
	

	std::cout << "Enemy has been hit" << endl;
	
}

//! Implementation of enchanting stats
//! @param int: additional stats
void NPC::enchant(int plus)
{
	abilityScores[0] = abilityScores[0] + plus;
	std::cout << "Strength enchanted" << endl << endl;
	
}
//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int NPC::getHitPoints()
{
	return currentHitPoints;
}
//! Implementation of a getter method for armorClass
//! @return int: value of armorClass
int NPC::getarmorClass()
{
	return armorClass;
}
//! Implementation of a getter method for attackBonus
//! @return int: value of attackBonus
int NPC::getAttackBonus()
{
	return attackBonus;
}
//! Implementation of a getter method for damageBonus
//! @return int: value of damageBonus
int NPC::getDamageBonus()
{
	return damageBonus;
}
//! Method to set NPC's aggro to true
void NPC::makeAggro() {
	aggro = true;
}
//! Implementation of a getter method for aggro
//! @return bool: boolean value for whether or not NPC is aggressive
bool NPC::getAggro() {
	return aggro;
}
//! Method to set NPC's x value for the Map
//! @param int: x value for Map
void NPC::setX(int X) {
	xValue = X;
}
//! Implementation of a getter method for x value for Map
//! @return int: x value for Map
int NPC::getX() {
	return xValue;
}
//! Method to set NPC's y value for the Map
//! @param int: y value for Map
void NPC::setY(int Y) {
	yValue = Y;
}
//! Implementation of a getter method for y value for Map
//! @return int: y value for Map
int NPC::getY() {
	return yValue;
}
//! Method to kill NPC (set alive to false)
void NPC::die() {
	cout << "YOU KILLED ME! blargh (dead)" << endl;
	alive = false;
}
//! Implementation of a getter method for alive status
//! @return bool: boolean value for alive status
bool NPC::getAlive() {
	return alive;
}

int NPC::getLevel() {
	return level;
}

void NPC::levelUp() {
	level++;
}