//! @file 
//! @brief Header file for the NPC class  
//!

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

//! Class that implements an NPC (passive or aggressive behavior)
class NPC

{
public:
	//contsructor, getter and setter
	NPC();
	NPC(int, int, int, int, int, int, bool);
	void hit(int);
	void enchant(int);
	int getHitPoints();
	int getarmorClass();
	int getAttackBonus();
	int getDamageBonus();
	void makeAggro();
	bool getAggro();
	void setX(int X);
	int getX();
	void setY(int Y);
	int getY();
	int * getAbilityScores() { return abilityScores; }
	int getCurrentHitPoints() { return currentHitPoints; }
	//dead NPC
	void die();
	bool getAlive();
	int getLevel();
	void levelUp();

private:
	int abilityScores[6];
	int currentHitPoints;

	int armorClass;
	int attackBonus;
	int damageBonus;
	int level;

	bool aggro;
	int xValue;
	int yValue;
	bool alive;


};

