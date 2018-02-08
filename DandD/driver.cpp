#include "NPC.h"
#include "Combat.h"
#include "CharacterObserver.h"
#include "MapObserver.h"
#include"DiceObserver.h"
#include "Campaign.h"
#include "Character.h"
#include "Item.h"
#include "ItemContainer.h"
#include "Map.h"
#include "Dice.h"
#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
#include <ctime>
#include<regex>
#include<time.h>

using namespace std;

int main() {

	//! unifed log file for game
	ofstream myfile("GameLog.txt");

	//! clear contents of file from previous game
	if (myfile.is_open())
	{
		myfile.close();
	}
	srand(time(0));
	char yesOrNo;
	char creatorDecision;
	char ending;
	char start;
	bool restart = true;
	Map map = Map();
	Campaign myCampaign;
	Map campStart, campEnd, campInt1, campInt2;
	char **tempMap;
	tempMap = new char*[5];
	for (int i = 0; i < 5; ++i)
		tempMap[i] = new char[5];
	string fileName = "";
	int mapS, mapE, mapI1, mapI2;

	cout << "Please choose 1 to start the game or 2 to start the map editor\n";
	cin >> start;



	if (start == '2') {
		//!Restarts if invalid map
		while (restart == true) {

			cout << "---------DUNGEONS & DRAGONS------------\n"
				<< "--------------MAP EDITOR--------------\n\n\n";

			//! Step 1: Promting the user for either a new map or editor existing one
			cout << "**************STEP 1*******************\n";
			cout << "Press '1'. To create a new map\nPress '2'. To modify an existing map\nPress '3'. To create a new campaign\nPress '4'. To modify an existing campaign\n";

			cin >> creatorDecision;

			//! Validate that the decision is exactly as demanded
			while (creatorDecision != '1' && creatorDecision != '2' && creatorDecision != '3' && creatorDecision != '4')
			{
				cout << "Press '1'. To create a new map\nPress '2'. To modify an existing a map\nPress '3'. To create a new campaign\nPress '4'. To modify an existing campaign\n";
				cin >> creatorDecision;
			}

			//! Creation of a new map (decision 1) is default
			//! 

			//! Editing an existing map (decision 2)
			//!
			//! inputs a filename and transfer content to a map 
			if (creatorDecision == '2') {
				string mapContent = "";
				cout << "Please enter the name of an existing map file (including .txt): ";
				cin >> fileName;
				ifstream input(fileName);

				if (input.is_open())
				{
					cout << "\nDisplaying " << fileName << "\n\n";

					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++) {
							input >> tempMap[i][j];
							cout << tempMap[i][j] << " ";
						}
						cout << "\n";
					}
					map.transferMap(tempMap);

					input.close();
				}

				else {
					cout << "\n\nFile unable to access please enter any input to exit.\n";
					cin >> ending;
					exit(EXIT_FAILURE);
				}
			}

			//! edit map using various steps (decision 1 and 2)
			//!
			if (creatorDecision == '1' || creatorDecision == '2') {
				cout << "\nNOTICE:\n\n"
					<< "\t-The indexing for the row starts at 0 to 4 increasing from top to bottom\n"
					<< "\t-The indexing for the column starts at 0 to 4 increasing from left to right\n"
					<< "\nCell names:\n\n"
					<< "\t 'S' -> start			'E' -> Exit\n"
					<< "\t 'X' -> Wall			'O' -> Free\n"
					<< "\t 'A' -> Aggro NPC		'N' -> Passive NPC\n"
					<< "\t 'C' -> Chest\n";

				if (creatorDecision == '1') {
					cout << "\nHere is the default map... \n";
				}
				if (creatorDecision == '2')
					cout << "\nHere is the current map... \n";

				//!Display new empty map
				if (creatorDecision == '1')
					map.printBoard();
				//!Display current map
				if (creatorDecision == '2')
					map.printBoard();

				//! Step 2: The user places the start & exit points
				cout << "\n\n**************STEP 2*******************\n";
				cout << "NOTICE: You must have a SINGLE start and end to have a valid map\n";

				if (creatorDecision == '1')
					cout << "Would you like to add START tile? (Y/N) ";
				if (creatorDecision == '2')
					cout << "Would you like to move a START tile? (Y/N) ";
				cin >> yesOrNo;

				while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
				{
					if (creatorDecision == '1')
						cout << "Would you like to add a START tile? (Y/N) ";
					if (creatorDecision == '2')
						cout << "Would you like to move a START tile? (Y/N) ";
					cin >> yesOrNo;
				}

				if (yesOrNo == 'Y' || yesOrNo == 'y') {
					if (creatorDecision == '1')
						map.setStart();
					if (creatorDecision == '2') {
						//!delete old start cell
						map.replaceCell('O', 'S');
						map.setStart();
					}
				}

				if (creatorDecision == '1')
					cout << "Would you like to add an END tile? (Y/N) ";
				if (creatorDecision == '2')
					cout << "Would you like to move an END tile? (Y/N) ";
				cin >> yesOrNo;

				while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
				{
					if (creatorDecision == '1')
						cout << "Would you like to add an END tile? (Y/N) ";
					if (creatorDecision == '2')
						cout << "Would you like to move an END tile? (Y/N) ";
					cin >> yesOrNo;
				}

				if (yesOrNo == 'Y' || yesOrNo == 'y') {
					if (creatorDecision == '1')
						map.setEnd();
					if (creatorDecision == '2') {
						//!delete old start cell
						map.replaceCell('O', 'E');
						map.setEnd();
					}
				}

				cout << "Here is the map so far...\n";
				map.printBoard();

				//! Step 3: Delete any unwanted cell (for either empty space or other cell types)
				cout << "\n\n**************STEP 3*******************\n";
				cout << "NOTICE: Delete any unwanted cell(for either empty space or other cell types)\n";

				//!Delete
				cout << "Would you like to delete any cells? (Y/N) ";
				cin >> yesOrNo;

				while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
				{
					cout << "Would you like to delete any cells? (Y/N) ";
					cin >> yesOrNo;
				}

				while (yesOrNo == 'Y' || yesOrNo == 'y')
				{
					map.removeCell();
					map.printBoard();

					cout << "\nWould you like to delete any more cells? (Y/N) ";
					cin >> yesOrNo;

					while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
					{
						cout << "Would you like to delete any more cells? (Y/N) ";
						cin >> yesOrNo;
					}
				}


				//!Step 4: Adding any extra cell types such as walls and NPCs
				cout << "\n\n**************STEP 4*******************\n";
				cout << "NOTICE: Add any walls, NPCs, etc. \n";

				//!Walls
				cout << "Would you like to add WALLS? (Y/N) ";
				cin >> yesOrNo;

				while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
				{
					cout << "Would you like to add WALLS? (Y/N) ";
					cin >> yesOrNo;
				}

				while (yesOrNo == 'Y' || yesOrNo == 'y')
				{
					map.setWalls();
					map.printBoard();

					cout << "\nWould you want to add more WALLS? (Y/N) ";
					cin >> yesOrNo;

					while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
					{
						cout << "Would you like to add more WALLS? (Y/N) ";
						cin >> yesOrNo;
					}
				}

				//!AGGRO NPC
				cout << "\n\n-Would you like to add an AGGRO NPC cells? (Y/N)";
				cin >> yesOrNo;

				while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
				{
					cout << "Would you like to add an AGGRO NPC cells? (Y/N) ";
					cin >> yesOrNo;
				}

				while (yesOrNo == 'Y' || yesOrNo == 'y')
				{
					map.setAggroNPC();
					map.printBoard();

					cout << "\nWould you want to add another AGGRO NPC tiles? (Y/N) ";
					cin >> yesOrNo;

					while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
					{
						cout << "Would you like to add another AGGRO NPC? (Y/N) ";
						cin >> yesOrNo;
					}

				}

				//!PASSIVE NPC
				cout << "\n\n-Would you like to add a PASSIVE NPC cells? (Y/N)";
				cin >> yesOrNo;

				while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
				{
					cout << "Would you like to add a PASSIVE NPC cells? (Y/N) ";
					cin >> yesOrNo;
				}

				while (yesOrNo == 'Y' || yesOrNo == 'y')
				{
					map.setPassiveNPC();
					map.printBoard();

					cout << "\nWould you want to add another PASSIVE NPC tiles? (Y/N) ";
					cin >> yesOrNo;

					while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
					{
						cout << "Would you like to add another PASSIVE NPC? (Y/N) ";
						cin >> yesOrNo;
					}

				}

				//! Valid map (must have a start/end cell and that start can reach end)
				if (map.isValid())
				{
					string mapContent = "";
					ofstream output;
					cout << "Your map is valid.\n Please name your file or re-enter old file name to modify (inluding .txt):";

					cin >> fileName;

					//!Create a new file or replace old file
					output.open(fileName);
					cout << "\n" << fileName << "was succesfully created\n";

					//!Write to file
					mapContent = map.stringContent();
					output << mapContent;

					//!Close and end
					output.close();
					restart = false;
				}
				else
				{
					cout << "\n\nYour map is not valid. Restarting editor...\n\n";
					map.restartMap();
					restart = true;
				}

			}//!Creating/editing map ends

			 //! Creating a new campaign (decision 3)
			 //! prompt user by decided the size of the campaign and what existing maps to use for what section
			if (creatorDecision == '3') {
				char numMap;
				string fileName;
				Map startMap = Map();
				Map interMap1 = Map();
				Map interMap2 = Map();
				Map endingMap = Map();
				Campaign campaign;

				cout << "Creating a new campaign\n";
				cout << "Enter the amount of maps within the campaign (from 2 to 4): ";
				cin >> numMap;

				while (numMap != '2' && numMap != '3' &&numMap != '4') {
					cout << "Enter the amount of maps within the campaign (from 2 to 4): ";
					cin >> numMap;
				}

				cout << "Please enter your starting campaign map's file name: ";
				cin >> fileName;
				ifstream startM(fileName);
				if (startM.is_open())
				{
					cout << "\nDisplaying " << fileName << "\n\n";

					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++) {
							startM >> tempMap[i][j];
							cout << tempMap[i][j] << " ";
						}
						cout << "\n";
					}
					startMap.transferMap(tempMap);
					startMap.setFileName(fileName);
					startM.close();
				}

				cout << "Please enter your ending campaign map's file name: ";
				cin >> fileName;
				ifstream endM(fileName);
				if (endM.is_open())
				{
					cout << "\nDisplaying " << fileName << "\n\n";

					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++) {
							endM >> tempMap[i][j];
							cout << tempMap[i][j] << " ";
						}
						cout << "\n";
					}
					endingMap.transferMap(tempMap);
					endingMap.setFileName(fileName);
					endM.close();
				}

				if (numMap == '2') {
					campaign = Campaign(startMap, endingMap);
					cout << "Campaign contains the following maps (in order): \n";
					campaign.displayStart();
					campaign.displayEnd();
					cout << "Please enter the name of the new campaign to write to (including .txt): ";
					cin >> fileName;
					campaign.toFileStart(fileName);
					campaign.toFileEnd(fileName);

				}

				if (numMap >= '3') {
					cout << "Please enter your intermediate (1st) campaign map's file name: ";
					cin >> fileName;
					ifstream interM1(fileName);
					if (interM1.is_open())
					{
						cout << "\nDisplaying " << fileName << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								interM1 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}
						interMap1.transferMap(tempMap);
						interMap1.setFileName(fileName);
						interM1.close();
					}

					if (numMap == '3') {
						campaign = Campaign(startMap, interMap1, endingMap);
						cout << "Campaign contains the following maps (in order): \n";
						campaign.displayStart();
						campaign.displayInt1();
						campaign.displayEnd();
						cout << "Please enter the name of the new campaign to write to (including .txt): ";
						cin >> fileName;
						campaign.toFileStart(fileName);
						campaign.toFileInt1(fileName);
						campaign.toFileEnd(fileName);
					}

					if (numMap == '4') {
						cout << "Please enter your intermediate (2nd) campaign map's file name: ";
						cin >> fileName;
						ifstream interM2(fileName);
						if (interM2.is_open())
						{
							cout << "\nDisplaying " << fileName << "\n\n";

							for (int i = 0; i < 5; i++) {
								for (int j = 0; j < 5; j++) {
									interM2 >> tempMap[i][j];
									cout << tempMap[i][j] << " ";
								}
								cout << "\n";
							}
							interMap2.transferMap(tempMap);
							interMap2.setFileName(fileName);
							interM2.close();
						}
						campaign = Campaign(startMap, interMap1, interMap2, endingMap);
						cout << "Campaign contains the following maps (in order): \n";
						campaign.displayStart();
						campaign.displayInt1();
						campaign.displayInt2();
						campaign.displayEnd();
						cout << "Please enter the name of the new campaign to write to (including .txt): ";
						cin >> fileName;
						campaign.toFileStart(fileName);
						campaign.toFileInt1(fileName);
						campaign.toFileInt2(fileName);
						campaign.toFileEnd(fileName);
					}
				}
				restart = false;
			}//!decision 3 ends

			 //! Editing existing campaign (decision 4)
			 //! Ask user for a file name, checks the number of maps and edits relationship between the maps (order)
			if (creatorDecision == '4') {
				cout << "Please enter the name of an existing campaign file (including .txt): ";
				cin >> fileName;
				//!ifstream input(fileName);
				ifstream read(fileName);
				int number_of_lines = 0;
				string line;
				int numM = 0;
				string maps[4];
				int s = 0;

				while (getline(read, line)) {
					++number_of_lines;
					maps[numM] = line;
					numM++;
				}
				cout << "Number of maps: " << number_of_lines << endl;


				if (number_of_lines == 2) {

					ifstream input0(maps[0]);

					if (input0.is_open())
					{
						cout << "\nDisplaying start campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input0 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campStart.setFileName(maps[0]);
						campStart.transferMap(tempMap);

						input0.close();
					}


					ifstream input1(maps[1]);

					if (input1.is_open())
					{
						cout << "\nDisplaying ending campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input1 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campEnd.setFileName(maps[1]);
						campEnd.transferMap(tempMap);

						input1.close();
					}

					campEnd.transferMap(tempMap);
					Campaign editCamp = Campaign(campStart, campEnd);
					Map* camp1 = editCamp.getStartM();
					Map* camp2 = editCamp.getEndM();


					cout << "\nSwap map order (start map becomes end, vice-versa)? (Y/N)";
					cin >> yesOrNo;

					while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
					{
						cout << "Swap map order (start map becomes end, vice-versa)? (Y/N)";
						cin >> yesOrNo;
					}

					if (yesOrNo == 'Y' || yesOrNo == 'y') {
						editCamp.swapMap();
						cout << "Maps succefully swapped.\n";
					}
					cout << "Please enter your campaign file name to save to (or overwrite): ";
					cin >> fileName;

					editCamp.toFileStart(fileName);
					editCamp.toFileEnd(fileName);
				}//!campaign size 2 end

				if (number_of_lines == 3) {

					ifstream input0(maps[0]);

					if (input0.is_open())
					{
						cout << "\nDisplaying start campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input0 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campStart.setFileName(maps[0]);
						campStart.transferMap(tempMap);

						input0.close();
					}

					ifstream input1(maps[1]);

					if (input1.is_open())
					{
						cout << "\nDisplaying intermediate campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input1 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campInt1.setFileName(maps[1]);
						campInt1.transferMap(tempMap);

						input1.close();
					}

					ifstream input2(maps[2]);

					if (input2.is_open())
					{
						cout << "\nDisplaying ending campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input2 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campEnd.setFileName(maps[2]);
						campEnd.transferMap(tempMap);

						input2.close();
					}


					Campaign editCamp = Campaign(campStart, campInt1, campEnd);


					cout << "\nWhich map would you like to use as your starting map? (1, 2, 3): ";
					cin >> mapS;

					if (mapS == 1)
						editCamp.setStartM(campStart);
					else if (mapS == 2)
						editCamp.setStartM(campInt1);
					else if (mapS == 3)
						editCamp.setStartM(campEnd);

					cout << "\nWhich map would you like to use as your intemediate map? (1, 2, 3): ";
					cin >> mapI1;

					if (mapI1 == 1)
						editCamp.setInt1M(campStart);
					else if (mapI1 == 2)
						editCamp.setInt1M(campInt1);
					else if (mapI1 == 3)
						editCamp.setInt1M(campEnd);

					cout << "\nWhich map would you like to use as your ending map? (1, 2, 3): ";
					cin >> mapE;

					if (mapE == 1)
						editCamp.setEndM(campStart);
					else if (mapE == 2)
						editCamp.setEndM(campInt1);
					else if (mapE == 3)
						editCamp.setEndM(campEnd);

					Campaign editedCamp = Campaign(campStart, campInt1, campEnd);
					cout << "Maps succefully swapped.\n";

					cout << "Please enter your campaign file name to save to (or overwrite): ";
					cin >> fileName;

					editedCamp.toFileStart(fileName);
					editedCamp.toFileInt1(fileName);
					editedCamp.toFileEnd(fileName);
				}//!campaign size 3 end

				if (number_of_lines == 4) {

					ifstream input0(maps[0]);

					if (input0.is_open())
					{
						cout << "\nDisplaying start campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input0 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campStart.setFileName(maps[0]);
						campStart.transferMap(tempMap);

						input0.close();
					}

					ifstream input1(maps[1]);

					if (input1.is_open())
					{
						cout << "\nDisplaying intermediate (1) campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input1 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campInt1.setFileName(maps[1]);
						campInt1.transferMap(tempMap);

						input1.close();
					}

					ifstream input2(maps[2]);

					if (input2.is_open())
					{
						cout << "\nDisplaying Intermediate(2) campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input2 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campInt2.setFileName(maps[2]);
						campInt2.transferMap(tempMap);

						input2.close();
					}


					ifstream input3(maps[3]);

					if (input3.is_open())
					{
						cout << "\nDisplaying Ending campaign map " << "\n\n";

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								input3 >> tempMap[i][j];
								cout << tempMap[i][j] << " ";
							}
							cout << "\n";
						}

						campEnd.setFileName(maps[3]);
						campEnd.transferMap(tempMap);

						input3.close();
					}


					Campaign editCamp = Campaign(campStart, campInt1, campInt2, campEnd);
					Map* camp1 = editCamp.getStartM();
					Map* camp2 = editCamp.getInt1M();
					Map* camp3 = editCamp.getInt2M();
					Map* camp4 = editCamp.getEndM();


					cout << "\nWhich map would you like to use as your starting map? (1, 2, 3, 4): ";
					cin >> mapS;

					if (mapS == 1)
						editCamp.setStartM(campStart);
					else if (mapS == 2)
						editCamp.setStartM(campInt1);
					else if (mapS == 3)
						editCamp.setStartM(campInt2);
					else if (mapS == 4)
						editCamp.setStartM(campEnd);


					cout << "\nWhich map would you like to use as your intemediate map 1? (1, 2, 3, 4): ";
					cin >> mapI1;

					if (mapS == 1)
						editCamp.setInt1M(campStart);
					else if (mapS == 2)
						editCamp.setInt1M(campInt1);
					else if (mapS == 3)
						editCamp.setInt1M(campInt2);
					else if (mapS == 4)
						editCamp.setInt1M(campEnd);


					cout << "\nWhich map would you like to use as your intemediate map 2? (1, 2, 3, 4): ";
					cin >> mapI2;

					if (mapS == 1)
						editCamp.setInt2M(campStart);
					else if (mapS == 2)
						editCamp.setInt2M(campInt1);
					else if (mapS == 3)
						editCamp.setInt2M(campInt2);
					else if (mapS == 4)
						editCamp.setInt2M(campEnd);

					cout << "\nWhich map would you like to use as your ending map? (1, 2, 3, 4): ";
					cin >> mapE;

					if (mapS == 1)
						editCamp.setStartM(campStart);
					else if (mapS == 2)
						editCamp.setStartM(campInt1);
					else if (mapS == 3)
						editCamp.setStartM(campInt2);
					else if (mapS == 4)
						editCamp.setStartM(campEnd);


					Campaign editedCamp = Campaign(campStart, campInt1, campInt2, campEnd);
					cout << "Maps succefully swapped.\n";

					cout << "Please enter your campaign file name to save to (or overwrite): ";
					cin >> fileName;

					editedCamp.toFileStart(fileName);
					editedCamp.toFileInt1(fileName);
					editedCamp.toFileInt2(fileName);
					editedCamp.toFileEnd(fileName);
				}//!campaign size 4 end

				restart = false;
				cin >> ending;
			}//!decision 4 ends
		}//!restart ends


	}

	if (start == '1') {

		Dice dice;
		Observer* diceO = new DiceObserver(); // attach dice observer
		dice.Attach(diceO);

		Observer * bullyO = new CharacterObserver();
		Observer * nimbleO = new CharacterObserver();
		Observer * tankO = new CharacterObserver();
		Observer* playerO = new CharacterObserver();

		Character *bully = new Character('b');
		Character *nimble = new Character('n');
		Character *tank = new Character('t');
		Character* player = new Character('d');

		bully->Attach(bullyO);
		nimble->Attach(nimbleO);
		tank->Attach(tankO);
		player->Attach(playerO);

		cout << "Bully stats: \n";
		bully->notify();
		cout << "Nimble stats: \n";
		nimble->notify();
		cout << "Tank stats: \n";
		tank->notify();

		cout << "Would you like to reroll your stats?";
		cin >> yesOrNo;

		while (yesOrNo != 'Y' && yesOrNo != 'y' && yesOrNo != 'N' && yesOrNo != 'n')
		{
			cout << "Would you like to reroll your stats?";
			cin >> yesOrNo;
		}
		while (yesOrNo == 'Y' || yesOrNo == 'y')
		{
			Observer * bullyO = new CharacterObserver();
			Observer * nimbleO = new CharacterObserver();
			Observer * tankO = new CharacterObserver();
			Observer* playerO = new CharacterObserver();

			Character *bully = new Character('b');
			Character *nimble = new Character('n');
			Character *tank = new Character('t');
			Character* player = new Character('d');

			bully->Attach(bullyO);
			nimble->Attach(nimbleO);
			tank->Attach(tankO);
			player->Attach(playerO);

			cout << "Bully stats: \n";
			bully->notify();
			cout << "Nimble stats: \n";
			nimble->notify();
			cout << "Tank stats: \n";
			tank->notify();
			cout << "Would you like to reroll your stats?";
			cin >> yesOrNo;
		}



		char freeMove;

		system("CLS");

		cout << "----------WELCOME TO DUNGEONS & DRAGONS----------" << endl << endl << endl;

		cout << "------------This game will be logged-------------" << endl << endl;
		//!string fileChoice;
		int num;

		cout << "Please enter the name of an existing campaign file (including .txt): ";

		cin >> fileName;

		Map myMap;
		Observer* mapO = new MapObserver(); //!attach map observer
		myMap.Attach(mapO);

		myMap.message = "Campaign started \n";
		myMap.notify();

		ifstream read(fileName);
		int number_of_lines = 0;
		string line;
		int numM = 0;
		string maps[4];
		int s = 0;

		while (getline(read, line)) {
			++number_of_lines;
			maps[numM] = line;
			numM++;
		}
		cout << "Number of maps: " << number_of_lines << endl;


		if (number_of_lines == 2) {

			ifstream input0(maps[0]);

			if (input0.is_open())
			{
				cout << "\nDisplaying start campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input0 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campStart.setFileName(maps[0]);
				campStart.transferMap(tempMap);

				input0.close();
			}


			ifstream input1(maps[1]);

			if (input1.is_open())
			{
				cout << "\nDisplaying ending campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input1 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campEnd.setFileName(maps[1]);
				campEnd.transferMap(tempMap);

				input1.close();
			}

			campEnd.transferMap(tempMap);
			Campaign myCampaign = Campaign(campStart, campEnd);

		}//!campaign size 2 end

		if (number_of_lines == 3) {

			ifstream input0(maps[0]);

			if (input0.is_open())
			{
				cout << "\nDisplaying start campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input0 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campStart.setFileName(maps[0]);
				campStart.transferMap(tempMap);

				input0.close();
			}

			ifstream input1(maps[1]);

			if (input1.is_open())
			{
				cout << "\nDisplaying intermediate campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input1 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campInt1.setFileName(maps[1]);
				campInt1.transferMap(tempMap);

				input1.close();
			}

			ifstream input2(maps[2]);

			if (input2.is_open())
			{
				cout << "\nDisplaying ending campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input2 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campEnd.setFileName(maps[2]);
				campEnd.transferMap(tempMap);

				input2.close();
			}


			Campaign myCampaign = Campaign(campStart, campInt1, campEnd);

		}//!campaign size 3 end

		if (number_of_lines == 4) {

			ifstream input0(maps[0]);

			if (input0.is_open())
			{
				cout << "\nDisplaying start campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input0 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campStart.setFileName(maps[0]);
				campStart.transferMap(tempMap);

				input0.close();
			}

			ifstream input1(maps[1]);

			if (input1.is_open())
			{
				cout << "\nDisplaying intermediate (1) campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input1 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campInt1.setFileName(maps[1]);
				campInt1.transferMap(tempMap);

				input1.close();
			}

			ifstream input2(maps[2]);

			if (input2.is_open())
			{
				cout << "\nDisplaying Intermediate(2) campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input2 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campInt2.setFileName(maps[2]);
				campInt2.transferMap(tempMap);

				input2.close();
			}


			ifstream input3(maps[3]);

			if (input3.is_open())
			{
				cout << "\nDisplaying Ending campaign map " << "\n\n";

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						input3 >> tempMap[i][j];
						cout << tempMap[i][j] << " ";
					}
					cout << "\n";
				}

				campEnd.setFileName(maps[3]);
				campEnd.transferMap(tempMap);

				input3.close();
			}


			Campaign myCampaign = Campaign(campStart, campInt1, campInt2, campEnd);

		}//!campaign size 4 end


		


		char pick;
		char choice;
		cout << endl;
		cout << "Noble sir, are thou a bully, a nimble or a tank?" << endl;
		cout << "Press 1 to view stats or 2 to choose a character" << endl;
		cin >> pick;
		cout << endl;
		while (pick != '2') {
			if (pick == '1') {
				cout << "Press B to see Bully stats" << endl;
				cout << "Press N to see Nimble Stats" << endl;
				cout << "Press T to see Tank Stats " << endl;
				cout << "Press E to exit stat page" << endl;
				cin >> choice;
				cout << endl;
				while (choice != 'E' && choice != 'e') {
					if (choice == 'B' || choice == 'b') {
						cout << "-------Bully Stats-------" << endl << endl;
						bully->message = "";
						bully->notify();
					}
					else if (choice == 'N' || choice == 'n') {
						cout << "-------Nimble Stats-------" << endl << endl;
						nimble->message = "";
						nimble->notify();
					}
					else if (choice == 'T' || choice == 't') {
						cout << "-------Tank Stats-------" << endl << endl;
						tank->message = "";
						tank->notify();
					}
					else
						cout << "-------No valid input-------" << endl << endl;
					cin >> choice;
					cout << endl;
				}
			}
			else
				cout << "-------No valid input-------" << endl << endl;
			cout << endl;
			cout << "Noble sir, are tho a bully, a nimble or a tank?" << endl;
			cout << "Press 1 to view stats or 2 to choose a character" << endl;
			cin >> pick;
			cout << endl;
		}
		char selection;
		cout << "Press B to become a Bully" << endl;
		cout << "Press N to become a Nimble" << endl;
		cout << "Press T to become a Tank" << endl;
		cout << "Press L to load a saved character" << endl;

		bool err = true;
		while (err) {
			cin >> selection;
			cout << endl;
			if (selection == 'B' || selection == 'b') {
				player = bully;
				player->message = "Player has chosen to be a Bully character\n";
				player->notify();
				cout << "-------Bully selected-------" << endl;
				err = false;
			}
			else if (selection == 'N' || selection == 'n') {
				player = nimble;
				player->message = "Player has chosen to be a Nimble character\n";
				player->notify();
				cout << "-------Nimble selected-------" << endl;
				err = false;
			}
			else if (selection == 'T' || selection == 't') {
				player = tank;
				player->message = "Player has chosen to be a Tank character\n";
				player->notify();
				cout << "-------Tank selected-------" << endl;
				err = false;
			}
			else if (selection == 'L' || selection == 'l') {
				string file;
				cout << "Please select character file you would like to load from (include .txt extension)" << endl;
				cin >> file;
				Character *load = new Character(file);
				Observer* loadO = new CharacterObserver();
				load->Attach(loadO);
				player = load;

				player->message = "Player has chosen to load\n";
				player->notify();

				system("CLS");
				cout << "-------Load selected-------" << endl;
				err = false;
			}
			else
				cout << "-------No valid input-------" << endl;
		}

		myMap.message = "First map has started \n";
		myMap.notify();

		Observer* mapOS = new MapObserver(); //!attach map observer
		campStart.Attach(mapOS);

		campStart.findStart();
		campStart.copyArray();
		campStart.printTemp();
		campStart.setMapLevel(1);
		cout << endl;

		bool aggroFound = false;
		bool passiveFound = false;

		player->getLevel();
		cout << player->getLevel();

		NPC *npc1 = new NPC(4 + player->getLevel(), 3, 30, 10, 10, 10, true);
		NPC *npc2 = new NPC(4 + player->getLevel(), 3, 30, 10, 10, 10, false);

		aggroFound = campStart.aggroNPC(*npc1);
		passiveFound = campStart.passiveNPC(*npc2);

		bool keepGoing = true;
		while (keepGoing) {

			//! seed the random number generator
			srand(static_cast<unsigned int> (time(0)));

			//! hold input string from user
			string input;
			int diceTotal = 0;

			while (true) {

				cout
					<< endl << "Enter the number of rolls 'x' , size of dice 'y' plus 'z' in the following format: xdy+z"
					<< endl << endl;
				cout << "Dice roll: ";
				cin >> input;
				cout << endl;

				//! Initialize the roll method
				diceTotal = dice.roll(input);
				if (diceTotal > 0)
					break;

			};

			cout << endl;
			cout << "-------Player Movement Phase-------" << endl;
			campStart.message = "Player movement Phase\n";
			campStart.notify();
			char move;

			while (diceTotal >= 1) {
				campStart.printTemp();
				cout << "Moves left: " << diceTotal << endl;
				cout << "\nWhere do you want to move WASD keys " << endl;
				cout << "Your move: ";
				cin >> move;
				cout << endl;


				//!player movement phase
				keepGoing = !campStart.movePlayer(move, *player);
				campStart.message;
				campStart.notify();

				if (keepGoing)
				{

					//!Combat and NPC action check
					if (npc1->getAlive())
						campStart.playerCombat(*player, *npc1);
					if (npc2->getAlive())
						campStart.playerCombat(*player, *npc2);


					diceTotal--;
				}
				else {
					diceTotal = 0;
				}

			}//!dice roll loop

			if (keepGoing)
			{

				cout << endl;
				cout << "-------NPC Movement Phase-------" << endl;
				campStart.message = "NPC movement Phase\n";
				campStart.notify();
				//!NPC movement phase
				if (npc1->getAlive()) {
					if (npc1->getAggro()) {
						campStart.moveAggro(*npc1);
					}
					else {
						campStart.movePassive(*npc1);
					}
				}
				if (npc2->getAlive()) {
					if (npc2->getAggro()) {
						campStart.moveAggro(*npc2);
					}
					else {
						campStart.movePassive(*npc2);
					}
				}
				campStart.printTemp();

				//!NPC action phase
				cout << endl;
				cout << "-------NPC Action Phase-------" << endl;
				campStart.message = "NPC Action Phase\n";
				campStart.notify();
				if (npc1->getAlive()) {
					if (npc1->getAggro()) {
						campStart.aggroAction(*player, *npc1);
					}
					else {
						campStart.passiveAction(*player, *npc1);
					}
				}
				if (npc2->getAlive()) {
					if (npc2->getAggro()) {
						campStart.aggroAction(*player, *npc2);
					}
					else {
						campStart.passiveAction(*player, *npc2);
					}
				}

				//!Free action
				cout << endl;
				cout << "-------Player Free Action Phase-------" << endl << endl;
				campStart.message = "Player Free action Phase\n";
				campStart.notify();
				cout << "Would you like to use a (F)ree action or (M)ove one extra step or do (N)othing" << endl;
				cin >> freeMove;
				cout << endl;

				if (freeMove == 'f' || freeMove == 'F') {
				cout << "Implementation of free moves in project (toggle display, loot, etc.)" << endl << endl;
				
				bool free = true;
				
		
				while (free) {
					cout << "What would you like to do?" << endl;
					cout << "Press 1 to check current stats" << endl;
					cout << "Press 2 to equip" << endl;
					cout << "Press 3 to unequip" << endl;
					cout << "Press 4 to switch off game log" << endl;
					cout << "Press 5 to switch on game log" << endl;
					cout << "Press 6 to save character" << endl;
					cout << "Press 9 to exit" << endl;
					char actionChoice;
					cin >> actionChoice;

					cout << endl;

					switch (actionChoice) {

						//!Toggle display
					case '1':
						cout << "Current stats:" << endl;
						cout << "==============" << endl;
						player->message = "";
						player->notify();
						break;
						//!Unequip items or equip items
					case '2':

						cout << "Equip item" << endl;
						cout << "===========" << endl;

						cout << "Press 1 to equip items from bag" << endl;
						char c1;
						cin >> c1;
						if (c1 == '1') {

							player->printBag();
							cout << "===========================" << endl;
							cout << "What do you want to add?" << endl;

							string itemName;
							cin >> itemName;

							Item request= player->getBagItem(itemName);
							player->equip(&request);
						}
						break;
					case '3':
						cout << "Unequip item" << endl;
						cout << "============" << endl;
						cout << "Press 1 view equiped and 2 to unequip" << endl;
						char unEq;
						cin >> unEq;
						if (unEq == '1') {
							player->printEquip();

						}

						if (unEq == '2') {
							cout << "===========================" << endl;
							cout << "What do you want to unequip?" << endl;
							string itemName2;
							cin >> itemName2;
							Item request = player->getEquipItem(itemName2);
							player->unequip(request);
						}
						break;
					case '4':

						if (selection == 'B' || selection == 'b') {
							bullyO->turnOffLog = true;
							diceO->turnOffLog = true;
						}
						else if (selection == 'N' || selection == 'n') {
							nimbleO->turnOffLog = true;
							diceO->turnOffLog = true;

						}
						else if (selection == 'T' || selection == 't') {
							tankO->turnOffLog = true;
							diceO->turnOffLog = true;
						}
						break;

					case '5':
						if (selection == 'B' || selection == 'b') {
							bullyO->turnOffLog = false;
							diceO->turnOffLog = false;
						}
						else if (selection == 'N' || selection == 'n') {
							nimbleO->turnOffLog = false;
							diceO->turnOffLog = false;
						}
						else if (selection == 'T' || selection == 't') {
							tankO->turnOffLog = false;
							diceO->turnOffLog = false;
						}
						break;
					

					case '6':
						player->save();
						break;

					case '9':
						free = false;
						break;

					default:
						cout << "Invalid input" << endl;
						free = false;
						break;

					}
				}
			}

				else if (freeMove == 'm' || freeMove == 'M') {
					campStart.printTemp();
					cout << "\nWhere do you want to move WASD keys " << endl;
					cout << "Your move: ";
					cin >> move;
					cout << endl;
					keepGoing = !campStart.movePlayer(move, *player);
					campStart.message;
					campStart.notify();
					if (keepGoing)
						campStart.printTemp();
				}
			}
		}//!keepgoing loop end of map1

		player->levelUp();

		myMap.message = "First map has ended \n";
		myMap.notify();

		myMap.message = "Second map has started \n";
		myMap.notify();

		Observer* mapO1 = new MapObserver(); //!attach map observer
		campInt1.Attach(mapO1);

		campInt1.findStart();
		campInt1.copyArray();
		campInt1.printTemp();
		campInt1.setMapLevel(2);
		cout << endl;

		

		NPC *npc3 = new NPC(4+player->getLevel(), 3+1, 30+10, 10, 10, 10, true);
		NPC *npc4 = new NPC(4+player->getLevel(), 3+1, 30+10, 10, 10, 10, false);

		aggroFound = campInt1.aggroNPC(*npc3);
		passiveFound = campInt1.passiveNPC(*npc4);

		keepGoing = true;
		while (keepGoing) {

			//!seed the random number generator
			srand(static_cast<unsigned int> (time(0)));

			//!hold input string from user
			string input;
			int diceTotal = 0;

			while (true) {

				cout
					<< endl << "Enter the number of rolls 'x' , size of dice 'y' plus 'z' in the following format: xdy+z"
					<< endl << endl;
				cout << "Dice roll: ";
				cin >> input;
				cout << endl;

				//!Initialize the roll method
				diceTotal = dice.roll(input);
				if (diceTotal > 0)
					break;

			};

			cout << endl;
			cout << "-------Player Movement Phase-------" << endl;
			campInt1.message = "Player movement Phase\n";
			campInt1.notify();
			char move;

			while (diceTotal >= 1) {
				campInt1.printTemp();
				cout << "Moves left: " << diceTotal << endl;
				cout << "\nWhere do you want to move WASD keys " << endl;
				cout << "Your move: ";
				cin >> move;
				cout << endl;


				//!player movement phase
				keepGoing = !campInt1.movePlayer(move, *player);
				campInt1.message;
				campInt1.notify();

				if (keepGoing)
				{

					//!Combat and NPC action check
					if (npc3->getAlive())
						campInt1.playerCombat(*player, *npc3);
					if (npc4->getAlive())
						campInt1.playerCombat(*player, *npc4);


					diceTotal--;
				}
				else {
					diceTotal = 0;
				}

			}//!dice roll loop

			if (keepGoing)
			{

				cout << endl;
				cout << "-------NPC Movement Phase-------" << endl;
				campInt1.message = "NPC movement Phase\n";
				campInt1.notify();

				//!NPC movement phase
				if (npc3->getAlive()) {
					if (npc3->getAggro()) {
						campInt1.moveAggro(*npc3);
					}
					else {
						campInt1.movePassive(*npc3);
					}
				}
				if (npc4->getAlive()) {
					if (npc4->getAggro()) {
						campInt1.moveAggro(*npc4);
					}
					else {
						campInt1.movePassive(*npc4);
					}
				}
				campInt1.printTemp();

				//!NPC action phase
				cout << endl;
				cout << "-------NPC Action Phase-------" << endl;
				campInt1.message = "NPC Action Phase\n";
				campInt1.notify();
				if (npc3->getAlive()) {
					if (npc3->getAggro()) {
						campInt1.aggroAction(*player, *npc3);
					}
					else {
						campInt1.passiveAction(*player, *npc3);
					}
				}
				if (npc4->getAlive()) {
					if (npc4->getAggro()) {
						campInt1.aggroAction(*player, *npc4);
					}
					else {
						campInt1.passiveAction(*player, *npc4);
					}
				}

				//!Free action
				cout << endl;
				cout << "-------Player Free Action Phase-------" << endl << endl;
				campInt1.message = "Player Free action Phase\n";
				campInt1.notify();
				cout << "Would you like to use a (F)ree action or (M)ove one extra step or do (N)othing" << endl;
				cin >> freeMove;
				cout << endl;

				if (freeMove == 'f' || freeMove == 'F') {
					cout << "Implementation of free moves in project (toggle display, loot, etc.)" << endl << endl;

					bool free = true;

			
					while (free) {
						cout << "What would you like to do?" << endl;
						cout << "Press 1 to check current stats" << endl;
						cout << "Press 2 to equip" << endl;
						cout << "Press 3 to unequip" << endl;
						cout << "Press 4 to switch off game log" << endl;
						cout << "Press 5 to switch on game log" << endl;
						cout << "Press 6 to save character" << endl;
						cout << "Press 9 to exit" << endl;
						int actionChoice;
						cin >> actionChoice;
						cout << endl;

						switch (actionChoice) {

							//!Toggle display
						case 1:
							cout << "Current stats:" << endl;
							cout << "==============" << endl;
							player->message = "";
							player->notify();
							break;
							//!Unequip items or equip items
						case 2:

							cout << "Equip item" << endl;
							cout << "===========" << endl;

							cout << "Press 1 to equip items from bag" << endl;
							int c1;
							cin >> c1;
							if (c1 == 1) {

								player->printBag();
								cout << "===========================" << endl;
								cout << "What do you want to add?" << endl;

								string poop2;
								cin >> poop2;

								Item request = player->getBagItem(poop2);
								player->equip(&request);
							}
							break;
						case 3:
							cout << "Unequip item" << endl;
							cout << "============" << endl;
							cout << "Press 1 view equiped and 2 to unequip" << endl;
							int unEq;
							cin >> unEq;
							if (unEq == 1) {
								player->printEquip();

							}

							if (unEq == 2) {
								cout << "===========================" << endl;
								cout << "What do you want to unequip?" << endl;
								string poop2;
								cin >> poop2;
								Item request = player->getEquipItem(poop2);
								player->unequip(request);
							}
							break;
						case 4:

							if (selection == 'B' || selection == 'b') {
								bullyO->turnOffLog = true;
								diceO->turnOffLog = true;
							}
							else if (selection == 'N' || selection == 'n') {
								nimbleO->turnOffLog = true;
								diceO->turnOffLog = true;

							}
							else if (selection == 'T' || selection == 't') {
								tankO->turnOffLog = true;
								diceO->turnOffLog = true;
							}
							break;

						case 5:
							if (selection == 'B' || selection == 'b') {
								bullyO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							else if (selection == 'N' || selection == 'n') {
								nimbleO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							else if (selection == 'T' || selection == 't') {
								tankO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							break;


						case 6:
							player->save();
							break;

						case 9:
							free = false;
							break;

						default:
							cout << "Invalid" << endl;

						}
					}
				}

				else if (freeMove == 'm' || freeMove == 'M') {
					campInt1.printTemp();
					cout << "\nWhere do you want to move WASD keys " << endl;
					cout << "Your move: ";
					cin >> move;
					cout << endl;
					keepGoing = !campInt1.movePlayer(move, *player);
					campInt1.message;
					campInt1.notify();

					if (keepGoing)
						campInt1.printTemp();
				}
			}
		}//!keepgoing loop end of map 2

		player->levelUp();

		myMap.message = "Second map has ended \n";
		myMap.notify();

		myMap.message = "Third map has started \n";
		myMap.notify();

		Observer* mapO2 = new MapObserver(); //!attach map observer
		campInt2.Attach(mapO2);

		campInt2.findStart();
		campInt2.copyArray();
		campInt2.printTemp();
		campInt2.setMapLevel(3);
		cout << endl;

		

		NPC *npc5 = new NPC(4 + player->getLevel(), 3 + 2, 30 + 20, 10, 10, 10, true);
		NPC *npc6 = new NPC(4 + player->getLevel(), 3 + 2, 30 + 20, 10, 10, 10, false);

		aggroFound = campInt2.aggroNPC(*npc5);
		passiveFound = campInt2.passiveNPC(*npc6);
	

		keepGoing = true;
		while (keepGoing) {

			//!seed the random number generator
			srand(static_cast<unsigned int> (time(0)));

			//!hold input string from user
			string input;
			int diceTotal = 0;

			while (true) {

				cout
					<< endl << "Enter the number of rolls 'x' , size of dice 'y' plus 'z' in the following format: xdy+z"
					<< endl << endl;
				cout << "Dice roll: ";
				cin >> input;
				cout << endl;

				//!Initialize the roll method
				diceTotal = dice.roll(input);
				if (diceTotal > 0)
					break;

			};

			cout << endl;
			cout << "-------Player Movement Phase-------" << endl;
			campInt2.message = "Player movement Phase\n";
			campInt2.notify();
			char move;

			while (diceTotal >= 1) {
				campInt2.printTemp();
				cout << "Moves left: " << diceTotal << endl;
				cout << "\nWhere do you want to move WASD keys " << endl;
				cout << "Your move: ";
				cin >> move;
				cout << endl;


				//!player movement phase
				keepGoing = !campInt2.movePlayer(move, *player);
				campInt2.message;
				campInt2.notify();

				if (keepGoing)
				{

					//!Combat and NPC action check
					if (npc5->getAlive())
						campInt2.playerCombat(*player, *npc5);
					if (npc6->getAlive())
						campInt2.playerCombat(*player, *npc6);


					diceTotal--;
				}
				else {
					diceTotal = 0;
				}

			}//!dice roll loop

			if (keepGoing)
			{

				cout << endl;
				cout << "-------NPC Movement Phase-------" << endl;
				campInt2.message = "NPC movement Phase\n";
				campInt2.notify();

				//!NPC movement phase
				if (npc5->getAlive()) {
					if (npc5->getAggro()) {
						campInt2.moveAggro(*npc5);
					}
					else {
						campInt2.movePassive(*npc5);
					}
				}
				if (npc6->getAlive()) {
					if (npc6->getAggro()) {
						campInt2.moveAggro(*npc6);
					}
					else {
						campInt2.movePassive(*npc6);
					}
				}
				campInt2.printTemp();

				//!NPC action phase
				cout << endl;
				cout << "-------NPC Action Phase-------" << endl;
				campInt2.message = "NPC action Phase\n";
				campInt2.notify();
				if (npc5->getAlive()) {
					if (npc5->getAggro()) {
						campInt2.aggroAction(*player, *npc5);
					}
					else {
						campInt2.passiveAction(*player, *npc5);
					}
				}
				if (npc6->getAlive()) {
					if (npc6->getAggro()) {
						campInt2.aggroAction(*player, *npc6);
					}
					else {
						campInt2.passiveAction(*player, *npc6);
					}
				}

				//!Free action
				cout << endl;
				cout << "-------Player Free Action Phase-------" << endl << endl;
				campInt2.message = "Player Free action Phase\n";
				campInt2.notify();
				cout << "Would you like to use a (F)ree action or (M)ove one extra step or do (N)othing" << endl;
				cin >> freeMove;
				cout << endl;

				if (freeMove == 'f' || freeMove == 'F') {
					cout << "Implementation of free moves in project (toggle display, loot, etc.)" << endl << endl;

					bool free = true;

					while (free) {
						cout << "What would you like to do?" << endl;
						cout << "Press 1 to check current stats" << endl;
						cout << "Press 2 to equip" << endl;
						cout << "Press 3 to unequip" << endl;
						cout << "Press 4 to switch off game log" << endl;
						cout << "Press 5 to switch on game log" << endl;
						cout << "Press 6 to save character" << endl;
						cout << "Press 9 to exit" << endl;
						int actionChoice;
						cin >> actionChoice;
						cout << endl;

						switch (actionChoice) {

							//!Toggle display
						case 1:
							cout << "Current stats:" << endl;
							cout << "==============" << endl;
							player->message = "";
							player->notify();
							break;
							//!Unequip items or equip items
						case 2:

							cout << "Equip item" << endl;
							cout << "===========" << endl;

							cout << "Press 1 to equip items from bag" << endl;
							int c1;
							cin >> c1;
							if (c1 == 1) {

								player->printBag();
								cout << "===========================" << endl;
								cout << "What do you want to add?" << endl;

								string poop2;
								cin >> poop2;

								Item request = player->getBagItem(poop2);
								player->equip(&request);
							}
							break;
						case 3:
							cout << "Unequip item" << endl;
							cout << "============" << endl;
							cout << "Press 1 view equiped and 2 to unequip" << endl;
							int unEq;
							cin >> unEq;
							if (unEq == 1) {
								player->printEquip();

							}

							if (unEq == 2) {
								cout << "===========================" << endl;
								cout << "What do you want to unequip?" << endl;
								string poop2;
								cin >> poop2;
								Item request = player->getEquipItem(poop2);
								player->unequip(request);
							}
							break;
						case 4:

							if (selection == 'B' || selection == 'b') {
								bullyO->turnOffLog = true;
								diceO->turnOffLog = true;
							}
							else if (selection == 'N' || selection == 'n') {
								nimbleO->turnOffLog = true;
								diceO->turnOffLog = true;

							}
							else if (selection == 'T' || selection == 't') {
								tankO->turnOffLog = true;
								diceO->turnOffLog = true;
							}
							break;

						case 5:
							if (selection == 'B' || selection == 'b') {
								bullyO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							else if (selection == 'N' || selection == 'n') {
								nimbleO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							else if (selection == 'T' || selection == 't') {
								tankO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							break;


						case 6:
							player->save();
							break;

						case 9:
							free = false;
							break;

						default:
							cout << "Invalid" << endl;

						}
					}
				}

				else if (freeMove == 'm' || freeMove == 'M') {
					campInt2.printTemp();
					cout << "\nWhere do you want to move WASD keys " << endl;
					cout << "Your move: ";
					cin >> move;
					cout << endl;
					keepGoing = !campInt2.movePlayer(move, *player);
					campInt2.message;
					campInt2.notify();
					if (keepGoing)
						campInt2.printTemp();
				}
			}
		}//!keepgoing loop end of map 3

		player->levelUp();

		myMap.message = "Third map has ended \n";
		myMap.notify();

		myMap.message = "Fourth map has started \n";
		myMap.notify();

		Observer* mapOE = new MapObserver(); //!attach map observer
		campEnd.Attach(mapOE);

		campEnd.findStart();
		campEnd.copyArray();
		campEnd.printTemp();
		campEnd.setMapLevel(4);
		cout << endl;


		NPC *npc7 = new NPC(4 + player->getLevel(), 3 + 3, 30 + 25, 10, 10, 10, true);
		NPC *npc8 = new NPC(4 + player->getLevel(), 3 + 3, 30 + 25, 10, 10, 10, false);

		aggroFound = campEnd.aggroNPC(*npc7);
		passiveFound = campEnd.passiveNPC(*npc8);

		keepGoing = true;
		while (keepGoing) {

			//! seed the random number generator
			srand(static_cast<unsigned int> (time(0)));

			//! hold input string from user
			string input;
			int diceTotal = 0;

			while (true) {

				cout
					<< endl << "Enter the number of rolls 'x' , size of dice 'y' plus 'z' in the following format: xdy+z"
					<< endl << endl;
				cout << "Dice roll: ";
				cin >> input;
				cout << endl;

				//! Initialize the roll method
				diceTotal = dice.roll(input);
				if (diceTotal > 0)
					break;

			};

			cout << endl;
			cout << "-------Player Movement Phase-------" << endl;
			campEnd.message = "Player movement Phase\n";
			campEnd.notify();
			char move;

			while (diceTotal >= 1) {
				campEnd.printTemp();
				cout << "Moves left: " << diceTotal << endl;
				cout << "\nWhere do you want to move WASD keys " << endl;
				cout << "Your move: ";
				cin >> move;
				cout << endl;


				//!player movement phase
				keepGoing = !campEnd.movePlayer(move, *player);
				campEnd.message;
				campEnd.notify();

				if (keepGoing)
				{

					//!Combat and NPC action check
					if (npc7->getAlive())
						campEnd.playerCombat(*player, *npc7);
					if (npc8->getAlive())
						campEnd.playerCombat(*player, *npc8);


					diceTotal--;
				}
				else {
					diceTotal = 0;
				}

			}//!dice roll loop

			if (keepGoing)
			{

				cout << endl;
				cout << "-------NPC Movement Phase-------" << endl;
				campEnd.message = "NPC movement Phase\n";
				campEnd.notify();

				//!NPC movement phase
				if (npc7->getAlive()) {
					if (npc7->getAggro()) {
						campEnd.moveAggro(*npc7);
					}
					else {
						campEnd.movePassive(*npc7);
					}
				}
				if (npc8->getAlive()) {
					if (npc8->getAggro()) {
						campEnd.moveAggro(*npc8);
					}
					else {
						campEnd.movePassive(*npc8);
					}
				}
				campEnd.printTemp();

				//!NPC action phase
				cout << endl;
				cout << "-------NPC Action Phase-------" << endl;
				campEnd.message = "NPC Action Phase\n";
				campEnd.notify();
				if (npc7->getAlive()) {
					if (npc7->getAggro()) {
						campEnd.aggroAction(*player, *npc7);
					}
					else {
						campEnd.passiveAction(*player, *npc7);
					}
				}
				if (npc8->getAlive()) {
					if (npc8->getAggro()) {
						campEnd.aggroAction(*player, *npc8);
					}
					else {
						campEnd.passiveAction(*player, *npc8);
					}
				}

				//!Free action
				cout << endl;
				cout << "-------Player Free Action Phase-------" << endl << endl;
				campEnd.message = "Player Free Action Phase\n";
				campEnd.notify();
				cout << "Would you like to use a (F)ree action or (M)ove one extra step or do (N)othing" << endl;
				cin >> freeMove;
				cout << endl;

				if (freeMove == 'f' || freeMove == 'F') {
					cout << "Implementation of free moves in project (toggle display, loot, etc.)" << endl << endl;

					bool free = true;

					
					while (free) {
						cout << "What would you like to do?" << endl;
						cout << "Press 1 to check current stats" << endl;
						cout << "Press 2 to equip" << endl;
						cout << "Press 3 to unequip" << endl;
						cout << "Press 4 to switch off game log" << endl;
						cout << "Press 5 to switch on game log" << endl;
						cout << "Press 6 to save character" << endl;
						cout << "Press 9 to exit" << endl;
						int actionChoice;
						cin >> actionChoice;
						cout << endl;

						switch (actionChoice) {

							//!Toggle display
						case 1:
							cout << "Current stats:" << endl;
							cout << "==============" << endl;
							player->message = "";
							player->notify();
							break;
							//!Unequip items or equip items
						case 2:

							cout << "Equip item" << endl;
							cout << "===========" << endl;

							cout << "Press 1 to equip items from bag" << endl;
							int c1;
							cin >> c1;
							if (c1 == 1) {

								player->printBag();
								cout << "===========================" << endl;
								cout << "What do you want to add?" << endl;

								string poop2;
								cin >> poop2;

								Item request = player->getBagItem(poop2);
								player->equip(&request);
							}
							break;
						case 3:
							cout << "Unequip item" << endl;
							cout << "============" << endl;
							cout << "Press 1 view equiped and 2 to unequip" << endl;
							int unEq;
							cin >> unEq;
							if (unEq == 1) {
								player->printEquip();

							}

							if (unEq == 2) {
								cout << "===========================" << endl;
								cout << "What do you want to unequip?" << endl;
								string poop2;
								cin >> poop2;
								Item request = player->getEquipItem(poop2);
								player->unequip(request);
							}
							break;
						case 4:

							if (selection == 'B' || selection == 'b') {
								bullyO->turnOffLog = true;
								diceO->turnOffLog = true;
							}
							else if (selection == 'N' || selection == 'n') {
								nimbleO->turnOffLog = true;
								diceO->turnOffLog = true;

							}
							else if (selection == 'T' || selection == 't') {
								tankO->turnOffLog = true;
								diceO->turnOffLog = true;
							}
							break;

						case 5:
							if (selection == 'B' || selection == 'b') {
								bullyO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							else if (selection == 'N' || selection == 'n') {
								nimbleO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							else if (selection == 'T' || selection == 't') {
								tankO->turnOffLog = false;
								diceO->turnOffLog = false;
							}
							break;


						case 6:
							player->save();
							break;

						case 9:
							free = false;
							break;

						default:
							cout << "Invalid" << endl;

						}
					}
				}

				else if (freeMove == 'm' || freeMove == 'M') {
					campEnd.printTemp();
					cout << "\nWhere do you want to move WASD keys " << endl;
					cout << "Your move: ";
					cin >> move;
					cout << endl;
					keepGoing = !campEnd.movePlayer(move, *player);
					campEnd.message;
					campEnd.notify();
					if (keepGoing)
						campEnd.printTemp();
				}
			}
		}//!keepgoing loop

		player->levelUp();

		myMap.message = "Fourth map has ended \n";
		myMap.notify();

		cout << "\n--------------------\n";
		myMap.message = "Game has ended \n";
		myMap.notify();
		cout << "\nYou have beaten the campaign! Press any key to end the game: ";
		cin >> yesOrNo;

	}//!end of start game
}
