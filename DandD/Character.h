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
#include <iostream>
#include <string>
#include <vector>
#include "Observer.h"
#include "Item.h"
#include <map>

class Character : public Subject

{
public:

	Character();
	Character(char);
	bool validateNewCharacter();
	void hit(int);
	void enchant(int);
	int getHitPoints();
	int getarmorClass();
	int getAttackBonus();
	int getDamageBonus();
	int getLevel() { return level; }
	int * getAbilityScores() { return abilityScores; }
	int getCurrentHitPoints() { return currentHitPoints; }

	void addToBag(Item*item);
	void removeFromBag(Item*item);
	void levelUp();

	int getFirstAttack();

	int getSecondAttack();

	int getThirdAttack();

	int getFourthAttack();

	void save();

	Character(string load);

	void printBag();

	void printEquip();

	Item getBagItem(string search);

	Item getEquipItem(string search);

	void equip(Item*item);
	void unequip(Item);

	int * calcStats() {
		int * tempStats = new int[9];
		for (int i = 0; i < 6; i++)
			tempStats[i] = abilityScores[i];
		//tempStats[6] = armorClass;
		//tempStats[7] = attackBonus;
		//tempStats[8] = damageBonus;

		std::map<string, int> characterStats;
		for (auto item : equipped) {
			for (auto stats : item.calculateEnhancements()) {
				string type = stats.first;
				int value = stats.second;

				if (type == "Strength")
					tempStats[0] += value;
				if (type == "Dexterity")
					tempStats[1] += value;
				if (type == "Constitution")
					tempStats[2] += value;
				if (type == "Intelligence")
					tempStats[3] += value;
				if (type == "Wisdom")
					tempStats[4] += value;
				if (type == "Charisma")
					tempStats[5] += value;
				/*	if (type == "armorClass")
				tempStats[6] += value;
				if (type == "AttackBonus")
				tempStats[7] += value;
				if (type == "DamageBonus")
				tempStats[8] += value;*/
			}
		}

		return tempStats;
	}

private:
	int abilityScores[6];
	int currentHitPoints;
	int maxHitPoints;
	int unsorted[6];
	int armorClass;
	int attackBonus;
	int damageBonus;
	int level;
	int attPerTurn[4];
	std::vector<Item> backpack;

	std::vector<Item> equipped;



};