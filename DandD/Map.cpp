#include "Map.h"
#include "Item.h"
#include "Enhancement.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Character.h"
#include <cstdlib>
#include <ctime>

using namespace std;


vector<Enhancement> vec;
int posX, posY;
int level;
bool deadNPC;
Combat fight;


Map::Map() {
	Map::startX = 0;
	Map::startY = column - 1;
	Map::endX = row - 1;
	Map::endY = 0;

	for (int x = 0; x<5; x++)
		for (int y = 0; y<5; y++)
			grid[x][y] = 'O';
}


/******************************************************************/
//Start Map editor methods

//! method that takes a 5x5 grid of char
//! @param newMap : 5x5 char grid
void Map::transferMap(char **newMap) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			grid[i][j] = newMap[i][j];
		}
	}
}

//! method that reverts map's grid to default empty
void Map::restartMap() {
	for (int x = 0; x<5; x++)
		for (int y = 0; y<5; y++)
			grid[x][y] = 'O';
}
//! Implementation of the map verification
//! @return bool value, true of the map is valid (there is at least one clear path between the mandatory begin and end cell). 
bool Map::isValid()
{
	bool startExists = false;
	bool endExists = false;
	//! If start cell doesn't exist
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == 'S')
				startExists = true;
		}
	}

	//! If end cell doesn't exist
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == 'E')
				endExists = true;
		}
	}

	if (startExists == false || endExists == false) {
		cout << "Start and/or ending cell do not exist";
		return false;
	}

	//!Maze traversal using right hand rule
	//!making sure that start cell can reach exit cell
	int i = startX, j = startY;
	char visited[row][column];

	visited[i][j] = 'v';

	do
	{
		//!goes to the right cell if possible
		if (i + 1<row && (grid[i + 1][j] == 'O' || grid[i + 1][j] == 'E') && visited[i + 1][j] != 'v' && visited[i + 1][j] != 'T')
		{
			i++;
			visited[i][j] = 'v';
		}

		//!otherwise goes up 1 cell, if possible
		else if (j - 1 >= 0 && (grid[i][j - 1] == 'O' || grid[i][j - 1] == 'E') && visited[i][j - 1] != 'v' && visited[i][j - 1] != 'T')
		{
			j--;
			visited[i][j] = 'v';
		}

		//!otherwise goes left 1 cell, if possible
		else if (i - 1 >= 0 && (grid[i - 1][j] == 'O' || grid[i - 1][j] == 'E') && visited[i - 1][j] != 'v' && visited[i - 1][j] != 'T')
		{
			i--;
			visited[i][j] = 'v';
		}

		//!otherwise goes down 1 cell, if possible
		else if (j + 1 >= 0 && (grid[i][j + 1] == 'O' || grid[i][j + 1] == 'E') && visited[i][j + 1] != 'v' && visited[i][j + 1] != 'T')
		{
			j++;
			visited[i][j] = 'v';
		}

		//!if none of these are possible (i.e. trapped) the 'v' in visisted is replaced with a 'T'
		//!then all the 'v's in the array visited are erased
		else
		{
			visited[i][j] = 'T';

			for (int x = 0; x<row; x++)
			{
				for (int y = 0; y<column; y++)
				{
					if (visited[x][y] == 'v')
						visited[x][y] = 'O';
				}
			}
			i = startX;
			j = startY;
		}

		if (visited[startX][startY] == 'T')
			return 0;
	} while (grid[i][j] != 'E');

	return 1;

}


//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
void Map::fillCell(int x, int y, char obj)
{
	grid[x][y] = obj;
}


//! Implementation occupation of a cell, check if a cell is occupied
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return : a boolean true if the cell is occupeid false otherwise
bool Map::isOccupied(int x, int y)
{
	if (grid[x][y] == '!') {
		return true;
	}

	return false;
}

//! method that sets start cell
void Map::setStart()
{
	cout << "\nEnter a row index ";
	cin >> startY;

	cout << "Enter a column index ";
	cin >> startX;

	grid[startX][startY] = 'S';

}

void Map::setEnd()
{
	cout << "\nEnter a row index ";
	cin >> endY;

	cout << "Enter a column index ";
	cin >> endX;

	grid[endX][endY] = 'E';

}

//! method that removes cell
void Map::removeCell()
{
	int i, j;
	cout << "\nEnter a row index ";
	cin >> j;

	cout << "Enter a column index ";
	cin >> i;

	grid[i][j] = 'O';
}

void Map::setAggroNPC()
{
	int i, j;

	cout << "\nEnter a row index ";
	cin >> j;

	cout << "Enter a column index ";
	cin >> i;

	if (grid[i][j] == 'O')
		grid[i][j] = 'A';
	else
		cout << "\nSorry that tile is already occupied\n";
}

void Map::setPassiveNPC()
{
	int i, j;

	cout << "\nEnter a row index ";
	cin >> j;

	cout << "Enter a column index ";
	cin >> i;

	if (grid[i][j] == 'O')
		grid[i][j] = 'P';
	else
		cout << "\nSorry that tile is already occupied\n";
}

//! method that sets wall cell
void Map::setWalls()
{
	int i, j;

	cout << "\nEnter a row index ";
	cin >> j;

	cout << "Enter a column index ";
	cin >> i;

	if (grid[i][j] == 'O')
		grid[i][j] = 'X';
	else
		cout << "\nSorry that tile is already occupied\n";
}

void Map::printBoard() {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

//! method that returns string content
//! @return : string of 5x5 grid
string Map::stringContent() {
	string content = "";

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			content = content + grid[i][j] + " ";
		}
		content = content + "\n";
	}
	return content;
}

void Map::replaceCell(char replaceWith, char replaceTarget) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == replaceTarget)
				grid[i][j] = replaceWith;
		}
	}
}

//!End of Map editor methods
/******************************************************************/





//!Item methods for the map

void Map::checkItem(Character& person, int i, int j) {

	vector<Enhancement> vecEnhancement;

	int randItem = (rand() % 15) + 1;

	if (temp[i][j] == 'C' || temp[i][j] == 'D') {

		cout << randItem << endl;

		if (randItem == 1) {
			cout << "Ring found " << endl;
			Enhancement	chaPlus1("Charisma", person.getLevel());
			vecEnhancement.push_back(chaPlus1);

			Item ring("Ring", vecEnhancement);
			cout << " " << endl;
			person.equip(&ring);
		}
		
		else if (randItem == 2) {
			cout << "Weapon found " << endl;

			Enhancement	strPlus1("Strength", person.getLevel());
			vecEnhancement.push_back(strPlus1);

			Item sword("Weapon", vecEnhancement);
			cout << " " << endl;
			person.equip(&sword);
		}
		
		else if (randItem == 3) {
			cout << "Boots found " << endl;

			Enhancement	dexPlus1("Dexterity", person.getLevel());
			vecEnhancement.push_back(dexPlus1);

			Item boot("Boots", vecEnhancement);
			cout << " " << endl;
			person.equip(&boot);
		}
		else if (randItem == 4) {
			cout << "Helmet found " << endl;

			Enhancement	intPlus1("Intelligence", person.getLevel());
			vecEnhancement.push_back(intPlus1);

			Item helmet("Helmet", vecEnhancement);
			cout << " " << endl;
			person.equip(&helmet);
		}
		else if (randItem == 5) {
			cout << "Belt found " << endl;

			Enhancement	contPlus1("Constitution", person.getLevel());
			vecEnhancement.push_back(contPlus1);

			Item belt("Belt", vecEnhancement);
			cout << " " << endl;
			person.equip(&belt);
		}
		else if (randItem == 6) {
			cout << "Helmet found " << endl;

			Enhancement	wisPlus1("Wisdom", person.getLevel());
			vecEnhancement.push_back(wisPlus1);

			Item helmet2("Helmet", vecEnhancement);
			cout << " " << endl;
			person.equip(&helmet2);
		}
		else
			cout << "Nothing was found! Dang..." << endl;

	}

}
//!end of item methods




//!Basic map methods


void Map::copyArray() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			
			temp[i][j] = grid[i][j];
		}

	}
}

void Map::findStart() {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == 'S') {
				cout << "Start position of player is at " << i << " " << j << endl;
				startX = i;
				startY = j;
			}
		}
	}
}

void Map::printTemp() {

	cout << "New map is: " << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << temp[i][j] << " ";
		}
		cout << endl;
	}

}


void Map::loadMap(string textfile) {
	ifstream file(textfile);
	if (file.is_open()) {

		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				file >> grid[x][y];
			}
		}
	}

}

void Map::print() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}




//!End of basic methods







//!Movement of the character



bool Map::movePlayer(char direction, Character& myPlayer) {
	char player = '*';
	
	if (direction == 'W' || direction == 'w') {
		if (temp[startX - 1][startY] == 'X') {
			cout << "Wall" << endl;
		}
		else if (temp[startX - 1][startY] == 'P' || temp[startX - 1][startY] == 'A') {
			cout << "Cannot pass through NPC" << endl;
		}
		else if (startX == 0) {
			cout << "Cannot move out of bound" << endl;
		}

		else if (temp[startX - 1][startY] == 'E') {
			cout << "Map is completed." << endl;
			return true;
		}
		else if (temp[startX - 1][startY] == 'D' || temp[startX - 1][startY] == 'C') {
			checkItem(myPlayer, startX - 1, startY);
			temp[startX][startY] = 'O';
			startX--;
			temp[startX][startY] = player;
		}
		else {
			temp[startX][startY] = 'O';
			startX--;
			temp[startX][startY] = player;

		}
	}
	else if (direction == 'S' || direction == 's') {
		if (temp[startX + 1][startY] == 'X') {
			cout << "Wall" << endl;
		}
		else if (temp[startX + 1][startY] == 'P' || temp[startX + 1][startY] == 'A') {
			cout << "Cannot pass through NPC" << endl;
		}
		else if (startX == 4) {
			cout << "Cannot move out of bound" << endl;
		}
		else if (temp[startX + 1][startY] == 'E') {
			cout << "Map is completed." << endl;
			return true;
		}
		else if (temp[startX + 1][startY] == 'D' || temp[startX + 1][startY] == 'C') {
			checkItem(myPlayer, startX + 1, startY);
			temp[startX][startY] = 'O';
			startX++;
			temp[startX][startY] = player;
		}
		else {
			temp[startX][startY] = 'O';
			startX++;
			temp[startX][startY] = player;
		}

	}
	else if (direction == 'A' || direction == 'a') {
		if (temp[startX][startY - 1] == 'X') {
			cout << "Wall" << endl;
		}
		else if (temp[startX][startY - 1] == 'P' || temp[startX][startY - 1] == 'A') {
			cout << "Cannot pass through NPC" << endl;
		}
		
		else if (startY == 0) {
			cout << "Cannot move out of bound" << endl;
		}
		else if (temp[startX][startY - 1] == 'E') {
			cout << "Map is completed." << endl;
			return true;
		}
		else if (temp[startX][startY - 1] == 'D' || temp[startX][startY - 1] == 'C') {
			checkItem(myPlayer, startX, startY - 1);
			temp[startX][startY] = 'O';
			startY--;
			temp[startX][startY] = player;
		}
		else {
			temp[startX][startY] = 'O';
			startY--;
			temp[startX][startY] = player;
		}

	}
	else if (direction == 'D' || direction == 'd') {
		if (temp[startX][startY + 1] == 'X') {
			cout << "Wall" << endl;
		}
		else if (temp[startX][startY + 1] == 'P' || temp[startX][startY + 1] == 'A') {
			cout << "Cannot pass through NPC" << endl;
		}

		else if (startY == 4) {
			cout << "Cannot move out of bound" << endl;
		}
		else if (temp[startX][startY + 1] == 'E') {
			cout << "Map is completed." << endl;
			return true;
		}
		else if (temp[startX][startY + 1] == 'D' || temp[startX][startY + 1] == 'C') {
			checkItem(myPlayer, startX, startY + 1);
			temp[startX][startY] = 'O';
			startY++;
			temp[startX][startY] = player;
		}
		else {
			temp[startX][startY] = 'O';
			startY++;
			temp[startX][startY] = player;
		}
	}

	string excerpt = "Player moved ";
	if (tolower(direction) == 'w')
		excerpt += "up";
	else if (tolower(direction) == 'a')
		excerpt += "left";
	else if (tolower(direction) == 'd')
		excerpt += "right";
	else if (tolower(direction) == 's')
		excerpt += "down";

	message = excerpt + "\n";
	notify();// log the movements of the character


		return false;
	

}

//!End of movement





//!NPC and combat methods

void Map::movePassive(NPC& passiveNPC) {
	if (temp[passiveNPC.getX()][passiveNPC.getY() + 1] == '*' || temp[passiveNPC.getX()][passiveNPC.getY() - 1] == '*' || temp[passiveNPC.getX() + 1][passiveNPC.getY()] == '*' || temp[passiveNPC.getX() - 1][passiveNPC.getY()] == '*') {

	}
	else if (startX == passiveNPC.getX()) {
		if (startY > passiveNPC.getY() + 1) {
			if (temp[passiveNPC.getX()][1 + passiveNPC.getY()] == 'O') {
				temp[passiveNPC.getX()][passiveNPC.getY()] = 'O';
				passiveNPC.setY(passiveNPC.getY() + 1);
				temp[passiveNPC.getX()][passiveNPC.getY()] = 'P';
			}
		}
		else if (startY < passiveNPC.getY() - 1) {
			if (temp[passiveNPC.getX()][passiveNPC.getY() - 1] == 'O') {
				temp[passiveNPC.getX()][passiveNPC.getY()] = 'O';
				passiveNPC.setY(passiveNPC.getY() - 1);
				temp[passiveNPC.getX()][passiveNPC.getY()] = 'P';
			}
		}
	}
	else if (startX > passiveNPC.getX()) {
		if (temp[1 + passiveNPC.getX()][passiveNPC.getY()] == 'O') {
			temp[passiveNPC.getX()][passiveNPC.getY()] = 'O';
			passiveNPC.setX(passiveNPC.getX() + 1);
			temp[passiveNPC.getX()][passiveNPC.getY()] = 'P';
		}
	}
	else if (startX < passiveNPC.getX()) {
		if (temp[passiveNPC.getX() - 1][passiveNPC.getY()] == 'O') {
			temp[passiveNPC.getX()][passiveNPC.getY()] = 'O';
			passiveNPC.setX(passiveNPC.getX() - 1);
			temp[passiveNPC.getX()][passiveNPC.getY()] = 'P';
		}
	}
}

void Map::moveAggro(NPC& aggroNPC) {
	if (temp[aggroNPC.getX()][aggroNPC.getY() + 1] == '*' || temp[aggroNPC.getX()][aggroNPC.getY() - 1] == '*' || temp[aggroNPC.getX() + 1][aggroNPC.getY()] == '*' || temp[aggroNPC.getX() - 1][aggroNPC.getY()] == '*') {

	}
	else if (startX == aggroNPC.getX()) {
		if (startY > aggroNPC.getY() + 1) {
			if (temp[aggroNPC.getX()][1 + aggroNPC.getY()] == 'O') {
				temp[aggroNPC.getX()][aggroNPC.getY()] = 'O';
				aggroNPC.setY(aggroNPC.getY() + 1);
				temp[aggroNPC.getX()][aggroNPC.getY()] = 'A';
			}
		}
		else if (startY < aggroNPC.getY() - 1) {
			if (temp[aggroNPC.getX()][aggroNPC.getY() - 1] == 'O') {
				temp[aggroNPC.getX()][aggroNPC.getY()] = 'O';
				aggroNPC.setY(aggroNPC.getY() - 1);
				temp[aggroNPC.getX()][aggroNPC.getY()] = 'A';
			}
		}
	}
	else if (startX > aggroNPC.getX()) {
		if (temp[1 + aggroNPC.getX()][aggroNPC.getY()] == 'O') {
			temp[aggroNPC.getX()][aggroNPC.getY()] = 'O';
			aggroNPC.setX(aggroNPC.getX() + 1);
			temp[aggroNPC.getX()][aggroNPC.getY()] = 'A';
		}
	}
	else if (startX < aggroNPC.getX()) {
		cout << temp[aggroNPC.getX() - 1][aggroNPC.getY()];
		if (temp[aggroNPC.getX() - 1][aggroNPC.getY()] == 'O') {
			temp[aggroNPC.getX()][aggroNPC.getY()] = 'O';
			aggroNPC.setX(aggroNPC.getX() - 1);
			temp[aggroNPC.getX()][aggroNPC.getY()] = 'A';
		}
	}
}


bool Map::passiveNPC(NPC& passiveNPC) {
	bool found = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == 'P') {
				passiveNPC.setX(i);
				passiveNPC.setY(j);
				cout << "Passive found" << endl;
				cout << passiveNPC.getX() << " " << passiveNPC.getY() << endl;
				found = true;
			}

		}
	}
	return found;
}

bool Map::aggroNPC(NPC& aggroNPC) {
	bool found = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == 'A') {
				aggroNPC.setX(i);
				aggroNPC.setY(j);
				cout << "Aggro found" << endl;
				cout << aggroNPC.getX() << " " << aggroNPC.getY() << endl;
				found = true;
			}

		}
	}
	return found;
}

void Map::playerCombat(Character& player1, NPC& NPC) {
	if (temp[NPC.getX()][NPC.getY() + 1] == '*' || temp[NPC.getX()][NPC.getY() - 1] == '*' || temp[NPC.getX() + 1][NPC.getY()] == '*' || temp[NPC.getX() - 1][NPC.getY()] == '*') {
		cout << "\n----Player Combat Phase------\n";
		//!Passive NPC
		if (NPC.getAggro() == false) {
			cout << "You wouldn't hit a guy with glasses would you? (Passive NPC)." << endl;
			cout << "Do you (A)ttack or (I)gnore" << endl;
			char choice;
			cin >> choice;
			if (choice == 'A' || choice == 'a') {
				NPC.makeAggro();
				temp[NPC.getX()][NPC.getY()] = 'A';
				cout << "I have no choice! REVENGE! (You have made the Passive NPC become an Aggressive NPC)." << endl;
				deadNPC = fight.fighting(player1, NPC);
				if (deadNPC)
					temp[NPC.getX()][NPC.getY()] = 'D';

			}

			else if (choice == 'I' || choice == 'i') {
				cout << "Successfully ignored NPC" << endl;

			}
		}
		//!Agressive NPC
		else {
			cout << "Beware of Aggressive NPC." << endl;
			char in;
			cout << "(A)ttack enemy or (R)un" << endl;
			cout << "Player choice: ";
			cin >> in;
			if (in == 'a' || in == 'A') {
				cout << "Me angry. Me kill(Aggressive NPC)." << endl;
				deadNPC = fight.fighting(player1, NPC);
				if (deadNPC)
					temp[NPC.getX()][NPC.getY()] = 'D';
			}
			if (in == 'r' || in == 'R') {
				cout << "You did not initiate combat with aggresive NPC" << endl;
			}
		}
	}
}

void Map::passiveAction(Character& player1, NPC& passiveNPC) {

	//!IMPLEMENT MOVEMENT

	if (temp[passiveNPC.getX()][passiveNPC.getY() + 1] == '*' || temp[passiveNPC.getX()][passiveNPC.getY() - 1] == '*' || temp[passiveNPC.getX() + 1][passiveNPC.getY()] == '*' || temp[passiveNPC.getX() - 1][passiveNPC.getY()] == '*') {
		cout << "Hello stranger, just passing through(Passive NPC)." << endl;
	}
}

void Map::aggroAction(Character& player1, NPC& aggroNPC) {
	if (temp[aggroNPC.getX()][aggroNPC.getY() + 1] == '*' || temp[aggroNPC.getX()][aggroNPC.getY() - 1] == '*' || temp[aggroNPC.getX() + 1][aggroNPC.getY()] == '*' || temp[aggroNPC.getX() - 1][aggroNPC.getY()] == '*') {
		cout << "Me angry. Me kill(Aggressive NPC)." << endl;
		deadNPC = fight.fighting(player1, aggroNPC);
		if (deadNPC)
			temp[aggroNPC.getX()][aggroNPC.getY()] = 'D';
	}

}

void Map::setFileName(string name) {
	fileName = name;
}

string Map::getFileName() {
	return fileName;
}

void Map::setMapLevel(int level) {
	mapLevel = level;
}

int Map::getMapLevel() {
	return mapLevel;
}



//!End of combat and NPC

