//! @file 
//! @brief Implementation file for the Character class  
//!
#include <iostream>
#include <fstream>
#include "Character.h"
#include "Dice.h"
#include <iostream>
#include <algorithm>
using std::endl;

Character::Character()
{
}

Character::Character(char charSelect)
{
	unsorted[0] = Dice::charRoll("4d6");
	unsorted[1] = Dice::charRoll("4d6");
	unsorted[2] = Dice::charRoll("4d6");
	unsorted[3] = Dice::charRoll("4d6");
	unsorted[4] = Dice::charRoll("4d6");
	unsorted[5] = Dice::charRoll("4d6");
	sort(unsorted, unsorted + 6);

	if (charSelect == 'b')
	{
		abilityScores[0] = unsorted[5];//!= str;
		abilityScores[1] = unsorted[3]; //!= dex;
		abilityScores[2] = unsorted[4];//!= con;
		abilityScores[3] = unsorted[2];//!= intel;
		abilityScores[4] = unsorted[0];//!= wis;
		abilityScores[5] = unsorted[1];//!= cha; 
	}

	else if (charSelect == 'n')
	{
		abilityScores[0] = unsorted[3];//!= str;
		abilityScores[1] = unsorted[5]; //!= dex;
		abilityScores[2] = unsorted[4];//!= con;
		abilityScores[3] = unsorted[2];//!= intel;
		abilityScores[4] = unsorted[0];//!= wis;
		abilityScores[5] = unsorted[1];//!= cha;
	}
	else if (charSelect == 't')
	{
		abilityScores[0] = unsorted[3];//!= str;
		abilityScores[1] = unsorted[4]; //!= dex;
		abilityScores[2] = unsorted[5];//!= con;
		abilityScores[3] = unsorted[2];//!= intel;
		abilityScores[4] = unsorted[0];//!= wis;
		abilityScores[5] = unsorted[1];//!= cha;
	}
	else
	{
		abilityScores[0] = 3; //!= str;
		abilityScores[1] = 3;//!= dex;
		abilityScores[2] = 3; //!= con;
		abilityScores[3] = 3;//!= intel;
		abilityScores[4] = 3;//!= wis;
		abilityScores[5] = 3;//!= cha;
	}


	//! and set hit points to 10 + con
	maxHitPoints = 10 + abilityScores[2] + Dice::charRoll("1d10");
	currentHitPoints = maxHitPoints;

	//! set armor class to base 10 + dex
	armorClass = 10 + abilityScores[1];

	//!set Attack Bonus to level + str + dex
	attackBonus = level + abilityScores[0] + abilityScores[1];

	//!set damage bonus to base + str
	damageBonus = 10 + abilityScores[0];
	
	level = 1;

	attPerTurn[0] = attackBonus;
	if (level >= 5)
		attPerTurn[1] = -5 + attackBonus;
	if (level >= 10)
		attPerTurn[2] = -10 + attackBonus;
	if (level >= 15)
		attPerTurn[3] = -15 + attackBonus;
}



//! Implementation of the verification of a newly created Character
//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter()
{
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i]<3 || abilityScores[i]>18)
			return false;
	return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the character
void Character::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;
	std::cout << "Player has been hit" << endl << endl;
	notify();
}

void Character::enchant(int plus)
{
	abilityScores[0] = abilityScores[0] + plus;
	std::cout << "Strength enchanted" << endl << endl;
	notify();
}
//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}

int Character::getarmorClass()
{
	return armorClass;
}

int Character::getAttackBonus()
{
	return attackBonus;
}

int Character::getDamageBonus()
{
	return damageBonus;
}

void Character::addToBag(Item *item)
{
	bool taken = false;
	string type = item->getType();
	if (type != "") {

		for (auto iterator = backpack.begin(); iterator != backpack.end(); ++iterator) {
			if (iterator->getType() == item->getType()) {
				taken = true;
				cout << "You already have a " << type << " in your bag, the weaker item will be discarded." << endl << endl;
				if (iterator->getInfluences()[0].getBonus() < item->getInfluences()[0].getBonus()) {
					backpack.erase(iterator);
					backpack.push_back(*item);
				}
			}
		}
		if (!taken) {
			backpack.push_back(*item);
			std::cout << endl << "Added to bag!" << endl << endl;
		}
		else
		{
		}
	}
	else
		cout << "You do not own such an item!" << endl << endl;

}

void Character::removeFromBag(Item *item)
{
	for (auto iterator = backpack.begin(); iterator != backpack.end(); ++iterator) {
		if (iterator->getType() == item->getType()) {
			cout << iterator->getType() << " being erased from bag" << endl;
			backpack.erase(iterator);
			break;
		}
	}
}

void Character::equip(Item *item)
{
	bool taken = false;
	string type = item->getType();
	if (type != "") {

		for (auto iterator = equipped.begin(); iterator != equipped.end(); ++iterator) {
			if (iterator->getType() == item->getType()) {
				taken = true;
			}
		}
		if (!taken) {
			equipped.push_back(*item);
			std::cout << endl << "Equipped!" << endl << endl;
			removeFromBag(item);
			notify();
		}
		else
			cout << "You already have a " << type << " equipped, I'll just put this back in the bag for now..." << endl << endl;
	}
	else
		cout << "You do not own such an item!" << endl << endl;
}

void Character::unequip(Item item)
{
	for (auto iterator = equipped.begin(); iterator != equipped.end(); ++iterator) {
		if (*iterator == item) {

			equipped.erase(iterator);

			std::cout << endl << "unequipped" << endl << endl;
			notify();
			addToBag(&item);
			break;
		}
	}
}

void Character::levelUp() {
	level += 1;
	Dice dice;
	cout << "\n-----------------------------\n";
	cout << "Rolling for additional max HP...\n";
	maxHitPoints += dice.roll("1d10");
	
	cout << "\nPlayer has leveled up to level " << level << " and now has " << maxHitPoints << " HP\n";
	currentHitPoints = maxHitPoints;
	int div = (level - 1) / 5;
	for (int i = 0; i <= div; i++)
	{
		attPerTurn[i] ++;
		cout << "Attack number " << (i + 1) << " has an attack bonus is: " << attPerTurn[i] << endl << endl;
	}

}

int Character::getFirstAttack()
{
		return attPerTurn[0];

}

int Character::getSecondAttack()
{
	if (level > 5)
		return attPerTurn[1];
	else
		return 0;
}

int Character::getThirdAttack()
{
	if (level > 10)
		return attPerTurn[2];
	else
		return 0;
}

int Character::getFourthAttack()
{
	if (level > 15)
		return attPerTurn[3];
	else
		return 0;
}


void Character::save()
{
	ofstream output;


	//!Create a new file or replace old file
	output.open("char.txt");

	//!Write to file
	string out = "";
	output << abilityScores[0] << " " << abilityScores[1] << " " << abilityScores[2] << " " << abilityScores[3] << " " <<
		abilityScores[4] << " " << abilityScores[5] << " " << currentHitPoints << " " << level;
	for (auto iterator = backpack.begin(); iterator != backpack.end(); ++iterator) {
		output << " false" << " " << iterator->getType() << " " << iterator->getInfluences()[0].getBonus() << " " << iterator->getInfluences()[0].getType();
	}

	for (auto iterator = equipped.begin(); iterator != equipped.end(); ++iterator) {
		output << " true" << " " << iterator->getType() << " " << iterator->getInfluences()[0].getBonus() << " " << iterator->getInfluences()[0].getType();
	}
	//!Close and end
	output.close();
}



Character::Character(string load)
{
	ifstream file(load);
	if (file.is_open()) {
		int str;
		int dex;
		int con;
		int intel;
		int wis;
		int cha;
		int hp;
		int lvl;
		file >> str;
		file >> dex;
		file >> con;
		file >> intel;
		file >> wis;
		file >> cha;
		file >> hp;
		file >> lvl;

		abilityScores[0] = str;
		abilityScores[1] = dex;
		abilityScores[2] = con;
		abilityScores[3] = intel;
		abilityScores[4] = wis;
		abilityScores[5] = cha;


		//! and set hit points 
		currentHitPoints = hp;
		//! set armor class to base 10 + dex
		armorClass = 10 + abilityScores[1];

		//!set Attack Bonus to level + str + dex
		attackBonus = level + abilityScores[0] + abilityScores[1];

		//!set damage bonus to base + str
		damageBonus = 10 + abilityScores[0];

		level = lvl;


		attPerTurn[0] = level;
		if (level >= 5)
			attPerTurn[1] = level - 5;
		if (level >= 10)
			attPerTurn[2] = level - 10;
		if (level >= 15)
			attPerTurn[3] = level - 15;


		int c = file.peek();
		while (c != EOF)
		{
			bool yes;
			string equip;
			string type;
			int val;
			string kind;
			file >> equip;
			file >> type;
			file >> val;
			file >> kind;

			cout << equip << endl;
			cout << type << endl;
			cout << val << endl;
			cout << kind << endl;

			if (equip == "true")
				yes = true;
			else
				yes = false;

			if (yes)
			{
				vector<Enhancement> vecEnhancement;
				Enhancement	strPlus1(kind, val);
				vecEnhancement.push_back(strPlus1);
				Item shmItem(type, vecEnhancement);
				this->equip(&shmItem);
			}
			else if (!yes)
			{
				vector<Enhancement> vecEnhancement;
				Enhancement	strPlus1(kind, val);
				vecEnhancement.push_back(strPlus1);
				Item shmItem(type, vecEnhancement);
				this->addToBag(&shmItem);
			}
			else
				cout << "no items" << endl;
			c = file.peek();
		}
	}

}

void Character::printBag() {
	cout << "Bag Contents: " << endl;
	for (auto iterator = backpack.begin(); iterator != backpack.end(); ++iterator) {
		cout << iterator->getType() << " " << iterator->getInfluences()[0].getBonus() << endl;
	}
	cout << endl;
}
void Character::printEquip() {
	cout << "Equip Contents: " << endl;
	for (auto iterator = equipped.begin(); iterator != equipped.end(); ++iterator) {
		cout << iterator->getType() << " " << iterator->getInfluences()[0].getBonus() << endl;
	}
	cout << endl;
}
Item Character::getBagItem(string search)
{
	for (auto iterator = backpack.begin(); iterator != backpack.end(); ++iterator) {
		if (iterator->getType() == search)
			return *iterator;
	}
}
Item Character::getEquipItem(string search)
{
	for (auto iterator = equipped.begin(); iterator != equipped.end(); ++iterator) {
		if (iterator->getType() == search)
			return *iterator;
	}
}