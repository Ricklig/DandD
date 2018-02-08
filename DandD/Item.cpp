//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"
#include <iostream>
using namespace std;

//! default constructor
Item::Item()
{
	type = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//!	
//! Only items of valid type will be created (temporary) otherwise display invalid type message
//! @param type_name : string representing the type of item (Helmet, Armor, Shield, Ring, Belt, Boots or Weapon)
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences)
{


	if (type_name == "Helmet" || type_name == "Armor" || type_name == "Shield" || type_name == "Ring" || type_name == "Belt" ||
		type_name == "Boots" || type_name == "Weapon") {

		//! enhances a character statistic valid for this item type
		type = type_name;
		influence = influences;

	}

	else {
		cerr << "Invalid item type was not created: " << type_name << endl;
	}


}

//! method to get the type of the item
//! @return : type of the item
string Item::getType()
{
	return type;
}

//! method to get the influences of the item
//! @return : vector containg the list of stats that the item enhances
vector<Enhancement> Item::getInfluences()
{
	return influence;
}

//! method to validate an item, e.g. verify that a new item of a certain type only enhances a character statistic valid for this item type

//! ADDITIONAL TEST: valide item only if it is within +1 and +5 (inclusively) bonus enchantment
//! @return : true if the enhancement list is valid according to the rules, false if not
bool Item::validateItem()
{

	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Helmet" && (influence[0].getType() == "Intelligence" || influence[0].getType() == "Wisdom" || influence[0].getType() == "ArmorClass")) {
		return true;
	}
	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Armor" && influence[0].getType() == "ArmorClass") {
		return true;
	}
	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Shield" && influence[0].getType() == "ArmorClass") {
		return true;
	}
	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Ring" && (influence[0].getType() == "ArmorClass" || influence[0].getType() == "Strength" || influence[0].getType() == "Constitution" || influence[0].getType() == "Wisdom" || influence[0].getType() == "Charisma")) {
		return true;
	}
	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Belt" && (influence[0].getType() == "Constitution" || influence[0].getType() == "Strength")) {
		return true;
	}
	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Boots" && (influence[0].getType() == "ArmorClass" || influence[0].getType() == "Dexterity")) {
		return true;
	}
	if ((influence[0].getBonus() >= 1 && influence[0].getBonus() <= 5) && type == "Weapon" && (influence[0].getType() == "AttackBonus" || influence[0].getType() == "DamageBonus")) {
		return true;
	}

	return false;

}
